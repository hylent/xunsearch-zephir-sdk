namespace Xs;

class Xs
{
    const CMD_NONE                                  = 0;
    const CMD_DEFAULT                               = 0; // XS_CMD_NONE;
    const CMD_PROTOCOL                              = 20110707;
    const CMD_USE                                   = 1;
    const CMD_HELLO                                 = 1;
    const CMD_DEBUG                                 = 2;
    const CMD_TIMEOUT                               = 3;
    const CMD_QUIT                                  = 4;
    const CMD_INDEX_SET_DB                          = 32;
    const CMD_INDEX_GET_DB                          = 33;
    const CMD_INDEX_SUBMIT                          = 34;
    const CMD_INDEX_REMOVE                          = 35;
    const CMD_INDEX_EXDATA                          = 36;
    const CMD_INDEX_CLEAN_DB                        = 37;
    const CMD_DELETE_PROJECT                        = 38;
    const CMD_INDEX_COMMIT                          = 39;
    const CMD_INDEX_REBUILD                         = 40;
    const CMD_FLUSH_LOGGING                         = 41;
    const CMD_INDEX_SYNONYMS                        = 42;
    const CMD_INDEX_USER_DICT                       = 43;
    const CMD_SEARCH_DB_TOTAL                       = 64;
    const CMD_SEARCH_GET_TOTAL                      = 65;
    const CMD_SEARCH_GET_RESULT                     = 66;
    const CMD_SEARCH_SET_DB                         = 32; // XS_CMD_INDEX_SET_DB;
    const CMD_SEARCH_GET_DB                         = 33; // XS_CMD_INDEX_GET_DB;
    const CMD_SEARCH_ADD_DB                         = 68;
    const CMD_SEARCH_FINISH                         = 69;
    const CMD_SEARCH_DRAW_TPOOL                     = 70;
    const CMD_SEARCH_ADD_LOG                        = 71;
    const CMD_SEARCH_GET_SYNONYMS                   = 72;
    const CMD_SEARCH_SCWS_GET                       = 73;
    const CMD_QUERY_GET_STRING                      = 96;
    const CMD_QUERY_GET_TERMS                       = 97;
    const CMD_QUERY_GET_CORRECTED                   = 98;
    const CMD_QUERY_GET_EXPANDED                    = 99;
    const CMD_OK                                    = 128;
    const CMD_ERR                                   = 129;
    const CMD_SEARCH_RESULT_DOC                     = 140;
    const CMD_SEARCH_RESULT_FIELD                   = 141;
    const CMD_SEARCH_RESULT_FACETS                  = 142;
    const CMD_SEARCH_RESULT_MATCHED                 = 143;
    const CMD_DOC_TERM                              = 160;
    const CMD_DOC_VALUE                             = 161;
    const CMD_DOC_INDEX                             = 162;
    const CMD_INDEX_REQUEST                         = 163;
    const CMD_IMPORT_HEADER                         = 191;
    const CMD_SEARCH_SET_SORT                       = 192;
    const CMD_SEARCH_SET_CUT                        = 193;
    const CMD_SEARCH_SET_NUMERIC                    = 194;
    const CMD_SEARCH_SET_COLLAPSE                   = 195;
    const CMD_SEARCH_KEEPALIVE                      = 196;
    const CMD_SEARCH_SET_FACETS                     = 197;
    const CMD_SEARCH_SCWS_SET                       = 198;
    const CMD_SEARCH_SET_CUTOFF                     = 199;
    const CMD_SEARCH_SET_MISC                       = 200;
    const CMD_QUERY_INIT                            = 224;
    const CMD_QUERY_PARSE                           = 225;
    const CMD_QUERY_TERM                            = 226;
    const CMD_QUERY_RANGEPROC                       = 227;
    const CMD_QUERY_RANGE                           = 228;
    const CMD_QUERY_VALCMP                          = 229;
    const CMD_QUERY_PREFIX                          = 230;
    const CMD_QUERY_PARSEFLAG                       = 231;
    const CMD_SORT_TYPE_RELEVANCE                   = 0;
    const CMD_SORT_TYPE_DOCID                       = 1;
    const CMD_SORT_TYPE_VALUE                       = 2;
    const CMD_SORT_TYPE_MULTI                       = 3;
    const CMD_SORT_TYPE_MASK                        = 0x3f;
    const CMD_SORT_FLAG_RELEVANCE                   = 0x40;
    const CMD_SORT_FLAG_ASCENDING                   = 0x80;
    const CMD_QUERY_OP_AND                          = 0;
    const CMD_QUERY_OP_OR                           = 1;
    const CMD_QUERY_OP_AND_NOT                      = 2;
    const CMD_QUERY_OP_XOR                          = 3;
    const CMD_QUERY_OP_AND_MAYBE                    = 4;
    const CMD_QUERY_OP_FILTER                       = 5;
    const CMD_RANGE_PROC_STRING                     = 0;
    const CMD_RANGE_PROC_DATE                       = 1;
    const CMD_RANGE_PROC_NUMBER                     = 2;
    const CMD_VALCMP_LE                             = 0;
    const CMD_VALCMP_GE                             = 1;
    const CMD_PARSE_FLAG_BOOLEAN                    = 1;
    const CMD_PARSE_FLAG_PHRASE                     = 2;
    const CMD_PARSE_FLAG_LOVEHATE                   = 4;
    const CMD_PARSE_FLAG_BOOLEAN_ANY_CASE           = 8;
    const CMD_PARSE_FLAG_WILDCARD                   = 16;
    const CMD_PARSE_FLAG_PURE_NOT                   = 32;
    const CMD_PARSE_FLAG_PARTIAL                    = 64;
    const CMD_PARSE_FLAG_SPELLING_CORRECTION        = 128;
    const CMD_PARSE_FLAG_SYNONYM                    = 256;
    const CMD_PARSE_FLAG_AUTO_SYNONYMS              = 512;
    const CMD_PARSE_FLAG_AUTO_MULTIWORD_SYNONYMS    = 1536;
    const CMD_PREFIX_NORMAL                         = 0;
    const CMD_PREFIX_BOOLEAN                        = 1;
    const CMD_INDEX_WEIGHT_MASK                     = 0x3f;
    const CMD_INDEX_FLAG_WITHPOS                    = 0x40;
    const CMD_INDEX_FLAG_SAVEVALUE                  = 0x80;
    const CMD_INDEX_FLAG_CHECKSTEM                  = 0x80;
    const CMD_VALUE_FLAG_NUMERIC                    = 0x80;
    const CMD_INDEX_REQUEST_ADD                     = 0;
    const CMD_INDEX_REQUEST_UPDATE                  = 1;
    const CMD_INDEX_SYNONYMS_ADD                    = 0;
    const CMD_INDEX_SYNONYMS_DEL                    = 1;
    const CMD_SEARCH_MISC_SYN_SCALE                 = 1;
    const CMD_SEARCH_MISC_MATCHED_TERM              = 2;
    const CMD_SCWS_GET_VERSION                      = 1;
    const CMD_SCWS_GET_RESULT                       = 2;
    const CMD_SCWS_GET_TOPS                         = 3;
    const CMD_SCWS_HAS_WORD                         = 4;
    const CMD_SCWS_GET_MULTI                        = 5;
    const CMD_SCWS_SET_IGNORE                       = 50;
    const CMD_SCWS_SET_MULTI                        = 51;
    const CMD_SCWS_SET_DUALITY                      = 52;
    const CMD_SCWS_SET_DICT                         = 53;
    const CMD_SCWS_ADD_DICT                         = 54;
    const CMD_ERR_UNKNOWN                           = 600;
    const CMD_ERR_NOPROJECT                         = 401;
    const CMD_ERR_TOOLONG                           = 402;
    const CMD_ERR_INVALIDCHAR                       = 403;
    const CMD_ERR_EMPTY                             = 404;
    const CMD_ERR_NOACTION                          = 405;
    const CMD_ERR_RUNNING                           = 406;
    const CMD_ERR_REBUILDING                        = 407;
    const CMD_ERR_WRONGPLACE                        = 450;
    const CMD_ERR_WRONGFORMAT                       = 451;
    const CMD_ERR_EMPTYQUERY                        = 452;
    const CMD_ERR_TIMEOUT                           = 501;
    const CMD_ERR_IOERR                             = 502;
    const CMD_ERR_NOMEM                             = 503;
    const CMD_ERR_BUSY                              = 504;
    const CMD_ERR_UNIMP                             = 505;
    const CMD_ERR_NODB                              = 506;
    const CMD_ERR_DBLOCKED                          = 507;
    const CMD_ERR_CREATE_HOME                       = 508;
    const CMD_ERR_INVALID_HOME                      = 509;
    const CMD_ERR_REMOVE_HOME                       = 510;
    const CMD_ERR_REMOVE_DB                         = 511;
    const CMD_ERR_STAT                              = 512;
    const CMD_ERR_OPEN_FILE                         = 513;
    const CMD_ERR_TASK_CANCELED                     = 514;
    const CMD_ERR_XAPIAN                            = 515;
    const CMD_OK_INFO                               = 200;
    const CMD_OK_PROJECT                            = 201;
    const CMD_OK_QUERY_STRING                       = 202;
    const CMD_OK_DB_TOTAL                           = 203;
    const CMD_OK_QUERY_TERMS                        = 204;
    const CMD_OK_QUERY_CORRECTED                    = 205;
    const CMD_OK_SEARCH_TOTAL                       = 206;
    const CMD_OK_RESULT_BEGIN                       = 206; // XS_CMD_OK_SEARCH_TOTAL;
    const CMD_OK_RESULT_END                         = 207;
    const CMD_OK_TIMEOUT_SET                        = 208;
    const CMD_OK_FINISHED                           = 209;
    const CMD_OK_LOGGED                             = 210;
    const CMD_OK_RQST_FINISHED                      = 250;
    const CMD_OK_DB_CHANGED                         = 251;
    const CMD_OK_DB_INFO                            = 252;
    const CMD_OK_DB_CLEAN                           = 253;
    const CMD_OK_PROJECT_ADD                        = 254;
    const CMD_OK_PROJECT_DEL                        = 255;
    const CMD_OK_DB_COMMITED                        = 256;
    const CMD_OK_DB_REBUILD                         = 257;
    const CMD_OK_LOG_FLUSHED                        = 258;
    const CMD_OK_DICT_SAVED                         = 259;
    const CMD_OK_RESULT_SYNONYMS                    = 280;
    const CMD_OK_SCWS_RESULT                        = 290;
    const CMD_OK_SCWS_TOPS                          = 291;

