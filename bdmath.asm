	#include bdmath.inc
	radix dec
	global BD2Inc
	global BD2Dec
	
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
	
	end