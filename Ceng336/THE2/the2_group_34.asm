;Group 34
;Furkan Goksel 2237436
;Ceren Gursoy 2237485
;Eren Erisken 2309953
;THE2_v2 on simulation environment
;We tried it on board, it was playable, but in seven segment display the numbers
;may seem conflict (there was no pure number, some segments lights dimmer.) We
;have awared that we need to apply some delay to get more clear numbers, however
;in pdf it says that no need to simulate segment display, just update them.
;So, there was a problem in our 7-segment display, and we know that we have to apply some
;delay to fix it, but since this was tested on simulation environment, we don't implement delay
list P=18F8722

#include <p18f8722.inc>
config OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF


    counterForTimer udata 0x21
    counterForTimer

    level udata 0x22
    level

    w_temp udata 0x23
    w_temp

    status_temp udata 0x24
    status_temp

    flagForCreateAndMove udata 0x25
    flagForCreateAndMove

    remainingBallsForNextLevel udata 0x26
    remainingBallsForNextLevel

    nextLevelFlag udata 0x27
    nextLevelFlag

    flagForLeftButton udata 0x28
    flagForLeftButton

    flagForRightButton udata 0x29
    flagForRightButton

    timer1Low udata 0x2A
    timer1Low

    timer1High udata 0x2B
    timer1High

    newPositionForNewBall udata 0x2C
    newPositionForNewBall

    counterForShift udata 0x2D
    counterForShift

    positionOfTab udata 0x2E ;0A, 1B, 2C, 3D
    positionOfTab

    healthPoints udata 0x2F
    healthPoints

    gameOver udata 0x30
    gameOver

    noNewBall udata 0x31
    noNewBall

    gameFinishNoBallLeft udata 0x32
    gameFinishNoBallLeft

    displayFlag udata 0x33
    displayFlag

    level_flag udata 0x34
    level_flag
    org 0x00
    goto init

    org 0x08
    goto isr

    init:
	movlw 0x81
	movwf T1CON
	movlw b'00001101'
	movwf TRISG
	movlw 0Fh ; Configure A/D
	movwf ADCON1 ; for digital inputs outputs
	clrf TRISA
	clrf TRISB
	clrf TRISC
	clrf TRISD
	clrf TRISH ;7 segment
	clrf TRISJ ;7 segment
   restart:
	clrf level_flag
	clrf timer1High
	clrf timer1Low
	clrf gameOver
	clrf flagForLeftButton
	clrf flagForRightButton
	clrf positionOfTab
	clrf nextLevelFlag
	clrf counterForTimer
	clrf flagForCreateAndMove
	clrf noNewBall
	clrf gameFinishNoBallLeft
	clrf displayFlag
	clrf PORTA
	clrf PORTB
	clrf PORTC
	clrf PORTD
	clrf PORTH
	clrf PORTJ
	clrf PORTG
	clrf LATA
	clrf LATB
	clrf LATC
	clrf LATD
	clrf LATG
	clrf LATH ;7 segment
	clrf LATJ ;7 segment
	clrf TMR1H
	clrf TMR1L
	bsf LATA, 5
	bsf LATB, 5
	movlw d'4'
	movwf remainingBallsForNextLevel
	movlw b'01000111' ; prescaler 256, 8 bit timer
	movwf T0CON
	movlw b'00100000' ; interrupts open, activate timer0 interrupt
	movwf INTCON
	movlw d'61'
	movwf TMR0
	bsf positionOfTab, 0
	bsf positionOfTab, 1
	movlw d'5'
	movwf healthPoints
	movlw 0x01
	movwf level
    waitTheStartPress:
	call segmentDisplay
	btfss PORTG, 0
	bra waitTheStartPress
    waitTheStartRelease:
	call segmentDisplay
	btfsc PORTG,0
	bra waitTheStartRelease
	movff TMR1L, timer1Low
	movff TMR1H, timer1High ; EN SON BURADA KALDIM
	bsf INTCON, 7
	bsf T0CON,7 ; start tmr0
	movlw d'5'
	movwf healthPoints
	movlw 0x01
	movwf level
	incf flagForCreateAndMove, f
    main:
	btfsc flagForCreateAndMove, 0
	call ballCreate
	tstfsz gameOver
	goto restart
	btfsc PORTG, 2
	call shiftRightTheBar
	btfss PORTG, 2
	clrf flagForRightButton
	btfsc PORTG, 3
	call shiftLeftTheBar
	btfss PORTG,3
	clrf flagForLeftButton
	call segmentDisplay
	goto main

    isr:
	call saveRegisters
	btfsc noNewBall, 0
	goto level_3_finish
	movf level, w
	dcfsnz WREG, f
	goto level_1_timer
	dcfsnz WREG, f
	goto level_2_timer
	dcfsnz WREG, f
	goto level_3_timer
	call restoreRegisters
	retfie

    saveRegisters:
	movwf 	w_temp          ;Copy W to TEMP register
	swapf 	STATUS, w       ;Swap status to be saved into W
	clrf 	STATUS          ;bank 0, regardless of current bank, Clears IRP,RP1,RP0
	movwf 	status_temp     ;Save status to bank zero STATUS_TEMP register
	return

    restoreRegisters:
	swapf 	status_temp, w  ;Swap STATUS_TEMP register into W
	movwf 	STATUS          ;Move W into STATUS register
	swapf 	w_temp, f       ;Swap W_TEMP heralde dorudur
	swapf 	w_temp, w       ;Swap W_TEMP into W
	return

    segmentDisplay:
	btfsc displayFlag, 0
	goto display_health
	incf displayFlag
	bcf LATH, 3
	bsf LATH, 0
	movf level,W
	call tableForSegments
	movwf LATJ
	return
	display_health:
	    clrf displayFlag
	    bcf LATH, 0
	    bsf LATH, 3
	    movf healthPoints,W
	    call tableForSegments
	    movwf LATJ
	    return

    level_1_timer:
	movlw d'100'
	incf counterForTimer, f
	cpfseq counterForTimer
	goto notYet
	incf flagForCreateAndMove, f
	dcfsnz remainingBallsForNextLevel,f
	call passLevel2
	clrf counterForTimer
	bcf	INTCON, 2
	movlw	d'61'
	movwf	TMR0
	call restoreRegisters
	retfie

    passLevel2:
	clrf counterForTimer
	movlw d'10'
	movwf remainingBallsForNextLevel
	incf level_flag, F
	return


    level_2_timer:
	movlw d'80'
	incf counterForTimer, f
	cpfseq counterForTimer
	goto notYet
	incf flagForCreateAndMove,f
	dcfsnz remainingBallsForNextLevel,f
	call passLevel3
	clrf counterForTimer
	bcf	INTCON, 2
	movlw	d'61'
	movwf	TMR0
	call restoreRegisters
	retfie

    passLevel3:
	clrf counterForTimer
	movlw d'16'
	movwf remainingBallsForNextLevel
	incf level_flag, F
	return


    level_3_timer:
	movlw d'70'
	incf counterForTimer, f
	cpfseq counterForTimer
	goto notYet
	incf flagForCreateAndMove,f
	dcfsnz remainingBallsForNextLevel,f
	call noCreate
	clrf counterForTimer
	bcf	INTCON, 2
	movlw	d'61'
	movwf	TMR0
	call restoreRegisters
	retfie

    noCreate:
	incf noNewBall,f ;indicates noNewBall
	clrf counterForTimer
	movlw d'5'
	movwf remainingBallsForNextLevel
	return

    level_3_finish:
	movlw d'70'
	incf counterForTimer, f
	cpfseq counterForTimer
	goto notYet
	incf flagForCreateAndMove,f
	dcfsnz remainingBallsForNextLevel,f
	incf gameFinishNoBallLeft,f
	clrf counterForTimer
	bcf	INTCON, 2
	movlw	d'61'
	movwf	TMR0
	call restoreRegisters
	retfie

    notYet: ;for timer interrupt
	bcf	INTCON, 2
	movlw	d'61'
	movwf	TMR0
	call restoreRegisters
	retfie

    shiftRightTheBar:
	btfsc flagForRightButton,0
	return
	incf flagForRightButton,f
	btfsc positionOfTab,0
	goto barOnABRight
	btfsc positionOfTab,1
	goto barOnBCRight
