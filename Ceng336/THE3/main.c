#pragma config OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF

#include <xc.h>
#include "breakpoints.h"
/*
 Group 34
 Furkan Goksel 2237436
 Ceren Gursoy 2237485
 Eren Erisken 2309953
 
 We use round robin with interrupts approach in our design, 
 * In main function, firstly we set firstTime variable used in init() function to call init_complete() breakpoint 
 * in only for the first time of the program.  After that, by calling init() function, we set the first values of 
 * the global variables as zero and arrange the special function registers. We set timer 0, timer 1 and timer 3 for 
 * using debouncing purpose. Since 5 seconds , 2 seconds are beyond the timers. We use software defined counter, to
 * arrange the required time (each timer0 and timer 1 overflow is 50 ms). Also we arrange the ADC in init then start the program. we start with the first check, 
 * which is whether adc stops its work or not.Then, we calculate the ADC value with convertADC() according to Table 1 
 * in homework text and hold it in curGuess variable. According to value given by user we call upArrow and downArrow to
 * set the leds. For debouncing simply we use timer 3 to check whether given value 1 or 0 is consistent during 10 ms for 
 * changing the state of button. State of the game (game over, correct guess etc.) is also managed by flags. Display
 * number function is used to set 7-segment display.
 
 */
int counterForTimer0;
int counterForTimer1;
int timer1For2Sec;
volatile int counterFor2Sec;
int adResult;
volatile int adc_value;
int curGuess;
char firstTime;
char dummyReadB;
char gameOver;
char endGame;
char correctGuess;
char timer3Tick;
char timer1Tick;
char adcUpdated; 
char timer3Started;
char rb4Last;

void __interrupt() isRoutine(){
    if(PIR1bits.TMR1IF == 1){
        if(timer1For2Sec){ //For 2 seconds
            counterFor2Sec = counterFor2Sec+1;
            if(counterFor2Sec % 10 == 0)
            {
                hs_passed();
                timer1Tick = 1;
            }
            if(counterFor2Sec == 40){
                
                TMR1H  = 0x0B;
                TMR1L = 0xDF;
                PIR1bits.TMR1IF = 0;
            }
            else{
                TMR1H  = 0x0B;
                TMR1L = 0xDF;
                PIR1bits.TMR1IF = 0;
            }
        }
        else{//For 5 seconds
            //50 ms 
            counterForTimer1 = counterForTimer1+1;
            if(counterForTimer1 % 10 == 0)
            {
                hs_passed(); // is it correct here?
            }
            if(counterForTimer1 == 100){
                //game Over
                TMR1H  = 0x0B;
                TMR1L = 0xDF;
                counterForTimer1  = 0;
                PIR1bits.TMR1IF = 0;
                gameOver = 1;
                T0CONbits.TMR0ON = 0;
                INTCONbits.TMR0IF = 0;
                INTCONbits.RBIE = 0;
            }
            else{
                TMR1H  = 0x0B;
                TMR1L = 0xDF;
                PIR1bits.TMR1IF = 0;
            }
        }
        
    }
    
    if(INTCONbits.TMR0IF == 1){
        //Since it is 50 ms
        TMR0H = 0x0B;
        TMR0L = 0xDF;
        ADCON0bits.GO = 1; //Start adc
        INTCONbits.TMR0IF = 0;
    }
    
    if(PIR1bits.ADIF == 1){ //finish adc
        adResult = 256*ADRESH+ADRESL;
        adc_value = adResult;
        adc_complete();
        adcUpdated = 1;
        PIR1bits.ADIF = 0;
    }
    if(PIR2bits.TMR3IF == 1)
    { //Bouncing debouncing, change state since 10 ms pasts
        T3CONbits.TMR3ON = 0; // disable timer3
        PIR2bits.TMR3IF = 0;
        rb4Last = !rb4Last;
        if(rb4Last){
            timer3Tick = 1; //Tell button is pressed
            rb4_handled();
        }
    }
    if(INTCONbits.RBIF == 1){ //Bouncing debouncing, set timer for bouncing
        if(PORTBbits.RB4 == 1){
            if(!rb4Last){
                TMR3H = 0x3C; // start Timer3
                TMR3L = 0xB0;
                T3CONbits.TMR3ON = 1;
            }
            else{
                 T3CONbits.TMR3ON = 0;
            }
        }
        else{
            if(rb4Last){
                TMR3H = 0x3C; // start Timer3
                TMR3L = 0xB0;
                T3CONbits.TMR3ON = 1;
            }
            else{
                T3CONbits.TMR3ON = 0;
            }
        }
        dummyReadB = LATB; //For clearing the interrupt
        dummyReadB = PORTB;
        INTCONbits.RBIF = 0;
    }
}


void upArrow(){
    LATC = 0;
    LATD = 0;
    LATE = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    LATCbits.LATC1 = 1;
    PORTCbits.RC1 = 1;
    LATD = 0x0F;
    PORTD = 0x0F;
    LATEbits.LATE1 = 1;
    PORTEbits.RE1 = 1;
    latcde_update_complete();
}

