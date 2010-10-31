	#include shutter-lowlevel.inc

StateMask equ 0x0f	

StateManual equ 0x01
StateAuto equ 0x02

StateE equ 0x03
StateT equ 0x04
StateR equ 0x05

StateAE equ 0x06
StateAT equ 0x07
StateAR equ 0x08

StateTrigger equ 0x09
StateHold equ 0x0a

StateAFine equ 0x10


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
	btfsc Buttons, BTN_UP
		call IncT
	btfsc Buttons, BTN_DOWN
		call DecT

	movfw quickt
	call TimeTable0
	movwf timer+0
	
	movfw quickt
	call TimeTable1
	movwf timer+1

	movfw quickt
	call TimeTable2
	movwf timer+2
	
	movlw timer
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
	
	movfw INDF
	movwf Temp
	btfsc STATUS, Z
		incf FSR, f
	
	BD7Seg Display, INDF
	incf FSR, f
	BD7Seg Display2, INDF
	
	movf Temp, w
	btfss STATUS, Z
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
	