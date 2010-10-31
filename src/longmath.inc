
LongLoad macro F, CONST
	movlw (CONST & 0xff)
	movwf (F)
	movlw ((CONST >> 8) & 0xff)
	movwf (F) + 1
	endm

LongInc macro F
	local EndInc

	incfsz (F)+0, f
	 goto EndInc

	incf (F)+1, f
EndInc
	endm

LongCopy macro DST, SRC
	movfw (SRC)+1
	movwf (DST)+1
	movfw (SRC)
	movwf (DST)
	endm

LongRLF macro F
	rlf (F), f
	rlf (F)+1, f
	endm

LongRRF macro F
	bcf STATUS, C
	btfsc (F)+1, 7
	bsf STATUS, C
	
	rrf (F)+1, f
	rrf (F), f
	endm

LongAdd macro DST, SRC
	movfw (SRC)
	addwf (DST), f
	btfsc STATUS, C
	incf (DST)+1, f
	movfw (SRC)+1
	addwf (DST)+1, f
	endm

LongDec macro F
	local EndInc

	decf (F)+0, f
	incfsz (F)+0, w
	 goto EndInc

	decf (F)+1, f
EndInc
	endm

LongSub	macro DST, X, Y
	movfw (Y) + 1
	subwf (X) + 1, w
	movwf (DST) + 1
	movfw (Y)
	subwf (X), w
	movwf (DST)
	btfss STATUS, C
	 decf (DST) + 1, f
	
	endm

LongNeg	macro	F
	comf    (F), f
	comf    (F)+1, f
	LongInc (F)
	endm