void downArrow(){
    LATC = 0;
    LATD = 0;
    LATE = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    PORTCbits.RC2 = 1;
    LATCbits.LATC2 = 1;
    LATD = 0x0F;
    PORTD = 0x0F;
    LATEbits.LATE2 = 1;
    PORTEbits.RE2 = 1;
    latcde_update_complete();
}

void clearLeds()
{
    LATC = 0;
    LATD = 0;
    LATE = 0;
    latcde_update_complete();
}

void displayNumber(int number) //7 segment-display
{
    LATHbits.LATH0 = 0;
    LATHbits.LATH1 = 0;
    LATHbits.LATH2 = 0;
    LATHbits.LATH3 = 1; // rightmost 7-segment
    
    switch(number)
    {
        case 0:
            LATJ = 0b00111111;
            break;
        case 1:
            LATJ = 0b00000110;
            break;
        case 2:
            LATJ = 0b01011011;
            break;
        case 3:
            LATJ = 0b01001111;
            break;
        case 4:
            LATJ = 0b01100110;
            break;
        case 5:
            LATJ = 0b01101101;
            break;
        case 6:
            LATJ = 0b01111101;
            break;
        case 7:
            LATJ = 0b00000111;
            break;
        case 8:
            LATJ = 0b01111111;
            break;
        case 9:
            LATJ = 0b01100111;
            break;
    }
    latjh_update_complete();
}

void clearDisplay()
{
    LATJ = 0;
    latjh_update_complete();
}

void init(void){
    gameOver = 0;
    endGame = 0;
    correctGuess = 0;
    timer3Tick = 0; //rb flag
    timer1Tick = 0; //timer 1 flag
    rb4Last = 0;
    timer3Started = 0;
    adcUpdated = 0;
    counterFor2Sec = 0;
    timer1For2Sec = 0;
    counterForTimer0 = 0;
    counterForTimer1 = 0;
    TRISB = 0;
    TRISBbits.RB4 = 1; //RB input
    LATB = 0;
    PORTB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    TRISH = 0;
    TRISJ = 0;
    LATC = 0;
    LATD = 0;
    LATE = 0;
    LATH = 0;
    TRISHbits.RH4 = 1; // AN 12 
    LATJ = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    T1CON  = 0xB0; //1011 0000
    T0CON = 0x02; //0000 0010
    T3CON = 0x90; // set to interrupt each 10 ms for checking rb4 debouncing 1001 0000
    TMR1H  = 0x0B; 
    TMR1L = 0xDF;
    TMR0H = 0x0B;
    TMR0L = 0xDF;
    TMR3H = 0x3C;
    TMR3L = 0xB0;
    PIE1 = 0x41;  //0100 0001
    PIE2bits.TMR3IE = 1;
    INTCON = 0xE8; //1110 1000
    TMR0ON = 1;
    TMR1ON = 1;
    ADCON0 = 0x30; //0011 0000
    ADCON1 = 0; /*all pins analog no external voltage*/
    ADCON2 = 0x92; /* right justified -  - f_osc/32 1001 0010 */ 
    ADON = 1;      
    if(firstTime){
        firstTime = 0;
        init_complete();
    }
    
}

void convertADC() //arranging guess according to table
{
    if(adc_value > 918)
        curGuess = 9;
    else
        curGuess = (adc_value - 1) / 102;
}

void main(void) {
    firstTime = 1;
    init();
    while(1){
        if(adcUpdated)
        {
            adcUpdated = 0;
            convertADC();
            if(!endGame)
                displayNumber(curGuess);
        }
        if(gameOver) // time is up, executed once
        {
            TMR1H  = 0x0B;
            TMR1L = 0xDF;
            T1CONbits.TMR1ON = 1;
            timer1For2Sec = 1;
            game_over();
            displayNumber(special_number());
            clearLeds();
            endGame = 1; // set the state to endgame
            gameOver = 0;
        }
        else if(correctGuess) // user guessed correctly
        {
           // hs_passed(); 
            TMR1H  = 0x0B;
            TMR1L = 0xDF;
            T1CONbits.TMR1ON = 1;
            timer1For2Sec = 1;
            correct_guess();
            displayNumber(special_number());
            clearLeds();
            endGame = 1; // set the state to endgame
            correctGuess = 0;
        }
        else if(endGame && timer1Tick) // 2 sec blinking period
        {
            timer1Tick = 0;
            if(counterFor2Sec == 20)
            {
                displayNumber(special_number());
                //hs_passed();
            }
            else if(counterFor2Sec == 10 || counterFor2Sec == 30)
            {
                clearDisplay();
                //hs_passed();
            }
            else if(counterFor2Sec == 40) // 2 sec over
            {
                //hs_passed();
                restart();
                init();
                continue;
            }
        }
        else // game continues
        {
            if(timer3Tick) // RB4 is high for > 10 ms
            {
                
                timer3Tick = 0;
                if(curGuess > special_number())
                {
                    downArrow();
                }
                else if(curGuess < special_number())
                {
                    upArrow();
                }
                else // correct guess
                {
                    correctGuess = 1;
                    T0CONbits.TMR0ON = 0;
                    T1CONbits.TMR1ON = 0;
                    INTCONbits.RBIE = 0;
                }
                
            }
        }
    }
    return;
}