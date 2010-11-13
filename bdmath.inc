	#include 16f628a-helper.inc
	
	radix dec
	
BDInc macro F
	local Done
	incf F, f 
	
	movfw F
	andlw 0x0f ; Check low digit == 10
	xorlw 10
	clrc
	bnz Done
	
	movlw 0xf0 ; Low digit to 0
	andwf F, f
	
	movlw 0x10 ; High digit++
	addwf F, f
	
	movfw F
	andlw 0xf0 ; Check high digit == 10
	xorlw 0xa0
	bnz Done
	
	movlw 0x0f ; High digit to 0
	andwf F, f
	setc       ; Carry
Done:
	endm

BDDec macro F
	local Done
	decf F, f 
	
	movfw F
	andlw 0x0f ; Check low digit == -1
	xorlw 0x0f
	setc
	bnz Done
	
	movlw 0xf9 ; Low digit to 9
	andwf F, f
	
	movfw F
	andlw 0xf0 ; Check high digit == -1
	xorlw 0xf0
	bnz Done
	
	movlw 0x9f ; Low digit to 9
	andwf F, f
	
	clrc       ; Borrow
Done:
	endm

	

	