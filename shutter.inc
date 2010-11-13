	#include shutter-lowlevel.inc

BUTTON_REPEAT_DELAY equ 32
BUTTON_HOLD_DELAY equ 200

	extern BD2Inc
	extern BD2Dec
	extern BD3Inc
	extern BD3Dec
	extern BD3Test
	
	#include states.inc

incFwrap macro F, max, min
	incf F, f
	movfw F
	xorlw max+1
	
	btfss STATUS, Z
		return
	
	movlw min
	movwf F
	
	return
	endm
	
decFwrap macro F, min, max
	decf F, f
	movfw F
	xorlw min-1
	
	btfss STATUS, Z
		return
	movlw max
	movwf F
	
	return
	endm

IncE
	incFwrap quicke, 17, 0
DecE
	decFwrap quicke, 0, 17

IncT
	incFwrap quickt, 17, 3
DecT
	decFwrap quickt, 3, 17

IncR
	incFwrap quickr, 14, 4
DecR
	decFwrap quickr, 4, 14



DoThinking
	
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
	
	
	return

CheckLeadingZero macro Digit
	movf (Display+Digit),w
	xorlw 0xDD
	btfss STATUS, Z
		return
	clrf (Display+Digit)
	endm


DisplayTime
	movwf FSR
	
	incf FSR,f
	incf FSR,f
	movfw INDF
	decf FSR, f
	iorwf INDF, w
	
	movwf Temp
	btfsc STATUS, Z
		decf FSR, f
	
	BD7Seg Display, INDF
	incf FSR, f
	BD7Seg Display2, INDF
	
	movf Temp, w
	btfsc STATUS, Z
		bsf Display+2, 1
		
	CheckLeadingZero 3
	CheckLeadingZero 2
	CheckLeadingZero 1
	
	return

TimeTable0
	TableLookup
	dt ToBD( 5), ToBD(10), ToBD(25), ToBD(50)
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 0), ToBD( 0)
TimeTable1
	TableLookup
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 1), ToBD( 2), ToBD( 4), ToBD( 8)
	dt ToBD(16), ToBD(32), ToBD(64), ToBD(28)
	dt ToBD(56), ToBD(12), ToBD(24), ToBD(48)
	dt ToBD(96), ToBD(92)
TimeTable2
	TableLookup
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 1)
	dt ToBD( 2), ToBD( 5), ToBD(10), ToBD(20)
	dt ToBD(40), ToBD(81)
	