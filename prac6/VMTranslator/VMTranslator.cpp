#include <string>

#include "VMTranslator.h"

using namespace std;

int VMTranslator::logic_calls = 0;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){

    string out = "";

    if (segment.compare("constant") == 0)
    {
        out += "@" + to_string(offset) + "\n";
        out += "D=A\n";
    }

    else if (segment.compare("static") == 0)
    {
        int loc = 16 + offset;
        out += "@" + to_string(loc) + "\n";
        out += "D=M\n";
        
    }

    else if (segment.compare("argument") == 0)
    {
        out += "@ARG\n";
        out += "D=M\n";
        out += "@" + to_string(offset) + "\n";
        out += "A=D+A\n";
        out += "D=M\n";
    }

    else if (segment.compare("local") == 0)
    {
        out += "@LCL\n";
        out += "D=M\n";
        out += "@" + to_string(offset) + "\n";
        out += "A=D+A\n";
        out += "D=M\n";
    }

    else if (segment.compare("this") == 0)
    {
        out += "@THIS\n";
        out += "D=M\n";
        out += "@" + to_string(offset) + "\n";
        out += "A=D+A\n";
        out += "D=M\n";
    }

    else if (segment.compare("that") == 0)
    {
        out += "@THAT\n";
        out += "D=M\n";
        out += "@" + to_string(offset) + "\n";
        out += "A=D+A\n";
        out += "D=M\n";
    }

    else if (segment.compare("pointer") == 0)
    {
        int loc = 3 + offset;
        out += "@" + to_string(loc) + "\n";
        out += "D=M\n";
    }

    else if (segment.compare("temp") == 0)
    {
        int loc = 5 + offset;
        out += "@" + to_string(loc) + "\n";
        out += "D=M\n";
    }

    else
    {
        out += "error\n";
    }
    

    out += "@SP\n";
    out += "A=M\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "M=M+1\n";

    return out;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){   

    string out = "";

    if (segment.compare("argument") == 0)
    {
        out += "@ARG\n";
        out += "D=M\n";
        out += "@" + to_string(offset) + "\n";
        out += "D=D+A\n";
    }

    else if (segment.compare("static") == 0)
    {
        int loc = 16 + offset;
        out += "@" + to_string(loc) + "\n";
        out += "D=A\n";
    }

    else if (segment.compare("local") == 0)
    {
        out += "@LCL\n";
        out += "D=M\n";
        out += "@" + to_string(offset) + "\n";
        out += "D=D+A\n";
    }

    else if (segment.compare("this") == 0)
    {
        out += "@THIS\n";
        out += "D=M\n";
        out += "@" + to_string(offset) + "\n";
        out += "D=D+A\n";
    }

    else if (segment.compare("that") == 0)
    {
        out += "@THAT\n";
        out += "D=M\n";
        out += "@" + to_string(offset) + "\n";
        out += "D=D+A\n";
    }

    else if (segment.compare("pointer") == 0)
    {
        int loc = 3 + offset;
        out += "@" + to_string(loc) + "\n";
        out += "D=A\n";
    }

    else if (segment.compare("temp") == 0)
    {
        int loc = 5 + offset;
        out += "@" + to_string(loc) + "\n";
        out += "D=A\n";
    }

    else
    {
        return "error";
    }

    out += "@R13\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "A=M\n";
    out += "M=D\n";

    return out;
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){

    string out = "";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R14\n";
    out += "M=D\n";
    out += "@R14\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "D=D+M\n";
    out += "@SP\n";
    out += "A=M\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "M=M+1\n";

    return out;
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    
    string out = "";

    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R14\n";
    out += "M=D\n";
    out += "@R14\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "D=D-M\n";
    out += "@SP\n";
    out += "A=M\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "M=M+1\n";

    return out;
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){

    string out = "";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "D=-D\n";
    out += "@SP\n";
    out += "A=M\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "M=M+1\n";

    return out;
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    
    string out = "";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R14\n";
    out += "M=D\n";
    out += "@R14\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "D=D-M\n";
    out += "@TRUE_" + to_string(logic_calls) + "\n";
    out += "D;JEQ\n";
    out += "@0\n";
    out += "D=A\n";
    out += "@END_" + to_string(logic_calls) + "\n";
    out += "0;JMP\n";
    out += "(TRUE_" + to_string(logic_calls) + ")" + "\n";
    out += "@1\n";
    out += "D=A\n";
    out += "D=-D\n";
    out += "(END_" + to_string(logic_calls) + ")" + "\n";
    out += "@SP\n";
    out += "A=M\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "M=M+1\n";

    logic_calls++;

    return out;

}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){

    string out = "";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R14\n";
    out += "M=D\n";
    out += "@R14\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "D=D-M\n";
    out += "@TRUE_" + to_string(logic_calls) + "\n";
    out += "D;JGT\n";
    out += "@0\n";
    out += "D=A\n";
    out += "@END_" + to_string(logic_calls) + "\n";
    out += "0;JMP\n";
    out += "(TRUE_" + to_string(logic_calls) + ")" + "\n";
    out += "@1\n";
    out += "D=A\n";
    out += "D=-D\n";
    out += "(END_" + to_string(logic_calls) + ")" + "\n";
    out += "@SP\n";
    out += "A=M\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "M=M+1\n";

    logic_calls++;

    return out;
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){

    string out = "";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R14\n";
    out += "M=D\n";
    out += "@R14\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "D=D-M\n";
    out += "@TRUE_" + to_string(logic_calls) + "\n";
    out += "D;JLT\n";
    out += "@0\n";
    out += "D=A\n";
    out += "@END_" + to_string(logic_calls) + "\n";
    out += "0;JMP\n";
    out += "(TRUE_" + to_string(logic_calls) + ")" + "\n";
    out += "@1\n";
    out += "D=A\n";
    out += "D=-D\n";
    out += "(END_" + to_string(logic_calls) + ")" + "\n";
    out += "@SP\n";
    out += "A=M\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "M=M+1\n";

    logic_calls++;

    return out;
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){

    string out = "";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R14\n";
    out += "M=D\n";
    out += "@R14\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "D=D&M\n";
    out += "@SP\n";
    out += "A=M\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "M=M+1\n";

    return out;
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){

    string out = "";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@R14\n";
    out += "M=D\n";
    out += "@R14\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "D=D|M\n";
    out += "@SP\n";
    out += "A=M\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "M=M+1\n";

    return out;
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){

    string out = "";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "D=!D\n";
    out += "@SP\n";
    out += "A=M\n";
    out += "M=D\n";
    out += "@SP\n";
    out += "M=M+1\n";

    return out;
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    string out = "";
    out += "(" + label + ")\n";
    return out;
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){

    string out = "";
    out += "@" + label + "\n";
    out += "0;JMP\n";

    return out;
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){

    string out = "";
    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@" + label + "\n";
    out += "D;JNE\n";

    return out;
    
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){

    string out = "";

    out += "(" + function_name + ")\n";
    
    for (int i = 0 ; i < n_vars; i++)
    {
        out += "@SP\n";
        out += "AM=M+1\n";
        out += "A=A-1\n";
        out += "M=0\n";
    }
    
    return out;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){

    string out = "";

    out += "@return_address\n";
    out += "D=A\n";
    out += "@SP\n";
    out += "AM=M+1\n";
    out += "A=A-1\n";
    out += "M=D\n";

    //return address pushed

    out += "@LCL\n";
    out += "D=M\n";
    out += "@SP\n";
    out += "AM=M+1\n";
    out += "A=A-1\n";
    out += "M=D\n";

    //pushed LCL to stack

    out += "@ARG\n";
    out += "D=M\n";
    out += "@SP\n";
    out += "AM=M+1\n";
    out += "A=A-1\n";
    out += "M=D\n";

    //pushed ARG to stack

    out += "@THIS\n";
    out += "D=M\n";
    out += "@SP\n";
    out += "AM=M+1\n";
    out += "A=A-1\n";
    out += "M=D\n";

    //pushed THIS to stack

    out += "@THAT\n";
    out += "D=M\n";
    out += "@SP\n";
    out += "AM=M+1\n";
    out += "A=A-1\n";
    out += "M=D\n";

    //pushed THAT to stack

    out += "@SP\n";
    out += "D=M\n";
    out += "@5\n";
    out += "D=D-A\n";
    out += "@" + to_string(n_args) + "\n";
    out += "D=D-A\n";
    out += "@ARG\n";
    out += "M=D\n";

    //ARG = SP-5-nArgs

    out += "@SP\n";
    out += "D=M\n";
    out += "@LCL\n";
    out += "M=D\n";

    //LCL = SP
    
    out += "@" + function_name + "\n";
    out += "0;JMP\n";

    out += "(return_address)\n";

    return out;
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){

    string out = "";

    out += "@LCL\n";
    out += "D=M\n";
    out += "@R13\n";
    out += "M=D\n";

    //frame = LCL stored in R13

    out += "@R13\n";
    out += "D=M\n";
    out += "@5\n";
    out += "A=D-A\n";
    out += "D=M\n";
    out += "@R14\n";
    out += "M=D\n";

    //retAddress = *(frame-5)

    out += "@SP\n";
    out += "AM=M-1\n";
    out += "D=M\n";
    out += "@ARG\n";
    out += "A=M\n";
    out += "M=D\n";

    //*ARG = pop()

    out += "@ARG\n";
    out += "D=M+1\n";
    out += "@SP\n";
    out += "M=D\n";

    //SP = ARG+1

    out += "@R13\n";
    out += "D=M\n";
    out += "@1\n";
    out += "A=D-A\n";
    out += "D=M\n";
    out += "@THAT\n";
    out += "M=D\n";

    //THAT=*(frame-1)

    out += "@R13\n";
    out += "D=M\n";
    out += "@2\n";
    out += "A=D-A\n";
    out += "D=M\n";
    out += "@THIS\n";
    out += "M=D\n";

    //THIS=*(frame-2)

    out += "@R13\n";
    out += "D=M\n";
    out += "@3\n";
    out += "A=D-A\n";
    out += "D=M\n";
    out += "@ARG\n";
    out += "M=D\n";

    //ARG=*(frame-3)

    out += "@R13\n";
    out += "D=M\n";
    out += "@4\n";
    out += "A=D-A\n";
    out += "D=M\n";
    out += "@LCL\n";
    out += "M=D\n";

    //LCL=*(frame-1)

    out += "@R14\n";
    out += "A=M\n";
    out += "0;JMP\n";

    return out;


}