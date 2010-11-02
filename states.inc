
ButtonMap
	movfw menustate
	TableLookup
	goto State0
	goto State1
	
State0
	
	btfss Buttons, BTN_UP
		call IncT
	btfss Buttons, BTN_DOWN
		call DecT
		
	btfss Buttons, BTN_OK
		bsf menustate, 0
	movfw quickt
	call TimeTable0
	movwf timer+0
	
	movfw quickt
	call TimeTable1
	movwf timer+1

	movfw quickt
	call TimeTable2
	movwf timer+2
	
	return


State1
	movlw timer+1
	btfss Buttons, BTN_UP
		call BD2Inc
	
	movlw timer+1
	btfss Buttons, BTN_DOWN
		call BD2Dec
	
Skip2	
	btfss Buttons, BTN_OK
		bcf menustate, 0
	
	
		
	btfsc Buttons, BTN_CANCEL
		goto NoCancel
		
	btfss T2CON, TMR2ON
		goto TimerIsOff
	
	clrf TMR2
	bcf T2CON, TMR2ON

	goto NoCancel
TimerIsOff
	bsf T2CON, TMR2ON
		
NoCancel
	
	
	return