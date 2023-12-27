#include "Assembler.h"
#include "SymbolTable.h"

#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <regex>
#include <fstream>

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    /*Assembler myAssembler;
    SymbolTable* symbols = new SymbolTable();*/

    /*@R1
    D=M
    @R2
    D=D+M
    @R3
    D=D-M
    @R0
    M=D
    (END)
    @END
    0;JMP*/

    /*cout << myAssembler.parseInstructionType("@124353") << endl;
    cout << myAssembler.parseInstructionType("(ASDSAD)") << endl;
    cout << myAssembler.parseInstructionType("AMD=10") << endl;
    cout << myAssembler.parseInstructionType("PLEASE") << endl;*/

    /*cout << myAssembler.parseInstructionDest("D=M") << endl;
    cout << myAssembler.parseInstructionDest("MD=D+M") << endl;
    cout << myAssembler.parseInstructionDest("AD=D-M") << endl;
    cout << myAssembler.parseInstructionDest("AMD=D") << endl;*/

    /*cout << myAssembler.parseInstructionJump("0;JMP") << endl;
    cout << myAssembler.parseInstructionJump("D;JGT") << endl;
    cout << myAssembler.parseInstructionJump("D=M") << endl;
    cout << myAssembler.parseInstructionJump("A=M;JEQ") << endl;*/

    /*cout << myAssembler.parseInstructionComp("D=M") << endl;
    cout << myAssembler.parseInstructionComp("D=D+M") << endl;
    cout << myAssembler.parseInstructionComp("D=D-M") << endl;
    cout << myAssembler.parseInstructionComp("0;JMP") << endl;
    cout << myAssembler.parseInstructionComp("WHY?") << endl;*/

    /*cout << myAssembler.parseSymbol("(ONE)") << endl;
    cout << myAssembler.parseSymbol("@TWO") << endl;
    cout << myAssembler.parseSymbol("@3") << endl;
    cout << myAssembler.parseSymbol("(4)") << endl;
    cout << myAssembler.parseSymbol("what?") << endl;*/

    /*cout << myAssembler.translateDest(Assembler::A) << endl;
    cout << myAssembler.translateDest(Assembler::M) << endl;
    cout << myAssembler.translateDest(Assembler::D) << endl;
    cout << myAssembler.translateDest(Assembler::NULL_DEST) << endl;
    cout << myAssembler.translateDest(Assembler::AMD) << endl;
    cout << myAssembler.translateDest(Assembler::MD) << endl;*/

    /*cout << myAssembler.translateJump(Assembler::JMP) << endl;
    cout << myAssembler.translateJump(Assembler::JNE) << endl;
    cout << myAssembler.translateJump(Assembler::JLE) << endl;
    cout << myAssembler.translateJump(Assembler::JGT) << endl;
    cout << myAssembler.translateJump(Assembler::JEQ) << endl;
    cout << myAssembler.translateJump(Assembler::JGE) << endl;*/

    /*cout << myAssembler.translateComp(Assembler::CONST_0) << endl;
    cout << myAssembler.translateComp(Assembler::CONST_1) << endl;
    cout << myAssembler.translateComp(Assembler::CONST_NEG_1) << endl; 
    cout << myAssembler.translateComp(Assembler::VAL_D) << endl;
    cout << myAssembler.translateComp(Assembler::VAL_A) << endl;
    cout << myAssembler.translateComp(Assembler::NOT_D) << endl;
    cout << myAssembler.translateComp(Assembler::NOT_A) << endl;
    cout << myAssembler.translateComp(Assembler::NEG_D) << endl;
    cout << myAssembler.translateComp(Assembler::NEG_A) << endl;*/


    /*cout << symbols.getSymbol("R0") << endl;

    symbols.addSymbol("twothousand", 2000);
    symbols.addSymbol("thousand", 1000);
    symbols.addSymbol("hundred", 100);

    cout << symbols.getSymbol("twothousand") << endl;
    cout << symbols.getSymbol("thousand") << endl;
    cout << symbols.getSymbol("hundred") << endl;*/

    /*cout << myAssembler.translateSymbol("128", symbols) << endl;
    cout << myAssembler.translateSymbol("64", symbols) << endl;
    cout << myAssembler.translateSymbol("R0", symbols) << endl;
    cout << myAssembler.translateSymbol("THIS", symbols) << endl;*/

    /*string temp = "D=M";



    cout << myAssembler.generateMachineCode(symbols, &temp, 1) << endl;*/

    vector<string> instructionList;

        if (argc > 1) 
        {
            SymbolTable symbolTable;
            Assembler assembler;
            vector<string> instructionList;

            // Open file
            fstream file;
            string fname = argv[1];
            file.open(argv[1], ios::in);
            if (file.is_open()) 
            {
                // Read line-by-line
                string line;
                while (getline(file, line)) {
                    /* remove comments */
                    string::size_type idx = line.find("//");  // find start of "//"
                    string lineRmComm = line.substr(0, idx);
                    if (lineRmComm.size() == 0) continue;  // skip empty line
                    /* remove spaces */
                    string::iterator str_iter = remove(lineRmComm.begin(), lineRmComm.end(), ' ');
                    lineRmComm.erase(str_iter, lineRmComm.end());
                    instructionList.push_back(lineRmComm);
                }
                file.close();
            }
            // Get array of instruction

            string instructions[instructionList.size()];
            copy(instructionList.begin(), instructionList.end(), instructions);

            // First pass
            assembler.buildSymbolTable(&symbolTable, instructions, instructionList.size());

            /*for (int i = 0; i < instructionList.size(); i++)
            {
                string code = "";
                
                cout << instructions[i] << endl;

                for (int j = 0; i < instructions[i].size(); j++)
                {
                    cout << int(instructions[i][j]) << " ";
                }

                cout << endl;

                if (assembler.parseInstructionType(instructions[i]) == Assembler::A_INSTRUCTION)
                {
                    code += "0";

                    code += assembler.translateSymbol(assembler.parseSymbol(instructions[i]), &symbolTable);

                    cout << code << endl;;
                }

                else if (assembler.parseInstructionType(instructions[i]) == Assembler::C_INSTRUCTION)
                {
                    code += "111";

                    code += assembler.translateComp(assembler.parseInstructionComp(instructions[i]));
                    code += assembler.translateDest(assembler.parseInstructionDest(instructions[i]));
                    code += assembler.translateJump(assembler.parseInstructionJump(instructions[i]));

                    cout << code << endl;

                }
            }*/

            cout << instructions[2] << endl;

            for (int i = 0; i < instructions[2].size(); i++)
            {
                cout << int(instructions[2][i]) << endl;
            }

        


        }


    


    

}