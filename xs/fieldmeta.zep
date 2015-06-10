namespace Xs;

class FieldMeta
{
    const MAX_WDF               = 0x3f;
    const TYPE_STRING           = 0;
    const TYPE_NUMERIC          = 1;
    const TYPE_DATE             = 2;
    const TYPE_ID               = 10;
    const TYPE_TITLE            = 11;
    const TYPE_BODY             = 12;
    const FLAG_INDEX_SELF       = 0x01;
    const FLAG_INDEX_MIXED      = 0x02;
    const FLAG_INDEX_BOTH       = 0x03;
    const FLAG_WITH_POSITION    = 0x10;
    const FLAG_NON_BOOL         = 0x80; // force weight calculation (Non-boolean)

    private static tokenizers;

    public name;
    public cutlen   = 0;
    public weight   = 1;
    public type     = 0;
    public vno      = 0;

    private tokenizer   = Tokenizer::DFL;
    private flag        = 0;

    public function __construct(string name, array config = null) -> void
    {
        let this->name = name;

        if typeof config == "array" {
            this->fromConfig(config);
        }
    }

    public function __toString() -> string
    {
        return (string) this->name;
    }

    public function val(var value)
    {
        if this->type == self::TYPE_DATE {
            if ! is_numeric(value) || strlen(value) !== 8 {
                let value = date("Ymd", is_numeric(value) ? value : strtotime(value));
            }
        }

        return value;
    }

    public function withPos() -> boolean
    {
        if (this->flag & self::FLAG_WITH_POSITION) {
            return true;
        }

        return false;
    }

    public function isBoolIndex() -> boolean
    {
        if (this->flag & self::FLAG_NON_BOOL) {
            return false;
        }

        return ! this->hasIndex() || this->tokenizer !== Tokenizer::DFL;
    }

    public function isNumeric() -> boolean
    {
        return this->type == self::TYPE_NUMERIC;
    }

    public function isSpeical() -> boolean
    {
        return this->type == self::TYPE_ID || this->type == self::TYPE_TITLE || this->type == self::TYPE_BODY;
    }

    public function hasIndex() -> boolean
    {
        if (this->flag & self::FLAG_INDEX_BOTH) {
            return true;
        }

        return false;
    }

    public function hasIndexMixed() -> boolean
    {
        if (this->flag & self::FLAG_INDEX_MIXED) {
            return true;
        }

        return false;
    }

    public function hasIndexSelf() -> boolean
    {
        if (this->flag & self::FLAG_INDEX_SELF) {
            return true;
        }

        return false;
    }

    public function hasCustomTokenizer() -> boolean
    {
        return this->tokenizer !== Tokenizer::DFL;
    }

    public function getCustomTokenizer() -> <Tokenizer>
    {
        var tokenizer;
        var m = null;
        string name, arg;

        if fetch tokenizer, self::tokenizers[this->tokenizer] {
            return tokenizer;
        }

        if preg_match("/^([^\\(]+)\\((.*)\\)$/", this->tokenizer, m) {
            let name = __NAMESPACE__ . "\\Tokenizer" . (string) ucfirst(m[1]);
            let arg = (string) m[2];
        } else {
            let name = __NAMESPACE__ . "\\Tokenizer" . (string) ucfirst(this->tokenizer);
            let arg = "";
        }

        if unlikely ! class_exists(name, true) {
            throw new Exception("Undefined custom tokenizer " . name . " for field `" . this->name . "`");
        }

        if arg->length() > 0 {
            let tokenizer = new {name}(arg);
        } else {
            let tokenizer = new {name}();
        }

        if unlikely ! (tokenizer instanceof Tokenizer) {
            throw new Exception(name . " for field `" . this->name . "` does not implement Tokenizer interface");
        }

        let self::tokenizers[this->tokenizer] = tokenizer;
        return tokenizer;
    }

