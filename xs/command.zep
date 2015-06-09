namespace Xs;

class Command
{
    public cmd  = Xs::CMD_NONE;
    public arg1 = 0;
    public arg2 = 0;
    public buf  = "";
    public buf1 = "";

    public function __construct(var cmd, long arg1 = 0, long arg2 = 0, string buf = "", string buf1 = "") -> void
    {
        var k, v;

        if typeof cmd == "array" {
            for k, v in cmd {
                if k === "arg" || property_exists(this, k) {
                    let this->{k} = v;
                }
            }
        } else {
            let this->cmd   = cmd;
            let this->arg1  = arg1;
            let this->arg2  = arg2;
            let this->buf   = buf;
            let this->buf1  = buf1;
        }
    }

    public function __toString() -> string
    {
        if strlen(this->buf1) > 0xff {
            let this->buf1 = substr(this->buf1, 0, 0xff);
        }

        return pack("CCCCI", this->cmd, this->arg1, this->arg2, strlen(this->buf1), strlen(this->buf))
            . this->buf . this->buf1;
    }

    public function getArg() -> long
    {
        return this->arg2 | (this->arg1 << 8);
    }

    public function setArg(long arg)
    {
        this->arg1 = (arg >> 8) & 0xff;
        this->arg2 = arg & 0xff;
    }

}
