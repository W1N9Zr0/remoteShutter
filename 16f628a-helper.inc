
	list	 p=16f628a
	#include p16f628a.inc
	processor 16f628a
	

PICINIT	macro 
		; Comparators off
		movlw	b'00000111'
		movwf	CMCON
		; Bank 1
		errorlevel -302
		bsf		STATUS, RP0
	
			movlw	PORTAInputs
			movwf	TRISA
			
			movlw	PORTBInputs
			movwf	TRISB
			
			bcf PCON, OSCF
	
	
		bcf		STATUS, RP0
		errorlevel +302
	endm




	ifdef INTERRUPTS
INT	code	0x0004	; Interrupt Vector
	SaveState
	call	interupt
	RestoreState
	retfie			; End Interrupt Vector
endif

StateSaveMemory	udata_shr
SAVE_W res 1
SAVE_STATUS res 1
Temp res 1


SaveState macro
		; Save state
		movwf	SAVE_W
		swapf	STATUS, W
		bcf		STATUS, RP0
		movwf	SAVE_STATUS
	endm

RestoreState macro
		; Restore state
		swapf	SAVE_STATUS, W
		movwf	STATUS
		swapf	SAVE_W, F
		swapf	SAVE_W, W
	endm


TableLookup macro
	local TABLE
	movwf Temp
	movlw high(TABLE)
	movwf PCLATH
	movfw Temp
	addlw low(TABLE)
	skpnc
	incf PCLATH, f
	movwf PCL
TABLE
	endm