;---------------------------------------------------------------------------
; 
; WARNING!  This code was produced automatically using the ECE190 C compiler
; (MP5 in the Spring 2008 semester).  If you choose to modify it by hand,
; be aware that you WILL LOSE such changes when the code is recompiled.
;
; Student-generated code is marked as "STUDENT CODE."
;
;---------------------------------------------------------------------------

	.ORIG x3000

BOGUSFP
	LD	R4,GDPTR
	LEA	R5,BOGUSFP
	LD	R6,SPTR
	JSR	MAIN
	LEA	R0,OUTPREFIX
	PUTS
	LDR	R0,R6,#0
	ADD	R6,R6,#1
	LD	R1,PNPTR
	JSRR	R1
	AND	R0,R0,#0
	ADD	R0,R0,#10
	OUT
	HALT

GDPTR	.FILL GLOBDATA
SPTR	.FILL STACK
PNPTR	.FILL PRINT_NUM
OUTPREFIX	.STRINGZ "main returned "

MAIN	ADD	R6,R6,#-3
	STR	R5,R6,#0
	STR	R7,R6,#1
	ADD	R5,R6,#-1

;---------------------------------------------------------------------------
; local variable space allocation
;---------------------------------------------------------------------------

	ADD R6,R6,#-7

;---------------------------------------------------------------------------
; R0...R3 are callee-saved
;---------------------------------------------------------------------------

	ADD	R6,R6,#-4
	STR	R0,R6,#0	; save R0...R3
	STR	R1,R6,#1
	STR	R2,R6,#2
	STR	R3,R6,#3
	
;---------------------------------------------------------------------------
; STUDENT CODE STARTS HERE (after the symbol table)
;---------------------------------------------------------------------------

;                piles[3]        global          offset=+0
;                 seed           local to main   offset=+0
;                    i           local to main   offset=-1
;                    j           local to main   offset=-2
;                 done           local to main   offset=-3
;            choice_ok           local to main   offset=-4
;                 pnum           local to main   offset=-5
;                  amt           local to main   offset=-6
	LEA R0,LBL2
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL3
LBL2
	.STRINGZ "Please type a number: "
LBL3
	LD R0,LBL4
	JSRR R0
	BRnzp LBL5
LBL4
	.FILL PRINTF
LBL5
	LDR R1,R6,#0
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
	LD R0,LBL7
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL8
LBL7
	.FILL #1
LBL8
	LD R2,LBL9
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL10
LBL9
	.FILL #0
LBL10
	STR R3,R6,#0
	LEA R0,LBL11
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL12
LBL11
	.STRINGZ "%d"
LBL12
	LD R0,LBL13
	JSRR R0
	BRnzp LBL14
LBL13
	.FILL SCANF 
LBL14
	LDR R1,R6,#0
	ADD R6,R6,#1
	ADD R6,R6,#1
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRz LBL6
	ADD R2,R2,#1
LBL6
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRz LBL17
	LD R3,LBL16
	JMP R3
LBL16
	.FILL LBL15
LBL17
	;  LBL20
	LD R3,LBL19
	JMP R3
LBL19
	.FILL LBL18
LBL20
LBL15
	LEA R0,LBL21
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL22
LBL21
	.STRINGZ "That's not a number!\n"
LBL22
	LD R0,LBL23
	JSRR R0
	BRnzp LBL24
LBL23
	.FILL PRINTF
LBL24
	LDR R1,R6,#0
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
	LD R0,LBL25
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL26
LBL25
	.FILL #3
LBL26
	LDR R0,R6,#0
	STR R0,R5,#3
	;  LBL28
	LD R3,LBL27
	JMP R3
LBL27
	.FILL LBL1
LBL28
LBL18
	LD R2,LBL29
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL30
LBL29
	.FILL #0
LBL30
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R0, LBL31
	JSRR R0
	BRnzp LBL32
LBL31
	.FILL SRAND
LBL32
	LDR R1,R6,#0
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
	LD R0,LBL33
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL34
LBL33
	.FILL #0
LBL34
	LD R2,LBL35
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL36
LBL35
	.FILL #-1
LBL36
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
LBL37
	LD R0,LBL39
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL40
LBL39
	.FILL #3
LBL40
	LD R2,LBL41
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL42
LBL41
	.FILL #-1
LBL42
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnz LBL38
	ADD R2,R2,#1
LBL38
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRnp LBL45
	LD R3,LBL44
	JMP R3
LBL44
	.FILL LBL43
LBL45
	LD R0,LBL46
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL47
LBL46
	.FILL #5
LBL47
	LD R0,LBL50
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL51
LBL50
	.FILL #10
LBL51
	LD R0, LBL52
	JSRR R0
	BRnzp LBL53
LBL52
	.FILL RAND
LBL53
	LDR R1,R6,#0
	STR R1,R6,#0
	LDR R1,R6,#1
	LDR R0,R6,#0
	ADD R6,R6,#2
	LD R3, LBL49
	JSRR R3
	BRnzp LBL48
LBL49
	.FILL MODULUS
LBL48
	ADD R6,R6,#-1
	STR R0,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R0,R1,R0
	ADD R6,R6,#1
	STR R0,R6,#0
	LD R2,LBL56
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL57
LBL56
	.FILL #-1
LBL57
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL54
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL55
LBL54
	.FILL #0
LBL55
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
	LD R2,LBL58
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL59
LBL58
	.FILL #-1
LBL59
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	ADD R1,R1,#1
	STR R1,R3,#0
	ADD R6,R6,#1
	;  LBL61
	LD R3,LBL60
	JMP R3
LBL60
	.FILL LBL37
LBL61
LBL43
	LD R0,LBL62
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL63
LBL62
	.FILL #0
LBL63
	LD R2,LBL64
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL65
LBL64
	.FILL #-3
LBL65
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
LBL66
	LD R0,LBL68
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL69
LBL68
	.FILL #0
LBL69
	LD R2,LBL70
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL71
LBL70
	.FILL #-3
LBL71
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnp LBL67
	ADD R2,R2,#1
LBL67
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRnp LBL74
	LD R3,LBL73
	JMP R3
LBL73
	.FILL LBL72
LBL74
	LD R0,LBL75
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL76
LBL75
	.FILL #0
LBL76
	LD R2,LBL77
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL78
LBL77
	.FILL #-1
LBL78
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
LBL79
	LD R0,LBL81
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL82
LBL81
	.FILL #3
LBL82
	LD R2,LBL83
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL84
LBL83
	.FILL #-1
LBL84
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnz LBL80
	ADD R2,R2,#1
LBL80
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRnp LBL87
	LD R3,LBL86
	JMP R3
LBL86
	.FILL LBL85
