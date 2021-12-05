#include "HtmlToPlain.h"

using namespace std;

string
htmlToPlain
(string html)
{
    /**Takes in html and returns the corresponding plain text*/

    unsigned char count;
    string plainText;
    // The patterns to be replaced
    regex patterns[] = 
    {
        regex("<[^>]*(>|$)"),
        regex("<br>"), 
        regex("&amp;"),
        regex("&lt;"),
        regex("&gt;"),
        regex("&quot;"),
        regex("&#039;")
    };

    // What each pattern will be replaced with
    const char *sign[] = 
    {
        "",
        "\n",
        "&",
        "<",
        ">",
        "\"",
        "'"
    };

    plainText = html;

    // loop through each pattern and set it with its
    // corresponding sign
    count = 6;
    do
    {
        plainText = regex_replace(plainText,patterns[count],sign[count]);
    } while (--count);
    
    // because the loop will exit when count is 0, do the last pattern here
    plainText = regex_replace(plainText,patterns[count],sign[count]);

    return plainText;
}
