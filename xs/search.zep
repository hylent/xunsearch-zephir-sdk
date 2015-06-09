namespace Xs;

class Search extends Server
{
    const PAGE_SIZE = 10;
    const LOG_DB    = "log_db";

    private defaultOp = Xs::CMD_QUERY_OP_AND;
    private prefix;
    private fieldSet;
    private resetScheme = false;
    private query;
    private terms;
    private count;
    private lastCount;
    private highlight;
    private curDb;
    private curDbs;
    private lastDb;
    private lastDbs;
    private facets;
    private limit = 0;
    private offset = 0;
    private charset = "UTF-8";

    public function open(string conn) -> void
    {
        parent::open(conn);
        let this->prefix = [];
        let this->fieldSet = false;
        let this->lastCount = false;
    }

    public function setCharset(string charset)
    {
        let charset = charset->upper();
        if charset == "UTF8" {
            let this->charset = "UTF-8";
        } else {
            let this->charset = charset;
        }
        return this;
    }

    public function setFuzzy(boolean value = true)
    {
        let this->defaultOp = value ? Xs::CMD_QUERY_OP_OR : Xs::CMD_QUERY_OP_AND;
        return this;
    }

    public function setCutOff(long percent, long weight = 0)
    {
        var cmd;

        let percent = (long) max(0, min(100, percent));
        let weight = (long) max(0, (long) (weight * 10) & 255);
        let cmd = new Command(Xs::CMD_SEARCH_SET_CUTOFF, percent, weight);
        this->execCommand(cmd);
        return this;
    }

    public function setRequireMatchedTerm(boolean value = true)
    {
        long arg1, arg2;
        var cmd;

        let arg1 = Xs::CMD_SEARCH_MISC_MATCHED_TERM;
        let arg2 = value ? 1 : 0;
        let cmd = new XSCommand(Xs::CMD_SEARCH_SET_MISC, , arg2);
        this->execCommand(cmd);
        return this;
    }

    public function setAutoSynonyms(boolean value = true)
    {
        long flag;
        var cmd;

        let flag = Xs::CMD_PARSE_FLAG_BOOLEAN | Xs::CMD_PARSE_FLAG_PHRASE | Xs::CMD_PARSE_FLAG_LOVEHATE;
        if value {
            let flag |= Xs::CMD_PARSE_FLAG_AUTO_MULTIWORD_SYNONYMS;
        }
        let cmd = ["cmd": Xs::CMD_QUERY_PARSEFLAG, "arg": flag];
        this->execCommand(cmd);
        return this;
    }

    public function setSynonymScale(double value)
    {
        long arg1, arg2;
        var cmd;

        let arg1 = Xs::CMD_SEARCH_MISC_SYN_SCALE;
        let arg2 = (long) max(0, (long) (value * 100) & 255);
        let cmd = new Command(Xs::CMD_SEARCH_SET_MISC, arg1, arg2);
        this->execCommand(cmd);
        return this;
    }

    public function getAllSynonyms(long limit = 0, long offset = 0, boolean stemmed = false) -> array
    {
        string page;
        var cmd, res, ret, line, value, key;

        if limit > 0 {
            let page = pack("II", offset, limit);
        } else {
            let page = "";
        }
        let cmd = ["cmd": Xs::CMD_SEARCH_GET_SYNONYMS, "buf1": page];
        let cmd["arg1"] = stemmed ? 1 : 0;
        let res = this->execCommand(cmd, Xs::CMD_OK_RESULT_SYNONYMS);
        let ret = [];
        if ! empty res->buf {
            for line in explode("\n", res->buf) {
                let value = explode("\t", line);
                let key = array_shift(value);
                let ret[key] = value;
            }
        }
        return ret;
    }

    public function getSynonyms(string term)
    {
        var cmd, res;

        if term->length() < 1 {
            return false;
        }
        let cmd = ["cmd": Xs::CMD_SEARCH_GET_SYNONYMS, "arg1": 2, "buf": term];
        let res = this->execCommand(cmd, Xs::CMD_OK_RESULT_SYNONYMS);
        if res->buf === "" {
            return [];
        }
        return explode("\n", res->buf);
    }

