// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@neg
M=1 
@store
M=0
@R2
D=M
@FIN
D;JEQ
@R1
D=M
@LOOP
D;JGE
@R1
M=-M
@neg
M=-1
(LOOP)
@R1
D=M
@TEST
D;JEQ
@store
D=M
@R2
D=D+M
@store
M=D
@R1
M=M-1
@LOOP
0;JMP
(TEST)
@neg
D=M
@FIN
D;JGT
@store
M=-M
(FIN)
@store
D=M
@R0
M=D
(END)
@END
0;JMP

