.ORIG x3000
LEA R6,STACK
LEA R1,STRING
ADD R2,R1,#1
PART1 LDR R0,R1,#0
BRz PART2
ADD R6,R6,#-1
STR R0,R6,#0
ADD R1,R1,#2
BRnzp PART1
PART2 LDR R0,R6,#0
ADD R6,R6,#1
OUT
LDR R0,R2,#0
OUT
ADD R2,R2,#2
LDR R0,R2,#-1
BRnp PART2
HALT
STRING .STRINGZ "SOOGTALUTARINNC!"
.BLKW #20
STACK
.END