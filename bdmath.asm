	#include bdmath.inc
	radix dec
	
	global BD2Inc
	global BD2Dec
	global BD2Test
	
	global BD3Inc
	global BD3Dec
	global BD3Test
	
	global ClockInc
	global ClockDec
	global IntInc
	global IntDec
	
	
	code 
	
	
IntInc
	movwf FSR
	incf FSR, f
	movfw FSR
	call BD2Inc
	return
IntDec
	movwf FSR
	incf FSR, f
	movfw FSR
	call BD2Dec
	return

ClockInc
	movwf FSR
	incf FSR, f
	incf FSR, f
	
	movfw INDF ; +2

	decf FSR, f
	iorwf INDF, w ; +1
	
	btfsc STATUS, Z
		goto IncMilli
	
	movfw FSR
	call BD2Inc
	return
IncMilli
	decf FSR, w ; +0
	call BD3Inc
	return
	
ClockDec
	movwf FSR
	incf FSR, f
	incf FSR, f

	movfw INDF ; +2
	movwf Temp
	
	decf FSR, f
	iorwf INDF, w ; +1
	
	btfsc STATUS, Z
		goto DecMilli
	
	movlw 0x01
	xorwf INDF, w
	iorwf Temp, w
	btfsc STATUS, Z
		goto DecMilli
	
	movfw FSR
	call BD2Dec
	return
DecMilli
	decf FSR, w ; +0
	call BD3Dec
	return	

BD2Inc
	movwf FSR
	
	BDInc INDF
	bnc DoneBD2Inc
	
	incf FSR, f
	BDInc INDF
DoneBD2Inc
	return
	
BD2Dec
	movwf FSR
	
	BDDec INDF
	bc DoneBD2Dec
	
	incf FSR, f
	BDDec INDF
DoneBD2Dec
	return
	
	
BD3Inc
	movwf FSR
	
	BDInc INDF
	bnc DoneBD3Inc
	
	incf FSR, f
	BDInc INDF
	bnc DoneBD3Inc
	
	incf FSR, f
	BDInc INDF

DoneBD3Inc
	return
	
BD3Dec
	movwf FSR
	
	BDDec INDF
	bc DoneBD3Dec
	
	incf FSR, f
	BDDec INDF
	bc DoneBD3Dec
	
	incf FSR, f
	BDDec INDF
DoneBD3Dec
	return
	
	
BD2Test
	movwf FSR
	movfw INDF ; +0
	incf FSR, f
	iorwf INDF, w; +1
	return
	
BD3Test
	movwf FSR
	movfw INDF ; +0
	incf FSR, f
	iorwf INDF, w; +1
	incf FSR, f
	iorwf INDF, w; +2
	return
	end