LBL87
	LD R0,LBL88
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL89
LBL88
	.FILL #1
LBL89
	LD R2,LBL90
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL91
LBL90
	.FILL #-1
LBL91
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R0,R1,R0
	ADD R6,R6,#1
	STR R0,R6,#0
	LEA R0,LBL92
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL93
LBL92
	.STRINGZ "Pile %d: "
LBL93
	LD R0,LBL94
	JSRR R0
	BRnzp LBL95
LBL94
	.FILL PRINTF
LBL95
	LDR R1,R6,#0
	ADD R6,R6,#1
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
	LD R0,LBL96
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL97
LBL96
	.FILL #0
LBL97
	LD R2,LBL98
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL99
LBL98
	.FILL #-2
LBL99
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
LBL100
	LD R2,LBL104
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL105
LBL104
	.FILL #-1
LBL105
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL102
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL103
LBL102
	.FILL #0
LBL103
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL106
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL107
LBL106
	.FILL #-2
LBL107
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnz LBL101
	ADD R2,R2,#1
LBL101
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRnp LBL110
	LD R3,LBL109
	JMP R3
LBL109
	.FILL LBL108
LBL110
	LEA R0,LBL111
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL112
LBL111
	.STRINGZ "*"
LBL112
	LD R0,LBL113
	JSRR R0
	BRnzp LBL114
LBL113
	.FILL PRINTF
LBL114
	LDR R1,R6,#0
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
	LD R2,LBL115
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL116
LBL115
	.FILL #-2
LBL116
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	ADD R1,R1,#1
	STR R1,R3,#0
	ADD R6,R6,#1
	;  LBL118
	LD R3,LBL117
	JMP R3
LBL117
	.FILL LBL100
LBL118
LBL108
	LEA R0,LBL119
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL120
LBL119
	.STRINGZ "\n"
LBL120
	LD R0,LBL121
	JSRR R0
	BRnzp LBL122
LBL121
	.FILL PRINTF
LBL122
	LDR R1,R6,#0
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
	LD R2,LBL123
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL124
LBL123
	.FILL #-1
LBL124
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	ADD R1,R1,#1
	STR R1,R3,#0
	ADD R6,R6,#1
	;  LBL126
	LD R3,LBL125
	JMP R3
LBL125
	.FILL LBL79
LBL126
LBL85
	LD R0,LBL127
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL128
LBL127
	.FILL #0
LBL128
	LD R2,LBL129
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL130
LBL129
	.FILL #-4
LBL130
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
LBL131
	LD R0,LBL133
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL134
LBL133
	.FILL #0
LBL134
	LD R2,LBL135
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL136
LBL135
	.FILL #-4
LBL136
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnp LBL132
	ADD R2,R2,#1
LBL132
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRnp LBL139
	LD R3,LBL138
	JMP R3
LBL138
	.FILL LBL137
LBL139
	LEA R0,LBL140
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL141
LBL140
	.STRINGZ "From which pile will you take sticks? "
LBL141
	LD R0,LBL142
	JSRR R0
	BRnzp LBL143
LBL142
	.FILL PRINTF
LBL143
	LDR R1,R6,#0
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
; --------------- DEBUG(3) ---------------
	LD R0,LBL145
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL146
LBL145
	.FILL #1
LBL146
	LD R2,LBL147
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL148
LBL147
	.FILL #-5
LBL148
	STR R3,R6,#0
	LEA R0,LBL149
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL150
LBL149
	.STRINGZ "%d"
LBL150
	LD R0,LBL151
	JSRR R0
	BRnzp LBL152
LBL151
	.FILL SCANF 
LBL152
	LDR R1,R6,#0
	ADD R6,R6,#1
	ADD R6,R6,#1
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRz LBL144
	ADD R2,R2,#1
LBL144
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRz LBL162
	LD R3,LBL161
	JMP R3
LBL161
	.FILL LBL155
LBL162
	LD R0,LBL164
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL165
LBL164
	.FILL #0
LBL165
	LD R0,LBL168
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL169
LBL168
	.FILL #1
LBL169
	LD R2,LBL170
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL171
LBL170
	.FILL #-5
LBL171
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#1
	NOT R1,R1
	ADD R1,R1,#1
	LDR R0,R6,#0
	ADD R0,R1,R0
	ADD R6,R6,#1
	STR R0,R6,#0
	LD R2,LBL166
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL167
LBL166
	.FILL #0
LBL167
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnp LBL163
	ADD R2,R2,#1
LBL163
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRz LBL156
LBL155
	AND R1,R1,#0
	ADD R1,R1,#1
	BRnzp LBL159
LBL156
	ADD R6,R6,#1
	AND R1,R1,#0
LBL159
	STR R1,R6,#0
	LDR R1,R6,#0
	BRz LBL181
	LD R3,LBL180
	JMP R3
LBL180
	.FILL LBL174
LBL181
	LD R0,LBL183
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL184
LBL183
	.FILL #1
LBL184
	LD R2,LBL185
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL186
LBL185
	.FILL #-5
LBL186
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnz LBL182
	ADD R2,R2,#1
LBL182
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRz LBL175
LBL174
	AND R1,R1,#0
	ADD R1,R1,#1
	BRnzp LBL178
LBL175
	ADD R6,R6,#1
	AND R1,R1,#0
LBL178
	STR R1,R6,#0
	LDR R1,R6,#0
	BRz LBL196
	LD R3,LBL195
	JMP R3
LBL195
	.FILL LBL189
LBL196
	LD R0,LBL198
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL199
LBL198
	.FILL #3
LBL199
	LD R2,LBL200
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL201
LBL200
	.FILL #-5
LBL201
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRzp LBL197
	ADD R2,R2,#1
LBL197
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRz LBL190
LBL189
	AND R1,R1,#0
	ADD R1,R1,#1
	BRnzp LBL193
LBL190
	ADD R6,R6,#1
	AND R1,R1,#0
LBL193
	STR R1,R6,#0
	LDR R1,R6,#0
	BRz LBL204
	LD R3,LBL203
	JMP R3
LBL203
	.FILL LBL202
LBL204
	LD R0,LBL205
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL206
LBL205
	.FILL #1
LBL206
	LD R2,LBL207
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL208
LBL207
	.FILL #-4
LBL208
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
	LD R0,LBL209
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL210
LBL209
	.FILL #1
LBL210
	LD R2,LBL211
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL212
LBL211
	.FILL #-5
LBL212
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#1
	NOT R1,R1
	ADD R1,R1,#1
	LDR R0,R6,#0
	ADD R0,R1,R0
	ADD R6,R6,#1
	STR R0,R6,#0
	LD R2,LBL213
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL214
LBL213
	.FILL #-5
