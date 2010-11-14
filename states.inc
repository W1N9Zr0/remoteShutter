

STATE_MANUAL equ 0
STATE_AUTO equ 1
STATE_EXP equ 2
STATE_TIME equ 3
STATE_REP equ 4
STATE_CLICK equ 5
STATE_HOLD equ 6
STATE_ADJ_E equ 7
STATE_ADJ_T equ 8
STATE_ADJ_R equ 9
STATE_RUNNING equ 10

STATEFLAG_FAST_ADJ equ 7
STATEMASK equ 0xf

#include state-helper.inc


TEXT_MAN 
	dt 0xd5, 0x85, 0, 0
TEXT_AUTO
	dt 0xf5, 0, 0, 0
TEXT_EXP
	dt 0xf8, 0, 0, 0
TEXT_TIME
	dt 0x85, 0x80, 0, 0
TEXT_REP
	dt 0x30, 0, 0, 0

ButtonMap
	movfw MenuState
	andlw STATEMASK
	TableLookup
	goto STATE_MANUAL_HANDLER
	goto STATE_AUTO_HANDLER
	goto STATE_EXP_HANDLER
	goto STATE_TIME_HANDLER
	goto STATE_REP_HANDLER
	goto STATE_CLICK_HANDLER
	goto STATE_HOLD_HANDLER
	goto STATE_ADJ_E_HANDLER
	goto STATE_ADJ_T_HANDLER
	goto STATE_ADJ_R_HANDLER
	goto STATE_RUNNING_HANDLER


ManuallyTrigger
	movlw b'11000000'
	movwf ShutterState
	clrf timerw
	clrf timerw+1
	clrf timerw+2
	clrf timerw+3
	
	movlw TIMER_COUNTUP
	movwf TimerMode
	bsf T2CON, TMR2ON
	
	movlw timerw
	movwf DisplayPointer
	return
	
ManuallyStop
AutoStop
	bcf T2CON, TMR2ON
	clrf ShutterState
	movlw TIMER_COUNTDOWN
	movwf TimerMode
	clrf DisplayPointer
	return
	

	
AutoStart
	Copy3 timerw,timer
	Copy3 exposurew, exposure
	
	movlw TIMER_COUNTDOWN
	movwf TimerMode
	bsf T2CON, TMR2ON
	
	movlw timerw
	movwf DisplayPointer
	return
	

STATE_MANUAL_HANDLER
	clrf DisplayPointer
	DisplayRaw TEXT_MAN
	
	IF_BUTTON_THEN_STATE BTN_OK, STATE_CLICK
	IF_BUTTON_THEN_STATE BTN_CANCEL, STATE_HOLD
	IF_BUTTON_THEN_STATE BTN_UP, STATE_REP
	IF_BUTTON_THEN_STATE BTN_DOWN, STATE_AUTO
	
	movfw MenuState
	xorlw STATE_CLICK
	btfsc STATUS, Z
		call ManuallyTrigger
	
	movfw MenuState
	xorlw STATE_HOLD
	btfsc STATUS, Z
		call ManuallyTrigger
	
	return
	
STATE_AUTO_HANDLER
	clrf DisplayPointer
	DisplayRaw TEXT_AUTO
	
	IF_BUTTON_THEN_STATE BTN_UP, STATE_MANUAL
	IF_BUTTON_THEN_STATE BTN_DOWN, STATE_EXP
	IF_BUTTON_THEN_STATE BTN_OK, STATE_RUNNING
	
	
	movfw MenuState
	xorlw STATE_RUNNING
	btfsc STATUS, Z
		call AutoStart
		
	return
	
STATE_EXP_HANDLER
	clrf DisplayPointer
	DisplayRaw TEXT_EXP
	
	IF_BUTTON_THEN_STATE BTN_UP, STATE_AUTO
	IF_BUTTON_THEN_STATE BTN_DOWN, STATE_TIME
	IF_BUTTON_THEN_STATE BTN_OK, STATE_ADJ_E
	return
	
STATE_TIME_HANDLER
	clrf DisplayPointer
	DisplayRaw TEXT_TIME
	
	IF_BUTTON_THEN_STATE BTN_UP, STATE_EXP
	IF_BUTTON_THEN_STATE BTN_DOWN, STATE_REP
	IF_BUTTON_THEN_STATE BTN_OK, STATE_ADJ_T
	return

STATE_REP_HANDLER
	clrf DisplayPointer
	DisplayRaw TEXT_REP
	
	IF_BUTTON_THEN_STATE BTN_UP, STATE_TIME
	IF_BUTTON_THEN_STATE BTN_DOWN, STATE_MANUAL
	IF_BUTTON_THEN_STATE BTN_OK, STATE_ADJ_R
	return

STATE_CLICK_HANDLER
	movlw STATE_MANUAL
	btfsc Buttons, BTN_OK
		movwf MenuState
	
	movfw MenuState
	xorlw STATE_MANUAL
	btfsc STATUS, Z
		call ManuallyStop
	
	return

STATE_HOLD_HANDLER
	IF_BUTTON_THEN_STATE BTN_OK, STATE_MANUAL
		
	movfw MenuState
	xorlw STATE_MANUAL
	btfsc STATUS, Z
		call ManuallyStop
	
	return

STATE_ADJ_T_HANDLER
	ADJ_TIME_HANDLER IncT, DecT, quickt, timer, STATE_TIME
	return

STATE_ADJ_E_HANDLER
	ADJ_TIME_HANDLER IncE, DecE, quicke, exposure, STATE_EXP
	return

STATE_ADJ_R_HANDLER
	ADJ_INT_HANDLER IncR, DecR, quickr, repeat, STATE_REP
	return


STATE_RUNNING_HANDLER
	
	IF_BUTTON_THEN_STATE BTN_CANCEL, STATE_AUTO
	
	movlw STATE_AUTO
	btfss T2CON, TMR2ON
		movwf MenuState
	
	movfw MenuState
	xorlw STATE_AUTO
	btfsc STATUS, Z
		call AutoStop
	
	return

