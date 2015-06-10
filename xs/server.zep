namespace Xs;

class Server extends Component
{
    const FILE      = 0x01;
    const BROKEN    = 0x02;

    public xs;

    protected sock;
    protected conn;
    protected flag;
    protected project;
    protected sendBuffer;

    public function __construct(string conn = "", <Xs> xs = null) -> void
    {
        let this->xs = xs;
        if conn->length() > 0 {
            this->open(conn);
        }
    }

    public function __destruct() -> void
    {
        let this->xs = null;
        this->close();
    }

    public function open(string conn) -> void
    {
        this->close();

        let this->conn = conn;
        let this->flag = self::BROKEN;
        let this->sendBuffer = "";
        let this->project = null;

        this->connect();
        let this->flag = this->flag ^ self::BROKEN;

        if typeof this->xs == "object" && (this->xs instanceof Xs) {
            this->setProject(this->xs->getName());
        }
    }

    public function reopen(boolean force = false)
    {
        if (this->flag & self::BROKEN) || force {
            this->open(this->conn);
        }

        return this;
    }

    public function close(boolean ioerr = false) -> void
    {
        var cmd;

        if this->sock && ! (this->flag & self::BROKEN) {
            if ! ioerr && this->sendBuffer !== "" {
                this->write(this->sendBuffer);
                let this->sendBuffer = "";
            }

            if ! ioerr && ! (this->flag & self::FILE) {
                let cmd = new Command(Command::CMD_QUIT);
                fwrite(this->sock, (string) cmd);
            }

            fclose(this->sock);
            let this->flag = this->flag | self::BROKEN;
        }
    }

    public function getConnString() -> string
    {
        string str;

        let str = (string) this->conn;

        if is_numeric(str) {
            return "localhost:" . str;
        }

        if (strpos(str, ":") === false) {
            return "unix://" . str;
        }

        return str;
    }

    public function getSocket()
    {
        return this->sock;
    }

    public function getProject() -> string
    {
        return this->project;
    }

    public function setProject(string name, string home = "") -> void
    {
        if name !== this->project {
            this->execCommand(["cmd": Command::CMD_USE, "buf": name, "buf1": home], Command::CMD_OK_PROJECT);
            let this->project = name;
        }
    }

    public function setTimeout(long sec) -> void
    {
        this->execCommand(["cmd": Command::CMD_TIMEOUT, "arg": sec], Command::CMD_OK_TIMEOUT_SET);
    }

    public function execCommand(var cmdArg, long resArg = Command::CMD_NONE, long resCmd = Command::CMD_OK)
    {
        string buf;
        var cmd, res;

        if typeof cmdArg == "object" && (cmdArg instanceof Command) {
            let cmd = cmdArg;
        } else {
            let cmd = new Command(cmdArg);
        }

        if (cmd->cmd & 0x80) {
            let this->sendBuffer .= cmd;
            return true;
        }

        let buf = this->sendBuffer . cmd;
        let this->sendBuffer = "";
        this->write(buf);

        if (this->flag & self::FILE) {
            return true;
        }

        let res = this->getRespond();
        if res->cmd === Command::CMD_ERR && resCmd != Command::CMD_ERR {
            throw new Exception(res->buf, res->getArg());
        }

        if res->cmd != resCmd || (resArg != Command::CMD_NONE && res->getArg() != resArg) {
            throw new Exception("Unexpected respond {CMD:" . res->cmd . ", ARG:" . res->getArg() . "}");
        }

        return res;
    }

    public function sendCommand(var cmdArg) -> void
    {
        var cmd;

        if typeof cmdArg == "object" && (cmdArg instanceof Command) {
            let cmd = cmdArg;
        } else {
            let cmd = new Command(cmdArg);
        }

        this->write((string) cmd);
    }

