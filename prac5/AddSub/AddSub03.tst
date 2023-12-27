//testing handling subtracting negatives

load AddSub.asm,
output-file AddSub03.out,
compare-to AddSub03.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[3]%D2.6.2;

set PC 0,
set RAM[0] 0,
set RAM[1] 10,
set RAM[2] 25,
set RAM[3] -100;

repeat 100
{
    ticktock;
}

set RAM[1] 10,
set RAM[2] 25,
set RAM[3] -100,
output;