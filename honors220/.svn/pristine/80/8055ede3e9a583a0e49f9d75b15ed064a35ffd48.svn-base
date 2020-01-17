.ORIG x3000
;LC-3 program that translates a student’s daily schedule
;from a list to a two dimensional matrix of pointers
;(memory addresses to names of events), then prints the schedule
;also takes in extra events and attempts to fit them
;in the schedule.
MAIN
JSR MAKE_FIXED_LEN
BRnzp FIT_EXTRA

;this is the section of the code where the schedule is
;converted into a 2D array. The register usage is -
;R0- used to load in slot numbers, table entries, day information etc
;R1- current address of given schedule table
;R3- Used as a counter for loops
;R4- current string address
;R5- keeps track of the current slot
;R7 - used by trap and JSR
;R6 isn't used by this method. This is used to separate the conflicts that
;occur here from the ones in the extra events method
MAKE_FIXED_LEN
AND R6, R6, #0
ST R7, RETURN_FOR_TRANSLATION
JSR STORE_REGISTERS
JSR CLEAR_ADDRESS_ALL      ;the subroutine that clears memory
LD R1, TABLE_ADDRESS       ;load x5000 into R1

FIXED_LEN
LDR R0, R1, #0             ;load table entry into R0
BRz MAKE_FIXED_LEN_DONE    ;if it's the null string, we're done
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

MAKE_FIXED_LEN_DONE
JSR LOAD_REGISTERS               ;subroutine done, load registers
LD R7, RETURN_FOR_TRANSLATION    ;load return address
RET                              ;return

;This is the section of the code that attempts to fit in
;extra events into the schedule. It explores the different
;time slots specified for each event, starting from the earliest
;slot. If  no such configuration is found, it simply prints an
;error message and halts the program. The registers have multiple
;uses, and considering the fact that it moves from one section to
;another a lot, these uses are often changed, but are mostly restored
;by the STORE and LOAD methods.
;R0-used for loading and storing, holds slot number  
;R1-current address of table of extra events
;R2-current address of stack
;R3-used as a counter, holding the slot value, argument for add day  
;R4-holds the bitmask, string address as argument for add day subroutine
;R5-addess of bitmasks, as argument into add day subroutine
;R6-used to hold last slot used, used as counter, day vector information
;R7-used by trap, jsr etc
FIT_EXTRA
LD R2, STACK_BASE          ;load x8000 into R2
LD R1, START_EXTRA         ;load x6000 into R1

EXTRA_EVENT
LDR R0, R1, #0             ;Load first string address
BRz MADE_FIXED_LEN         ;if it's null, we're done
ADD R2, R2, #-3            ;increase stack size
STR R0, R2, #2             ;string address
LDR R0, R1, #1             ;day vector
STR R0, R2, #1             ;store it in the stack
LDR R0, R1, #2             ;bit vector
STR R0, R2, #0
ADD R1, R1, #3             ;increase the address of the table

;This does a bunch of things. If there was an error with the last
;slot, it checks the next one. Otherwise, it just gives us the
;earliest slot to check.
TRY_NEXT_SLOT
LDR R0, R2, #0             ;Load the slot bit vector
AND R3, R3, #0             ;clear R3
LEA R5, BIT_MASKS          ;Load bitmask adress
ADD R3, R3, #15            ;add 15 to R3

;Get the next slot (bit)
NEXT_BIT
ADD R5, R5, #1             ;Takes care of the zero padding, incrementing
LDR R4, R5, #0             ;load the bit mask
AND R4, R0, R4             ;if it's 1, we're gold
ADD R3, R3, #-1            ;decrement count
BRn NO_MORE_SLOTS          ;if it's zero, we're short on slots
ADD R4, R4, #0             ;set cc for R4
BRz NEXT_BIT               ;if it's zero, its a no go

ADD R3, R3, #-14           ;slot number
BRz SLOT_IS_7              ;if R3 is zero, we need a special check
ADD R6, R3, R6             ;otherwise, just add it to the slot number
BRzp NEXT_BIT_2            ;that was checked previously (zero if no slots
NOT R3, R3                 ;were checked)
ADD R3, R3, #1             ;make -R3 R3
ADD R6, R6, R3             ;restore the value of R6
SKIP_7
LEA R5, SLOT_ADDRESS       ;load first slot address from lookup table into R5
ADD R5, R5, R3             ;add slot number to it
LDR R5, R5, #0             ;load the first slot number back into R5


LDR R6, R2, #1             ;load day vector
LDR R4, R2, #2             ;string into R4

