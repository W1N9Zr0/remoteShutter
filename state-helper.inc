
ADJ_TIME_HANDLER macro IncFn, DecFn, quick, value, returnState
	ADJ_HANDLER IncFn, DecFn, quick, value, returnState, ClockInc, ClockDec
	endm

ADJ_INT_HANDLER macro IncFn, DecFn, quick, value, returnState
	ADJ_HANDLER IncFn, DecFn, quick, value, returnState, IntInc, IntDec
	endm;

ADJ_HANDLER macro IncFn, DecFn, quick, value, returnState, SIncFn, SDecFn
	local FineT, DoneT, EndT, NoChange
	
		movlw value
		movwf DisplayPointer
		
		btfss MenuState, STATEFLAG_FAST_ADJ
			goto FineT
	
		btfss Buttons, BTN_UP
			call IncFn
		btfss Buttons, BTN_DOWN
			call DecFn
		
;		comf Buttons, w
;		andlw 1<<BTN_UP | 1<<BTN_DOWN
;		btfsc STATUS, Z
;			goto NoChange
			
		movfw quick
		call TimeTable0
		movwf value+0
		
		movfw quick
		call TimeTable1
		movwf value+1
	
		movfw quick
		call TimeTable2
		movwf value+2

NoChange
		btfss Buttons, BTN_CANCEL
			bcf MenuState, STATEFLAG_FAST_ADJ
	
		goto DoneT

FineT
		movlw value
		btfss Buttons, BTN_UP
			call SIncFn
		
		movlw value
		btfss Buttons, BTN_DOWN
			call SDecFn
	
		btfss Buttons, BTN_CANCEL
			bsf MenuState, STATEFLAG_FAST_ADJ
		
	
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