/*
$Id: misc.c 202 2014-12-01 Vlad $
 */

#include "Main.h"
#include "math.h"

/******************************************************************************************/
void pwm4_load(WORD load){

    if(load & 1) CCP4CONbits.DC4B0 = 1;
    else CCP4CONbits.DC4B0 = 0;
    if(load & 2) CCP4CONbits.DC4B1 = 1;
    else CCP4CONbits.DC4B1 = 0;

    CCPR4L = load >> 2;
}



//double temp_t;

/****************************************************************************/
void InitializeSystem(void){


    unsigned int pll_startup_counter = 600;

    OSCCON = 0b01110000;
    OSCTUNEbits.PLLEN = 1; //Enable the PLL and wait 2+ms until the PLL locks before enabling USB module
    while(pll_startup_counter --);



    RCONbits.IPEN = 1;

    // Подобрано 1ms
    T2CONbits.T2CKPS = 3;
    PR2 = 200;
    T2CONbits.T2OUTPS = 3;
    T2CONbits.TMR2ON = 1;
    IPR1bits.TMR2IP = 1;
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;


    T4CONbits.T4CKPS = 3;
    PR4 = 100;
    T4CONbits.T4OUTPS = 0;
    T4CONbits.TMR4ON = 1;
    IPR5bits.TMR4IP = 1;
    PIR5bits.TMR4IF = 0;
    PIE5bits.TMR4IE = 1;

    MTouchInit();

    ANSELA = 0b00000000;
    ANSELB = 0b00000000;
    ANSELC = 0b00000000;
    ANSELD = 0b00000000;
    ANSELE = 0b00000000;

    CCP5CON = 0;

    // STEP 2
    // Sensors initialization. All sensors must be initialized (see MTOUCH_SENSORS_NUMBER in mTouchConfig.h).
    MTouchSetSensor(0, CH0_TRIS, CH0_LAT, CH0_IO_BIT, CH0_AN_NUM, - 1, - 1, - 1);
    MTouchSetSensor(1, CH1_TRIS, CH1_LAT, CH1_IO_BIT, CH1_AN_NUM, - 1, - 1, - 1);
    MTouchSetSensor(2, CH2_TRIS, CH2_LAT, CH2_IO_BIT, CH2_AN_NUM, - 1, - 1, - 1);
    MTouchSetSensor(3, CH3_TRIS, CH3_LAT, CH3_IO_BIT, CH3_AN_NUM, - 1, - 1, - 1);


    MTouchSetButton(KEY_1, 0, DECODE_ONE_EVENT);
    MTouchSetButton(KEY_2, 2, DECODE_ONE_EVENT);
    MTouchSetButton(KEY_3, 3, DECODE_ONE_EVENT);
    MTouchSetButton(KEY_4, 1, DECODE_ONE_EVENT);



    uart16_init();
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    RCIP = 0;
    RCIE = 1;
    TX_EN = 0;
    TX_EN_TRIS = 0;


    PCD8544_SCK_TRIS = 0;
    PCD8544_DI_TRIS = 0;
    PCD8544_DC_TRIS = 0;
    PCD8544_SCE_TRIS = 0;
    PCD8544_RES_TRIS = 0;
    
    


    INTCONbits.PEIE = 1;

    // после инициал всего
    //	INTCONbits.GIE = 1;


}//end InitializeSystem




/******************************************************************************************/
#define SysDelay1Ms()  { UINT16 d=1067; while(d--){Nop();} }

void SysDelayMs(UINT16 delay){
    while(delay --){
        SysDelay1Ms();
    }
}