    public function getQuery(var query = null) -> string
    {
        var cmd, res;
        string regex;

        if query === null {
            let query = "";
        } else {
            let query = this->preQueryString(query);
        }

        let cmd = new Command(Xs::CMD_QUERY_GET_STRING, 0, this->defaultOp, query);
        let res = this->execCommand(cmd, Xs::CMD_OK_QUERY_STRING);
        if strpos(res->buf, "VALUE_RANGE") !== false {
            let regex = "/(VALUE_RANGE) (\d+) (\S+) (.+?)(?=\))/";
            let res->buf = preg_replace_callback(regex, [this, "formatValueRange"], res->buf);
        }
        if strpos(res->buf, "VALUE_GE") !== false || strpos(res->buf, "VALUE_LE") !== false {
            let regex = "/(VALUE_[GL]E) (\d+) (.+?)(?=\))/";
            let res->buf = preg_replace_callback(regex, [this, "formatValueRange"], res->buf);
        }
        return Xs::convert(res->buf, this->charset, "UTF-8");
    }

    public function setQuery(var query)
    {
        this->clearQuery();
        if query !== null {
            let this->query = query;
            this->addQueryString(query);
        }
        return this;
    }

    public function setMultiSort(var fields, boolean reversed = false, boolean relevanceFirst = false)
    {
        string buf;
        var key, value, cmd;
        long vno, type;
        boolean asc;

        if typeof fields != "array" {
            return this->setSort(fields, ! reversed, relevanceFirst);
        }
        let buf = "";
        for key, value in fields {
            if typeof value == "bool" {
                let vno = this->xs->getField(key, true)->vno;
                let asc = value;
            } else {
                let vno = this->xs->getField(value, true)->vno;
                let asc = false;
            }
            if vno != XSFieldScheme::MIXED_VNO {
                let buf .= chr(vno) . chr(asc ? 1 : 0);
            }
        }
        if buf !== "" {
            let type = Xs::CMD_SORT_TYPE_MULTI;
            if relevanceFirst {
                let type |= Xs::CMD_SORT_FLAG_RELEVANCE;
            }
            if ! reversed {
                let type |= Xs::CMD_SORT_FLAG_ASCENDING;
            }
            let cmd = new Command(Xs::CMD_SEARCH_SET_SORT, type, 0, buf);
            this->execCommand(cmd);
        }
        return this;
    }

    public function setSort(var field, boolean asc = false, boolean relevanceFirst = false)
    {
        var cmd;
        long type, vno;

        if typeof field == "array" {
            return this->setMultiSort(field, asc, relevanceFirst);
        }
        if field === null {
            let cmd = new Command(Xs::CMD_SEARCH_SET_SORT, Xs::CMD_SORT_TYPE_RELEVANCE);
        } else {
            let type = Xs::CMD_SORT_TYPE_VALUE;
            if relevanceFirst {
                let type |= Xs::CMD_SORT_FLAG_RELEVANCE;
            }
            if asc {
                let type |= Xs::CMD_SORT_FLAG_ASCENDING;
            }
            let vno = this->xs->getField(field, true)->vno;
            let cmd = new XSCommand(Xs::CMD_SEARCH_SET_SORT, type, vno);
        }
        this->execCommand(cmd);
        return this;
    }

    public function setDocOrder(boolean asc = false)
    {
        long type;
        var cmd;

        if asc {
            let type = Xs::CMD_SORT_TYPE_DOCID | Xs::CMD_SORT_FLAG_ASCENDING;
        } else {
            let type = Xs::CMD_SORT_TYPE_DOCID;
        }
        let cmd = new Command(Xs::CMD_SEARCH_SET_SORT, type);
        this->execCommand(cmd);
        return this;
    }

    public function setCollapse(var field, long num = 1)
    {
        long vno, max;
        var cmd;

        if field === null {
            let vno = FieldScheme::MIXED_VNO;
        } else {
            let vno = this->xs->getField(field, true)->vno;
        }
        let max = (long) min(255, num);
        let cmd = new Command(Xs::CMD_SEARCH_SET_COLLAPSE, max, vno);
        this->execCommand(cmd);
        return this;
    }

