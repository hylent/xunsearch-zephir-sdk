namespace Xs;

class Document implements \ArrayAccess, \IteratorAggregate
{
    private static resSize      = 20;
    private static resFormat    = "Idocid/Irank/Iccount/ipercent/fweight";

    private data;
    private terms;
    private texts;
    private charset;
    private meta;

    public function __construct(var p = null, string d = "") -> void
    {
        if typeof p == "array" {
            let this->data = p;
        } else {
            let this->data = [];

            if typeof p == "string" {
                if strlen(p) !== self::resSize {
                    this->setCharset(p);
                    return;
                }

                let this->meta = unpack(self::resFormat, p);
            }
        }

        if d->length() > 0 {
            this->setCharset(d);
        }
    }

    public function __get(string name)
    {
        var v;

        if fetch v, this->data[name] && v !== null {
            return this->autoConvert(v);
        }
    }

    public function __set(string name, var value) -> void
    {
        if unlikely this->meta !== null {
            throw new Exception("Magick property of result document is read-only");
        }

        this->setField(name, value);
    }

    public function __call(string name, array args)
    {
        string nameLower;
        var v;

        if this->meta !== null {
            let nameLower = name->lower();

            if fetch v, this->meta[name] && v !== null {
                return v;
            }
        }

        throw new Exception("Call to undefined method " . get_class(this) . "::" . name . "()");
    }

    public function getCharset() -> string
    {
        return this->charset;
    }

    public function setCharset(string charset) -> void
    {
        string charsetUpper;

        let charsetUpper = charset->upper();

        if charsetUpper == "UTF8" {
            let this->charset = "UTF-8";
        } else {
            let this->charset = charsetUpper;
        }
    }

    public function getFields() -> array
    {
        return this->data;
    }

    public function setFields(array data = null) -> void
    {
        if data === null {
            let this->data = [];
            let this->meta = null;
            let this->terms = null;
            let this->texts = null;
        } else {
            let this->data = array_merge(this->data, data);
        }
    }

    public function setField(string name, var value, boolean isMeta = false) -> void
    {
        if value === null {
            if isMeta {
                unset(this->meta[name]);
            } else {
                unset(this->data[name]);
            }
        } else {
            if isMeta {
                this->meta[name] = value;
            } else {
                this->data[name] = value;
            }
        }
    }

    public function f(string name)
    {
        return this->__get(name);
    }

    public function getAddTerms(string field) -> array
    {
        var ts, t, weight, terms;

        if ! fetch ts, this->terms[field] {
            return;
        }

        if typeof ts != "array" {
            return;
        }

        let terms = [];
        for t, weight in ts {
            let t = this->autoConvert(t);
            let terms[t] = weight;
        }

        return terms;
    }

    public function getAddIndex(string field)
    {
        var v;

        if ! fetch v, this->texts[field] || v === null {
            return;
        }

        return this->autoConvert(v);
    }

    public function addTerm(string field, string term, long weight = 1) -> void
    {
        var v;

        if fetch v, this->terms[field][term] {
            let v += weight;
        } else {
            let v = weight;
        }

        let this->terms[field][term] = v;
    }

    public function addIndex(string field, string text) -> void
    {
        var v;

        if fetch v, this->texts[field] {
            let v .= "\n" . text;
        } else {
            let v = text;
        }

        let this->texts[field] = v;
    }

    public function getIterator() -> <ArrayIterator>
    {
        var data;
        string from, to;

        if this->charset && this->charset !== "UTF-8" {
            if this->meta === null {
                let from = (string) this->charset;
                let to = "UTF-8";
            } else {
                let from = "UTF-8";
                let to = (string) this->charset;
            }

            let data = Xs::convert(this->data, to, from);
        } else {
            let data = this->data;
        }

        return new ArrayIterator(data);
    }

    public function offsetExists(string name) -> boolean
    {
        return isset this->data[name];
    }

    public function offsetGet(string name)
    {
        return this->__get(name);
    }

    public function offsetSet(string name, var value) -> void
    {
        if name->length() > 0 {
            this->__set(name, value);
        }
    }

    public function offsetUnset(string name) -> void
    {
        unset(this->data[name]);
    }

    public function beforeSubmit(<Index> index) -> boolean
    {
        if this->charset === null {
            let this->charset = index->xs->getDefaultCharset();
        }

        return true;
    }

    public function afterSubmit(<Index> index) -> boolean
    {
        return true;
    }

    private function autoConvert(var value)
    {
        string charset, from, to;

        let charset = (string) this->charset;

        if charset == "" || charset == "UTF-8" || typeof value != "string" || ! preg_match("/[\x81-\xfe]/", value) {
            return value;
        }

        if this->meta === null {
            let from = charset;
            let to = "UTF-8";
        } else {
            let from = "UTF-8";
            let to = charset;
        }

        return Xs::convert(value, to, from);
    }

}
