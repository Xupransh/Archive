.ORIG x3000

;LC-3 program that translates a student’s daily schedule
;from a list to a two dimensional matrix of pointers
;(memory addresses to names of events), then prints the schedule

;this is the section of the code where the schedule is
;converted into a 2D array. The register usage is -
;R0- used to load in slot numbers, table entries, day information etc
;R1- current address of given schedule table
;R3- Used as a counter for loops
;R4- current string address
;R5- keeps track of the current slot
;R7 - used by trap and JSR
MAKE_FIXED_LEN
JSR CLEAR_ADDRESS          ;the subroutine that clears memory

LD R1, TABLE_ADDRESS       ;load x5000 into R1

FIXED_LEN
LDR R0, R1, #0             ;load table entry into R0
BRz MADE_FIXED_LEN         ;if it's the null string, we're done, go to printing
AND R4, R4, #0             ;else, clear R4, we'll store the string address
ADD R4, R4, R1             ;keep string address in R4

STRING_NULL
ADD R1, R1, #1             ;loop to detect where the string ends
LDR R0, R1, #0             ;add one to R1, load value into R0
BRnp STRING_NULL           ;if it's 0, we're at the end of the string

ADD R1, R1, #2             ;go to the slot information
LDR R0, R1, #0             ;load slot number into R0
ADD R0, R0, #-15           ;subtract 15 from it
BRp ERROR_2                ;if it's positive, it's a bad slot number, ERROR_2

ADD R0, R0, #15            ;add back the 15
LEA R5, SLOT_ADDRESS       ;load first slot address from lookup table into R5
ADD R5, R5, R0             ;add slot number to it
LDR R5, R5, #0             ;load the first slot number back into R5
ADD R1, R1, #-1            ;go to the address with the day information
LDR R0, R1, #0             ;load in the day information into R0
AND R3, R3, #0             ;Clear R3
ADD R3, R3, #11            ;put 11 into R3

SHIFT_ELEVEN
ADD R0, R0, R0             ;shift day information by 11 places
ADD R3, R3, #-1            ;decrement R3
BRp SHIFT_ELEVEN           ;if R3 is zero or negative, we're done

ADD R3, R3, #5             ;add 5 into R3, this acts as the day number
ADD_DAY_LOOP
ADD R3, R3, #-1            ;decrement R3
ADD R0, R0, #0             ;set cc for R0
BRzp SKIP                  ;if the msb is 0, we don't want to add it
JSR ADD_DAY                ;else, add it to it's respective day
SKIP
ADD R0, R0, R0             ;left shift R0
ADD R3, R3, #0             ;set cc for R3
BRzp ADD_DAY_LOOP          ;if it's non negative, continue

ADD R1, R1, #2             ;move R1 to next entry in table
BRnzp FIXED_LEN            ;unconditional jump to start


;this is the section of the code where the schedule is
;printed. The register usage is -
;R0- used to print vertical lines and newlines
;R1- holds string addresses for subroutines to print strings
;R2- load address of heading strings
;R3- used to hold slot address where string address is stored
;R4- used as slot number, used to check if everything is printed
;R5- used to check if all items in a slot are printed
;R6- used as counter
;R7- used by trap and JSR and in subroutines
MADE_FIXED_LEN
LEA R1, SIX_SPACES         ;load address of six spaces
JSR PRINT_CENTERED         ;print six spaces

LD R0, VLINE               ;print vertical line
OUT

AND R1, R1, #0             ;clear R1, R6
AND R6, R6, #0             ;R6 used as counter, R1 to hold string address
LEA R2, DAY_STRINGS        ;load address where address "Mon" etc are stored

;used to print heading (mon, tue wed)
PRINT_HEADING
LDR R1, R2, #0             ;load first day string
JSR PRINT_CENTERED         ;print it
ADD R6, R6, #1             ;increment R6
ADD R2, R2, #1             ;increment address
ADD R6, R6, #-5            ;check if loop is done
BRz HEADING_PRINTED        ;if R6-5 = 0, we're done
ADD R6, R6, #5             ;else, keep on going
LD R0, VLINE               ;print out a vertical line
OUT
BRnzp PRINT_HEADING        ;go back

HEADING_PRINTED
AND R4, R4, #0             ;heading printed, clear R4
LD R3, SLOT_ADDRESS        ;load x4000 into R3

;let's start printing the schedule
PRINT_SCHEDULE
LD R0, NEWLINE             ;print a newline at the start of each slot
OUT
AND R1, R1, #0             ;clear R1, add R4 into it
ADD R1, R1, R4
JSR PRINT_SLOT             ;Print out slot no. R4 (0 for 7 etc)
LD R0, VLINE               ;Print out a vertical line
OUT

