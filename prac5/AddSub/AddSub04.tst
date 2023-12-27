//testing very large numbers but only for the added parts

load AddSub.asm,
output-file AddSub04.out,
compare-to AddSub04.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[3]%D2.6.2;

set PC 0,
set RAM[0] 0,
set RAM[1] 32767,
set RAM[2] 32767,
set RAM[3] 1;

repeat 100
{
    ticktock;
}

set RAM[1] 32767,
set RAM[2] 32767,
set RAM[3] 1,
output;