;	btfsc LATC,5
;	goto barOnCD on CD can't move right
	return
    shiftLeftTheBar:
	btfsc flagForLeftButton,0
	return
	incf flagForLeftButton,f
	btfsc positionOfTab,0
	return
	btfsc positionOfTab,1
	goto barOnBCLeft
	btfsc positionOfTab,2
	goto barOnCDLeft
	return

    barOnABRight:
	bcf LATA,5
	bcf positionOfTab, 0
	bsf LATC,5
	bsf positionOfTab, 2
	return

    barOnBCRight:
	bcf LATB,5
	bcf positionOfTab, 1
	bsf LATD,5
	bsf positionOfTab, 3
	return

    barOnBCLeft:
	bcf LATC,5
	bcf positionOfTab,2
	bsf LATA,5
	bsf positionOfTab,0
	return

    barOnCDLeft:
	bcf LATD,5
	bcf positionOfTab,3
	bsf LATB,5
	bsf positionOfTab,1
	return

    ballCreate:
	clrf flagForCreateAndMove
	btfsc noNewBall, 0 ;No new ball
	goto moduloDone
	movf timer1Low,W
	andlw b'00000111'
	movwf newPositionForNewBall
	movlw d'4'
    moduloOpt:
	subwf newPositionForNewBall, W
	bn moduloDone
	movwf newPositionForNewBall
	movlw d'4'
	bra moduloOpt
    moduloDone:
	call nowCreateAndMove ; create new ball here
	btfsc noNewBall, 0 ;No new ball
	return
	movf level, w
	dcfsnz WREG, f
	goto shift_1 ;level 1
	dcfsnz WREG, f
	goto shift_3 ;level 2
	dcfsnz WREG, f
	goto shift_5 ;level 3

    shift_1:
	movf timer1High, W
	rrcf WREG, W
	rrcf timer1Low, F
	rrcf timer1High,F
	btfsc level_flag, 0
	call increaseLevel
	return
    shift_3:
	movlw d'3'
	movwf counterForShift
    shift_3_loop:
	movf timer1High, W
	rrcf WREG, W
	rrcf timer1Low, F
	rrcf timer1High,F
	decfsz counterForShift
	bra shift_3_loop
	btfsc level_flag, 0
	call increaseLevel
	return
    shift_5:
	movlw d'5'
	movwf counterForShift
    shift_5_loop:
	movf timer1High, W
	rrcf WREG, W
	rrcf timer1Low, F
	rrcf timer1High,F
	decfsz counterForShift
	bra shift_5_loop
	return

    nowCreateAndMove:
	;bcf STATUS, 0 ;make carry bit 0 to shift not necessary actually
	rlncf LATA ; shift left
	rlncf LATB ; shift left
	rlncf LATC ; shift left
	rlncf LATD ; shift left
	call lifeCalculation
	tstfsz gameOver
	return
	btfsc gameFinishNoBallLeft, 0
	incf gameOver,f ;Need debug
	call setTabAgain
	btfsc noNewBall, 0
	return
	incf newPositionForNewBall, f
	dcfsnz newPositionForNewBall ;if it is 1, A
	bsf LATA,0
	dcfsnz newPositionForNewBall ;if it is 2, B
	bsf LATB,0
	dcfsnz newPositionForNewBall ;if it is 3, C
	bsf LATC,0
	dcfsnz newPositionForNewBall ;if it is 4, D
	bsf LATD,0
	return ;moveAndCreateBalls

    lifeCalculation:
	btfsc LATA,6
	call checkLatA
	tstfsz gameOver
	return
	btfsc LATB,6
	call checkLatB
	tstfsz gameOver
	return
	btfsc LATC,6
	call checkLatC
	tstfsz gameOver
	return
	btfsc LATD,6
	call checkLatD
	return

    checkLatA:
	bcf LATA,6
	btfsc positionOfTab, 0
	return
	call decreaseHealthPoints
	return
    checkLatB:
	bcf LATB,6
	btfsc positionOfTab, 1
	return
	call decreaseHealthPoints
	return
    checkLatC:
	bcf LATC,6
	btfsc positionOfTab, 2
	return
	call decreaseHealthPoints
	return
    checkLatD:
	bcf LATD,6
	btfsc positionOfTab, 3
	return
	call decreaseHealthPoints
	return
    setTabAgain:
	btfsc positionOfTab, 0
	bsf PORTA, 5
	btfsc positionOfTab, 1
	bsf PORTB, 5
	btfsc positionOfTab, 2
	bsf PORTC, 5
	btfsc positionOfTab, 3
	bsf PORTD, 5
	return

    tableForSegments:
	movf WREG, F
	bz sendZero
	decf WREG, F
	bz sendOne
	decf WREG, F
	bz sendTwo
	decf WREG, F
	bz sendThree
	decf WREG, F
	bz sendFour
	decf WREG, F
	bz sendFive
	return ; never executed
    sendZero:
	movlw b'00111111' ;0 representation in 7-seg. disp. portJ
	return
    sendOne:
	movlw  b'00000110' ;1 representation in 7-seg. disp. portJ
	return
    sendTwo:
	movlw b'01011011' ;2 representation in 7-seg. disp. portJ
	return
    sendThree:
	movlw b'01001111' ;3 representation in 7-seg. disp. portJ
	return
    sendFour:
	movlw b'01100110' ;4 representation in 7-seg. disp. portJ
	return
    sendFive:
	movlw b'01101101' ;5 representation in 7-seg. disp. portJ
	return
    decreaseHealthPoints:
	dcfsnz healthPoints, f ;check game end
	incf gameOver, F
	return
    increaseLevel:
	incf level, F
	clrf level_flag
	return
END
