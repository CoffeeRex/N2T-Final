#include "SymbolTable.h"

#include <string>
#include <map>

using namespace std;

/**
 * Symbol Table constructor
 */
SymbolTable::SymbolTable() {
    map<string, string> mySymbols;
    mySymbols.insert(pair<string, string> ("R0", "0"));
    mySymbols.insert(pair<string, string> ("R1", "1"));
    mySymbols.insert(pair<string, string> ("R2", "2"));
    mySymbols.insert(pair<string, string> ("R3", "3"));
    mySymbols.insert(pair<string, string> ("R4", "4"));
    mySymbols.insert(pair<string, string> ("R5", "5"));
    mySymbols.insert(pair<string, string> ("R6", "6"));
    mySymbols.insert(pair<string, string> ("R7", "7"));
    mySymbols.insert(pair<string, string> ("R8", "8"));
    mySymbols.insert(pair<string, string> ("R9", "9"));
    mySymbols.insert(pair<string, string> ("R10", "10"));
    mySymbols.insert(pair<string, string> ("R11", "11"));
    mySymbols.insert(pair<string, string> ("R12", "12"));
    mySymbols.insert(pair<string, string> ("R13", "13"));
    mySymbols.insert(pair<string, string> ("R14", "14"));
    mySymbols.insert(pair<string, string> ("R15", "15"));
    mySymbols.insert(pair<string, string> ("SP", "0"));
    mySymbols.insert(pair<string, string> ("LCL", "1"));
    mySymbols.insert(pair<string, string> ("ARG", "2"));
    mySymbols.insert(pair<string, string> ("THIS", "3"));
    mySymbols.insert(pair<string, string> ("THAT", "4"));
    mySymbols.insert(pair<string, string> ("SCREEN", "16384"));
    mySymbols.insert(pair<string, string> ("KBD", "24576"));

    symbols = mySymbols;
}

/**
 * Symbol Table destructor
 */
SymbolTable::~SymbolTable() {
    // Your code here
}

/**
 * Adds a symbol to the symbol table
 * @param symbol The name of the symbol
 * @param value The address for the symbol
 */
void SymbolTable::addSymbol(string symbol, uint16_t value) {
    string myValue = to_string(value);
    symbols.insert(pair<string, string> (symbol, myValue));
}

/**
 * Gets a symbol from the symbol table
 * @param symbol The name of the symbol
 * @return The address for the symbol or -1 if the symbol isn't in the table
 */
int SymbolTable::getSymbol(string symbol) {
    if(symbols.count(symbol) > 0)
    {
        return stoi(symbols.at(symbol));
    }

    else
    {
        return -1;
    }
}