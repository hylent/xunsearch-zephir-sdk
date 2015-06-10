namespace Xs;

class TokenizerFull implements Tokenizer
{
    public function getTokens(string value, <Document> doc = null) -> array
    {
        return [value];
    }

}
