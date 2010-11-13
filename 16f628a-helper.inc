
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
			
			;bcf PCON, OSCF ; 48khz osc
	
	
		bcf		STATUS, RP0
		errorlevel +302
	endm


StateSaveMemory	udata_shr
SAVE_W res 1
SAVE_STATUS res 1
SAVE_FSR res 1
Temp res 1



SaveState macro
		; Save state
		movwf	SAVE_W
		
		swapf	STATUS, W
		movwf	SAVE_STATUS
		
		movfw	FSR
		movwf	SAVE_FSR
		
		bcf		STATUS, RP0
	endm

RestoreState macro
		; Restore state
		movwf	SAVE_FSR
		movfw	FSR
		
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
	
	
	
Copy3 macro Dst, Src
		movfw Src
		movwf Dst
		movfw Src+1
		movwf Dst+1
		movfw Src+2
		movwf Dst+2
	endm