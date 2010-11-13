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



interupt
	movfw TimerMode
	TableLookup
	goto DelayCountdown
	goto ExposureCountdown

DelayCountdown
		movlw timerw
		call BD3Dec
	
		movlw timerw
		call BD3Test
		btfss STATUS, Z
			goto NonZeroCountDown
			
		
		bsf ShutterState, SHUTTER_CLICK
		bsf TimerMode, 0
		
		movlw exposurew
		movwf DisplayPointer
		
		Copy3 timerw, timer
	goto DoneInterrupt
	
NonZeroCountDown
	 	movfw timerw+1
	 	andlw 0xff-1
	 	iorwf timerw+2, w
	 	btfsc STATUS, Z
	 		bsf ShutterState, SHUTTER_HALFWAY
	
	goto DoneInterrupt

ExposureCountdown
		movlw exposurew
		call BD3Dec
	
		movlw exposurew
		call BD3Test
		btfss STATUS, Z
			goto DoneInterrupt
			
		
		clrf ShutterState
		bcf TimerMode, 0
		
		Copy3 exposurew, exposure
	 	
		movlw timerw
		movwf DisplayPointer

	 	
DoneInterrupt
	bcf PIR1, TMR2IF
	return

main
	PICINIT

	MYINIT


loop


	bcf INTCON, GIE
	call UpdateDisplay
	bsf INTCON, GIE
	
	call ReadButtons
	
	call FrameDelay
	btfss STATUS, Z
		goto loop
		
	call DoThinking
	

	goto loop

	end
	
