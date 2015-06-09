namespace Xs\Tokenizer;

use Xs\Tokenizer;

class Split implements Tokenizer
{
    private arg = " ";

    public function __construct(string arg = "") -> void
    {
        if arg->length() > 0 {
            let this->arg = arg;
        }
    }

    public function getTokens(string value, <Document> doc = null) -> array
    {
        if strlen(this->arg) > 2 && substr(this->arg, 0, 1) == '/' && substr(this->arg, -1, 1) == '/' {
            return preg_split(this->arg, value);
        }
        return explode(this->arg, value);
    }

}