    const PACKAGE_BUGREPORT = "http://www.xunsearch.com/bugs";
    const PACKAGE_NAME      = "xunsearch";
    const PACKAGE_TARNAME   = "xunsearch";
    const PACKAGE_URL       = "";
    const PACKAGE_VERSION   = "1.4.9";

    private static lastXs;

    private index;
    private search;
    private scws;
    private scheme;
    private bindScheme;
    private config;

    public static function getLastXs() -> <Xs>
    {
        return self::lastXs;
    }

    public static function convert(var data, string to, string from)
    {
        var k, v;

        if to == from {
            return data;
        }

        if typeof data == "array" {
            for k, v in data {
                let data[k] = self::convert(v, to, from);
            }

            return data;
        }

        if typeof data == "string" && preg_match("/[\x81-\xfe]/", data) {
            return mb_convert_encoding(data, to, from);
        }

        return data;
    }

    public function __construct(string file) -> void
    {
        string data;
        var config, scheme, k, v;

        if unlikely ! file_exists(file) {
            throw new Exception("Cannot find project config file: " . file);
        }

        let self::lastXs = this;

        let data = (string) file_get_contents(file);
        let config = this->parseIniData(data);

        let scheme = new FieldScheme();
        for k, v in config {
            if typeof v == "array" {
                scheme->addField(k, v);
            }
        }

        scheme->checkValid(true);

        let this->scheme = scheme;
        let this->bindScheme = scheme;

        let this->config = config;
        if ! isset config["project.name"] {
            let this->config["project.name"] = basename(file, ".ini");
        }
    }

