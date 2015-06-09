namespace Xs\Tokenizer;

use Xs\Tokenizer;

class Xstep implements Tokenizer
{
    private arg = 2;

    public function __construct(long arg = 0) -> void
    {
        if arg > 0 {
            let this->arg = max(1, min(255, arg));
        }
    }

    public function getTokens(string value, <Document> doc = null) -> array
    {
        var terms = [];
        long c, a, i;

        let c = value->length();
        let a = (long) this->arg;
        let i = a;
        loop {
            let terms[] = substr(value, 0, i);
            if i >= c {
                break;
            }
            let i += a;
        }
        return terms;
    }

}