PRINT_ALL_DAYS
LDR R1, R3, #0             ;load string stored at address in R3 into R1
BRnp PRINT_ITEM            ;if it's non zero, print it

LEA R1, SIX_SPACES         ;else, load address of six space into R1
JSR PRINT_CENTERED         ;print six spaces

;program jumps here when string is printed
ITEM_PRINTED
ADD R3, R3, #1             ;increment address
LEA R5, SLOT_ADDRESS       ;load address of x4000 into R5
ADD R5, R5, R4             ;add slot number to R5
ADD R5, R5, #1             ;add one to that, this is address of where current slot ends
LDR R5, R5, #0             ;load whatever is stored at that address
NOT R5, R5                 ;make it negative
ADD R5, R5, #1
ADD R6, R5, R3             ;add it to current slot address
BRz NEXT_SLOT              ;if it's zero, move to next slot
LD R0, VLINE               ;else, keep on going, print out a vertical line
OUT
BRnzp PRINT_ALL_DAYS       ;loop back

;program jumps here when a slot is filled
NEXT_SLOT
ADD R4, R4, #-15           ;check if all slots are over
BRz DONE_PRINTING          ;if R4-15 = 0, then done
ADD R4, R4, #15            ;else, increment slot, and print
ADD R4, R4, #1
BRnzp PRINT_SCHEDULE       ;go to printing part of the code

;program jumps here when schedule is printed
DONE_PRINTING
HALT                       ;HALT

;program jumps here when a string needs to be printed
PRINT_ITEM
JSR PRINT_CENTERED         ;use subroutine to print string of address in R1
BRnzp ITEM_PRINTED         ;go to ITEM_PRINTED

;subroutine used to clear the memory from
;x4000 to x404F. Goes from x404F, and decrements
;address till x4000 is reached, stores 0 in
;all the address. Doesn't store any register values.
CLEAR_ADDRESS
AND R1, R1, #0             ;store 0 in R1
LD R2, LAST_ADDRESS        ;load x404F into R2
LD R3, MINUS_FIRST_ADDRESS ;load -x4000 into R3
CLEAR
STR R1, R2, #0             ;store 0 into address in R2
ADD R2, R2, #-1            ;decrement address
ADD R4, R2, R3             ;add it to -x4000
BRzp CLEAR                 ;if non negative, go back to clear
RET                        ;else, return

;Subroutine used to add an entry into the days
;it occurs on. First, it checks if the entry in that
;spot is null. If it isn't, it goes to the conflict
;message, else, it adds the event to it's particular
;slot in the array. Stores register values and then loads
;them back later. R4 holds address of string, R5 holds
;array slot, R3 holds the day number (0 for monday etc)
ADD_DAY
ST R7, RETURN_ADDRESS      ;store return adress (not really needed)
JSR STORE_REGISTERS        ;store register values
ADD R5, R5, R3             ;go to slot no. associated with the day
LDR R3, R5, #0             ;load value in slot
BRnp ERROR_1               ;if non zero, conflict error
STR R4, R5, #0             ;else, store string address in M[R5]
JSR LOAD_REGISTERS         ;load back register values
LD R7, RETURN_ADDRESS      ;load back return address
RET                        ;return

;program jumps here if theres a conflict
ERROR_1
AND R0, R0, #0             ;clear R0
ADD R0, R0, R4             ;put the string address with bad slot in R0
PUTS                       ;print string
LEA R0, ERROR_MESSAGE_1    ;load error message into R0
PUTS                       ;print error message
LD R0, NEWLINE             ;print newline
OUT
HALT                       ;halt

;program jumps here if theres a bad slot number
ERROR_2
AND R0, R0, #0             ;clear R0
ADD R0, R0, R4             ;put the string address with bad slot in R0
PUTS                       ;print string
LEA R0, ERROR_MESSAGE_2    ;load error message into R0
PUTS                       ;print error message
LD R0, NEWLINE             ;print newline
OUT
HALT                       ;halt

VLINE
.FILL x007C ;ascii for vertical line

SIX_SPACES
.STRINGZ "      " ;used to print out an empty space in the schedule

;Mondays of all the slots (mark the change in slot)
SLOT_ADDRESS
.FILL x4000
.FILL x4005
.FILL x400A
.FILL x400F
.FILL x4014
.FILL x4019
.FILL x401E
.FILL x4023
.FILL x4028
.FILL x402D
.FILL x4032
.FILL x4037
.FILL x403C
.FILL x4041
.FILL x4046
.FILL x404B
.FILL x4050

TABLE_ADDRESS
.FILL x5000 ;address of the input

ERROR_MESSAGE_1
.STRINGZ " conflicts with an earlier event." ;string used to print a conflict error message

