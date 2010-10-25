	list	 p=16f628a
	#include p16f628a.inc
	processor 16f628a
	radix dec

	udata_shr
TEMP res 1
TEMP2 res 1

	extern main



NopLoop macro
	local mysleep2
	local mysleep
		movlw 25
		movwf TEMP2
mysleep2:
			movlw 255
			movwf TEMP
mysleep:
			decfsz	TEMP, f
			goto mysleep
		decfsz TEMP2, f
		goto mysleep2
	return


	endm