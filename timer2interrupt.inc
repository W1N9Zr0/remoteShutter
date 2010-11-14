
TIMER_COUNTDOWN equ 0
TIMER_EXPOSURE_COUNTDOWN equ 1
TIMER_COUNTUP equ 2

interupt
	movfw TimerMode
	TableLookup
	goto TimerCountdown
	goto ExposureCountdown
	goto TimerCountup

TimerCountdown
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
	goto DoneInterrupt
	
TimerCountup
		movlw timerw
		call BD3Inc
	 	
DoneInterrupt
	bcf PIR1, TMR2IF
	return

