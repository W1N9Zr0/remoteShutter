	
	#include 16f628a-helper.inc
	radix dec
	
	global ToSevenSegHex
	
DECIMALSEG equ 2
	
	code
	
ToSevenSegHex
	addwf PCL, f
	retlw 0xFD	;0
	retlw 0x05	;1
	retlw 0xB9	;2
	retlw 0xAD	;3
	retlw 0x65	;4
	retlw 0xEC	;5
	retlw 0xFC	;6
	retlw 0x85	;7
	retlw 0xFD	;8
	retlw 0xED	;9
	retlw 0xF5	;A
	retlw 0x7C	;B
	retlw 0xD8	;C
	retlw 0x3D	;D
	retlw 0xF8	;E
	retlw 0xF0	;F
	retlw 0xDC  ;G
	retlw 0x75	;H
	retlw 0x50  ;I
	retlw 0x1D	;J
	retlw 0x70	;K
	retlw 0x58	;L
	retlw 0xD5	;M
	retlw 0x34	;N
	retlw 0x3C	;O
	retlw 0xF1	;P
	retlw 0xE5	;Q
	retlw 0x30	;R
	retlw 0xCC	;S
	retlw 0xD0	;T
	retlw 0x5D	;U
	retlw 0x49	;V
	retlw 0x4D	;W
	retlw 0x55	;X
	retlw 0x6D	;Y
	retlw 0x99	;Z

	end