    public function __destruct() -> void
    {
        let this->index = null;
        let this->search = null;
    }

    public function getScheme() -> <FieldScheme>
    {
        return this->scheme;
    }

    public function setScheme(<FieldScheme> fs) -> void
    {
        fs->checkValid(true);
        let this->scheme = fs;
        if this->search !== null {
            this->search->markResetScheme();
        }
    }

    public function restoreScheme() -> void
    {
        if this->scheme !== this->bindScheme {
            let this->scheme = this->bindScheme;
            if this->search !== null {
                this->search->markResetScheme(true);
            }
        }
    }

    public function getConfig() -> array
    {
        return this->config;
    }

    public function getName() -> string
    {
        return this->config["project.name"];
    }

    public function setName(string name) -> void
    {
        let this->config["project.name"] = name;
    }

    public function getDefaultCharset() -> string
    {
        var dc;

        if fetch dc, this->config["project.default_charset"] {
            return strtoupper(dc);
        }

        return "UTF-8";
    }

    public function setDefaultCharset(string charset) -> void
    {
        let this->config["project.default_charset"] = strtoupper(charset);
    }

    public function getIndex() -> <Index>
    {
        var index;

        var conf, adds, add, pos;
        string conn;

        let index = this->index;
        if index !== null {
            return index;
        }

        if ! fetch conf, this->config["server.index"] {
            let conf = "8383";
        }

        let pos = strpos(conn, ";");
        if pos === false {
            let adds = [];
            let conn = (string) conf;
        } else {
            let adds = explode(";", substr(conf, pos + 1));
            let conn = (string) substr(conf, 0, pos);
        }

        let index = new Index(conn, this);
        index->setTimeout(0);

        for add in adds {
            let conn = (string) trim(add);
            if conn->length() > 0 {
                index->addServer(conn)->setTimeout(0);
            }
        }

        let this->index = index;
        return index;
    }

