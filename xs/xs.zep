namespace Xs;

class Xs extends Component
{
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

        let self::lastXs = this;
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

        let pos = strpos(conf, ";");
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
            try {
                let search = new Search(conns[i], this);
                search->setCharset(this->getDefaultCharset());

                let this->search = search;
                return search;
            } catch Exception, ex {
                if i + 1 >= c {
                    throw ex;
                }
            }

            let i++;
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
                let r[sec] = [];
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
