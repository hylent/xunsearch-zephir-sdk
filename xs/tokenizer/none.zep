namespace Xs\Tokenizer;

use Xs\Tokenizer;

class None implements Tokenizer
{
    public function getTokens(string value, <Document> doc = null) -> array
    {
        return [];
    }

}
