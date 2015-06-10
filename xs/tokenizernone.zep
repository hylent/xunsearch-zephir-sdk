namespace Xs;

class TokenizerNone implements Tokenizer
{
    public function getTokens(string value, <Document> doc = null) -> array
    {
        return [];
    }

}
