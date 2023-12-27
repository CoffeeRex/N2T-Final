#include <iostream>
#include <list>

#include "CompilerParser.h"
#include "Token.h"

using namespace std;

int main(int argc, char *argv[]) {
    /* Tokens for:
     *     class MyClass {
     *
     *     }
     */
    list<Token*> tokens;
    /*tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "MyClass"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));*/

    /*tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "MyClass"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("keyword", "static"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("identifier", "b"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("identifier", "c"));
    tokens.push_back(new Token("symbol", ";"));
    tokens.push_back(new Token("keyword", "field"));
    tokens.push_back(new Token("keyword", "bool"));
    tokens.push_back(new Token("identifier", "d"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("identifier", "e"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("identifier", "f"));
    tokens.push_back(new Token("symbol", ";"));
    tokens.push_back(new Token("keyword", "method"));
    tokens.push_back(new Token("keyword", "bool"));
    tokens.push_back(new Token("identifier", "myFunc"));
    tokens.push_back(new Token("symbol", "("));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "var1"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "var2"));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));


    tokens.push_back(new Token("symbol", "}"));*/
    tokens.push_back(new Token("keyword", "var"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "var2"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("keyword", "bool"));
    tokens.push_back(new Token("identifier", "var3"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("keyword", "char"));
    tokens.push_back(new Token("identifier", "var4"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("identifier", "varName"));
    tokens.push_back(new Token("identifier", "var5"));
    tokens.push_back(new Token("symbol", ";"));

    try {
        CompilerParser parser(tokens);
        ParseTree* result = parser.compileVarDec();
        if (result != NULL){
            cout << result->tostring() << endl;
        }
    } catch (ParseException e) {
        cout << "Error Parsing!" << endl;
    }
}