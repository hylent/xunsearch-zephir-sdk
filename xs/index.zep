namespace Xs;

class Index extends Server
{
    private static adds;

    private buf = "";
    private bufSize = 0;
    private rebuild = false;

    public function __destruct() -> void
    {
        var srv;

        if this->rebuild {
            try {
                this->endRebuild();
            } catch Exception {
            }
        }
        if typeof self::adds == "array" {
            for srv in self::adds {
                srv->close();
            }
        }
        let self::adds = [];
        parent::__destruct();
    }

    public function addServer(string conn) -> <Server>
    {
        var srv;

        let srv = new Server(conn, this->xs);
        let self::adds[] = srv;

        return srv;
    }

    public function execCommand(var cmd, long resArg = Command::CMD_NONE, long resCmd = Command::CMD_OK) -> <Command>
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
        this->execCommand(Command::CMD_INDEX_CLEAN_DB, Command::CMD_OK_DB_CLEAN);
        return this;
    }

    public function add(<Document> doc)
    {
        return this->update(doc, true);
    }

    public function update(<Document> doc, boolean add = false)
    {
        var fid, key, cmd, cmds, field, value;
        long varg, wdf, wdf1, wdf2;
        var terms, term, wdfVar, text, lastCmd;

        if doc->beforeSubmit(this) === false {
            return this;
        }

        let fid = this->xs->getFieldId();
        let key = doc->f(fid);
        if key === null || key === "" {
            throw new Exception("Missing value of primary key (FIELD:" . fid . ")");
        }

        let cmd = new Command(Command::CMD_INDEX_REQUEST, Command::CMD_INDEX_REQUEST_ADD);
        if ! add {
            let cmd->arg1 = Command::CMD_INDEX_REQUEST_UPDATE;
            let cmd->arg2 = fid->vno;
            let cmd->buf = key;
        }
        let cmds = [];
        let cmds[] = cmd;

        // FieldMeta field
        for field in this->xs->getAllFields() {
            let value = doc->f(field);
            if value !== null {
                if field->isNumeric() {
                    let varg = Command::CMD_VALUE_FLAG_NUMERIC;
                } else {
                    let varg = 0;
                }
                let value = field->val(value);
                if ! field->hasCustomTokenizer() {
                    if field->withPos() {
                        let wdf = field->weight | Command::CMD_INDEX_FLAG_WITHPOS;
                    } else {
                        let wdf = (long) field->weight;
                    }
                    if field->hasIndexMixed() {
                        let cmds[] = new Command(Command::CMD_DOC_INDEX, wdf, FieldScheme::MIXED_VNO, value);
                    }
                    if field->hasIndexSelf() {
                        if ! field->isNumeric() {
                            let wdf = wdf | Command::CMD_INDEX_FLAG_SAVEVALUE;
                        }
                        let cmds[] = new Command(Command::CMD_DOC_INDEX, wdf, field->vno, value);
                    }
                    if ! field->hasIndexSelf() || field->isNumeric() {
                        let cmds[] = new Command(Command::CMD_DOC_VALUE, varg, field->vno, value);
                    }
                } else {
                    if field->hasIndex() {
                        let terms = field->getCustomTokenizer()->getTokens(value, doc);
                        if field->hasIndexSelf() {
                            if field->isBoolIndex() {
                                let wdf = 1;
                            } else {
                                let wdf = field->weight | Command::CMD_INDEX_FLAG_CHECKSTEM;
                            }
                            for term in terms {
                                if strlen(term) > 200 {
                                    continue;
                                }
                                let term = strtolower(term);
                                let cmds[] = new Command(Command::CMD_DOC_TERM, wdf, field->vno, term);
                            }
                        }
                        if field->hasIndexMixed() {
                            let cmds[] = new Command(Command::CMD_DOC_INDEX, field->weight, FieldScheme::MIXED_VNO,
                                implode(" ", terms));
                        }
                    }
                    let cmds[] = new Command(Command::CMD_DOC_VALUE, varg, field->vno, value);
                }
            }
            let terms = doc->getAddTerms(field);
            if terms !== null {
                if field->isBoolIndex() {
                    let wdf1 = 0;
                } else {
                    let wdf1 = Command::CMD_INDEX_FLAG_CHECKSTEM;
                }
                for term, wdfVar in terms {
                    let term = strtolower(term);
                    if strlen(term) > 200 {
                        continue;
                    }
                    if field->isBoolIndex() {
                        let wdf2 = 1;
                    } else {
                        let wdf2 = wdfVar * field->weight;
                    }
                    while wdf2 > FieldMeta::MAX_WDF {
                        let cmds[] = new Command(Command::CMD_DOC_TERM, wdf1 | FieldMeta::MAX_WDF, field->vno, term);
                        let wdf2 -= FieldMeta::MAX_WDF;
                    }
                    let cmds[] = new Command(Command::CMD_DOC_TERM, wdf1 | wdf2, field->vno, term);
                }
            }
            let text = doc->getAddIndex(field);
            if text !== null {
                if ! field->hasCustomTokenizer() {
                    if field->withPos() {
                        let wdf = field->weight | Command::CMD_INDEX_FLAG_WITHPOS;
                    } else {
                        let wdf = (long) field->weight;
                    }
                    let cmds[] = new Command(Command::CMD_DOC_INDEX, wdf, field->vno, text);
                } else {
                    if field->isBoolIndex() {
                        let wdf = 1;
                    } else {
                        let wdf = field->weight | Command::CMD_INDEX_FLAG_CHECKSTEM;
                    }
                    let terms = field->getCustomTokenizer()->getTokens(text, doc);
                    for term in terms {
                        if strlen(term) > 200 {
                            continue;
                        }
                        let term = strtolower(term);
                        let cmds[] = new Command(Command::CMD_DOC_TERM, wdf, field->vno, term);
                    }
                }
            }
        }
        let cmds[] = new Command(Command::CMD_INDEX_SUBMIT);
        if this->bufSize > 0 {
            this->appendBuffer(implode("", cmds));
        } else {
            let lastCmd = array_pop(cmds);
            for cmd in cmds {
                this->execCommand(cmd);
            }
            this->execCommand(lastCmd, Command::CMD_OK_RQST_FINISHED);
        }
        doc->afterSubmit(this);
        return this;
    }

    public function del(var term, var field = null)
    {
        var cmds = [], terms;

        if field === null {
            let field = this->xs->getFieldId();
        } else {
            let field = this->xs->getField(field);
        }
        if typeof term == "array" {
            let terms = array_unique(term);
        } else {
            let terms = [term];
        }
        let terms = Xs::convert(terms, "UTF-8", this->xs->getDefaultCharset());
        for term in terms {
            let cmds[] = new Command(Command::CMD_INDEX_REMOVE, 0, field->vno, strtolower(term));
        }
        if this->bufSize > 0 {
            this->appendBuffer(implode("", cmds));
        } else {
            if count(cmds) == 1 {
                this->execCommand(cmds[0], Command::CMD_OK_RQST_FINISHED);
            } else {
                this->execCommand(["cmd": Command::CMD_INDEX_EXDATA, "buf": implode("", cmds)], Command::CMD_OK_RQST_FINISHED);
            }
        }
        return this;
    }

    public function addExdata(string data, boolean checkFile = true)
    {
        var dataVar;
        long first;

        if strlen(data) < 255 && checkFile && file_exists(data) {
            let dataVar = file_get_contents(data);
            if unlikely dataVar === false {
                throw new Exception("Failed to read exdata from file");
            }
            let data = (string) dataVar;
        }
        let first = (long) ord(substr(data, 0, 1));
        switch first {
            case Command::CMD_IMPORT_HEADER:
            case Command::CMD_INDEX_REQUEST:
            case Command::CMD_INDEX_SYNONYMS:
            case Command::CMD_INDEX_REMOVE:
            case Command::CMD_INDEX_EXDATA:
                break;
            default:
                throw new Exception("Invalid start command of exdata (CMD:" . first . ")");
        }
        this->execCommand(["cmd": Command::CMD_INDEX_EXDATA, "buf": data], Command::CMD_OK_RQST_FINISHED);
        return this;
    }

    public function addSynonym(string raw, string synonym)
    {
        var cmd;

        if raw !== "" && synonym !== "" {
            let cmd = new Command(Command::CMD_INDEX_SYNONYMS, Command::CMD_INDEX_SYNONYMS_ADD, 0, raw, synonym);
            if this->bufSize > 0 {
                this->appendBuffer((string) cmd);
            } else {
                this->execCommand(cmd, Command::CMD_OK_RQST_FINISHED);
            }
        }
        return this;
    }

    public function delSynonym(string raw, string synonym = "")
    {
        var cmd;

        if raw !== "" {
            let cmd = new Command(Command::CMD_INDEX_SYNONYMS, Command::CMD_INDEX_SYNONYMS_DEL, 0, raw, synonym);
            if this->bufSize > 0 {
                this->appendBuffer((string) cmd);
            } else {
                this->execCommand(cmd, Command::CMD_OK_RQST_FINISHED);
            }
        }
        return this;
    }

    public function setScwsMulti(long level)
    {
        if level >= 0 && level < 16 {
            this->execCommand(["cmd": Command::CMD_SEARCH_SCWS_SET, "arg1": Command::CMD_SCWS_SET_MULTI, "arg2": level]);
        }
        return this;
    }

    public function getScwsMulti() -> long
    {
        var res;

        let res = this->execCommand(["cmd": Command::CMD_SEARCH_SCWS_GET, "arg1": Command::CMD_SCWS_GET_MULTI], Command::CMD_OK_INFO);
        return (long) res->buf;
    }

    public function openBuffer(long size = 4)
    {
        if this->buf !== "" {
            this->addExdata(this->buf, false);
        }
        let this->bufSize = size << 20;
        let this->buf = "";
        return this;
    }

    public function closeBuffer()
    {
        return this->openBuffer(0);
    }

    public function beginRebuild()
    {
        this->execCommand(["cmd": Command::CMD_INDEX_REBUILD, "arg1": 0], Command::CMD_OK_DB_REBUILD);
        let this->rebuild = true;
        return this;
    }

    public function endRebuild()
    {
        if this->rebuild {
            let this->rebuild = false;
            this->execCommand(["cmd": Command::CMD_INDEX_REBUILD, "arg1": 1], Command::CMD_OK_DB_REBUILD);
        }
        return this;
    }

    public function stopRebuild()
    {
        var ex;

        try {
            this->execCommand(["cmd": Command::CMD_INDEX_REBUILD, "arg1": 2], Command::CMD_OK_DB_REBUILD);
            let this->rebuild = false;
        } catch Exception, ex {
            if ex->getCode() !== Command::CMD_ERR_WRONGPLACE {
                throw ex;
            }
        }
        return this;
    }

    public function setDb(string name)
    {
        this->execCommand(["cmd": Command::CMD_INDEX_SET_DB, "buf": name], Command::CMD_OK_DB_CHANGED);
        return this;
    }

    public function flushLogging() -> boolean
    {
        var ex;

        try {
            this->execCommand(Command::CMD_FLUSH_LOGGING, Command::CMD_OK_LOG_FLUSHED);
        } catch Exception, ex {
            if ex->getCode() === Command::CMD_ERR_BUSY {
                return false;
            }
            throw ex;
        }
        return true;
    }

    public function flushIndex() -> boolean
    {
        var ex;

        try {
            this->execCommand(Command::CMD_INDEX_COMMIT, Command::CMD_OK_DB_COMMITED);
        } catch Exception, ex {
            switch ex->getCode() {
                case Command::CMD_ERR_BUSY:
                case Command::CMD_ERR_RUNNING:
                    return false;
            }
            throw ex;
        }
        return true;
    }
    public function getCustomDict() -> string
    {
        var res;

        let res = this->execCommand(Command::CMD_INDEX_USER_DICT, Command::CMD_OK_INFO);
        return res->buf;
    }

    public function setCustomDict(string content) -> void
    {
        this->execCommand(["cmd": Command::CMD_INDEX_USER_DICT, "arg1": 1, "buf": content], Command::CMD_OK_DICT_SAVED);
    }

    public function close(ioerr = false) -> void
    {
        this->closeBuffer();
        parent::close(ioerr);
    }

    private function appendBuffer(string buf) -> void
    {
        let this->buf .= buf;
        if strlen(this->buf) >= this->bufSize {
            this->addExdata(this->buf, false);
            let this->buf = "";
        }
    }

}