    public function getSearch() -> <Search>
    {
        var search;
        var conns, serverSearch, serverSearchParts, serverSearchPart, ex;
        string item;
        long i, c;

        let search = this->search;
        if search !== null {
            return search;
        }

        let conns = [];

        if fetch serverSearch, this->config["server.search"] {
            let serverSearchParts = explode(";", serverSearch);
            for serverSearchPart in serverSearchParts {
                let item = (string) trim(serverSearchPart);
                if item->length() > 0 {
                    let conns[] = item;
                }
            }
        } else {
            let conns[] = 8384;
        }

        let c = count(conns);
        if c > 1 {
            shuffle(conns);
        }

        let i = 0;
        while i < c {
            let i++;

            try {
                let search = new Search(conn[i], this);
                search->setCharset(this->getDefaultCharset());

                let this->search = search;
                return search;
            } catch Exception, ex {
                if i >= c {
                    throw ex;
                }
            }
        }

        throw new Exception("Unreachable!");
    }

    public function getScwsServer() -> <Server>
    {
        var scws, conn;

        let scws = this->scws;
        if scws !== null {
            return scws;
        }

        if ! fetch conn, this->config["server.search"] {
            let conn = 8384;
        }

        let scws = new Server(conn, this);
        let this->scws = scws;

        return scws;
    }

    public function getFieldId()
    {
        return this->scheme->getFieldId();
    }

    public function getFieldTitle()
    {
        return this->scheme->getFieldTitle();
    }

    public function getFieldBody()
    {
        return this->scheme->getFieldBody();
    }

    public function getField(string name, boolean throws = true)
    {
        return this->scheme->getField(name, throws);
    }

    public function getAllFields()
    {
        return this->scheme->getAllFields();
    }

    private function parseIniData(string data) -> array
    {
        var r = [];
        var lines, line, pos;
        string l, sec = "", k, v;
        char c;

        let lines = explode("\n", data);
        for line in lines {
            let l = (string) trim(line);
            if l === "" {
                continue;
            }

            let c = l[0];
            if c == ';' || c == '#' {
                continue;
            }

            if c == '[' && substr(l, -1, 1) === "]" {
                let sec = (string) substr(l, 1, -1);
                let ret[sec] = [];
                continue;
            }

            let pos = strpos(line, "=");
            if pos === false {
                continue;
            }

            let k = (string) trim(substr(l, 0, pos));
            let v = (string) trim(substr(l, pos + 1), " '\"\t");

            if sec->length() > 0 {
                let r[sec][k] = v;
            } else {
                let r[k] = v;
            }
        }

        return r;
    }

}
