namespace Xs;

class Index extends Server
{
    private static adds;

    private buf = "";
    private bufSize = 0;
    private rebuild = false;

    public function addServer(string conn) -> <Server>
    {
        var srv;

        let srv = new Server(conn, this->xs);
        let self::adds[] = srv;

        return srv;
    }

    public function execCommand(cmd, resArg = Xs::CMD_NONE, resCmd = Xs::CMD_OK) -> <Command>
    {
        var res, srv;

        let res = parent::execCommand(cmd, resArg, resCmd);

        if typeof self::adds == "array" {
            for srv in self::adds {
                srv->execCommand(cmd, resArg, resCmd);
            }
        }

        return res;
    }

    public function clean()
    {
        this->execCommand(Xs::CMD_INDEX_CLEAN_DB, Xs::CMD_OK_DB_CLEAN);
        return this;
    }

    public function add(<Document> doc)
    {
        return this->update(doc, true);
    }

    public function update(<Document> doc, boolean add = false)
    {
        var fid, key, cmd, cmds, field, value;

        if doc->beforeSubmit(this) === false {
            return this;
        }

        let fid = this->xs->getFieldId();
        let key = doc->f(fid);

        if key === null || key === "" {
            throw new Exception("Missing value of primary key (FIELD:" . fid . ")");
        }

        let cmd = new Command(Xs::CMD_INDEX_REQUEST, Xs::CMD_INDEX_REQUEST_ADD);

        if ! add {
            cmd->arg1 = Xs::CMD_INDEX_REQUEST_UPDATE;
            cmd->arg2 = fid->vno;
            cmd->buf = key;
        }

        let cmds = [];
        let cmds[] = cmd;

        // FieldMeta field
        for field in this->xs->getAllFields() {
            long varg;


            let value = doc->f(field);
            if value !== null {
                let varg = field->isNumeric() ? Xs::CMD_VALUE_FLAG_NUMERIC : 0;
                let value = field->val(value);
                if (!field->hasCustomTokenizer()) {
                    wdf = field->weight | (field->withPos() ? Xs::CMD_INDEX_FLAG_WITHPOS : 0);
                    if (field->hasIndexMixed()) {
                        cmds[] = new XSCommand(Xs::CMD_DOC_INDEX, wdf, XSFieldScheme::MIXED_VNO, value);
                    }
                    if (field->hasIndexSelf()) {
                        wdf |= field->isNumeric() ? 0 : Xs::CMD_INDEX_FLAG_SAVEVALUE;
                        cmds[] = new XSCommand(Xs::CMD_DOC_INDEX, wdf, field->vno, value);
                    }
                    if (!field->hasIndexSelf() || field->isNumeric()) {
                        cmds[] = new XSCommand(Xs::CMD_DOC_VALUE, varg, field->vno, value);
                    }
                } else {
                    if (field->hasIndex()) {
                        terms = field->getCustomTokenizer()->getTokens(value, doc);
                        if (field->hasIndexSelf()) {
                            wdf = field->isBoolIndex() ? 1 : (field->weight | Xs::CMD_INDEX_FLAG_CHECKSTEM);
                            foreach (terms as term) {
                                if (strlen(term) > 200) {
                                    continue;
                                }
                                term = strtolower(term);
                                cmds[] = new XSCommand(Xs::CMD_DOC_TERM, wdf, field->vno, term);
                            }
                        }
                        if (field->hasIndexMixed()) {
                            mtext = implode(" ", terms);
                            cmds[] = new XSCommand(Xs::CMD_DOC_INDEX, field->weight, XSFieldScheme::MIXED_VNO, mtext);
                        }
                    }
                    cmds[] = new XSCommand(Xs::CMD_DOC_VALUE, varg, field->vno, value);
                }
            }
            if ((terms = doc->getAddTerms(field)) !== null) {
                wdf1 = field->isBoolIndex() ? 0 : Xs::CMD_INDEX_FLAG_CHECKSTEM;
                foreach (terms as term => wdf) {
                    term = strtolower(term);
                    if (strlen(term) > 200) {
                        continue;
                    }
                    wdf2 = field->isBoolIndex() ? 1 : wdf * field->weight;
                    while (wdf2 > XSFieldMeta::MAX_WDF) {
                        cmds[] = new XSCommand(Xs::CMD_DOC_TERM, wdf1 | XSFieldMeta::MAX_WDF, field->vno, term);
                        wdf2 -= XSFieldMeta::MAX_WDF;
                    }
                    cmds[] = new XSCommand(Xs::CMD_DOC_TERM, wdf1 | wdf2, field->vno, term);
                }
            }
            if ((text = doc->getAddIndex(field)) !== null) {
                if (!field->hasCustomTokenizer()) {
                    wdf = field->weight | (field->withPos() ? Xs::CMD_INDEX_FLAG_WITHPOS : 0);
                    cmds[] = new XSCommand(Xs::CMD_DOC_INDEX, wdf, field->vno, text);
                } else {
                    wdf = field->isBoolIndex() ? 1 : (field->weight | Xs::CMD_INDEX_FLAG_CHECKSTEM);
                    terms = field->getCustomTokenizer()->getTokens(text, doc);
                    foreach (terms as term) {
                        if (strlen(term) > 200) {
                            continue;
                        }
                        term = strtolower(term);
                        cmds[] = new XSCommand(Xs::CMD_DOC_TERM, wdf, field->vno, term);
                    }
                }
            }
        }
        cmds[] = new XSCommand(Xs::CMD_INDEX_SUBMIT);
        if (this->_bufSize > 0) {
            this->appendBuffer(implode("", cmds));
        } else {
            for (i = 0; i < count(cmds) - 1; i++) {
                this->execCommand(cmds[i]);
            }
            this->execCommand(cmds[i], Xs::CMD_OK_RQST_FINISHED);
        }
        doc->afterSubmit(this);
        return this;
    }
    public function del(term, field = null)
    {
        field = field === null ? this->xs->getFieldId() : this->xs->getField(field);
        cmds = array();
        terms = is_array(term) ? array_unique(term) : array(term);
        terms = XS::convert(terms, "UTF-8", this->xs->getDefaultCharset());
        foreach (terms as term) {
            cmds[] = new XSCommand(Xs::CMD_INDEX_REMOVE, 0, field->vno, strtolower(term));
        }
        if (this->_bufSize > 0) {
            this->appendBuffer(implode("", cmds));
        } elseif (count(cmds) == 1) {
            this->execCommand(cmds[0], Xs::CMD_OK_RQST_FINISHED);
        } else {
            cmd = array("cmd" => Xs::CMD_INDEX_EXDATA, "buf" => implode("", cmds));
            this->execCommand(cmd, Xs::CMD_OK_RQST_FINISHED);
        }
        return this;
    }
    public function addExdata(data, check_file = true)
    {
        if (strlen(data) < 255 && check_file
                && file_exists(data) && (data = file_get_contents(data)) === false) {
            throw new Exception("Failed to read exdata from file");
        }
        first = ord(substr(data, 0, 1));
        if (first != Xs::CMD_IMPORT_HEADER
                && first != Xs::CMD_INDEX_REQUEST && first != Xs::CMD_INDEX_SYNONYMS
                && first != Xs::CMD_INDEX_REMOVE && first != Xs::CMD_INDEX_EXDATA) {
            throw new Exception("Invalid start command of exdata (CMD:" . first . ")");
        }
        cmd = array("cmd" => Xs::CMD_INDEX_EXDATA, "buf" => data);
        this->execCommand(cmd, Xs::CMD_OK_RQST_FINISHED);
        return this;
    }
    public function addSynonym(raw, synonym)
    {
        raw = strval(raw);
        synonym = strval(synonym);
        if (raw !== "" && synonym !== "") {
            cmd = new XSCommand(Xs::CMD_INDEX_SYNONYMS, Xs::CMD_INDEX_SYNONYMS_ADD, 0, raw, synonym);
            if (this->_bufSize > 0) {
                this->appendBuffer(strval(cmd));
            } else {
                this->execCommand(cmd, Xs::CMD_OK_RQST_FINISHED);
            }
        }
        return this;
    }
    public function delSynonym(raw, synonym = null)
    {
        raw = strval(raw);
        synonym = synonym === null ? "" : strval(synonym);
        if (raw !== "") {
            cmd = new XSCommand(Xs::CMD_INDEX_SYNONYMS, Xs::CMD_INDEX_SYNONYMS_DEL, 0, raw, synonym);
            if (this->_bufSize > 0) {
                this->appendBuffer(strval(cmd));
            } else {
                this->execCommand(cmd, Xs::CMD_OK_RQST_FINISHED);
            }
        }
        return this;
    }
    public function setScwsMulti(level)
    {
        level = intval(level);
        if (level >= 0 && level < 16) {
            cmd = array("cmd" => Xs::CMD_SEARCH_SCWS_SET, "arg1" => Xs::CMD_SCWS_SET_MULTI, "arg2" => level);
            this->execCommand(cmd);
        }
        return this;
    }
    public function getScwsMulti()
    {
        cmd = array("cmd" => Xs::CMD_SEARCH_SCWS_GET, "arg1" => Xs::CMD_SCWS_GET_MULTI);
        res = this->execCommand(cmd, Xs::CMD_OK_INFO);
        return intval(res->buf);
    }
    public function openBuffer(size = 4)
    {
        if (this->_buf !== "") {
            this->addExdata(this->_buf, false);
        }
        this->_bufSize = intval(size) << 20;
        this->_buf = "";
        return this;
    }
    public function closeBuffer()
    {
        return this->openBuffer(0);
    }
    public function beginRebuild()
    {
        this->execCommand(array("cmd" => Xs::CMD_INDEX_REBUILD, "arg1" => 0), Xs::CMD_OK_DB_REBUILD);
        this->_rebuild = true;
        return this;
    }
    public function endRebuild()
    {
        if (this->_rebuild === true) {
            this->_rebuild = false;
            this->execCommand(array("cmd" => Xs::CMD_INDEX_REBUILD, "arg1" => 1), Xs::CMD_OK_DB_REBUILD);
        }
        return this;
    }
    public function stopRebuild()
    {
        try {
            this->execCommand(array("cmd" => Xs::CMD_INDEX_REBUILD, "arg1" => 2), Xs::CMD_OK_DB_REBUILD);
            this->_rebuild = false;
        } catch (Exception e) {
            if (e->getCode() !== Xs::CMD_ERR_WRONGPLACE) {
                throw e;
            }
        }
        return this;
    }
    public function setDb(name)
    {
        this->execCommand(array("cmd" => Xs::CMD_INDEX_SET_DB, "buf" => name), Xs::CMD_OK_DB_CHANGED);
        return this;
    }
    public function flushLogging()
    {
        try {
            this->execCommand(Xs::CMD_FLUSH_LOGGING, Xs::CMD_OK_LOG_FLUSHED);
        } catch (Exception e) {
            if (e->getCode() === Xs::CMD_ERR_BUSY) {
                return false;
            }
            throw e;
        }
        return true;
    }
    public function flushIndex()
    {
        try {
            this->execCommand(Xs::CMD_INDEX_COMMIT, Xs::CMD_OK_DB_COMMITED);
        } catch (Exception e) {
            if (e->getCode() === Xs::CMD_ERR_BUSY || e->getCode() === Xs::CMD_ERR_RUNNING) {
                return false;
            }
            throw e;
        }
        return true;
    }
    public function getCustomDict()
    {
        res = this->execCommand(Xs::CMD_INDEX_USER_DICT, Xs::CMD_OK_INFO);
        return res->buf;
    }
    public function setCustomDict(content)
    {
        cmd = array("cmd" => Xs::CMD_INDEX_USER_DICT, "arg1" => 1, "buf" => content);
        this->execCommand(cmd, Xs::CMD_OK_DICT_SAVED);
    }
    public function close(ioerr = false)
    {
        this->closeBuffer();
        parent::close(ioerr);
    }
    private function appendBuffer(buf)
    {
        this->_buf .= buf;
        if (strlen(this->_buf) >= this->_bufSize) {
            this->addExdata(this->_buf, false);
            this->_buf = "";
        }
    }
    public function __destruct()
    {
        if (this->_rebuild === true) {
            try {
                this->endRebuild();
            } catch (Exception e) {
            }
        }
        foreach (self::adds as srv) {
            srv->close();
        }
        self::adds = array();
        parent::__destruct();
    }
}
