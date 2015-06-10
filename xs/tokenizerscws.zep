namespace Xs;

class TokenizerScws implements Tokenizer
{
    const MULTI_MASK    = 15;
    const MULTI_NONE    = 0;
    const MULTI_SHORT   = 1;
    const MULTI_DUALITY = 2;
    const MULTI_ZMAIN   = 4;
    const MULTI_ZALL    = 8;

    const XDICT_XDB     = 1;
    const XDICT_MEM     = 2;
    const XDICT_TXT     = 4;

    private static charset;
    private static server;

    private setting;

    public function __construct(var arg = null) -> void
    {
        var xs;

        if self::server === null {
            let xs = Xs::getLastXs();
            if xs === null {
                throw new Exception("An Xs instance should be created before using " . __CLASS__);
            }
            let self::server = xs->getScwsServer();
            self::server->setTimeout(0);
            let self::charset = xs->getDefaultCharset();
        }
        if arg !== null && arg !== "" {
            this->setMulti(arg);
        }
    }

    public function getTokens(string value, <Document> doc = null) -> array
    {
        var tokens = [], words, word;
        string charset;

        this->setIgnore(true);
        let charset = self::charset;
        let self::charset = "UTF-8";
        let words = this->getResult(value);
        for word in words {
            let tokens[] = word["word"];
        }
        let self::charset = charset;
        return tokens;
    }

    public function setCharset(string charset)
    {
        let charset = charset->upper();
        if charset == "UTF8" {
            let self::charset = "UTF-8";
        } else {
            let self::charset = charset;
        }
        return this;
    }

    public function setIgnore(boolean yes = true)
    {
        let this->setting["ignore"] = new Command(Command::CMD_SEARCH_SCWS_SET, Command::CMD_SCWS_SET_IGNORE, yes ? 1 : 0);
        return this;
    }

    public function setMulti(long mode = 3)
    {
        let mode = mode & self::MULTI_MASK;
        let this->setting["multi"] = new Command(Command::CMD_SEARCH_SCWS_SET, Command::CMD_SCWS_SET_MULTI, mode);
        return this;
    }

    public function setDict(string fpath, var mode = null)
    {
        if typeof mode != "int" {
            if stripos(fpath, ".txt") === false {
                let mode = self::XDICT_XDB;
            } else {
                let mode = self::XDICT_TXT;
            }
        }
        let this->setting["set_dict"] = new Command(Command::CMD_SEARCH_SCWS_SET, Command::CMD_SCWS_SET_DICT, mode, fpath);
        unset(this->setting["add_dict"]);
        return this;
    }

    public function addDict(string fpath, var mode = null)
    {
        if typeof mode != "int" {
            if stripos(fpath, ".txt") === false {
                let mode = self::XDICT_XDB;
            } else {
                let mode = self::XDICT_TXT;
            }
        }
        let this->setting["add_dict"][] = new Command(Command::CMD_SEARCH_SCWS_SET, Command::CMD_SCWS_ADD_DICT, mode, fpath);
        return this;
    }

    public function setDuality(boolean yes = true)
    {
        let this->setting["duality"] = new Command(Command::CMD_SEARCH_SCWS_SET, Command::CMD_SCWS_SET_DUALITY, yes ? 1 : 0);
        return this;
    }

    public function getVersion() -> string
    {
        var cmd, res;

        let cmd = new Command(Command::CMD_SEARCH_SCWS_GET, Command::CMD_SCWS_GET_VERSION);
        let res = self::server->execCommand(cmd, Command::CMD_OK_INFO);
        return res->buf;
    }

    public function getResult(string text) -> array
    {
        var words = [], cmd, res, tmp;

        let text = this->applySetting(text);
        let cmd = new Command(Command::CMD_SEARCH_SCWS_GET, Command::CMD_SCWS_GET_RESULT, 0, text);
        let res = self::server->execCommand(cmd, Command::CMD_OK_SCWS_RESULT);
        while res->buf !== "" {
            let tmp = unpack("Ioff/a4attr/a*word", res->buf);
            let tmp["word"] = Xs::convert(tmp["word"], self::charset, "UTF-8");
            let words[] = tmp;
            let res = self::server->getRespond();
        }
        return words;
    }

    public function getTops(string text, long limit = 10, string xattr = "")
    {
        var words = [], cmd, res, tmp;

        let text = this->applySetting(text);
        let cmd = new Command(Command::CMD_SEARCH_SCWS_GET, Command::CMD_SCWS_GET_TOPS, limit, text, xattr);
        let res = self::server->execCommand(cmd, Command::CMD_OK_SCWS_TOPS);
        while res->buf !== "" {
            let tmp = unpack("Itimes/a4attr/a*word", res->buf);
            let tmp["word"] = Xs::convert(tmp["word"], self::charset, "UTF-8");
            let words[] = tmp;
            let res = self::server->getRespond();
        }
        return words;
    }

    public function hasWord(string text, string xattr)
    {
        var cmd, res;

        let text = this->applySetting(text);
        let cmd = new Command(Command::CMD_SEARCH_SCWS_GET, Command::CMD_SCWS_HAS_WORD, 0, text, xattr);
        let res = self::server->execCommand(cmd, Command::CMD_OK_INFO);
        return res->buf === "OK";
    }

    private function applySetting(string text) -> string
    {
        var cmd, c;

        self::server->reopen();
        if typeof this->setting == "array" {
            for cmd in this->setting {
                if typeof cmd == "array" {
                    for c in cmd {
                        self::server->execCommand(c);
                    }
                } else {
                    self::server->execCommand(cmd);
                }
            }
        }
        return Xs::convert(text, "UTF-8", self::charset);
    }

}
