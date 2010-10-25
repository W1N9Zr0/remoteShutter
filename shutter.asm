	title "Remote shutter"
	errorlevel 0

; Serial Port PC Control Panel
	radix dec
Fosc equ 8 * 1000 * 1000
	#include shutter.inc
	#include 16f628a-helper.inc

	__config _CP_OFF & _WDT_OFF & _BODEN_OFF & _PWRTE_ON & _INTOSC_OSC_NOCLKOUT & _LVP_OFF & _MCLRE_OFF
	; Code Protect off, WatchDogTimer off, BrownOutDetection off, 
	; PowerUpTimer on, Internal Oscilator, LowVoltageProgram off,
	; MCLR off
	__idlocs 0xfa11


	extern ToSevenSegHex
	code
	
main
	PICINIT
	
	MYINIT

	movlw 0
	movwf Value
	movlw 1
	movwf Loopv1
	movlw 1 
	movwf Loopv2

MainLoop

	movfw Value
	movwf Digit0
	
	movfw Buttons
	movwf Digit1	
	
	movfw Value
	andlw 0xf
	call ToSevenSegHex
	movwf Digit3
	
	swapf Value, w
	andlw 0xf
	call ToSevenSegHex
	movwf Digit2
	
	call UpdateDisplay
	

	
	call ReadButtons
	btfss Buttons, 1
		goto MainLoop


	call FrameDelay
	btfsc STATUS, Z
		incf Value,f
	
	goto MainLoop

ReadButtons
	clrf PORTA
	movlw LEDOFFNEG
	movwf PORTB	
	errorlevel -302
	bsf STATUS, RP0
		movlw b'00001111'
		movwf TRISB
		bcf TRISA, 4
	bcf STATUS, RP0
	errorlevel +302

	clrf PORTB

	movfw PORTB
	movwf Buttons

	errorlevel -302
	bsf STATUS, RP0
		movlw PORTBInputs
		movwf TRISB
		bsf TRISA, 4
	bcf STATUS, RP0
	errorlevel +302
	
	movlw LEDOFFNEG
	movwf PORTB
	
	return

UpdateDisplay
	showdigit Digit0 , 0
	showdigit Digit1 , 1
	showdigit Digit2 , 2
	showdigit Digit3 , 3
	return


FrameDelay
	decfsz Loopv1, f
		retlw 0
	movlw 5
	movwf Loopv1
	
	decfsz Loopv2, f
		retlw 0
	movlw 5
	movwf Loopv2
	bsf STATUS, Z
	return

DigitDisplayDelay
	nop
	nop
	nop
	nop
	nop
	return;

EndProgram
	end
	