LBL214
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
	;  LBL217
	LD R3,LBL216
	JMP R3
LBL216
	.FILL LBL215
LBL217
LBL202
	LEA R0,LBL218
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL219
LBL218
	.STRINGZ "That's not a good choice.\n"
LBL219
	LD R0,LBL220
	JSRR R0
	BRnzp LBL221
LBL220
	.FILL PRINTF
LBL221
	LDR R1,R6,#0
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
LBL215
	;  LBL223
	LD R3,LBL222
	JMP R3
LBL222
	.FILL LBL131
LBL223
LBL137
	LD R0,LBL224
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL225
LBL224
	.FILL #0
LBL225
	LD R2,LBL226
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL227
LBL226
	.FILL #-4
LBL227
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
LBL228
	LD R0,LBL230
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL231
LBL230
	.FILL #0
LBL231
	LD R2,LBL232
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL233
LBL232
	.FILL #-4
LBL233
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnp LBL229
	ADD R2,R2,#1
LBL229
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRnp LBL236
	LD R3,LBL235
	JMP R3
LBL235
	.FILL LBL234
LBL236
; --------------- DEBUG(1) ---------------
	LD R0,LBL237
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL238
LBL237
	.FILL #1
LBL238
	LD R2,LBL239
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL240
LBL239
	.FILL #-5
LBL240
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R0,R1,R0
	ADD R6,R6,#1
	STR R0,R6,#0
	LEA R0,LBL241
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL242
LBL241
	.STRINGZ "How many sticks will you take from pile %d? "
LBL242
	LD R0,LBL243
	JSRR R0
	BRnzp LBL244
LBL243
	.FILL PRINTF
LBL244
	LDR R1,R6,#0
	ADD R6,R6,#1
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
	LD R0,LBL246
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL247
LBL246
	.FILL #1
LBL247
	LD R2,LBL248
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL249
LBL248
	.FILL #-6
LBL249
	STR R3,R6,#0
	LEA R0,LBL250
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL251
LBL250
	.STRINGZ "%d"
LBL251
	LD R0,LBL252
	JSRR R0
	BRnzp LBL253
LBL252
	.FILL SCANF 
LBL253
	LDR R1,R6,#0
	ADD R6,R6,#1
	ADD R6,R6,#1
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRz LBL245
	ADD R2,R2,#1
LBL245
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRz LBL263
	LD R3,LBL262
	JMP R3
LBL262
	.FILL LBL256
LBL263
	LD R0,LBL265
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL266
LBL265
	.FILL #0
LBL266
	LD R2,LBL267
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL268
LBL267
	.FILL #-6
LBL268
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRn LBL264
	ADD R2,R2,#1
LBL264
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRz LBL257
LBL256
	AND R1,R1,#0
	ADD R1,R1,#1
	BRnzp LBL260
LBL257
	ADD R6,R6,#1
	AND R1,R1,#0
LBL260
	STR R1,R6,#0
	LDR R1,R6,#0
	BRz LBL278
	LD R3,LBL277
	JMP R3
LBL277
	.FILL LBL271
LBL278
	LD R2,LBL282
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL283
LBL282
	.FILL #-5
LBL283
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL280
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL281
LBL280
	.FILL #0
LBL281
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL284
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL285
LBL284
	.FILL #-6
LBL285
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRzp LBL279
	ADD R2,R2,#1
LBL279
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRz LBL272
LBL271
	AND R1,R1,#0
	ADD R1,R1,#1
	BRnzp LBL275
LBL272
	ADD R6,R6,#1
	AND R1,R1,#0
LBL275
	STR R1,R6,#0
	LDR R1,R6,#0
	BRz LBL288
	LD R3,LBL287
	JMP R3
LBL287
	.FILL LBL286
LBL288
	LD R0,LBL289
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL290
LBL289
	.FILL #1
LBL290
	LD R2,LBL291
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL292
LBL291
	.FILL #-4
LBL292
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
	;  LBL295
	LD R3,LBL294
	JMP R3
LBL294
	.FILL LBL293
LBL295
LBL286
; --------------- DEBUG(2) ---------------
	LEA R0,LBL296
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL297
LBL296
	.STRINGZ "That's not a good choice.\n"
LBL297
	LD R0,LBL298
	JSRR R0
	BRnzp LBL299
LBL298
	.FILL PRINTF
LBL299
	LDR R1,R6,#0
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
LBL293
	;  LBL301
	LD R3,LBL300
	JMP R3
LBL300
	.FILL LBL228
LBL301
LBL234
	LD R2,LBL302
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL303
LBL302
	.FILL #-6
LBL303
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL306
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL307
LBL306
	.FILL #-5
LBL307
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL304
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL305
LBL304
	.FILL #0
LBL305
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#1
	NOT R1,R1
	ADD R1,R1,#1
	LDR R0,R6,#0
	ADD R0,R1,R0
	ADD R6,R6,#1
	STR R0,R6,#0
	LD R2,LBL310
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL311
LBL310
	.FILL #-5
LBL311
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL308
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL309
LBL308
	.FILL #0
LBL309
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
	LD R0,LBL313
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL314
LBL313
	.FILL #0
LBL314
	LD R0,LBL317
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL318
LBL317
	.FILL #0
LBL318
	LD R2,LBL315
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL316
LBL315
	.FILL #0
LBL316
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnp LBL312
	ADD R2,R2,#1
LBL312
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRnp LBL328
	LD R3,LBL327
	JMP R3
LBL327
	.FILL LBL324
LBL328
	LD R0,LBL330
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL331
LBL330
	.FILL #0
LBL331
	LD R0,LBL334
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL335
LBL334
	.FILL #1
LBL335
	LD R2,LBL332
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL333
LBL332
	.FILL #0
LBL333
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnp LBL329
	ADD R2,R2,#1
LBL329
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	ADD R6,R6,#1
	
ADD R1,R1,#0
	BRz LBL324
LBL323
	AND R1,R1,#0
	ADD R1,R1,#1
	BRnzp LBL326
LBL324
	AND R1,R1,#0
LBL326
	STR R1,R6,#0
	LDR R1,R6,#0
	BRnp LBL345
	LD R3,LBL344
	JMP R3
LBL344
	.FILL LBL341
LBL345
	LD R0,LBL347
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL348
LBL347
	.FILL #0
LBL348
	LD R0,LBL351
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL352
LBL351
	.FILL #2
LBL352
	LD R2,LBL349
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL350
LBL349
	.FILL #0
LBL350
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnp LBL346
	ADD R2,R2,#1
LBL346
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	ADD R6,R6,#1
	
ADD R1,R1,#0
	BRz LBL341
