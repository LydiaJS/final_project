#include <iostream>
#include <string>
#include <regex>
using namespace std;

string htmlToPlain(string);

string htmlToPlain(string html){
    /**Takes in html and returns the corresponding plain text*/
    regex breakSeq("<br>"); 
    string plainText = regex_replace(html, breakSeq, "\n"); //adds line breaks
    regex formatChars("<[^>]*(>|$)"); 
    plainText = regex_replace(plainText, formatChars, ""); //takes out tags and other formatting
    regex ampSign("&amp;"); 
    plainText = regex_replace(plainText, ampSign, "&"); //re inserts &'s
    regex ltSign("&lt;");
    plainText = regex_replace(plainText, ltSign, "<");  //re inserts <'s
    regex gtSign("&gt;"); 
    plainText = regex_replace(plainText, gtSign, ">"); //re inserts >'s
    return plainText;
}