
ButtonMap
	movfw menustate
	TableLookup
	goto State0
	goto State1
	
State0
	
	btfss Buttons, BTN_UP
		call IncE
	btfss Buttons, BTN_DOWN
		call DecE
		
	btfss Buttons, BTN_OK
		bsf menustate, 0
	movfw quicke
	call TimeTable0
	movwf exposure+0
	
	movfw quicke
	call TimeTable1
	movwf exposure+1

	movfw quicke
	call TimeTable2
	movwf exposure+2
	
	return


State1
	movlw exposure+1
	btfss Buttons, BTN_UP
		call BD2Inc
	
	movlw exposure+1
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