LBL340
	AND R1,R1,#0
	ADD R1,R1,#1
	BRnzp LBL343
LBL341
	AND R1,R1,#0
LBL343
	STR R1,R6,#0
	LDR R1,R6,#0
	BRz LBL355
	LD R3,LBL354
	JMP R3
LBL354
	.FILL LBL353
LBL355
	LD R0,LBL358
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL359
LBL358
	.FILL #3
LBL359
	LD R0, LBL360
	JSRR R0
	BRnzp LBL361
LBL360
	.FILL RAND
LBL361
	LDR R1,R6,#0
	STR R1,R6,#0
	LDR R1,R6,#1
	LDR R0,R6,#0
	ADD R6,R6,#2
	LD R3, LBL357
	JSRR R3
	BRnzp LBL356
LBL357
	.FILL MODULUS
LBL356
	ADD R6,R6,#-1
	STR R0,R6,#0
	LD R2,LBL362
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL363
LBL362
	.FILL #-5
LBL363
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
LBL364
	LD R0,LBL366
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL367
LBL366
	.FILL #0
LBL367
	LD R2,LBL370
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL371
LBL370
	.FILL #-5
LBL371
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL368
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL369
LBL368
	.FILL #0
LBL369
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnp LBL365
	ADD R2,R2,#1
LBL365
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRnp LBL374
	LD R3,LBL373
	JMP R3
LBL373
	.FILL LBL372
LBL374
	LD R0,LBL377
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL378
LBL377
	.FILL #3
LBL378
	LD R0, LBL379
	JSRR R0
	BRnzp LBL380
LBL379
	.FILL RAND
LBL380
	LDR R1,R6,#0
	STR R1,R6,#0
	LDR R1,R6,#1
	LDR R0,R6,#0
	ADD R6,R6,#2
	LD R3, LBL376
	JSRR R3
	BRnzp LBL375
LBL376
	.FILL MODULUS
LBL375
	ADD R6,R6,#-1
	STR R0,R6,#0
	LD R2,LBL381
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL382
LBL381
	.FILL #-5
LBL382
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
	;  LBL384
	LD R3,LBL383
	JMP R3
LBL383
	.FILL LBL364
LBL384
LBL372
	LD R0,LBL385
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL386
LBL385
	.FILL #1
LBL386
	LD R2,LBL391
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL392
LBL391
	.FILL #-5
LBL392
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL389
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL390
LBL389
	.FILL #0
LBL390
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R0, LBL393
	JSRR R0
	BRnzp LBL394
LBL393
	.FILL RAND
LBL394
	LDR R1,R6,#0
	STR R1,R6,#0
	LDR R1,R6,#1
	LDR R0,R6,#0
	ADD R6,R6,#2
	LD R3, LBL388
	JSRR R3
	BRnzp LBL387
LBL388
	.FILL MODULUS
LBL387
	ADD R6,R6,#-1
	STR R0,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R0,R1,R0
	ADD R6,R6,#1
	STR R0,R6,#0
	LD R2,LBL395
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL396
LBL395
	.FILL #-6
LBL396
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
	LD R0,LBL397
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL398
LBL397
	.FILL #1
LBL398
	LD R2,LBL399
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL400
LBL399
	.FILL #-5
LBL400
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R0,R1,R0
	ADD R6,R6,#1
	STR R0,R6,#0
	LD R2,LBL401
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL402
LBL401
	.FILL #-6
LBL402
	LDR R1,R3,#0
	STR R1,R6,#0
	LEA R0,LBL403
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL404
LBL403
	.STRINGZ "I take %d from pile %d\n"
LBL404
	LD R0,LBL405
	JSRR R0
	BRnzp LBL406
LBL405
	.FILL PRINTF
LBL406
	LDR R1,R6,#0
	ADD R6,R6,#1
	ADD R6,R6,#1
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
	LD R2,LBL407
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL408
LBL407
	.FILL #-6
LBL408
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL411
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL412
LBL411
	.FILL #-5
LBL412
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL409
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL410
LBL409
	.FILL #0
LBL410
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#1
	NOT R1,R1
	ADD R1,R1,#1
	LDR R0,R6,#0
	ADD R0,R1,R0
	ADD R6,R6,#1
	STR R0,R6,#0
	LD R2,LBL415
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL416
LBL415
	.FILL #-5
LBL416
	LDR R1,R3,#0
	STR R1,R6,#0
	LD R2,LBL413
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL414
LBL413
	.FILL #0
LBL414
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
	LD R0,LBL418
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL419
LBL418
	.FILL #0
LBL419
	LD R0,LBL422
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL423
LBL422
	.FILL #0
LBL423
	LD R2,LBL420
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL421
LBL420
	.FILL #0
LBL421
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnp LBL417
	ADD R2,R2,#1
LBL417
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	BRnp LBL433
	LD R3,LBL432
	JMP R3
LBL432
	.FILL LBL429
LBL433
	LD R0,LBL435
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL436
LBL435
	.FILL #0
LBL436
	LD R0,LBL439
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL440
LBL439
	.FILL #1
LBL440
	LD R2,LBL437
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL438
LBL437
	.FILL #0
LBL438
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnp LBL434
	ADD R2,R2,#1
LBL434
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	ADD R6,R6,#1
	
ADD R1,R1,#0
	BRz LBL429
LBL428
	AND R1,R1,#0
	ADD R1,R1,#1
	BRnzp LBL431
LBL429
	AND R1,R1,#0
LBL431
	STR R1,R6,#0
	LDR R1,R6,#0
	BRnp LBL450
	LD R3,LBL449
	JMP R3
LBL449
	.FILL LBL446
LBL450
	LD R0,LBL452
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL453
LBL452
	.FILL #0
LBL453
	LD R0,LBL456
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL457
LBL456
	.FILL #2
LBL457
	LD R2,LBL454
	LDR R1,R6,#0
	ADD R0,R4,R1
	ADD R3,R2,R0
	BRnzp LBL455
LBL454
	.FILL #0
LBL455
	LDR R1,R3,#0
	STR R1,R6,#0
	LDR R1,R6,#0
	LDR R0,R6,#1
	ADD R6,R6,#2
	AND R2,R2,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R0,R1
	BRnp LBL451
	ADD R2,R2,#1
LBL451
	ADD R6,R6,#-1
	STR R2,R6,#0
	LDR R1,R6,#0
	ADD R6,R6,#1
	
ADD R1,R1,#0
	BRz LBL446
LBL445
	AND R1,R1,#0
	ADD R1,R1,#1
	BRnzp LBL448
LBL446
	AND R1,R1,#0
LBL448
	STR R1,R6,#0
	LDR R1,R6,#0
	BRz LBL460
	LD R3,LBL459
	JMP R3