AND R0, R0, #0
ADD R0, R0, #11            ;load 11 in R0
SHIFT_ELEVEN_2
ADD R6, R6, R6             ;shift day information by 11 places
ADD R0, R0, #-1            ;decrement R3
BRp SHIFT_ELEVEN_2         ;if R3 is zero or negative, we're done
AND R0, R0, #0
ADD R0, R3, R0             ;put slot number in R0

;this is code that I wrote in the second mp
;to add a particular event to the days it's supposed to be added
;into. I could probably make this into a subroutine, but it already
;uses a subroutine in it. I felt that copying it straight up would be
;easier than dealing with a subception (subroutine in a subroutine
;all inside a bigger subroutine, haha)
AND R3, R3, #0
ADD R3, R3, #5             ;add 5 into R3, this acts as the day number
DAY_LOOP_2
ADD R3, R3, #-1            ;decrement R3
ADD R6, R6, #0             ;set cc for R6
BRzp SKIP_2                ;if the msb is 0, we don't want to add it
JSR ADD_DAY                ;else, add it to it's respective day
SKIP_2
ADD R6, R6, R6             ;left shift R6, when the loop is done, R6 = 0
ADD R3, R3, #0             ;set cc for R3
BRzp DAY_LOOP_2            ;if it's non negative, continue

LEA R5, BIT_MASKS          ;load in the bit mask address
ADD R5, R5, R0             ;add the slot number to it
LDR R5, R5, #1             ;add one to that, because it's 0 padded
NOT R5, R5                 ;make it the negative of itself
ADD R5, R5, #1
LDR R3, R2, #0             ;load the bit vector
ADD R3, R5, R3             ;remove the slot from it, because it works
STR R3, R2, #0             ;so we don't want it working again and again
BRnzp EXTRA_EVENT          ;and again. keep it back, then try the next event

