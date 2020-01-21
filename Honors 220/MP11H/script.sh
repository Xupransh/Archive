#!/bin/bash
make
cat test.c | ./c220 > code.asm
lc3as code.asm
lc3sim code.obj

