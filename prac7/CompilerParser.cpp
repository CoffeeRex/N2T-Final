#include "CompilerParser.h"
#include <iostream>


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {

    tkns = tokens;
    it = tkns.begin();
    itnext = tkns.begin();
    itnext++;
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    return NULL;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {

    ParseTree* Class = new ParseTree("class", "");

    Class->addChild(mustBe("keyword", "class"));

    if ((current()->getType()).compare("identifier") == 0)
    {
        Class->addChild(current());
        next();
    }

    else
    {
        throw ParseException();
        return Class;
    }

    Class->addChild(mustBe("symbol", "{"));

    if (!have("symbol", "}"))
    {
        while(have("keyword", "static") or have("keyword", "field"))
        {
            Class->addChild(compileClassVarDec());
            next();
        }

        while(have("keyword", "constructor") or have("keyword", "function") or have("keyword", "method"))
        {
            Class->addChild(compileSubroutine());
            next();
        }
    }

    if (have("symbol", "}"))
    {
        Class->addChild(current());
        return Class;
    }

    else
    {
        throw ParseException();
        return Class;
    }
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* ClassVarDec = new ParseTree("classVarDec", "");

    
    if (have("keyword", "static") or have("keyword", "field"))
    {
        ClassVarDec->addChild(current());
        next();
    }

    else
    {
        throw ParseException();
        return ClassVarDec;
    }

    if (have("keyword", "int") or have("keyword", "char") or have("keyword", "bool") or ((current()->getType()).compare("identifier") == 0))
    {
        ClassVarDec->addChild(current());
        next();
    }

    else
    {
        throw ParseException();
        return ClassVarDec;
    }

    if ((current()->getType()).compare("identifier") == 0)
    {
        ClassVarDec->addChild(current());

        if (std::distance(it, tkns.end()) == 1)
        {
            return ClassVarDec;
        }

        next();
    }

    else
    {
        throw ParseException();
        return ClassVarDec;
    }

    while (have("symbol", ","))
    {
        ClassVarDec->addChild(current());
        next();

        if ((current()->getType()).compare("identifier") == 0)
        {
            ClassVarDec->addChild(current());

            if (std::distance(it, tkns.end()) == 1)
            {
                return ClassVarDec;
            }

            next();
        }

        else
        {
            throw ParseException();
            return ClassVarDec;
        }
    }

    if (have("symbol", ";"))
    {
        ClassVarDec->addChild(current());
        return ClassVarDec;
    }

    else
    {
        throw ParseException();
        return ClassVarDec;
    }
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* Subroutine = new ParseTree("subroutine", "");

    if (have("keyword", "constructor") or have("keyword", "function") or have("keyword", "method"))
    {
        Subroutine->addChild(current());
        next();
    }

    else
    {
        throw ParseException();
        return Subroutine;
    }

    if (have("keyword", "void") or have("keyword", "int") or have("keyword", "char") or have("keyword", "bool") or ((current()->getType()).compare("identifier") == 0))
    {
        Subroutine->addChild(current());
        next();
    }

    else
    {
        throw ParseException();
        return Subroutine;
    }

    if ((current()->getType()).compare("identifier") == 0)
    {
        Subroutine->addChild(current());
        next();
    }

    else
    {
        throw ParseException();
        return Subroutine;
    }

    if (have("symbol", "("))
    {
        Subroutine->addChild(current());
        next();
    }

    else
    {
        throw ParseException();
        return Subroutine;
    }

    Subroutine->addChild(compileParameterList());

    if (have("symbol", ")"))
    {
        Subroutine->addChild(current());
        next();
    }
    else
    {
        throw ParseException();
        return Subroutine;
    }

    Subroutine->addChild(compileSubroutineBody());
    return Subroutine;

}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* ParameterList = new ParseTree("parameterList", "");

    if (have("symbol", ")"))
    {
        return ParameterList;
    }

    else 
    {

        std::cout << current()->getType() << " " << current()->getValue() << std::endl;
        if (((current()->getType()).compare("identifier") == 0) or (have("keyword", "int")) or (have("keyword", "bool")) or (have("keyword", "char")))
        {
            ParameterList->addChild(current());
            next();
        }

        else
        {
            throw ParseException();
            return ParameterList;
        }

        std::cout << current()->getType() << " " << current()->getValue() << std::endl;

        if ((current()->getType()).compare("identifier") == 0)
        {
            std::cout << "wtf" << std::endl;
            ParameterList->addChild(current());

            if (std::distance(it, tkns.end()) == 1)
            {
                return ParameterList;
            }

            next();
        }

        else
        {
            throw ParseException();
            return ParameterList;
        }

        while(have("symbol", ","))
        {
            ParameterList->addChild(current());
            next();

            if (((current()->getType()).compare("identifier") == 0) or (have("keyword", "int")) or (have("keyword", "bool")) or (have("keyword", "char")))
            {
                ParameterList->addChild(current());
                next();
            }

            else
            {
                throw ParseException();
                return ParameterList;
            }

            if ((current()->getType()).compare("identifier") == 0)
            {
                ParameterList->addChild(current());
                if (std::distance(it, tkns.end()) == 1)
                {
                    return ParameterList;
                }
                next();
            }

            else
            {
                throw ParseException();
                return ParameterList;
            }
        }

        return ParameterList;
    }
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* SubroutineBody = new ParseTree("subroutineBody", "");

    if (have("symbol", "{"))
    {
        SubroutineBody->addChild(current());
        next();
    }

    else
    {
        throw ParseException();
        return SubroutineBody;
    }

    if (!have("symbol", "}"))
    {
        while(have("keyword", "var"))
        {
            SubroutineBody->addChild(compileVarDec());
            next();
        }

        while (!have("symbol", "}"))
        {
            if (have("keyword", "let") or have("keyword", "if") or have("keyword", "while") or have("keyword", "do") or have("keyword", "return"))
            {
                SubroutineBody->addChild(compileStatements());
                next();
            }

            else
            {
                throw ParseException();
                return SubroutineBody;
            }
        }
    }

    if (have("symbol", "}"))
    {
        SubroutineBody->addChild(current());
        return SubroutineBody;
    }

    else
    {
        throw ParseException();
        return SubroutineBody;
    }



    
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* VarDec = new ParseTree("varDec", "");

    if (have("keyword", "var"))
    {
        std::cout << "var" << std::endl;
        VarDec->addChild(current());
        next();
    }

    else
    {
        throw ParseException();
        return VarDec;
    }

    if (have("keyword", "int") or have("keyword", "bool") or have("keyword", "char") or ((current()->getType()).compare("identifier") == 0))
    {
        std::cout << "type" << std::endl;
        VarDec->addChild(current());
        next();
    }

    else
    {
        throw ParseException();
        return VarDec;
    }

    if ((current()->getType()).compare("identifier") == 0)
    {
        std::cout << "varName" << std::endl;
        VarDec->addChild(current());
        if (std::distance(it, tkns.end()) == 1)
        {
            return VarDec;
        }

        next();
    }

    else
    {
        throw ParseException();
        return VarDec;
    }

    while (have("symbol", ","))
    {
        VarDec->addChild(current());
        next();
        std::cout << "comma" << std::endl;
        if (have("keyword", "int") or have("keyword", "bool") or have("keyword", "char") or ((current()->getType()).compare("identifier") == 0))
        {
            std::cout << "type" << std::endl;
            VarDec->addChild(current());
            next();
        }

        else
        {
            throw ParseException();
            return VarDec;
        }

        if ((current()->getType()).compare("identifier") == 0)
        {
            std::cout << "varName" << std::endl;
            VarDec->addChild(current());
            next();
        }

        else
        {
            throw ParseException();
            return VarDec;
        }
    }

    if (have("symbol", ";"))
    {
        return VarDec;
    }

    else
    {
        throw ParseException();
        return VarDec;
    }
    
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    if (std::distance( it, tkns.end() ) == 2)
    {
        it++;
    }

    else if (std::distance( it, tkns.end() ) <= 1)
    {
        throw ParseException();
        return;
    }

    else
    {
        it++;
        itnext++;
    }
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    return *it;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    std::string type = current()->getType();
    std::string value = current()->getValue();
    if ((expectedType.compare(type) == 0) and (expectedValue.compare(value) == 0))
    {
        return true;
    }

    else
    {
        return false;
    }
    return true;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */

Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if (have(expectedType, expectedValue))
    {
        Token* temp = current();
        next();
        return temp;
    }
    
    else
    {
        throw ParseException();
        return current();
    }
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