    public function toConfig() -> string
    {
        var index;
        string s = "";

        let s .= "[" . this->name . "]\n";

        switch this->type {
            case self::TYPE_NUMERIC:
                let s .= "type = numeric\n";
                break;
            case self::TYPE_ID:
                let s .= "type = id\n";
                break;
            case self::TYPE_TITLE:
                let s .= "type = title\n";
                break;
            case self::TYPE_BODY:
                let s .= "type = body\n";
                break;
        }

        if this->type !== self::TYPE_BODY {
            let index = this->flag & self::FLAG_INDEX_BOTH;
            if index {
                switch index {
                    case self::FLAG_INDEX_BOTH:
                        if this->type !== self::TYPE_TITLE {
                            let s .= "index = both\n";
                        }
                        break;
                    case self::FLAG_INDEX_MIXED:
                        let s .= "index = mixed\n";
                        break;
                    default:
                        if this->type !== self::TYPE_ID {
                            let s .= "index = self\n";
                        }
                        break;
                }
            }
        }

        if this->type !== self::TYPE_ID && this->tokenizer !== Tokenizer::DFL {
            let s .= "tokenizer = " . this->tokenizer . "\n";
        }

        if this->cutlen > 0 && ! (this->cutlen === 300 && this->type === self::TYPE_BODY) {
            let s .= "cutlen = " . this->cutlen . "\n";
        }

        if this->weight !== 1 && ! (this->weight === 5 && this->type === self::TYPE_TITLE) {
            let s .= "weight = " . this->weight . "\n";
        }

        if (this->flag & self::FLAG_WITH_POSITION) {
            if this->type !== self::TYPE_BODY && this->type !== self::TYPE_TITLE {
                let s .= "phrase = yes\n";
            }
        } else {
            if this->type === self::TYPE_BODY || this->type === self::TYPE_TITLE {
                let s .= "phrase = no\n";
            }
        }

        if (this->flag & self::FLAG_NON_BOOL) {
            let s .= "non_bool = yes\n";
        }

        return s;
    }

    public function fromConfig(array config)
    {
        var c;
        string predef;

        if fetch c, config["type"] {
            let predef = __CLASS__ . "::TYPE_" . strtoupper(c);
            if defined(predef) {
                let this->type = constant(predef);
                switch this->type {
                    case self::TYPE_ID:
                        let this->flag = self::FLAG_INDEX_SELF;
                        let this->tokenizer = "full";
                        break;
                    case self::TYPE_TITLE:
                        let this->flag = self::FLAG_INDEX_BOTH | self::FLAG_WITH_POSITION;
                        let this->weight = 5;
                        break;
                    case self::TYPE_BODY:
                        let this->vno = FieldScheme::MIXED_VNO;
                        let this->flag = self::FLAG_INDEX_SELF | self::FLAG_WITH_POSITION;
                        let this->cutlen = 300;
                        break;
                }
            }
        }

        if fetch c, config["index"] && this->type != self::TYPE_BODY {
            let predef = __CLASS__ . "::FLAG_INDEX_" . strtoupper(c);
            if defined(predef) {
                let this->flag = (this->flag & (0xffff - self::FLAG_INDEX_BOTH)) | (long) constant(predef);
            }
            if this->type == self::TYPE_ID {
                let this->flag = this->flag | self::FLAG_INDEX_SELF;
            }
        }

        if fetch c, config["cutlen"] {
            let this->cutlen = (long) c;
        }

        if fetch c, config["weight"] && this->type != self::TYPE_BODY {
            let this->weight = ((long) c) & self::MAX_WDF;
        }

        if fetch c, config["phrase"] {
            switch strtolower(c) {
                case "yes":
                    let this->flag = this->flag | self::FLAG_WITH_POSITION;
                    break;
                case "no":
                    let this->flag = this->flag & (0xffff - self::FLAG_WITH_POSITION);
                    break;
            }
        }

        if fetch c, config["non_bool"] {
            switch strtolower(c) {
                case "yes":
                    let this->flag = this->flag | self::FLAG_NON_BOOL;
                    break;
                case "no":
                    let this->flag = this->flag & (0xffff - self::FLAG_NON_BOOL);
                    break;
            }
        }

        if fetch c, config["tokenizer"] && this->type != self::TYPE_ID && c != "default" {
            let this->tokenizer = c;
        }
    }

}