ERROR_MESSAGE_2
.STRINGZ " has an invalid slot number."      ;string used to print the bad slot error message

;these strings are used to print out the headings for the days (by passing into PRINT_CENTERED)
DAY_STRINGS
.FILL MON
.FILL TUE
.FILL WED
.FILL THU
.FILL FRI

MON
.STRINGZ "Mon"
TUE
.STRINGZ "Tue"
WED
.STRINGZ "Wed"
THU
.STRINGZ "Thu"
FRI
.STRINGZ "Fri"

NEWLINE
.FILL x000A ;ascii for newline

MINUS_FIRST_ADDRESS
.FILL xC000 ;This is the inverse of x4000, used to check if all slots have been cleared

LAST_ADDRESS
.FILL x404F           ;last address in the table

ZERO
.FILL X0030           ;ascii for zero

SEVEN
.Fill x0037           ;ascii for seven

COLON
.FILL X003A           ;ascii for colon

RETURN_ADDRESS
.FILL x0000           ;storage space for return address of main subroutines

RETURN_ADDRESS_1
.FILL x0000           ;storage space for subroutines called inside subroutines

R_ZERO
.FILL x0000           ;these are storage space for R0-R6 as R-<register number>

R_ONE
.FILL x0000

R_TWO
.FILL x0000

R_THREE
.FILL x0000

R_FOUR
.FILL x0000

R_FIVE
.FILL x0000

R_SIX
.FILL x0000

SPACE
.FILL x0020         ;ascii for space

;this is the lookup table used for determining number
;of leading spaces needed for a string of length between
;0 and 6
LEADING_SPACES
.FILL x0006
.FILL x0002
.FILL x0002
.FILL x0001
.FILL x0001
.FILL x0000
.FILL x0000

;This subroutine takes in a number between 0-15 in R1
;and prints out the corresponding time slot.
;it works by dividing the given number into 3 possible
;sets of numbers, and depending on which set the given
;number lies in, it prints out a corresponding first digit
;and then the corresponding second digit, followed by a
;common set of characters.
;All register values are saved by the subroutine
;Call by storing a value in R1, then JSR PRINT_SLOT
PRINT_SLOT
ST R7, RETURN_ADDRESS    ;Store the address to return to
JSR STORE_REGISTERS      ;Go to subroutine to store register values
ADD R1, R1, #-2          ;check if the first digit to be printed is zero
BRnz OUT_ZERO            ;if it is, go to OUT_ZERO (to output a zero)
ADD R1, R1, #-10         ;if it isn't, check if first digit is a one
BRnz OUT_ONE             ;if it is, go to OUT_ONE (to output a one)
BRnzp OUT_TWO            ;go to OUT_TWO to out a two

OUT_ZERO
LD R0, ZERO              ;load ascii value of zero into R0
OUT                      ;TRAP for displaying R0
ADD R1, R1, #2           ;subtracted 2 before branch, add it back
BRnzp USE_SEVEN          ;Go to USE_SEVEN- adds R1 to seven, prints it

OUT_ONE
LD R0, ZERO              ;load ascii value of zero into R0
ADD R0, R0, #1           ;ADD #1 to it, because we want to output one
OUT                      ;TRAP for displaying R0
ADD R1, R1, #9           ;Given number was between 3-12, make it between 0-9
BRnzp USE_ZERO           ;go to USE_ZERO- outputs corresponding second digit

OUT_TWO
LD R0, ZERO              ;load ascii value of zero into R0
ADD R0, R0, #2           ;add #2, because we want to output two
OUT                      ;TRAP for displaying R0
ADD R1, R1, #-1          ;Given number was between 13-15, make it between 0-2
BRnzp USE_ZERO           ;go to USE_ZERO - outputs corresponding second digit

USE_ZERO
LD R6, ZERO              ;load ascii value of zero into R6
ADD R0, R1, R6           ;add R1 and R6 and store into R0
OUT                      ;TRAP for displaying R0
BRnzp PRINT_REST         ;Go to PRINT_REST - to print ":00"

USE_SEVEN
LD R6, SEVEN             ;load ascii value of seven into R6
ADD R0, R1, R6           ;add R1 ad R6 and store into R0
OUT                      ;TRAP for displaying ascii in R0
BRnzp PRINT_REST         ;Go to PRINT_REST - to print ":00"

PRINT_REST
LD R0, COLON             ;Load ascii for colon into R0
OUT                      ;output a colon
LD R0, ZERO              ;ascii for zero into R0
OUT                      ;output 0 to display
OUT                      ;output 0 to display
LD R0, SPACE             ;load ascii for space
OUT                      ;output a space

