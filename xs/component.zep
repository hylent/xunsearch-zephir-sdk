namespace Xs;

class Component
{
    public function __get(string name)
    {
        string getter;

        let getter = "get" . name;
        if method_exists(this, getter) {
            return this->{getter}();
        }

        throw new Exception(sprintf(
            "%s property: %s::%s",
            method_exists(this, "set" . name) ? "Write-only" : "Undefined",
            get_class(this),
            name
        ));
    }

    public function __set(string name, var value) -> void
    {
        string setter;

        let setter = "set" . name;
        if method_exists(this, setter) {
            this->{setter}(value);
            return;
        }

        throw new Exception(sprintf(
            "%s property: %s::%s",
            method_exists(this, "get" . name) ? "Read-only" : "Undefined",
            get_class(this),
            name
        ));
    }

    public function __isset(string name) -> boolean
    {
        return method_exists(this, "get" . name);
    }

    public function __unset(string name) -> void
    {
        this->__set(name, null);
    }

}
