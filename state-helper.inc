
ADJ_HANDLER macro IncFn, DecFn, quick, value, returnState
	local FineT, DoneT, EndT
	
		movlw value
		movwf DisplayPointer
		
		btfsc MenuState, STATEFLAG_FINE_ADJ
			goto FineT
	
		btfss Buttons, BTN_UP
			call IncFn
		btfss Buttons, BTN_DOWN
			call DecFn
		
	
		movfw quick
		call TimeTable0
		movwf value+0
		
		movfw quick
		call TimeTable1
		movwf value+1
	
		movfw quick
		call TimeTable2
		movwf value+2

		btfss Buttons, BTN_CANCEL
			bsf MenuState, STATEFLAG_FINE_ADJ
	
		goto DoneT

FineT
		movlw value
		btfss Buttons, BTN_UP
			call BD2Inc
		
		movlw value
		btfss Buttons, BTN_DOWN
			call BD2Dec
	
		btfss Buttons, BTN_CANCEL
			bcf MenuState, STATEFLAG_FINE_ADJ
		
	
DoneT

	movlw returnState
	btfss Buttons, BTN_OK
		movwf MenuState
EndT
	
	endm
	
IF_BUTTON_THEN_STATE macro button, state
		movlw state
		btfss Buttons, button
			movwf MenuState
	endm