JSR LOAD_REGISTERS       ;go to subroutine to load back register values
LD R7, RETURN_ADDRESS    ;load address from where subroutine was called
RET                      ;return to that address

;This subroutine takes a string a outputs such that
;it appears to be centered by padding it with an apt
;number of spaces, or by truncating it. This is done
;by first calculating the string length, determining the
;amount of leading spaces needed using a lookup table
;(called LEADING_SPACES), then calculating the trailing
;spaces by subtracting the sum of the string length and
;leading spaces from 6. All registers are stored by this
;subroutine. Store the address of the starting of the
;string in R1 then JSR PRINT_CENTERED to use the subroutine.
PRINT_CENTERED
ST R7, RETURN_ADDRESS    ;Store the address to return to
JSR STORE_REGISTERS      ;go to subroutine to store register values
AND R2, R2, #0           ;Clear R2
AND R3, R3, #0           ;Clear R3
AND R4, R4, #0           ;Clear R4
AND R5, R5, #0           ;Clear R5
ADD R2, R1, #0           ;Duplicate R1 into R2

STRING_LENGTH
LDR R6, R2, #0           ;Get ascii stored at address in R2
BRz PRINT_LEADING        ;If it's null, go to PRINT_LEADING
ADD R4, R4, #1           ;Else, increment string length (in R4)
ADD R2, R2, #1           ;Increment address in R2
BRnzp STRING_LENGTH      ;go back to the loop

PRINT_LEADING
ADD R4, R4, #-6          ;Check if length is more than 6
BRp MORE_THAN_SIX        ;if yes, go to MORE_THAN_SIX (truncates string)
ADD R4, R4, #6           ;if not, restore string length
LEA R2, LEADING_SPACES   ;Store initial address of lookup table in R2
ADD R2, R2, R4           ;Get the address needed for given length
LDR R3, R2, #0           ;Load the number of leading spaces into R3
ADD R5, R3, #0           ;Store it into R5
JSR PRINT_SPACES         ;Go to subroutine for printing spaces

PRINT_STRING
ADD R0, R1, #0           ;Put the starting string address into R0
PUTS                     ;output the string

PRINT_TRAILING
ADD R5, R4, R3           ;Add string length, leading spaces, into R5
ADD R5, R5, #-6          ;R5-6
NOT R5, R5               ;Negate R5
ADD R5, R5, #1           ;add one to convert R5 into -R5
JSR PRINT_SPACES         ;go to subroutine for printing spaces
BRnzp DONE               ;go to halt section

MORE_THAN_SIX
ADD R3, R3, #6           ;initialize counter to 6

PRINT
LDR R0, R1, #0           ;Load ascii in address R1 into R1
OUT                      ;display said ascii character
ADD R1, R1, #1           ;increment address
ADD R3, R3, #-1          ;decrement counter
BRz DONE                 ;if counter is zero, we're done
BRnzp PRINT              ;if not, then print again.

DONE
JSR LOAD_REGISTERS       ;load back inital register values
LD R7, RETURN_ADDRESS    ;load back address we're supposed to return to
RET                      ;return to said address

;this subroutine prints a specified number of spaces
;the number of spaces to be printed should be in R5
;the subroutine doesn't save any register values
;to call it, store number of spaces in R5, then
;JSR PRINT_SPACES
PRINT_SPACES
LD R0, SPACE            ;load ascii for space into R0
ST R7, RETURN_ADDRESS_1 ;store return address of caller

SPACE_LOOP
ADD R5, R5, #0          ;set cc for number of spaces to be printed
BRz NO_SPACES           ;if no spaces left, we're done
OUT                     ;else, print a space
ADD R5, R5, #-1         ;decrement number of spaces to be printed
BRp SPACE_LOOP          ;return to loop

NO_SPACES
LD R7, RETURN_ADDRESS_1 ;if no more spaces left, load return address
RET                     ;return to that address


;subroutine for storing registers
;stores registers r0-r6
;store r7 before calling if needed
;call as JSR STORE_REGISTERS
STORE_REGISTERS
ST R1, R_ONE           ;all lines store respective register in
ST R2, R_TWO           ;their respective memory location
ST R3, R_THREE
ST R4, R_FOUR
ST R5, R_FIVE
ST R6, R_SIX
ST R0, R_ZERO
RET                    ;return to caller

;subroutine to load back registers
;stores registers r0-r6
;store r7 before calling if needed
;call as JSR LOAD_REGISTERS
LOAD_REGISTERS
LD R1, R_ONE          ;all lines load respective register from
LD R2, R_TWO          ;their respective memory location
LD R3, R_THREE
LD R4, R_FOUR
LD R5, R_FIVE
LD R6, R_SIX
LD R0, R_ZERO
RET                   ;return to caller

.END