    public function addRange(var field, var from, var to)
    {
        long vno;

        if from === "" || from === false {
            let from = null;
        }
        if to === "" || to === false {
            let to = null;
        }
        if from !== null || to !== null {
            if strlen(from) > 255 || strlen(to) > 255 {
                throw new Exception("Value of range is too long");
            }
            let vno = this->xs->getField(field)->vno;
            let from = Xs::convert(from, "UTF-8", this->charset);
            let to = Xs::convert(to, "UTF-8", this->charset);
            if from === null {
                let cmd = new Command(Xs::CMD_QUERY_VALCMP, Xs::CMD_QUERY_OP_FILTER, vno, to, chr(Xs::CMD_VALCMP_LE));
            } else {
                if to === null {
                    let cmd = new Command(Xs::CMD_QUERY_VALCMP, Xs::CMD_QUERY_OP_FILTER, vno, from,
                        chr(Xs::CMD_VALCMP_GE));
                } else {
                    let cmd = new Command(Xs::CMD_QUERY_RANGE, Xs::CMD_QUERY_OP_FILTER, vno, from, to);
                }
            }
            this->execCommand(cmd);
        }
        return this;
    }

    public function addWeight(var field, string term, long weight = 1)
    {
        return this->addQueryTerm(field, term, Xs::CMD_QUERY_OP_AND_MAYBE, weight);
    }

    public function setFacets(var field, boolean exact = false)
    {
        string buf = "";
        var fields, ff;

        if typeof field == "array" {
            let fields = field;
        } else {
            let fields = [field];
        }

        for field in fields {
            let ff = this->xs->getField(field);
            if ff->type !== FieldMeta::TYPE_STRING {
                throw new Exception("Field `name` cannot be used for facets search, can only be string type");
            }
            let buf .= chr(ff->vno);
        }
        let cmd = ["cmd": Xs::CMD_SEARCH_SET_FACETS, "buf": buf];
        let cmd["arg1"] = exact ? 1 : 0;
        this->execCommand(cmd);
        return this;
    }

    public function getFacets(var field = null) -> array
    {
        var f;

        if field === null {
            return this->facets;
        }
        if fetch f, this->facets[field] {
            return f;
        }
        return [];
    }

    public function setScwsMulti(long level)
    {
        var cmd;

        if level >= 0 && level < 16 {
            let cmd = ["cmd": Xs::CMD_SEARCH_SCWS_SET, "arg1": Xs::CMD_SCWS_SET_MULTI, "arg2": level];
            this->execCommand(cmd);
        }
        return this;
    }

    public function setLimit(long limit, long offset = 0)
    {
        let this->limit = limit;
        let this->offset = offset;
        return this;
    }

    public function setDb(string name)
    {
        this->execCommand(["cmd": Xs::CMD_SEARCH_SET_DB, "buf": name]);
        this->lastDb = this->curDb;
        this->lastDbs = this->curDbs;
        this->curDb = name;
        this->curDbs = [];
        return this;
    }

    public function addDb(string name)
    {
        this->execCommand(["cmd": Xs::CMD_SEARCH_ADD_DB, "buf": name]);
        let this->curDbs[] = name;
        return this;
    }

    public function markResetScheme() -> void
    {
        let this->resetScheme = true;
    }

    public function terms(var query = null, boolean convert = true) -> array
    {
        var ret, cmd, res, tmps, tmp;

        if query === null {
            let query = "";
        } else {
            let query = this->preQueryString(query);
        }
        if (query === "" && this->terms !== null) {
            let ret = this->terms;
        } else {
            let cmd = new Command(Xs::CMD_QUERY_GET_TERMS, 0, this->defaultOp, query);
            let res = this->execCommand(cmd, Xs::CMD_OK_QUERY_TERMS);
            let ret = [];
            let tmps = explode(" ", res->buf);
            for tmp in tmps {
                if tmp === "" || strpos(tmp, ":") !== false {
                    continue;
                }
                let ret[] = tmp;
            }
            if query === "" {
                this->terms = ret;
            }
        }
        if convert {
            return Xs::convert(ret, this->charset, "UTF-8")
        }
        return ret;
    }

    public function count(var query = null) -> long
    {
        var cmd, res, ret;

        if query === null {
            let query = "";
        } else {
            let query = this->preQueryString(query);
        }
        if query === "" && this->count !== null {
            return this->count;
        }
        let cmd = new Command(Xs::CMD_SEARCH_GET_TOTAL, 0, this->defaultOp, query);
        let res = this->execCommand(cmd, Xs::CMD_OK_SEARCH_TOTAL);
        let ret = unpack("Icount", res->buf);
        if query === "" {
            let this->count = ret["count"];
        }
        return ret["count"];
    }

