#include "Assembler.h"
#include "SymbolTable.h"

#include <string>
#include <map>

using namespace std;

/**
 * Assembler constructor
 */
Assembler::Assembler() {
    // Your code here
}

/**
 * Assembler destructor
 */
Assembler::~Assembler() {
    // Your code here
}

/**
 * Assembler first pass; populates symbol table with label locations.
 * @param instructions An array of the assembly language instructions.
 * @param symbolTable The symbol table to populate.
 */
void Assembler::buildSymbolTable(SymbolTable* symbolTable, string instructions[], int numOfInst) {

    uint16_t linecount = 0;
    uint16_t varcount = 16;

    for (int i = 0; i < numOfInst; i++)
    {
        if (parseInstructionType(instructions[i]) == L_INSTRUCTION)
        {
            if (symbolTable->getSymbol(symbol) == -1)
                {
                    symbolTable->addSymbol(symbol, linecount);
                }
        }

        else
        {
            linecount++;
        }
    }

    for (int i = 0; i < numOfInst; i++)
    {
        if (parseInstructionType(instructions[i]) == A_INSTRUCTION)
        {
            string symbol = parseSymbol(instructions[i]);

            if (!((symbol[0] == '0') or (symbol[0] == '1') or (symbol[0] == '2') or (symbol[0] == '3') or (symbol[0] == '4') or (symbol[0] == '5') or (symbol[0] == '6') or (symbol[0] == '7') or (symbol[0] == '8') or (symbol[0] == '9')))
            {
                if (symbolTable->getSymbol(symbol) == -1)
                {
                    symbolTable->addSymbol(symbol, varcount);
                    varcount ++;
                }
            }


        }
    }
}

/**
 * Assembler second pass; Translates a set of instructions to machine code.
 * @param instructions An array of the assembly language instructions to be converted to machine code.
 * @param symbolTable The symbol table to reference/update.
 * @return A string containing the generated machine code as lines of 16-bit binary instructions.
 */
string Assembler::generateMachineCode(SymbolTable* symbolTable, string instructions[], int numOfInst) {

    string code = "";
    
    for (int i = 0; i < numOfInst; i++)
    {
        if (parseInstructionType(instructions[i]) == A_INSTRUCTION)
        {
            code += "0";

            code += translateSymbol(parseSymbol(instructions[i]));

            code += '\n';
        }

        else if (parseInstructionType(instructions[i]) == C_INSTRUCTION)
        {
            code += "111";

            code += translateComp(parseInstructionComp(instructions[i]));
            code += translateDest(parseInstructionDest(instructions[i]));
            code += translateJump(parseInstructionJump(instructions[i]));

            code += '\n';

        }
    }
}

/**
 * Parses the type of the provided instruction
 * @param instruction The assembly language representation of an instruction.
 * @return The type of the instruction (A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION, NULL)
 */
Assembler::InstructionType Assembler::parseInstructionType(string instruction) {
    // Your code here:

    if (instruction[0] == '@')
    {
        return A_INSTRUCTION;
    }

    else if (instruction[0] == '(')
    {
        return L_INSTRUCTION;
    }

    else if ((instruction[0] == 'A') or (instruction[0] == 'M') or (instruction[0] == 'D') or (instruction[0] == '0') or (instruction[0] == '1') or (instruction[0] == '-') or (instruction[0] == '!'))
    {
        return C_INSTRUCTION;
    }

    else
    {
        return NULL_INSTRUCTION;
    }
    
}

/**
 * Parses the destination of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The destination of the instruction (A, D, M, AM, AD, MD, AMD, NULL)
 */
Assembler::InstructionDest Assembler::parseInstructionDest(string instruction) {
    
    size_t eq = instruction.find('=');

    if (eq != string::npos)
    {
        string myDest = instruction.substr(0, eq);

        map<string, InstructionDest> myDests;
        myDests.insert(pair<string, InstructionDest> ("A", A));
        myDests.insert(pair<string, InstructionDest> ("D", D));
        myDests.insert(pair<string, InstructionDest> ("M", M));
        myDests.insert(pair<string, InstructionDest> ("AD", AD));
        myDests.insert(pair<string, InstructionDest> ("AM", AM));
        myDests.insert(pair<string, InstructionDest> ("MD", MD));
        myDests.insert(pair<string, InstructionDest> ("AMD", AMD));

        if (myDests.count(myDest) > 0)
        {
            return myDests.at(myDest);
        }

        else
        {
            return NULL_DEST;
        }
    }

    else
    {
        return NULL_DEST;
    }
}

