	title "Remote shutter"
	errorlevel 0

; Serial Port PC Control Panel
	radix dec
Fosc equ 8 * 1000 * 1000
	#include 16f628a-helper.inc

	__config _CP_OFF & _WDT_OFF & _BODEN_OFF & _PWRTE_ON & _INTOSC_OSC_NOCLKOUT & _LVP_OFF & _MCLRE_OFF
	; Code Protect off, WatchDogTimer off, BrownOutDetection off, 
	; PowerUpTimer on, Internal Oscilator, LowVoltageProgram off,
	; MCLR off
	__idlocs 0x567a

	#include shutter.inc


LoadTime macro DST, XX, YY, ZZ
	movlw ToBD(ZZ)
	movwf DST
	movlw ToBD(YY)
	movwf DST+1
	movlw ToBD(XX)
	movwf DST+2
	endm


interupt
	decfsz TimeCounter5ms, f
		goto IncrTime
	goto DoneInter
IncrTime
	bsf TimeCounter5ms, 1
	movlw exposure
	call BD2Dec
	
DoneInter
	bcf PIR1, TMR2IF
	return

main
	PICINIT

	MYINIT
	
	movlw 0
	movwf menustate
	movlw 0
	movwf quicke
	movlw 4
	movwf quickt
	movlw 4
	movwf quickr


	LoadTime exposure, 0, 0, 10
	LoadTime timer, 0, 1, 0
	movlw ToBD(1)
	movwf repeat
	movlw 0
	movwf repeat+1

loop


	call UpdateDisplay
	
	call ReadButtons
	
	call FrameDelay
	btfss STATUS, Z
		goto loop
		
	call DoThinking
	

	goto loop

	end
	
