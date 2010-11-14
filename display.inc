
CheckLeadingZero macro Digit
	movf (Display+Digit),w
	xorlw 0xDD
	btfss STATUS, Z
		return
	clrf (Display+Digit)
	endm


UpdateDisplay
	incf DisplayLoop, f
	movlw 5
	xorwf DisplayLoop, w
	btfsc STATUS, Z
		clrf DisplayLoop

	movfw DisplayLoop
	TableLookup
	goto DisplayDigit0
	goto DisplayDigit1
	goto DisplayDigit2
	goto DisplayDigit3
	goto ReadButtons

DisplayDigit0
	ShowDigit Display+0 , 0
	return;
DisplayDigit1
	ShowDigit Display+1 , 1
	return;
DisplayDigit2
	ShowDigit Display+2 , 2
	return;
DisplayDigit3
	ShowDigit Display+3 , 3
	return;


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
	

DisplayRaw macro Text
	variable I
I = 0
	while (I < 4)
J = 3 - I
		call Text+I
		movwf Display + J
I++
	endw
	endm

DisplayText macro TEXT, LEN
	variable I
	variable J
I = 0
	while (I < LEN) 
J = +3 - I
		call TEXT+I
		call ToSevenSegLET
		movwf Display + J
I++
	endw
	if ( LEN < 4) 
I = LEN
		clrw
		while ( I < 4 )
J = +3 - I
			movwf Display + J
I++
		endw	
	endif
	endm 