/**
 * Parses the jump condition of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The jump condition for the instruction (JLT, JGT, JEQ, JLE, JGE, JNE, JMP, NULL)
 */
Assembler::InstructionJump Assembler::parseInstructionJump(string instruction) {
    // Your code here:
    // for example if "JLT" appear at the comp field return enum label JLT

    size_t semi = instruction.find(';');

    if (semi != string::npos)
    {
        string myJump = instruction.substr(semi + 1);

        map<string, InstructionJump> myJumps;
        myJumps.insert(pair<string, InstructionJump> ("JLT", JLT));
        myJumps.insert(pair<string, InstructionJump> ("JGT", JGT));
        myJumps.insert(pair<string, InstructionJump> ("JEQ", JEQ));
        myJumps.insert(pair<string, InstructionJump> ("JLE", JLE));
        myJumps.insert(pair<string, InstructionJump> ("JGE", JGE));
        myJumps.insert(pair<string, InstructionJump> ("JNE", JNE));
        myJumps.insert(pair<string, InstructionJump> ("JMP", JMP));

        if (myJumps.count(myJump) > 0)
        {
            return myJumps.at(myJump);
        }

        else
        {
            return NULL_JUMP;
        }

    }
    
    else
    {
        return NULL_JUMP;
    }
    
}

/**
 * Parses the computation/op-code of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The computation/op-code of the instruction (CONST_0, ... ,D_ADD_A , ... , NULL)
 */
Assembler::InstructionComp Assembler::parseInstructionComp(string instruction) {
    // Your code here:
    // for example if "0" appear at the comp field return CONST_0
    string myComp;
    size_t eq = instruction.find('=');
    if (eq != string::npos)
    {
        size_t semi = instruction.find(';');
        if (semi != string::npos)
        {
            myComp = instruction.substr(eq + 1, semi - eq - 1);
        }

        else
        {
            myComp = instruction.substr(eq + 1);
        }
    }

    else
    {
        size_t semi = instruction.find(';');
        if (semi != string::npos)
        {
            myComp = instruction.substr(0, semi);
        }

        else
        {
            myComp = instruction;
        }
    }

    map<string, InstructionComp> myComps;

    myComps.insert(pair<string, InstructionComp> ("0", CONST_0));
    myComps.insert(pair<string, InstructionComp> ("1", CONST_1));
    myComps.insert(pair<string, InstructionComp> ("-1", CONST_NEG_1));
    myComps.insert(pair<string, InstructionComp> ("A", VAL_A));
    myComps.insert(pair<string, InstructionComp> ("M", VAL_M));
    myComps.insert(pair<string, InstructionComp> ("D", VAL_D));
    myComps.insert(pair<string, InstructionComp> ("!A", NOT_A));
    myComps.insert(pair<string, InstructionComp> ("!M", NOT_M));
    myComps.insert(pair<string, InstructionComp> ("!D", NOT_D));
    myComps.insert(pair<string, InstructionComp> ("-A", NEG_A));
    myComps.insert(pair<string, InstructionComp> ("-M", NEG_M));
    myComps.insert(pair<string, InstructionComp> ("-D", NEG_D));
    myComps.insert(pair<string, InstructionComp> ("A+1", A_ADD_1));
    myComps.insert(pair<string, InstructionComp> ("M+1", M_ADD_1));
    myComps.insert(pair<string, InstructionComp> ("D+1", D_ADD_1));
    myComps.insert(pair<string, InstructionComp> ("A-1", A_SUB_1));
    myComps.insert(pair<string, InstructionComp> ("M-1", M_SUB_1));
    myComps.insert(pair<string, InstructionComp> ("D-1", D_SUB_1));
    myComps.insert(pair<string, InstructionComp> ("D+A", D_ADD_A));
    myComps.insert(pair<string, InstructionComp> ("D+M", D_ADD_M));
    myComps.insert(pair<string, InstructionComp> ("D-A", D_SUB_A));
    myComps.insert(pair<string, InstructionComp> ("D-M", D_SUB_M));
    myComps.insert(pair<string, InstructionComp> ("A-D", A_SUB_D));
    myComps.insert(pair<string, InstructionComp> ("M-D", M_SUB_D));
    myComps.insert(pair<string, InstructionComp> ("D&A", D_AND_A));
    myComps.insert(pair<string, InstructionComp> ("D&M", D_AND_M));
    myComps.insert(pair<string, InstructionComp> ("D|A", D_OR_A));
    myComps.insert(pair<string, InstructionComp> ("D|M", D_OR_M));

    if (myComps.count(myComp) > 0)
    {
        return myComps.at(myComp);
    }

    else
    {
        return NULL_COMP;
    }
}