LBL459
	.FILL LBL458
LBL460
	;  LBL463
	LD R3,LBL462
	JMP R3
LBL462
	.FILL LBL461
LBL463
LBL458
	LEA R0,LBL464
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL465
LBL464
	.STRINGZ "I win!\n"
LBL465
	LD R0,LBL466
	JSRR R0
	BRnzp LBL467
LBL466
	.FILL PRINTF
LBL467
	LDR R1,R6,#0
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
	LD R0,LBL468
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL469
LBL468
	.FILL #1
LBL469
	LD R2,LBL470
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL471
LBL470
	.FILL #-3
LBL471
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
LBL461
	;  LBL474
	LD R3,LBL473
	JMP R3
LBL473
	.FILL LBL472
LBL474
LBL353
	LEA R0,LBL475
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL476
LBL475
	.STRINGZ "You win!\n"
LBL476
	LD R0,LBL477
	JSRR R0
	BRnzp LBL478
LBL477
	.FILL PRINTF
LBL478
	LDR R1,R6,#0
	ADD R6,R6,#1
	STR R1,R6,#0
	ADD R6,R6,#1
	LD R0,LBL479
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL480
LBL479
	.FILL #1
LBL480
	LD R2,LBL481
	ADD R3,R5,R2
	ADD R6,R6,#-1
	BRnzp LBL482
LBL481
	.FILL #-3
LBL482
		LDR R1,R6,#1
	STR R1,R3,#0
	ADD R6,R6,#1
LBL472
	;  LBL484
	LD R3,LBL483
	JMP R3
LBL483
	.FILL LBL66
LBL484
LBL72
	LD R0,LBL485
	ADD R6,R6,#-1
	STR R0,R6,#0
	BRnzp LBL486
LBL485
	.FILL #0
LBL486
	LDR R0,R6,#0
	STR R0,R5,#3
	;  LBL488
	LD R3,LBL487
	JMP R3
LBL487
	.FILL LBL1
LBL488
LBL1

;---------------------------------------------------------------------------
; STUDENT CODE ENDS HERE
;---------------------------------------------------------------------------

	LDR	R0,R6,#0	; restore R0...R3
	LDR	R1,R6,#1
	LDR	R2,R6,#2
	LDR	R3,R6,#3

	ADD	R6,R5,#1	; pop off local variables
	LDR	R5,R6,#0
	LDR	R7,R6,#1
	ADD	R6,R6,#2	; leave return value on stack
	RET
	
;---------------------------------------------------------------------------
; C library routines
;---------------------------------------------------------------------------

