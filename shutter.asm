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
	__idlocs 0x567b

	#include shutter.inc

main
	PICINIT
	MYINIT

loop
	bcf INTCON, GIE
	call UpdateDisplay
	bsf INTCON, GIE
	
	call FrameDelay
	btfss STATUS, Z
		goto loop
		
	
	; Main logic
	
	movfw Buttons
	xorwf OldButtons, f
	btfss STATUS, Z
		goto PassButton
	
	decfsz HoldDelay, f
		goto NoButtons
		
	movlw BUTTON_REPEAT_DELAY
	movwf HoldDelay
	goto NoReDelay
PassButton
	movlw BUTTON_HOLD_DELAY
	movwf HoldDelay
NoReDelay

	call ButtonMap

NoButtons

	movfw Buttons
	movwf OldButtons

	movfw DisplayPointer
	btfss STATUS, Z
		call DisplayTime

	goto loop

	end
	
