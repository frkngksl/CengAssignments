LIST    P=18F8722

#INCLUDE <p18f8722.inc>
CONFIG OSC=HSPLL, FCMEN=OFF, IESO=OFF,PWRT=OFF,BOREN=OFF, WDT=OFF, MCLRE=ON, LPT1OSC=OFF, LVP=OFF, XINST=OFF, DEBUG=OFF
secCounterL udata 0x20
secCounterL
secCounterH udata 0x21
secCounterH
secCounterU udata 0x22
secCounterU
portBValue udata 0x23
portBValue
portCValue udata 0x24
portCValue
counter udata 0x25
counter
ledForResult udata 0x26
ledForResult
    
 
    org 0x00
    goto main
    
    
init:
    movlw b'00010000' ; RA4 input
    movwf TRISA
    clrf PORTA
    clrf LATA
    
    
    movlw b'00011000';RE3,RE4 input
    movwf TRISE
    clrf PORTE
    clrf LATE
    
    movlw h'00'
    movwf TRISB
    movwf TRISC
    movwf TRISD ;Clear outputs
    
    clrf LATB
    clrf LATC
    clrf LATD
    
    return

countReset:
    movlw h'00'
    movwf portBValue
    movwf portCValue
    movwf counter
    movwf ledForResult
    return
    
initialOneSecLed:
    movlw h'34'
    movwf secCounterU
    movlw h'10'
    movwf secCounterH
    movlw h'A0'
    movwf secCounterL
    movlw 0x0F
    movwf LATB
    movwf LATC
    movlw 0xFF
    movwf LATD
    waitL: ;low part
	decfsz secCounterL, F
	bra waitL
    waitH: ;high part
	comf secCounterL, F
	decfsz secCounterH, F
	bra waitL
    waitU:
	comf secCounterH, F
	decfsz secCounterU, F
	bra waitL
    movlw h'00'
    movwf LATB
    movwf LATC
    movwf LATD
return

    
operationSelect:
    btfss PORTA, 4
    bra operationSelect
    bra pushAddition
    
    pushAddition:
	btfsc PORTA, 4
	bra pushAddition
	bra selectedAddition

    selectedAddition:
	btfsc PORTA, 4 ;eger hala 0sa pushSubtractioni geç
	bra pushSubtraction
	btfss PORTE, 3 ;eger burdayken RE3'e basilirsa operation Additiona geç
	bra selectedAddition
	bra WaitReleaseForAddition
    
    pushSubtraction:
	btfsc PORTA,4
	bra pushSubtraction
	bra selectedSubtraction

    selectedSubtraction:
	btfsc PORTA,4
	bra pushAddition
	btfss PORTE,3 ;Eger RE3'e basilirsa subtraction secilmis demek
	bra selectedSubtraction
	bra WaitReleaseForSubtraction

	
WaitReleaseForAddition:
    btfsc PORTE, 3 ;clearsa birak
    bra WaitReleaseForAddition
    bra operationAdditionPortB

    
operationAdditionPortB:
    btfsc PORTE, 3
    bra operationAdditionReleaseC
    btfsc PORTE, 4
    call increasePortB
    bra operationAdditionPortB

increasePortB:
    btfsc PORTE,4
    bra increasePortB
    movf portBValue, W
    sublw 4
    bz portBWillBe0
    INCF portBValue,F
    movf LATB, W
    addwf LATB, W
    INCF WREG, F
    movwf LATB
    return
    
portBWillBe0:
    movlw 0x00
    movwf portBValue
    movwf LATB
    return
 
operationAdditionReleaseC:
    btfsc PORTE, 3
    bra operationAdditionReleaseC
    bra operationAdditionPortC

operationAdditionPortC:
    btfsc PORTE, 3
    bra resultAddition
    btfsc PORTE, 4
    call increasePortC
    bra operationAdditionPortC

increasePortC:
    btfsc PORTE,4
    bra increasePortC
    movf portCValue, W
    sublw 4
    bz portCWillBe0
    INCF portCValue, F
    movf LATC, W
    addwf LATC,W
    INCF WREG, F
    movwf LATC
    return

portCWillBe0:
    movlw 0x00
    movwf portCValue
    movwf LATC
    return    
    
resultAddition:
    btfsc PORTE, 3
    bra resultAddition
    movf portBValue, W
    addwf portCValue, W
    movwf counter  
ResultLoop:
    decf counter, f
    bn waitForResult
    movf ledForResult, W
    addwf ledForResult,W
    INCF WREG, F
    movwf ledForResult
    bra ResultLoop


WaitReleaseForSubtraction:
    btfsc PORTE, 3
    bra WaitReleaseForSubtraction
    bra operationSubtractionPortB

operationSubtractionPortB:
    btfsc PORTE, 3
    bra operationSubtractionReleaseC
    btfsc PORTE, 4
    call increasePortB
    bra operationSubtractionPortB
    
operationSubtractionReleaseC:
    btfsc PORTE, 3
    bra operationSubtractionReleaseC
    bra operationSubtractionPortC
    
operationSubtractionPortC:
    btfsc PORTE, 3
    bra resultSubtraction
    btfsc PORTE, 4
    call increasePortC
    bra operationSubtractionPortC

resultSubtraction:
    btfsc PORTE, 3
    bra resultSubtraction
    movf portBValue, W
    subwf portCValue, W
    bn BisBigger
    movwf counter  
    bra ResultLoop

BisBigger:
    movf portCValue, W
    subwf portBValue, W
    movwf counter
    bra ResultLoop
    
    
waitForResult:
    movlw h'34'
    movwf secCounterU
    movlw h'10'
    movwf secCounterH
    movlw h'9F'
    movwf secCounterL
    movff ledForResult, LATD
    waitLR: ;low part
	decfsz secCounterL, F
	bra waitLR
    waitHR: ;high part
	comf secCounterL, F
	decfsz secCounterH, F
	bra waitLR
    waitUR:
	comf secCounterH, F
	decfsz secCounterU, F
	bra waitLR
    movlw 0x00
    movwf LATB
    movwf LATC
    movwf LATD
    return
    
main:
    call init
    call initialOneSecLed
    loop:
	call countReset
	call operationSelect
    goto loop
    end
    


