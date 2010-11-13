	#include bdmath.inc
	radix dec
	global BD2Inc
	global BD2Dec
	global BD3Inc
	global BD3Dec
	global BD3Test
	
	code 
	
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
	
	
BD3Test
	movwf FSR
	movfw INDF
	incf FSR, f
	iorwf INDF, w
	incf FSR, f
	iorwf INDF, w
	return
	
	end