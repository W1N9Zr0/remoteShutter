
	radix dec			; Default to Decimal numbers




LEDOFFNEG equ b'00001111'
BUTTONNEG equ b'00010000'

PORTAInputs	equ	b'00110000'

PORTBInputs	equ	b'00000000'



RST	code     0x0000
	goto    main


DEEPROM code
EEShutter dw 0, 0, 0
EETimer   dw 0, 0, 0
EERepeat  dw 0, 0, 0

	udata
Value res 1
Buttons res 1

Digit0 res 1
Digit1 res 1
Digit2 res 1
Digit3 res 1

Loopv1 res 1
Loopv2 res 1

	

MYINIT macro
		errorlevel -302
		bsf STATUS, RP0
			bcf OPTION_REG, 7 ; Port B pullups
			bcf OPTION_REG, T0CS
		bcf STATUS, RP0
		errorlevel +302
		

	endm

showdigit macro value, digit
		movlw LEDOFFNEG
		movwf PORTB
		
		movfw value
		movwf PORTA

		;movfw value
		andlw b'00110000'
		iorlw ((~(1 << digit)) & b'00001111')
		movwf PORTB
		call DigitDisplayDelay
		
	endm


LongLoad macro Target, X1, X0
	movlw (X0)
	movwf (Target)
	movlw (X1)
	movwf (Target) + 1
	endm

LongInc macro VAR
	local EndInc

	incfsz (VAR)+0, f
	 goto EndInc

	incf (VAR)+1, f
EndInc
	endm

LongCopy macro DST, SRC
	movfw (SRC)+1
	movwf (DST)+1
	movfw (SRC)
	movwf (DST)
	endm


LongRLF macro F
	rlf (F), f
	rlf (F)+1, f
	endm

LongRRF macro F
	bcf STATUS, C
	btfsc (F)+1, 7
	bsf STATUS, C
	
	rrf (F)+1, f
	rrf (F), f
	endm

IfZeroGoto macro Label
	btfsc STATUS, Z
	goto (Label)
	endm

LongAdd macro DST, SRC
	movfw (SRC)
	addwf (DST), f
	btfsc STATUS, C
	incf (DST)+1, f
	movfw (SRC)+1
	addwf (DST)+1, f

	endm

LongDec macro VAR
	local EndInc

	decf (VAR)+0, f
	incfsz (VAR)+0, w
	 goto EndInc

	decf (VAR)+1, f
EndInc
	endm

LongSub	macro Result, X, Y
	movfw (Y) + 1
	subwf (X) + 1, w
	movwf (Result) + 1
	movfw (Y)
	subwf (X), w
	movwf (Result)
	btfss STATUS, C
	 decf (Result) + 1, f
	
	endm


LongNeg	macro	Dst
	comf    (Dst), f
	comf    (Dst)+1, f
	LongInc (Dst)
	endm

