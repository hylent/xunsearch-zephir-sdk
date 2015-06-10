namespace Xs;

class TokenizerXlen implements Tokenizer
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
        return str_split(value, this->arg);
    }

}
