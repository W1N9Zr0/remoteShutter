	#include shutter-lowlevel.inc

BUTTON_REPEAT_DELAY equ 32
BUTTON_HOLD_DELAY equ 200

	extern BD2Inc
	extern BD2Dec
	extern BD3Inc
	extern BD3Dec
	extern BD3Test
	extern ClockInc
	extern ClockDec
	extern IntInc
	extern IntDec

	#include display.inc
	
	#include states.inc
	#include timer2interrupt.inc


IncE
	incFwrap quicke, 17, 0
DecE
	decFwrap quicke, 0, 17

IncT
	incFwrap quickt, 17, 3
DecT
	decFwrap quickt, 3, 17

IncR
	incFwrap quickr, 14, 4
DecR
	decFwrap quickr, 4, 14




TimeTable0
	TableLookup
	dt ToBD( 5), ToBD(10), ToBD(25), ToBD(50)
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 0), ToBD( 0)
TimeTable1
	TableLookup
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 1), ToBD( 2), ToBD( 4), ToBD( 8)
	dt ToBD(16), ToBD(32), ToBD(64), ToBD(28)
	dt ToBD(56), ToBD(12), ToBD(24), ToBD(48)
	dt ToBD(96), ToBD(92)
TimeTable2
	TableLookup
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 0)
	dt ToBD( 0), ToBD( 0), ToBD( 0), ToBD( 1)
	dt ToBD( 2), ToBD( 5), ToBD(10), ToBD(20)
	dt ToBD(40), ToBD(81)
	