    public function search(var query = null, boolean saveHighlight = true) -> array
    {
        string page, value;
        var cmd, res, tmp, ret, vnoes, name, doc = null;
        long off;

        if this->curDb !== self::LOG_DB && saveHighlight {
            let this->highlight = query;
        }
        if query === null {
            let query = "";
        } else {
            let query = this->preQueryString(query);
        }
        let page = pack("II", this->offset, this->limit > 0 ? this->limit : self::PAGE_SIZE);
        let cmd = new Command(Xs::CMD_SEARCH_GET_RESULT, 0, this->defaultOp, query, page);
        let res = this->execCommand(cmd, Xs::CMD_OK_RESULT_BEGIN);
        let tmp = unpack("Icount", res->buf);
        let this->lastCount = tmp["count"];
        let this->facets = [];
        let ret = [];
        let vnoes = this->xs->getScheme()->getVnoMap();
        loop {
            let res = this->getRespond();
            switch res->cmd {
                case Xs::CMD_SEARCH_RESULT_FACETS:
                    let off = 0;
                    while off + 6 < strlen(res->buf) {
                        let tmp = unpack("Cvno/Cvlen/Inum", substr(res->buf, off, 6));
                        if fetch name, vnoes[tmp["vno"]] {
                            let value = substr(res->buf, off + 6, tmp["vlen"]);
                            if ! isset this->facets[name] {
                                let this->facets[name] = [];
                            }
                            let this->facets[name][value] = tmp["num"];
                        }
                        let off += tmp["vlen"] + 6;
                    }
                    break;
                case Xs::CMD_SEARCH_RESULT_DOC:
                    let doc = new Document(res->buf, this->charset);
                    let ret[] = doc;
                    break;
                case Xs::CMD_SEARCH_RESULT_FIELD:
                    if doc {
                        if ! fetch name, vnoes[res->arg] {
                            let name = res->arg;
                        }
                        doc->setField(name, res->buf);
                    }
                    break;
                case Xs::CMD_SEARCH_RESULT_MATCHED:
                    if doc {
                        doc->setField("matched", explode(" ", res->buf), true);
                    }
                    break;
                case Xs::CMD_OK:
                    if res->arg == Xs::CMD_OK_RESULT_END {
                        break;
                    }
                default:
                    throw new Exception("Unexpected respond in search {CMD:" . res->cmd . ", ARG:" . res->arg . "}");
            }
        }
        if query === "" {
            let this->count = this->lastCount;
            if this->curDb !== self::LOG_DB {
                this->logQuery();
                if saveHighlight {
                    this->initHighlight();
                }
            }
        }
        let this->offset = 0;
        let this->limit = 0;
        return ret;
    }

    public function getLastCount() -> long
    {
        return this->lastCount;
    }

    public function getDbTotal() -> long
    {
        var cmd, res, tmp;

        let cmd = new Command(Xs::CMD_SEARCH_DB_TOTAL);
        let res = this->execCommand(cmd, Xs::CMD_OK_DB_TOTAL);
        let tmp = unpack("Itotal", res->buf);
        return tmp["total"];
    }

    public function getHotQuery(long limit = 6, string type = "total") -> array
    {
        var ret = [], result, doc, body, ex;
        long limit;

        let limit = (long) max(1, min(50, limit));
        this->xs->setScheme(FieldScheme::logger());
        try {
            this->setDb(self::LOG_DB)->setLimit(limit);
            if type !== "lastnum" && type !== "currnum" {
                let type = "total";
            }
            let result = this->search(type . ":1");
            // XSDocument doc
            for doc in result {
                let body = doc->body;
                let ret[body] = doc->f(type);
            }
            this->restoreDb();
        } catch Exception, ex {
            if ex->getCode() != Xs::CMD_ERR_XAPIAN {
                throw ex;
            }
        }
        this->xs->restoreScheme();
        return ret;
    }

