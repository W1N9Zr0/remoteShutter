

	radix dec			; Default to Decimal numbers

	extern ToSevenSegDec
	extern ToSevenSegLET


LEDOFFNEG equ b'00001111'
BUTTONNEG equ b'00010000'

PORTAInputs	equ	b'00110000'
PORTBInputs	equ	b'00000000'


;DEEPROM code
;EEShutter dw 0, 0, 0
;EETimer   dw 0, 0, 0
;EERepeat  dw 0, 0, 0

	udata
MenuState res 1

TimerMode res 1
ShutterState res 1
SHUTTER_HALFWAY equ 6
SHUTTER_CLICK equ 7

Buttons res 1
BTN_DOWN equ 0
BTN_UP equ 1
BTN_CANCEL equ 2
BTN_OK equ 3
OldButtons res 1

HoldDelay res 1

Display res 2
Display2 res 2

DECIMALSEG equ 2
DisplayPointer res 1

quicke res 1
quickt res 1
quickr res 1

exposure res 3
timer res 3
repeat res 3

exposurew res 3
timerw res 3

Loopv1 res 1

DisplayLoop res 1


	code

RST	code     0x0000
	goto    main

INT	code	0x0004	; Interrupt Vector
	SaveState
	call	interupt
	RestoreState
	retfie			; End Interrupt Vector




MYINIT macro
		errorlevel -302
		bsf STATUS, RP0
			bcf OPTION_REG, 7 ; Port B pullups
			bcf OPTION_REG, T0CS
			
			bsf PIE1, TMR2IE ; TIMER2 interrupt
			movlw 250
			movwf PR2 ; TIMER2 period
		bcf STATUS, RP0
		errorlevel +302

		movlw 1
		movwf Loopv1
		
		;timer2
		clrf T2CON
		clrf TMR2
		movlw ((10-1) << 3) | 1
		movwf T2CON
		
		bsf INTCON, GIE ; interrupts
		bsf INTCON, PEIE; peripheral interrupts
		
		clrf ShutterState
		clrf MenuState
		clrf TimerMode
		clrf DisplayPointer
		clrf DisplayLoop
		
		movlw 0
		movwf quicke
		movlw 4
		movwf quickt
		movlw 4
		movwf quickr
	
		LoadTime exposure, 0, 1, 0
		LoadTime timer, 0, 2, 0
		
		clrf repeat
		clrf repeat+2
		movlw 5
		movwf repeat+1
	endm



ReadButtons
	clrf PORTA
	movlw LEDOFFNEG
	iorwf ShutterState, w
	movwf PORTB	
	
	errorlevel -302
	bsf STATUS, RP0
		movlw b'00001111'
		movwf TRISB
		bcf TRISA, 4
	bcf STATUS, RP0
	errorlevel +302

	movfw ShutterState
	movwf PORTB

	movfw PORTB
	andlw 0x0f
	movwf Buttons

	errorlevel -302
	bsf STATUS, RP0
		movlw PORTBInputs
		movwf TRISB
		bsf TRISA, 4
	bcf STATUS, RP0
	errorlevel +302
	
	movlw LEDOFFNEG
	iorwf ShutterState, w
	movwf PORTB
	
	return


ShowDigit macro value, digit
		movlw LEDOFFNEG
		iorwf ShutterState, w
		movwf PORTB
		
		movfw value
		movwf PORTA

		;movfw value
		andlw b'00110000'
		iorlw ((~(1 << digit)) & b'00001111')
		iorwf ShutterState, w
		movwf PORTB
		;call DigitDisplayDelay
		
	endm
	

FrameDelay
	decfsz Loopv1, f
		retlw 0
	movlw 50
	movwf Loopv1

	bsf STATUS, Z
	return

	
#define ToBD(X) (X / 10 << 4) | (X % 10)



BD7Seg macro DSTF, BDF
	movfw BDF
	andlw 0x0f
	call ToSevenSegDec
	movwf DSTF+0
	
	swapf BDF, w
	andlw 0x0f
	call ToSevenSegDec
	movwf DSTF+1
	
	endm
	
	
	


LoadTime macro DST, XX, YY, ZZ
	movlw ToBD(ZZ)
	movwf DST
	movlw ToBD(YY)
	movwf DST+1
	movlw ToBD(XX)
	movwf DST+2
	endm