/**
 * Parses the symbol of the provided A/L-instruction
 * @param instruction The assembly language representation of a A/L-instruction.
 * @return A string containing either a label name (L-instruction),
 *         a variable name (A-instruction), or a constant integer value (A-instruction)
 */
string Assembler::parseSymbol(string instruction) {
    if (parseInstructionType(instruction) == A_INSTRUCTION)
    {
        return instruction.substr(1, instruction.size()-1);
    }

    else if (parseInstructionType(instruction) == L_INSTRUCTION)
    {
        return instruction.substr(1, instruction.size()-2);
    }

    else
    {
        return "";
    }
}

/**
 * Generates the binary bits of the dest part of a C-instruction
 * @param dest The destination of the instruction
 * @return A string containing the 3 binary dest bits that correspond to the given dest value.
 */
string Assembler::translateDest(InstructionDest dest) {
    map<string, string> strToBin;

    strToBin.insert(pair<InstructionDest, string> (A, "100"));
    strToBin.insert(pair<InstructionDest, string> (D, "010"));
    strToBin.insert(pair<InstructionDest, string> (M, "001"));
    strToBin.insert(pair<InstructionDest, string> (AM, "101"));
    strToBin.insert(pair<InstructionDest, string> (AD, "110"));
    strToBin.insert(pair<InstructionDest, string> (MD, "011"));
    strToBin.insert(pair<InstructionDest, string> (AMD, "111"));
    strToBin.insert(pair<InstructionDest, string> (NULL_DEST, "000"));

    if (dests.count(instruction) > 0)
    {
        return strToBin.at(instruction);
    }

    else
    {
        return "Error";
    }
}

/**
 * Generates the binary bits of the jump part of a C-instruction
 * @param jump The jump condition for the instruction
 * @return A string containing the 3 binary jump bits that correspond to the given jump value.
 */
string Assembler::translateJump(InstructionJump jump) {

    map<string, string> stringToBin;

    stringToBin.insert(pair<InstructionJump, string> (NULL_JUMP, "000"));
    stringToBin.insert(pair<InstructionJump, string> (JGT, "001"));
    stringToBin.insert(pair<InstructionJump, string> (JEQ, "010"));
    stringToBin.insert(pair<InstructionJump, string> (JGE, "011"));
    stringToBin.insert(pair<InstructionJump, string> (JLT, "100"));
    stringToBin.insert(pair<InstructionJump, string> (JNE, "101"));
    stringToBin.insert(pair<InstructionJump, string> (JLE, "110"));
    stringToBin.insert(pair<InstructionJump, string> (JMP, "111"));

    if (jumps.count(instruction) > 0)
    {
        return stringToBin.at(instruction);
    }

    else
    {
        return "Error";
    }
}

/**
 * Generates the binary bits of the computation/op-code part of a C-instruction
 * @param comp The computation/op-code for the instruction
 * @return A string containing the 7 binary computation/op-code bits that correspond to the given comp value.
 */