;this is where you come if the slot was occupied
;by someone else. It's simple, you try the next slot.
;If there's no more slots, well then that's someone
;else's business (see NO_MORE_SLOTS). You load back register
;values, see if R6 was 0 (doesn't happen in EXTRA_SLOTS, only in
;MAKE_FIXED_LEN. Then you clear the addresses with the current event's
;string in it, Set R6 to the slot number we just tried, and try all
;the ones that aren't that slot number (special case for slot 0, see below)
ERROR_OCCURRED
JSR LOAD_REGISTERS          ;load back those register values
ADD R6, R6, #0              ;set cc for R6
BRz ORIGINAL_HALT           ;if R6 is zero, we don't wanna go further
LDR R5, R2, #2              ;if it's not, then clear traces of this event
JSR CLEAR_ADDRESS_OF        ;from the schedule
AND R6, R6, #0              ;clear R6 and load in the slot we just checked
ADD R6, R6, R0
BRz SET_FOR_SEVEN           ;if it was zero, do something different
BRnzp TRY_NEXT_SLOT         ;otherwise, go check the next slot

;setting R6 to -1 if the slot for 7 am, this works.
;didn't want to set it to 0 because then checking if
;it had already occurred would be hard, thanks assembly.
SET_FOR_SEVEN
ADD R6, R6, #-1             ;set it to -1
BRnzp TRY_NEXT_SLOT         ;try a the next slot

;needed a different section of code to handle cases when
;the slot number was 0 because checking if it had
;already occurred was hard with the regular section
SLOT_IS_7
ADD R6, R6, #1              ;we don't want 7 in 2 cases
BRz NEXT_BIT_2              ;in the case R6 is -1
ADD R6, R6, #-1             ;and in the case R6 is 1 or something
BRp NEXT_BIT_2              ;which would mean a slot higher than 7 has
BRnzp SKIP_7                ;been tried already, otherwise just try 7.

;code jumps here when no more slots are left to try
;ie, all the slots give an error. This is unfortunate.
;First, you remove all traces of the current event,
;then all traces of the event before,
;and you try a different slot for the event before.
;if there's no more slots for that, well then this is
;called again, till you hit the base of the stack, in which
;case, the schedule won't work. Sorry :(
NO_MORE_SLOTS
LDR R5, R2, #2
JSR CLEAR_ADDRESS_OF
ADD R2, R2, #3
LD R0, STACK_BASE
ADD R0, R2, R0
BRz NOT_POSSIBLE
LDR R5, R2, #2
JSR CLEAR_ADDRESS_OF
AND R6, R6, #0
ADD R1, R1, #-3
BRnzp TRY_NEXT_SLOT

;the original conflict message in the original schedule
;the fact that R6 isn't used in the subroutine used to convert
;the schedule into a 2d array is used.
ORIGINAL_HALT
AND R0, R0, #0             ;clear R0
ADD R0, R0, R4             ;put the string address with bad slot in R0
PUTS                       ;print string
LEA R0, ERROR_MESSAGE_1    ;load error message into R0
PUTS                       ;print error message
LD R0, NEWLINE             ;print newline
OUT
HALT

;We come here, because on of the slots was explored
;we don't want to go there again. It'll give an error
;so let's just skip that. keep the values where they are
;and see if there's another slot we can use
NEXT_BIT_2
NOT R3, R3
ADD R3, R3, #1
ADD R6, R6, R3
ADD R3, R3, #-1
NOT R3, R3
ADD R3, R3, #14
BRnzp NEXT_BIT

;The code jumps here if a schedule config is not possible
NOT_POSSIBLE
LEA R0, COULDNT_FIT         ;load and print the error
PUTS
HALT                        ;halt

;Bit masks for resolving the slot number from the slot bit vector
;padded with x0000 for safety
BIT_MASKS
.FILL x0000
.FILL x0001
.FILL x0002
.FILL x0004
.FILL x0008
.FILL x0010
.FILL x0020
.FILL x0040
.FILL x0080
.FILL x0100
.FILL x0200
.FILL x0400
.FILL x0800
.FILL x1000
.FILL x2000
.FILL x4000
.FILL x8000
.FILL x0000


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
ADD R5, R5, #1             ;add one to that, address of where current slot ends
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
LD R0, NEWLINE
OUT
HALT

;program jumps here when a string needs to be printed
PRINT_ITEM
JSR PRINT_CENTERED         ;use subroutine to print string of address in R1
BRnzp ITEM_PRINTED         ;go to ITEM_PRINTED

;subroutine used to clear the memory from
;x4000 to x404F. Goes from x404F, and decrements
;address till x4000 is reached, stores 0 in
;all the addresses that hold a particular string.
;It stores register value. String to be cleared is
;in R5.
CLEAR_ADDRESS_OF
ST R7, RETURN_CLEAR_OF
JSR STORE_REGISTERS
AND R1, R1, #0             ;store 0 in R1
LD R2, LAST_ADDRESS        ;load x404F into R2
LD R3, MINUS_FIRST_ADDRESS ;load -x4000 into R3
CLEAR_OF
LDR R6, R2, #0             ;load whatever is there at R2
NOT R6, R6                 ;make it it's own negative
ADD R6, R6, #1
ADD R6, R6, R5             ;add it to the string that we want to delete
BRnp SKIP_ADDRESS          ;if it's zero, delete it from the address
STR R1, R2, #0             ;store 0 into address in R2
SKIP_ADDRESS
ADD R2, R2, #-1            ;decrement address
ADD R4, R2, R3             ;add it to -x4000
BRzp CLEAR_OF              ;if non negative, go back to clear
JSR LOAD_REGISTERS
LD R7, RETURN_CLEAR_OF
RET                        ;else, return

;we store the return value of the fixed len subroutine here
RETURN_FOR_TRANSLATION
.FILL x0000

;clear address of return address stored here
RETURN_CLEAR_OF
.FILL x0000

;This is like clear address of, except, it
;doesn't really care what's in the addresses
;it makes all of them zero (4000 - 404F) without
;even checking. Called at the beginning to start
;anew. No register values are stored.
CLEAR_ADDRESS_ALL
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
ST R7, RETURN_ADDRESS
JSR STORE_REGISTERS        ;store register values
ADD R5, R5, R3             ;go to slot no. associated with the day
LDR R3, R5, #0             ;load value in slot
BRnp ERROR_OCCURRED        ;if non zero, conflict error
STR R4, R5, #0             ;else, store string address in M[R5]
JSR LOAD_REGISTERS         ;load back register values
LD R7, RETURN_ADDRESS      ;load back return address
RET                        ;return

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

;base of the stack used in fit_extra, as one would expect.
STACK_BASE
.FILL x8000

;starting address of the initial schedule
TABLE_ADDRESS
.FILL x5000 ;address of the input

VLINE
.FILL x007C ;ascii for vertical line

SIX_SPACES
.STRINGZ "      " ;used to print out an empty space in the schedule

;initial address of the extra events
START_EXTRA
.FILL x6000

NEWLINE
.FILL x000A ;ascii for newline

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

;string used when there's no valid config for extra events
COULDNT_FIT
.STRINGZ "Could not fit all events into schedule.\n"

ERROR_MESSAGE_1
.STRINGZ " conflicts with an earlier event." ;string used to print a conflict
                                             ;error message

ERROR_MESSAGE_2
.STRINGZ " has an invalid slot number."      ;string used to print the
                                             ;bad slot error message

;these strings are used to print out the headings for the
;days (by passing into PRINT_CENTERED)
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

MINUS_FIRST_ADDRESS
.FILL xC000 ;This is the inverse of x4000, used to check if all
            ;slots have been cleared

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
