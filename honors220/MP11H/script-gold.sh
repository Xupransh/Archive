#!/bin/bash

cat tests/testprog.c | ./c220-gold > code-gold.asm
lc3as code-gold.asm
lc3sim code-gold.obj

make
cat tests/testprog.c | ./c220 > code.asm
lc3as code.asm
lc3sim code.obj

