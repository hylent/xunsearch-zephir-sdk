namespace Xs;

class FieldScheme implements \IteratorAggregate
{
    const MIXED_VNO = 255;

    private static logger;

    private fields;
    private typeMap;
    private vnoMap;

    public static function logger() -> <FieldScheme>
    {
        var scheme;

        if unlikely self::logger === null {
            let scheme = new FieldScheme();

            scheme->addField("id", ["type": "id"]);
            scheme->addField("pinyin");
            scheme->addField("partial");
            scheme->addField("total", ["type": "numeric", "index": "self"]);
            scheme->addField("lastnum", ["type": "numeric", "index": "self"]);
            scheme->addField("currnum", ["type": "numeric", "index": "self"]);
            scheme->addField("currtag", ["type": "string"]);
            scheme->addField("body", ["type": "body"]);

            let self::logger = scheme;
        }

        return self::logger;
    }

    public function __toString() -> string
    {
        string str = "";
        var field;

        if typeof this->fields == "array" {
            for field in this->fields {
                let str .= field->toConfig() . "\n";
            }
        }

        return str;
    }

    public function getFieldId()
    {
        var name;

        if fetch name, this->typeMap[FieldMeta::TYPE_ID] {
            return this->fields[name];
        }

        return false;
    }

    public function getFieldTitle()
    {
        var name, field;

        if fetch name, this->typeMap[FieldMeta::TYPE_TITLE] {
            return this->fields[name];
        }

        if typeof this->fields == "array" {
            for field in this->fields {
                if field->type === FieldMeta::TYPE_STRING && ! field->isBoolIndex() {
                    return field;
                }
            }
        }

        return false;
    }

    public function getFieldBody()
    {
        var name;

        if fetch name, this->typeMap[FieldMeta::TYPE_BODY] {
            return this->fields[name];
        }

        return false;
    }

    public function getField(var name, boolean throws = true)
    {
        var v;

        if typeof name == "int" {
            if ! fetch v, this->vnoMap[name] {
                if throws {
                    throw new Exception("Not exists field with vno: " . name);
                }
                return false;
            }
            let name = v;
        }

        if ! fetch v, this->fields[name] || v === null {
            if throws {
                throw new Exception("Not exists field with name: " . name);
            }
            return false;
        }

        return v;
    }

    public function getAllFields() -> array
    {
        if typeof this->fields == "array" {
            return this->fields;
        }

        return [];
    }

    public function getVnoMap() -> array
    {
        if typeof this->vnoMap == "array" {
            return this->vnoMap;
        }

        return [];
    }

    public function addField(var fieldArg, array config = null) -> void
    {
        var field, prev;

        if typeof fieldArg == "object" && (fieldArg instanceof FieldMeta) {
            let field = fieldArg;
        } else {
            let field = new FieldMeta(fieldArg, config);
        }

        if unlikely isset this->fields[field->name] {
            throw new Exception("Duplicated field name: " . field->name);
        }

        if field->isSpeical() {
            if fetch prev, this->typeMap[field->type] {
                throw new Exception("Duplicated " . config["type"] . " field: " . field->name . " and " . prev);
            }

            let this->typeMap[field->type] = field->name;
        }

        if field->type == FieldMeta::TYPE_BODY {
            let field->vno = self::MIXED_VNO;
        } else {
            let field->vno = count(this->vnoMap);
        }

        let this->vnoMap[field->vno] = field->name;

        if field->type != FieldMeta::TYPE_ID || ! isset this->fields[field->name] {
            let this->fields[field->name] = field;
        }
    }

    public function checkValid(boolean throws = false) -> boolean
    {
        if ! isset this->typeMap[FieldMeta::TYPE_ID] {
            if throws {
                throw new Exception("Missing field of type ID");
            }
            return false;
        }

        return true;
    }

    public function getIterator() -> <\ArrayIterator>
    {
        return new \ArrayIterator(this->fields);
    }

}
