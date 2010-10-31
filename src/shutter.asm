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
	__idlocs 0x4321

	#include shutter.inc

main
	PICINIT
	
	MYINIT
	movlw 0
	movwf quicke
	movlw 0
	movwf exposure
	movlw 0
	movwf exposure+1
	movlw 0
	movwf exposure+2

loop


	call UpdateDisplay
	
	call ReadButtons
	
	call FrameDelay
	btfss STATUS, Z
		goto loop
		
	call DoThinking
	

	goto loop



	end
	