    public function getRelatedQuery(var query = null, long limit = 6) -> array
    {
        var ret = [], result, doc, body, ex;
        long op;

        let limit = (long) max(1, min(20, limit));
        if query === null {
            let query = this->cleanFieldQuery(this->query);
        }
        if empty query || strpos(query, ":") !== false {
            return ret;
        }
        let op = this->defaultOp;
        this->xs->setScheme(FieldScheme::logger());
        try {
            let result = this->setDb(self::LOG_DB)->setFuzzy()->setLimit(limit + 1)->search(query);
            // XSDocument doc
            for doc in result {
                doc->setCharset(this->charset);
                let body = doc->body;
                if ! strcasecmp(body, query) {
                    continue;
                }
                let ret[] = body;
                if count(ret) == limit {
                    break;
                }
            }
        } catch Exception, ex {
            if ex->getCode() != Xs::CMD_ERR_XAPIAN {
                throw ex;
            }
        }
        this->restoreDb();
        this->xs->restoreScheme();
        let this->defaultOp = op;
        return ret;
    }

    public function getExpandedQuery(string query, long limit = 10) -> array
    {
        var ret = [];
        string buf;
        var cmd, res, ex;

        let limit = (long) max(1, min(20, limit));
        try {
            let buf = Xs::convert(query, "UTF-8", this->charset);
            let cmd = ["cmd": Xs::CMD_QUERY_GET_EXPANDED, "arg1": limit, "buf": buf];
            let res = this->execCommand(cmd, Xs::CMD_OK_RESULT_BEGIN);
            loop {
                let res = this->getRespond();
                if res->cmd == Xs::CMD_SEARCH_RESULT_FIELD {
                    let ret[] = Xs::convert(res->buf, this->charset, "UTF-8");
                    continue;
                }
                if res->cmd == Xs::CMD_OK && res->arg == Xs::CMD_OK_RESULT_END {
                    break;
                }
                throw new Exception("Unexpected respond in search {CMD:" . res->cmd . ", ARG:" . res->arg . "}");
            }
        } catch Exception, ex {
            if ex->getCode() != Xs::CMD_ERR_XAPIAN {
                throw ex;
            }
        }
        return ret;
    }

    public function getCorrectedQuery(var query = null) -> array
    {
        var ret = [];
        string buf;
        var cmd, res, ex;

        try {
            if query === null {
                if this->count > 0 && this->count > ceil(this->getDbTotal() * 0.001) {
                    return ret;
                }
                let query = this->cleanFieldQuery(this->query);
            }
            if empty query || strpos(query, ":") !== false {
                return ret;
            }
            let buf = Xs::convert(query, "UTF-8", this->charset);
            let cmd = ["cmd": Xs::CMD_QUERY_GET_CORRECTED, "buf": buf];
            let res = this->execCommand(cmd, Xs::CMD_OK_QUERY_CORRECTED);
            if res->buf !== "" {
                let ret = explode("\n", Xs::convert(res->buf, this->charset, "UTF-8"));
            }
        } catch Exception, ex {
            if ex->getCode() != Xs::CMD_ERR_XAPIAN {
                throw ex;
            }
        }
        return ret;
    }