    public function getRespond() -> <Command>
    {
        string buf;
        var hdr, res;

        let buf = (string) this->read(8);
        let hdr = unpack("Ccmd/Carg1/Carg2/Cblen1/Iblen", buf);
        let res = new Command(hdr);
        let res->buf = this->read(hdr["blen"]);
        let res->buf1 = this->read(hdr["blen1"]);

        return res;
    }

    public function hasRespond() -> boolean
    {
        var wfds, xfds, rfds;

        if this->sock === null || (this->flag & (self::BROKEN | self::FILE)) {
            return false;
        }

        let wfds = [];
        let xfds = [];
        let rfds = [];
        let rfds[] = this->sock;

        return stream_select(rfds, wfds, xfds, 0, 0) > 0;
    }

    protected function write(string buf, long len = 0) -> void
    {
        long size;
        var bytes, meta;
        string msg;

        if len == 0 {
            let len = buf->length();
            if len == 0 {
                return;
            }
        }

        this->check();
        let size = len;

        loop {
            let bytes = fwrite(this->sock, buf, len);
            if bytes === false || bytes === 0 || bytes === len {
                break;
            }
            let len -= bytes;
            let buf = substr(buf, bytes);
        }

        if bytes === false || bytes === 0 {
            let meta = stream_get_meta_data(this->sock);
            this->close(true);
            if meta["timed_out"] {
                let msg = "timeout";
            } else {
                if meta["eof"] {
                    let msg = "closed";
                } else {
                    let msg = "unknown";
                }
            }
            throw new Exception(sprintf(
                "Failed to send data to server completely (SIZE:%d/%d, REASON:%s)",
                size - len,
                size,
                msg
            ));
        }
    }

    protected function read(long len) -> string
    {
        long size;
        var bytes, meta;
        string buf, msg;

        if len == 0 {
            return "";
        }

        this->check();
        let size = len;
        let buf = "";

        loop {
            let bytes = fread(this->sock, len);
            if bytes === false || strlen(bytes) == 0 {
                break;
            }

            let len -= strlen(bytes);
            let buf .= bytes;

            if len <= 0 {
                return buf;
            }
        }

        let meta = stream_get_meta_data(this->sock);
        this->close(true);
        if meta["timed_out"] {
            let msg = "timeout";
        } else {
            if meta["eof"] {
                let msg = "closed";
            } else {
                let msg = "unknown";
            }
        }
        throw new Exception(sprintf(
            "Failed to recv data to server completely (SIZE:%d/%d, REASON:%s)",
            size - len,
            size,
            msg
        ));
    }

    protected function check() -> void
    {
        if unlikely this->sock === null {
            throw new Exception("No server connection");
        }

        if (this->flag & self::BROKEN) {
            throw new Exception("Broken server connection");
        }
    }

    protected function connect() -> void
    {
        string conn, host;
        long port, timeout;
        var pos, sock, errNo = null, err = null;

        let conn = (string) this->conn;

        if ! strncmp(conn, "file://", 7) {
            let conn = (string) substr(conn, 7);
            let sock = fopen(conn, "wb");
            if sock === false {
                throw new Exception("Failed to open local file for writing: " . conn);
            }
            let this->flag = this->flag | self::FILE;
            let this->sock = sock;
            return;
        }

        if is_numeric(conn) {
            let host = "localhost";
            let port = intval(conn);
        } else {
            let pos = strpos(conn, ":");
            if pos !== false {
                let host = (string) substr(conn, 0, pos);
                let port = intval(substr(conn, pos + 1));
            } else {
                let host = "unix://" . conn;
                let port = -1;
            }
        }

        let sock = fsockopen(host, port, errNo, err, 5);
        if sock === false {
            throw new Exception(err . "(C#" . errNo . ", " . host . ":" . port . ")");
        }

        let timeout = (long) ini_get("max_execution_time");
        if timeout > 0 {
            let timeout--;
        } else {
            let timeout = 30;
        }

        stream_set_blocking(sock, true);
        stream_set_timeout(sock, timeout, 0);

        let this->sock = sock;
    }

}
