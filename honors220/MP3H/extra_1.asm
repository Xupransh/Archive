    .ORIG x6000

    .FILL NAME1 ; "A"
    .FILL x10   ; M W F
    .FILL x0202 ; 10, 13, 15

    .FILL NAME2 ; "B"
    .FILL x10   ; F
    .FILL x008A ; 8, 10, 14

    .FILL NAME3 ; "C"
    .FILL x11   ; M Tu W Th F
    .FILL x808   ; 8, 11, 16

    .FILL NAME4 ; "D"
    .FILL x10   ; Tu Th F
    .FILL x0080 ; 9, 11, 14


    .FILL x0000 ; end of list

NAME1   .STRINGZ "A"
NAME2   .STRINGZ "B"
NAME3   .STRINGZ "C"
NAME4   .STRINGZ "D"
NAME5   .STRINGZ "E"
NAME6   .STRINGZ "F"

    .END