    public function addSearchLog(string query, long wdf = 1) -> void
    {
        var cmd;

        let cmd = ["cmd": Xs::CMD_SEARCH_ADD_LOG, "buf": query)];
        if wdf > 1 {
            let cmd["buf1"] = pack("i", wdf);
        }
        this->execCommand(cmd, Xs::CMD_OK_LOGGED);
    }

    public function highlight(string value, boolean strtr = false)
    {
        var p;

        if empty value {
            return value;
        }
        if typeof this->highlight != "array" {
            this->initHighlight();
        }
        if fetch p, this->highlight["pattern"] {
            let value = preg_replace(p, this->highlight["replace"], value);
        }
        if fetch p, this->highlight["pairs"] {
            if strtr {
                let value = strtr(value, this->highlight["pairs"]);
            } else {
                let value = str_replace(array_keys(p), array_values(p), value);
            }
        }
        return value;
    }

    private function logQuery(var query = null) -> void
    {
        var terms, term, pos2;
        string log;
        long max, pos, pos1;

        if this->isRobotAgent() {
            return;
        }
        if query !== "" && query !== null {
            let terms = this->terms(query, false);
        } else {
            let query = this->query;
            if ! this->lastCount
                || (this->defaultOp == Xs::CMD_QUERY_OP_OR && strpos(query, " "))
                || strpos(query, " OR ")
                || strpos(query, " NOT ")
                || strpos(query, " XOR ") {
                return;
            }
            let terms = this->terms(null, false);
        }
        let log = "";
        let max = 0;
        let pos = 0;
        for term in terms {
            if pos > 3 && strlen(term) === 6 {
                let pos1 = pos - 3;
            } else {
                let pos1 = pos;
            }
            let pos2 = strpos(query, term, pos1);
            if pos2 === false {
                continue;
            }
            if pos2 === pos {
                let log .= term;
            } else {
                if pos2 < pos {
                    let log .= substr(term, 3);
                } else {
                    let max++;
                    if max > 3 || strlen(log) > 42 {
                        break;
                    }
                    let log .= " " . term;
                }
            }
            let pos = pos2 + strlen(term);
        }
        let log = (string) trim(log);
        if strlen(log) < 2 || (strlen(log) == 3 && ord(log[0]) > 0x80) {
            return;
        }
        this->addSearchLog(log);
    }

    private function clearQuery() -> void
    {
        var cmd;

        let cmd = new XSCommand(Xs::CMD_QUERY_INIT);
        if this->resetScheme === true {
            let cmd->arg1 = 1;
            let this->prefix = [];
            let this->fieldSet = false;
            let this->resetScheme = false;
        }
        this->execCommand(cmd);
        let this->terms = null;
        let this->count = null;
        let this->query = null;
    }

    public function addQueryString(var query, long addOp = Xs::CMD_QUERY_OP_AND, long scale = 1) -> string
    {
        string bscale;
        var cmd;

        let query = this->preQueryString(query);
        if scale > 0 && scale != 1 {
            let bscale = pack("n", (long) (scale * 100));
        } else {
            let bscale = "";
        }
        let cmd = new Command(Xs::CMD_QUERY_PARSE, addOp, this->defaultOp, query, bscale);
        this->execCommand(cmd);
        return query;
    }

    public function addQueryTerm(var field, string term, long addOp = Xs::CMD_QUERY_OP_AND, long scale = 1)
    {
        string bscale;
        long vno;
        var cmd;

        let term = Xs::convert(term->lower(), "UTF-8", this->charset);
        if scale > 0 && scale != 1 {
            let bscale = pack("n", (long) (scale * 100));
        } else {
            let bscale = "";
        }
        if field === null {
            let vno = FieldScheme::MIXED_VNO;
        } else {
            let vno = this->xs->getField(field, true)->vno;
        }
        cmd = new Command(Xs::CMD_QUERY_TERM, addOp, vno, term, bscale);
        this->execCommand(cmd);
        return this;
    }

    private function restoreDb() -> void
    {
        var db, dbs, name;

        let db = this->lastDb;
        let dbs = this->lastDbs;
        this->setDb(db);
        for name in dbs {
            this->addDb(name);
        }
    }

    private function preQueryString(string query) -> string
    {
        string newQuery, name, prefix, suffix, value;
        var parts, part, pos, field, terms, tokens, term;
        long i;

        let query = (string) trim(query);
        if this->resetScheme === true {
            this->clearQuery();
        }
        this->initSpecialField();
        let newQuery = "";
        let parts = preg_split("/[ \t\r\n]+/", query);
        for part in parts {
            if part === "" {
                continue;
            }
            if newQuery != "" {
                newQuery .= " ";
            }
            let pos = strpos(part, ":", 1);
            if pos !== false {
                let i = 0;
                while i < pos {
                    if strpos("+-~(", part[i]) === false {
                        break;
                    }
                    let i++;
                }
                let name = substr(part, i, pos - i);
                let field = this->xs->getField(name, false);
                if field !== false && field->vno != FieldScheme::MIXED_VNO {
                    this->regQueryPrefix(name);
                    if field->hasCustomTokenizer() {
                        let prefix = i > 0 ? substr(part, 0, i) : "";
                        let suffix = "";
                        let value = substr(part, pos + 1);
                        if substr(value, -1, 1) === ")" {
                            let suffix = ")";
                            let value = substr(value, 0, -1);
                        }
                        let terms = [];
                        let tokens = field->getCustomTokenizer()->getTokens(value);
                        for term in tokens {
                            let terms[] = strtolower(term);
                        }
                        let terms = array_unique(terms);
                        let newQuery .= prefix . name . ":" . implode(" " . name . ":", terms) . suffix;
                    } else {
                        if substr(part, pos + 1, 1) != "(" && preg_match("/[\x81-\xfe]/", part) {
                            let newQuery .= substr(part, 0, pos + 1) . "(" . substr(part, pos + 1) . ")";
                        } else {
                            let newQuery .= part;
                        }
                    }
                    continue;
                }
            }
            if strlen(part) > 1
                && (part[0] == "+" || part[0] == "-")
                && part[1] != "("
                && preg_match("/[\x81-\xfe]/", part) {
                let newQuery .= substr(part, 0, 1) . "(" . substr(part, 1) . ")";
                continue;
            }
            let newQuery .= part;
        }
        return Xs::convert(newQuery, "UTF-8", this->charset);
    }

    private function regQueryPrefix(string name) -> void
    {
        var field, cmd;
        long type;

        if ! isset this->prefix[name] {
            let field = this->xs->getField(name, false);
            if field->vno != FieldScheme::MIXED_VNO {
                let type = field->isBoolIndex() ? Xs::CMD_PREFIX_BOOLEAN : Xs::CMD_PREFIX_NORMAL;
                let cmd = new Command(Xs::CMD_QUERY_PREFIX, type, field->vno, name);
                this->execCommand(cmd);
                let this->prefix[name] = true;
            }
        }
    }

    private function initSpecialField() -> void
    {
        var field, cmd;
        long len;

        if this->fieldSet === true {
            return;
        }
        // FieldMeta field
        for field in this->xs->getAllFields() {
            if field->cutlen != 0 {
                let len = min(127, ceil(field->cutlen / 10));
                let cmd = new Command(Xs::CMD_SEARCH_SET_CUT, len, field->vno);
                this->execCommand(cmd);
            }
            if field->isNumeric() {
                let cmd = new Command(Xs::CMD_SEARCH_SET_NUMERIC, 0, field->vno);
                this->execCommand(cmd);
            }
        }
        let this->fieldSet = true;
    }

    private function cleanFieldQuery(string query) -> string
    {
        let query = strtr(query, [" AND ": " ", " OR ": " "]);
        if strpos(query, ":") !== false {
            return preg_replace_callback("/(^|\s)([0-9A-Za-z_\.-]+):([^\s]+)/", [this, "cleanFieldCallback"], query);
        }
        return query;
    }

    private function cleanFieldCallback(array match) -> string
    {
        var field;

        let field = this->xs->getField(match[2], false)
        if field === false {
            return match[0];
        }
        if field->isBoolIndex() {
            return "";
        }
        if substr(match[3], 0, 1) == "(" && substr(match[3], -1, 1) == ")" {
            let match[3] = substr(match[3], 1, -1);
        }
        return match[1] . match[3];
    }

    private function initHighlight() -> void
    {
        var terms = [], tmps, pairs, replace, pattern, term;
        long i, j, k;

        let tmps = this->terms(this->highlight, false);
        let i = 0;
        while i < count(tmps) {
            if strlen(tmps[i]) !== 6 || ord(substr(tmps[i], 0, 1)) < 0xc0 {
                let terms[] = Xs::convert(tmps[i], this->charset, "UTF-8");
                let i++;
                continue;
            }
            let j = i + 1;
            while j < count(tmps) {
                if strlen(tmps[j]) !== 6 || substr(tmps[j], 0, 3) !== substr(tmps[j - 1], 3, 3) {
                    break;
                }
                let j++;
            }
            let k = j - i;
            if k == 1 {
                let terms[] = Xs::convert(tmps[i], this->charset, "UTF-8");
            } else {
                let i = j - 1;
                while k {
                    let j--;
                    if (k & 1) {
                        let terms[] = Xs::convert(substr(tmps[j - 1], 0, 3) . tmps[j], this->charset, "UTF-8");
                    }
                    let terms[] = Xs::convert(tmps[j], this->charset, "UTF-8");
                    let k--;
                }
            }
            let i++;
        }
        let pairs = [];
        let replace = [];
        let pattern = [];
        for term in terms {
            if ! preg_match("/[a-zA-Z]/", term) {
                let pairs[term] = "<em>" . term . "</em>";
            } else {
                let pattern[] = "/" . strtr(term, ["+": "\\+", "/": "\\/"]) . "/i";
                let replace[] = "<em>0</em>";
            }
        }
        let this->highlight = [];
        if count(pairs) > 0 {
            let this->highlight["pairs"] = pairs;
        }
        if count(pattern) > 0 {
            let this->highlight["pattern"] = pattern;
            let this->highlight["replace"] = replace;
        }
    }

    private function formatValueRange(array match) -> string
    {
        var field;
        string val1, val2;

        let field = this->xs->getField((long) match[2], false);
        if field === false {
            return match[0];
        }
        let val1 = "~";
        let val2 = "~";
        if isset match[4] {
            let val2 = field->isNumeric() ? this->xapianUnserialise(match[4]) : match[4];
        }
        if match[1] === "VALUE_LE" {
            let val2 = field->isNumeric() ? this->xapianUnserialise(match[3]) : match[3];
        } else {
            let val1 = field->isNumeric() ? this->xapianUnserialise(match[3]) : match[3];
        }
        return field->name . ":[" . val1 . "," . val2 . "]";
    }

    private function numfromstr(string str, long index) -> long
    {
        return index < strlen(str) ? ord(str[index]) : 0;
    }

    private function xapianUnserialise(string value) -> double
    {
        long i, c, negative, exponentNegative, explen, exponent, word1, word2;
        double mantissa;

        if value === "\x80" {
            return 0.0;
        }
        if value === str_repeat("\xff", 9) {
            return INF;
        }
        if value === "" {
            return -INF;
        }
        let i = 0;
        let c = ord(value[0]) ^ ((c & 0xc0) >> 1);
        if (c & 0x80) {
            let negative = 0;
        } else {
            let negative = 1;
        }
        if (c & 0x40) {
            let exponentNegative = 1;
        } else {
            let exponentNegative = 0;
        }
        if (c & 0x20) {
            let explen = 0;
        } else {
            let explen = 1;
        }
        let exponent = c & 0x1f;
        if explen {
            let i++;
            let c = this->numfromstr(value, i);
            let exponent = (exponent << 6) | (c >> 2);
            if (negative ^ exponentNegative) {
                let exponent = exponent & 0x07ff;
            }
        } else {
            let exponent = exponent >> 2;
            if (negative ^ exponentNegative) {
                let exponent = exponent ^ 0x07;
            }
        }
        let word1 = (c & 0x03) << 24;
        let word1 = word1 | this->numfromstr(value, ++i) << 16;
        let word1 = word1 | this->numfromstr(value, ++i) << 8;
        let word1 = word1 | this->numfromstr(value, ++i);
        let word2 = 0;
        if i < strlen(value) {
            let word2 = this->numfromstr(value, ++i) << 24;
            let word2 = word2 | this->numfromstr(value, ++i) << 16;
            let word2 = word2 | this->numfromstr(value, ++i) << 8;
            let word2 = word2 | this->numfromstr(value, ++i);
        }
        if negative {
            let word1 = 0 - word1;
            if (word2 != 0) {
                let word1++;
            }
            let word2 = 0 - word2;
            let word1 = word1 & 0x03ffffff;
        } else {
            let word1 = word1 | 1 << 26;
        }
        let mantissa = 0;
        if word2 {
            let mantissa = word2 / 4294967296.0; // 1<<32
        }
        let mantissa += word1;
        let mantissa /= 1 << (negative === 1 ? 26 : 27);
        if exponentNegative {
            let exponent = 0 - exponent;
        }
        let exponent += 8;
        if negative {
            mantissa = 0 - mantissa;
        }
        return round(mantissa * pow(2, exponent), 2);
    }

    private function isRobotAgent() -> boolean
    {
        var agentVar, key;
        string agent;

        if fetch agentVar, _SERVER["HTTP_USER_AGENT"] {
            let agent = strtolower(agentVar);
            for key in ["bot", "slurp", "spider", "crawl", "curl"] {
                if strpos(agent, key) !== false {
                    return true;
                }
            }
        }
        return false;
    }

}
