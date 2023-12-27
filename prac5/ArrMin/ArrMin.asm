// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

    @R1
    D=M
    A=D
    D=M
    @min
    M=D
    @R2
    D=M
    @STORE
    D;JLE
(LOOP)
    @min
    D=M
    @MINPOS
    D;JGT
    @MINLTE
    0;JMP
(MINPOS)
    @R1
    D=M
    A=D
    D=M
    @SAMESIGN
    D;JGT
    @MINLARGER
    0;JMP
(MINLTE)
    @R1
    D=M
    A=D
    D=M
    @TOLOOP
    D;JGT
    @SAMESIGN
    0;JMP
(SAMESIGN)
    @R1
    D=M
    A=D
    D=M
    @min
    D=M-D
    @MINLARGER
    D;JGT
    @TOLOOP
    0;JMP
(MINLARGER)
    @R1
    D=M
    A=D
    D=M
    @min
    M=D
(TOLOOP)
    @R1
    M=M+1
    @R2
    M=M-1
    D=M
    @LOOP
    D;JGT
(STORE)
    @min
    D=M
    @R0
    M=D
(END)
    @END
    0;JMP