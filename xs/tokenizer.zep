namespace Xs;

interface Tokenizer
{
    const DFL = 0;

    public function getTokens(string value, <Document> doc = null) -> array;

}