string Assembler::translateComp(InstructionComp comp) {
    map<string, string> strToBin;

    strToBin.insert(pair<InstructionComp, string> (CONST_0, "0101010"));
    strToBin.insert(pair<InstructionComp, string> (CONST_1, "0111111"));
    strToBin.insert(pair<InstructionComp, string> (CONST_NEG_1, "0111010"));
    strToBin.insert(pair<InstructionComp, string> (D, "0001100"));
    strToBin.insert(pair<InstructionComp, string> (A, "0110000"));
    strToBin.insert(pair<InstructionComp, string> (NOT_D, "0001101"));
    strToBin.insert(pair<InstructionComp, string> (NOT_A, "0110001"));
    strToBin.insert(pair<InstructionComp, string> (NEG_D, "0001111"));
    strToBin.insert(pair<InstructionComp, string> (NEG_A, "0110011"));
    strToBin.insert(pair<InstructionComp, string> (D_ADD_1, "0011111"));
    strToBin.insert(pair<InstructionComp, string> (A_ADD_1, "0110111"));
    strToBin.insert(pair<InstructionComp, string> (D_SUB_1, "0001110"));
    strToBin.insert(pair<InstructionComp, string> (A_SUB_1, "0110010"));
    strToBin.insert(pair<InstructionComp, string> (D_ADD_A, "0000010"));
    strToBin.insert(pair<InstructionComp, string> (D_SUB_A, "0010011"));
    strToBin.insert(pair<InstructionComp, string> (A_SUB_D, "0000111"));
    strToBin.insert(pair<InstructionComp, string> (D_AND_A, "0000000"));
    strToBin.insert(pair<InstructionComp, string> (D_OR_A, "0010101"));
    strToBin.insert(pair<InstructionComp, string> (M, "1110000"));
    strToBin.insert(pair<InstructionComp, string> (NOT_M, "1110001"));
    strToBin.insert(pair<InstructionComp, string> (NEG_M, "1110011"));
    strToBin.insert(pair<InstructionComp, string> (M_ADD_1, "1110111"));
    strToBin.insert(pair<InstructionComp, string> (M_SUB_1, "1110010"));
    strToBin.insert(pair<InstructionComp, string> (D_ADD_M, "1000010"));
    strToBin.insert(pair<InstructionComp, string> (D_SUB_M, "1010011"));
    strToBin.insert(pair<InstructionComp, string> (M_SUB_D, "1000111"));
    strToBin.insert(pair<InstructionComp, string> (D_AND_M, "1000000"));
    strToBin.insert(pair<InstructionComp, string> (D_OR_M, "1010101"));

    if (comps.count(instruction) > 0)
    {
        return strToBin.at(instruction);
    }
    
    else
    {
        return "Error";
    }
}

/**
 * Generates the binary bits for an A-instruction, parsing the value, or looking up the symbol name.
 * @param symbol A string containing either a label name, a variable name, or a constant integer value
 * @param symbolTable The symbol table for looking up label/variable names
 * @return A string containing the 15 binary bits that correspond to the given sybmol.
 */
string Assembler::translateSymbol(string symbol, SymbolTable* symbolTable) {
    if ((symbol[0] == '0') or (symbol[0] == '1') or (symbol[0] == '2') or (symbol[0] == '3') or (symbol[0] == '4') or (symbol[0] == '5') or (symbol[0] == '6') or (symbol[0] == '7') or (symbol[0] == '8') or (symbol[0] == '9'))
    {
        int dec = stoi(symbol);

        string output = "";

        while (dec > 0)
        {
            if (dec % 2 == 0)
            {
                output = "0" + output;
                dec = dec / 2;
            }

            else
            {
                output = "1" + output;
                dec = (dec - 1) / 2;
            }
        }

        while (output.length() < 15)
        {
            output = "0" + output;
        }

        return output;
    }

    else
    {
        string temp = symbolTable->getSymbol(symbol);

        int dec = stoi(temp);

        string output = "";

        while (dec > 0)
        {
            if (dec % 2 == 0)
            {
                output = "0" + output;
                dec = dec / 2;
            }

            else
            {
                output = "1" + output;
                dec = (dec - 1) / 2;
            }
        }

        while (output.length() < 15)
        {
            output = "0" + output;
        }

        return output;
    }
}
