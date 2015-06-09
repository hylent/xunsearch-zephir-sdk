namespace Xs\Tokenizer;

use Xs\Tokenizer;

class Full implements Tokenizer
{
    public function getTokens(string value, <Document> doc = null) -> array
    {
        return [value];
    }

}