; assembly routines in this library
;   MULTIPLY (R0 <- R0 * R1)
;   DIVIDE   (R0 <- R0 / R1, rounded toward 0)
;   MODULUS  (R0 <- R0 MOD R1, using C's definition)

; routines with C interfaces in this library
;   int PRINTF (const char* fmt, ...);
;   int SCANF (const char* fmt, ...);
;   void SRAND (int new_seed);
;   int RAND ();
; NOTES: 
;    - ALL C ROUTINES LEAVE A RETURN VALUE LOCATION ON THE STACK, EVEN
;      IF THEY PRODUCE NO RETURN VALUE!
;    - PRINTF and SCANF only handle %d, %%, \n, \\, and normal characters
;

; INTERNAL routines (you should not call them)
;   LOG_RIGHT_SHIFT
;   PRINT_NUM
;   LOAD_FORMAT
;

;---------------------------------------------------------------------------

; MULTIPLY -- calculate R0 * R1
;     INPUTS -- R0 and R1
;     OUTPUTS -- R0 is the product
;     SIDE EFFECTS -- uses stack to save registers
;     NOTE: the calling convention here is NOT for use directly by C
;
MULTIPLY
	ADD R6,R6,#-3	; save R1, R2, and R3
	STR R1,R6,#0
	STR R2,R6,#1
	STR R3,R6,#2

	AND R2,R2,#0	; number of negative operands

	ADD R1,R1,#0	; set R1 to its absolute value
	BRzp MULT_R1_NON_NEG
	NOT R1,R1
	ADD R1,R1,#1
	ADD R2,R2,#1
MULT_R1_NON_NEG

	AND R3,R3,#0
MULT_LOOP
	ADD R1,R1,#0
	BRz MULT_FINISH
	ADD R3,R3,R0
	ADD R1,R1,#-1
	BRnzp MULT_LOOP

MULT_FINISH
	ADD R0,R3,#0	; move result into R0

	AND R2,R2,#1	; negate answer?
	BRz MULT_DONE
	NOT R0,R0
	ADD R0,R0,#1

MULT_DONE
	LDR R1,R6,#0	; restore R1, R2, and R3
	LDR R2,R6,#1
	LDR R3,R6,#2
	ADD R6,R6,#3
	RET


; DIVIDE -- calculate R0 / R1 (rounded toward zero)
;     INPUTS -- R0 and R1
;     OUTPUTS -- R0 is the quotient
;     SIDE EFFECTS -- uses stack to save registers; may print divide by
;                     zero error
;     NOTE: the calling convention here is NOT for use directly by C
;
DIVIDE	ADD R6,R6,#-4	; save R1, R2, R3, and R7
	STR R1,R6,#0
	STR R2,R6,#1
	STR R3,R6,#2
	STR R7,R6,#3

	AND R2,R2,#0	; number of negative operands
	ADD R2,R2,#1

	ADD R1,R1,#0	; set R1 to its negative absolute value
	BRn DIV_R1_NEG
	BRp DIV_R1_POS
	LEA R0,MSG_DIV
	PUTS
	AND R0,R0,#0
	BRnzp DIV_DONE
DIV_R1_POS
	NOT R1,R1
	ADD R1,R1,#1
	ADD R2,R2,#-1
DIV_R1_NEG

	ADD R0,R0,#0	; set R0 to its absolute value
	BRzp DIV_R0_NON_NEG
	NOT R0,R0
	ADD R0,R0,#1
	ADD R2,R2,#1
DIV_R0_NON_NEG

	AND R3,R3,#0
DIV_LOOP
	ADD R0,R0,R1
	BRn DIV_FINISH
	ADD R3,R3,#1
	BRnzp DIV_LOOP
DIV_FINISH
	ADD R0,R3,#0	; move result into R0

	AND R2,R2,#1	; negate answer?
	BRz DIV_DONE
	NOT R0,R0
	ADD R0,R0,#1

DIV_DONE
	LDR R1,R6,#0	; restore R1, R2, R3, and R7
	LDR R2,R6,#1
	LDR R3,R6,#2
	LDR R7,R6,#3
	ADD R6,R6,#4
	RET

MSG_DIV	.STRINGZ "\nDIVIDE BY ZERO\n"



; MODULUS -- calculate R0 MOD R1 (defined in C as R0 - (R0 / R1) * R1)
;     INPUTS -- R0 and R1
;     OUTPUTS -- R0 is the modulus
;     SIDE EFFECTS -- uses stack to save registers; may print divide by
;                     zero error
;     NOTE: the calling convention here is NOT for use directly by C
;
MODULUS	ADD R6,R6,#-3	; save R0, R1, and R7
	STR R0,R6,#0
	STR R1,R6,#1
	STR R7,R6,#2

	JSR DIVIDE	; R0 = R0 / R1
	JSR MULTIPLY	; R0 = (R0 / R1) * R1
	NOT R1,R0	; negate it
	ADD R1,R1,#1
	LDR R0,R6,#0	; add to original R0
	ADD R0,R0,R1

	LDR R1,R6,#1	; restore R1 and R7
	LDR R7,R6,#2
	ADD R6,R6,#3
	RET


; SRAND -- set random number generation seed
;     INPUTS -- new seed (on top of stack)
;     OUTPUTS -- one (meaningless) location left on top of stack
;     SIDE EFFECTS -- changes random seed
;     NOTE: call as a C function
;
SRAND	ADD R6,R6,#-1		; save R0
	STR R0,R6,#0
	LDR R0,R6,#1
	ST R0,RAND_SEED
	LDR R0,R6,#0		; restore R0
	RET


; LOG_RIGHT_SHIFT -- logically shift R0 right by one bit (MSB <- 0)
;     INPUTS -- R0
;     OUTPUTS -- R0 shifted right by a bit
;     SIDE EFFECTS -- uses stack to save registers
;     NOTE: the calling convention here is NOT for use directly by C
;
LOG_RIGHT_SHIFT
	ADD R6,R6,#-1		; save R1
	STR R1,R6,#0

	AND R0,R0,xFFFE		; set low bit to 0 (will become MSB)

	AND R1,R1,#0		; loop 15 times...
	ADD R1,R1,#15

LRSHFT_LOOP
	ADD R0,R0,#0		; rotate left (copy high bit to low bit)
	BRn LOW_BIT_IS_1
	ADD R0,R0,R0
	BRnzp LRSHFT_NEXT
LOW_BIT_IS_1
	ADD R0,R0,R0
	ADD R0,R0,1

LRSHFT_NEXT
	ADD R1,R1,#-1
	BRp LRSHFT_LOOP

	LDR R1,R6,#0		; restore R1
	ADD R6,R6,#1
	RET


; RAND -- generate random number using the function
;             NEW = (27193 * OLD) + 35993   MOD 65536
;	  the low bit is right-shifted out before returning, since
;         it is not random (the rest are not too bad, at least by 
;         separation of order 2 in Knuth's methods...)
;     INPUTS -- none
;     OUTPUTS -- random value left on top of stack (return value)
;     SIDE EFFECTS -- changes random seed
;     NOTE: call as a C function
;
RAND	ADD R6,R6,#-3		; save R0, R1, and R7
	STR R0,R6,#0
	STR R1,R6,#1
	STR R7,R6,#2
	LD R0,RAND_SEED
	ADD R1,R0,R0		; x 0002
	ADD R1,R1,R0		; x 0003
	ADD R1,R1,R1		; x 0006
	ADD R1,R1,R1		; x 000C
	ADD R1,R1,R0		; x 000D
	ADD R1,R1,R1		; x 001A
	ADD R1,R1,R1		; x 0034
	ADD R1,R1,R0		; x 0035
	ADD R1,R1,R1		; x 006A
	ADD R1,R1,R1		; x 00D4
	ADD R1,R1,R1		; x 01A8
	ADD R1,R1,R1		; x 0350
	ADD R1,R1,R0		; x 0351
	ADD R1,R1,R1		; x 06A2
	ADD R1,R1,R0		; x 06A3
	ADD R1,R1,R1		; x 0D46
	ADD R1,R1,R0		; x 0D47
	ADD R1,R1,R1		; x 1A8E
	ADD R1,R1,R1		; x 351C
	ADD R1,R1,R1		; x 6A38
	ADD R0,R1,R0		; x 6A39 = #27193
	LD R1,RAND_ADD
	ADD R0,R0,R1
	ST R0,RAND_SEED
	JSR LOG_RIGHT_SHIFT	; drop the low bit
	LDR R7,R6,#2		; restore R7
	STR R0,R6,#2		; save return value onto stack
	LDR R0,R6,#0		; restore R0 and R1 
	LDR R1,R6,#1
	ADD R6,R6,#2
	RET

; storage for SRAND and RAND

RAND_SEED 
	.BLKW 1
RAND_ADD
	.FILL #35993


; PRINT_NUM -- print a number in decimal to the monitor (based on code 
;              incorporated as TRAP x26 for MP2 in the Spring 2004 
;              semester of ECE190)
;     INPUTS -- R0 is the number to be printed
;     OUTPUTS -- R0 is the number of characters printed
;     SIDE EFFECTS -- none
;     NOTE: the calling convention here is NOT for use directly by C
;
; The basic strategy is to handle the sign first, then to loop over place
; values starting from 10,000 down to 10.  Place values are subtracted
; repeatedly to calculate each digit, then digits are printed, with 
; leading zeroes omitted.

; R0 is the current digit (calculated in the inner loop)
; R1 points to table of negative digit place values
; R2 holds current digit's place value, again negative
; R3 is the remaining value after removing the previous digit
; R4 is a temporary
; R5 holds the ASCII value '0'
; R6 is a marker used to avoid leading zeroes

PRINT_NUM
	ST R1,PN_SAVE_R1	; callee saves registers
	ST R2,PN_SAVE_R2
	ST R3,PN_SAVE_R3
	ST R4,PN_SAVE_R4
	ST R5,PN_SAVE_R5
	ST R6,PN_SAVE_R6
	ST R7,PN_SAVE_R7

	AND R3,R0,#0		; initialize number of characters printed
	ST R3,PN_PRINTED

	ADD R3,R0,#0		; move to R3 and check for negative value
	BRzp PN_NON_NEG
	LD R0,PN_MINUS		; if negative, print a minus sign
	OUT
	LD R0,PN_PRINTED	; add one to printed characters count
	ADD R0,R0,#1
	ST R0,PN_PRINTED
	NOT R3,R3		; and replace R0 with its absolute value
	ADD R3,R3,#1		; (-32768 will be handled correctly, too)
PN_NON_NEG
	
	LEA R1,PN_SUB		; initialize pointer to place value table
	LD R5,PN_ASC_ZERO	; initialize register with ASCII '0'
	AND R6,R6,#0		; skip leading zeroes
PN_LOOP
	LDR R2,R1,#0		; load digit place value from table
	BRz PN_LAST_DIGIT	; end of table?
	AND R0,R0,#0		; start current digit at 0 (count ADDs)
PN_DIG_LOOP			; loop to determine digit value
	ADD R4,R3,R2		; subtract place value once
	BRn PN_DIG_DONE		; done?
	ADD R3,R4,#0		; no, so copy to remaining value
	ADD R0,R0,#1		;   and increment digit
	BRnzp PN_DIG_LOOP
PN_DIG_DONE
	ADD R4,R0,R6		; do not print leading zeroes
	BRz PN_NO_PRINT
	ADD R0,R0,R5		; print current digit
	OUT
	LD R0,PN_PRINTED	; add one to printed characters count
	ADD R0,R0,#1
	ST R0,PN_PRINTED
	ADD R6,R6,#1		; always print subsequent digits, even zeroes
PN_NO_PRINT
	ADD R1,R1,#1		; point to next place value
	BRnzp PN_LOOP		; loop back for next digit
PN_LAST_DIGIT
	ADD R0,R3,R5		; always print last digit
	OUT
	LD R0,PN_PRINTED	; add one to printed characters count
	ADD R0,R0,#1

	LD R1,PN_SAVE_R1	; restore original register values
	LD R2,PN_SAVE_R2
	LD R3,PN_SAVE_R3
	LD R4,PN_SAVE_R4
	LD R5,PN_SAVE_R5
	LD R6,PN_SAVE_R6
	LD R7,PN_SAVE_R7
	RET

PN_SAVE_R1 .BLKW 1		; space for caller's register values
PN_SAVE_R2 .BLKW 1
PN_SAVE_R3 .BLKW 1
PN_SAVE_R4 .BLKW 1
PN_SAVE_R5 .BLKW 1
PN_SAVE_R6 .BLKW 1
PN_SAVE_R7 .BLKW 1
PN_PRINTED .BLKW 1

PN_SUB  .FILL #-10000		; table of place values
	.FILL #-1000
	.FILL #-100
	.FILL #-10
	.FILL #0

PN_ASC_ZERO .FILL x30		; '0'
PN_MINUS    .FILL x2D		; '-'


; LOAD_FORMAT -- load a character from a format string (for PRINTF or
;		 SCANF), translating escape sequences (-1 for %d)
;                and advancing the string pointer appropriately
;     INPUTS -- R1 is the format string pointer
;     OUTPUTS -- R0 is the next character (-1 for %d)
;                R1 is advanced either one or two locations
;     SIDE EFFECTS -- uses stack to save registers
;     NOTE: the calling convention here is NOT for use directly by C
;
LOAD_FORMAT
	ADD R6,R6,#-2	; save R2 and R3
	STR R2,R6,#0
	STR R3,R6,#1
	LDR R0,R1,#0
	LD R2,LDF_TEST_1
	ADD R3,R0,R2
	BRnp LDF_NOT_PCT
	LDR R0,R1,#1
	ADD R2,R0,R2
	BRnp LDF_CHECK_D
	ADD R1,R1,#1
LDF_BAD_PCT
	LDR R0,R1,#0
	BRnzp LDF_DONE
LDF_CHECK_D
	LD R2,LDF_TEST_2
	ADD R0,R0,R2
	BRnp LDF_BAD_PCT
	AND R0,R0,#0
	ADD R0,R0,#-1
	ADD R1,R1,#1
	BRnzp LDF_DONE
LDF_NOT_PCT
	LD R2,LDF_TEST_3
	ADD R3,R0,R2
	BRnp LDF_DONE
	LDR R0,R1,#1
	ADD R2,R0,R2
	BRnp LDF_CHECK_N
	ADD R1,R1,#1
LDF_BAD_BS
	LDR R0,R1,#0
	BRnzp LDF_DONE
LDF_CHECK_N
	LD R2,LDF_TEST_4
	ADD R0,R0,R2
	BRnp LDF_BAD_BS
	AND R0,R0,#0
	ADD R0,R0,#10
	ADD R1,R1,#1
LDF_DONE
	ADD R1,R1,#1	; default string pointer advance
	LDR R2,R6,#0	; restore R2 and R3
	LDR R3,R6,#1
	ADD R6,R6,#2
	RET

LDF_TEST_1 	.FILL xFFDB	; -'%'
LDF_TEST_2	.FILL xFF9C	; -'d'
LDF_TEST_3	.FILL xFFA4	; -'\\'
LDF_TEST_4	.FILL xFF92	; -'n'


; PRINTF -- print formatted data
;     INPUTS -- format string followed by arguments
;     OUTPUTS -- number of characters printed left on top of stack 
;                (return value)
;     SIDE EFFECTS -- uses stack to save registers
;     NOTE: call as a C function
;
; R0 holds the character to print
; R1 is the format string pointer
; R2 points to the next argument
; R3 is the number of characters printed so far
;
PRINTF	ADD R6,R6,#-5		; save R0, R1, R2, R3, and R7
	STR R0,R6,#0
	STR R1,R6,#1
	STR R2,R6,#2
	STR R3,R6,#3
	STR R7,R6,#4
	LDR R1,R6,#5
	ADD R2,R6,#6
	AND R3,R3,#0
PR_LOOP	JSR LOAD_FORMAT
	ADD R0,R0,#0
	BRz PR_DONE
	BRp PR_REG
	LDR R0,R2,#0
	ADD R2,R2,#1
	JSR PRINT_NUM
	ADD R3,R3,R0
	BRnzp PR_LOOP
PR_REG	OUT
	ADD R3,R3,#1
	BRnzp PR_LOOP
PR_DONE	LDR R7,R6,#4		; restore R7
	STR R3,R6,#4		; save return value
	LDR R0,R6,#0		; restore R0, R1, R2, and R3
	LDR R1,R6,#1
	LDR R2,R6,#2
	LDR R3,R6,#3
	ADD R6,R6,#4
	RET


; BUF_GETC -- read a character from the keyboard, with preference for
;                a character previously read but buffered (in INBUF)
;     INPUTS -- none
;     OUTPUTS -- R4 holds the character
;     SIDE EFFECTS -- uses stack to save registers
;     NOTE: the calling convention here is NOT for use directly by C
;
BUF_GETC
	ADD R6,R6,#-2
	STR R0,R6,#0
	STR R7,R6,#1
	LD R4,INBUF
	BRnp BGC_OLD
	GETC
	OUT
	ADD R4,R0,#0
	BRnzp BGC_DONE
BGC_OLD	LD R0,INBUF2
        ST R0,INBUF
	AND R0,R0,#0
	ST R0,INBUF
BGC_DONE
	LDR R0,R6,#0
	LDR R7,R6,#1
	ADD R6,R6,#2
	RET

; BUF_UNGETC -- push a character back into the input buffer
;     INPUTS -- R4 holds the character
;     OUTPUTS -- none
;     SIDE EFFECTS -- uses stack to save registers
;     NOTE: the calling convention here is NOT for use directly by C
;
BUF_UNGETC
	ADD R6,R6,#-1
	STR R0,R6,#0
	LD R0,INBUF
	ST R0,INBUF2
	ST R4,INBUF
	LDR R0,R6,#0
	ADD R6,R6,#1
	RET

; READ_NUM -- read a decimal number from the keyboard, starting with
;             a character previously read but buffered (in INBUF) if necessary;
;             skip white space before the first digit; terminate on non-digit
;             (after first digit); buffer character that causes termination;
;             ignore overflow
;             (this code based on readnumsub.asm code from 190 materials)
;     INPUTS -- none
;     OUTPUTS -- R4 holds the number typed in; R0 holds 1 if number was typed,
;                or 0 if not
;     SIDE EFFECTS -- uses stack to save registers
;     NOTE: the calling convention here is NOT for use directly by C
;

; R0 is used as a temporary register
; R1 holds the current value of the number being input
; R2 holds the additive inverse of ASCII '0' (0xFFD0)
; R3 is used as a temporary register
; R4 holds the value of the last key pressed
; R5 marks whether a digit has been seen (positive), just a negative sign (-),
;    or nothing has been seen (0) yet

READ_NUM
	ADD R6,R6,#-5		; save R1, R2, R3, R5, and R7
	STR R1,R6,#0
	STR R2,R6,#1
	STR R3,R6,#2
	STR R5,R6,#3
	STR R7,R6,#4
	AND R1,R1,#0		; clear the current value
	LD R2,RN_NEG_0		; put the value -x30 in R2
	AND R5,R5,#0		; no digits yet
	ST R5,RN_NEGATE
READ_LOOP
	JSR BUF_GETC
	ADD R0,R4,R2		; subtract x30 from R4 and store in R0 
	BRn RN_NON_DIG		; smaller than '0' means a non-digit
	ADD R3,R0,#-10		; check if > '9'
	BRzp RN_NON_DIG		; greater than '9' means a non-digit
	ADD R5,R4,#0		; a digit has been seen
	ADD R3,R1,R1		; sequence of adds multiplies R1 by 10
	ADD R3,R3,R3
	ADD R1,R1,R3
	ADD R1,R1,R1
	ADD R1,R1,R0		; finally, add in new digit
	BRnzp READ_LOOP		; get another digit
RN_NON_DIG
	; if we see space, tab, CR, or LF, we consume if no digits have
	; been seen; otherwise, we stop and buffer the character
	AND R0,R0,#0
	ADD R5,R5,#0
	BRp RN_GOT_NUM 
	BRz RN_NO_DIGITS

	; need to put the minus sign back, too
	JSR BUF_UNGETC
	LD R4,RN_MINUS
	BRnzp RN_SAVE_CHAR

RN_NO_DIGITS
	ADD R3,R4,#-9
	BRz READ_LOOP
	ADD R3,R4,#-10
	BRz READ_LOOP
	ADD R3,R4,#-13
	BRz READ_LOOP
	ADD R3,R4,#-16
	ADD R3,R3,#-16
	BRz READ_LOOP

	LD R3,RN_NEG_MIN
	ADD R3,R3,R4
	BRnp RN_SAVE_CHAR
	ADD R5,R5,#-1
	ST R5,RN_NEGATE
	BRnzp READ_LOOP

RN_GOT_NUM
	ADD R0,R0,#1
	LD R5,RN_NEGATE
	BRz RN_SAVE_CHAR
	NOT R1,R1
	ADD R1,R1,#1
RN_SAVE_CHAR
	JSR BUF_UNGETC
	ADD R4,R1,#0		; move R1 into R4	
	LDR R1,R6,#0		; restore R1, R2, R3, R5, and R7
	LDR R2,R6,#1
	LDR R3,R6,#2
	LDR R5,R6,#3
	LDR R7,R6,#4
	ADD R6,R6,#5
	RET

RN_NEG_0	.FILL xFFD0	; -'0'
RN_NEG_MIN	.FILL xFFD3	; -'-'
RN_MINUS	.FILL x002D	; '-'
RN_NEGATE	.BLKW 1

; SCANF -- scan in formatted data
;     INPUTS -- format string followed by arguments
;     OUTPUTS -- number of integers converted left on top of stack 
;                (return value)
;     SIDE EFFECTS -- uses stack to save registers
;     NOTE: call as a C function
;
; R0 holds the character to be read
; R1 is the format string pointer
; R2 points to the next argument
; R3 is the number of integer conversions so far
; R4 is the character/number actually read from the keyboard
;
SCANF	ADD R6,R6,#-6		; save R0, R1, R2, R3, R4, and R7
	STR R0,R6,#0
	STR R1,R6,#1
	STR R2,R6,#2
	STR R3,R6,#3
	STR R4,R6,#4
	STR R7,R6,#5
	LDR R1,R6,#6
	ADD R2,R6,#7
	AND R3,R3,#0
SC_LOOP	JSR LOAD_FORMAT
	ADD R0,R0,#0
	BRz SC_DONE
	BRp SC_REG
	JSR READ_NUM
	ADD R0,R0,#0
	BRz SC_DONE
	LDR R0,R2,#0
	ADD R2,R2,#1
	STR R4,R0,#0
	ADD R3,R3,#1
	BRnzp SC_LOOP
SC_REG	JSR BUF_GETC
	NOT R0,R0
	ADD R0,R0,#1
	ADD R0,R0,R4
	BRz SC_LOOP
	JSR BUF_UNGETC
SC_DONE	LDR R7,R6,#5		; restore R7
	STR R3,R6,#5		; save return value
	LDR R0,R6,#0		; restore R0, R1, R2, R3, and R4
	LDR R1,R6,#1
	LDR R2,R6,#2
	LDR R3,R6,#3
	LDR R4,R6,#4
	ADD R6,R6,#5
	RET

; buffered input characters (0 means none)
INBUF	.FILL x0000
INBUF2	.FILL x0000

;---------------------------------------------------------------------------
; global data space allocation
;---------------------------------------------------------------------------

GLOBDATA
	.BLKW #3

;---------------------------------------------------------------------------
; stack allocation
;---------------------------------------------------------------------------

	.BLKW #1000
STACK

	.END

