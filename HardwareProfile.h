/*
$Id: HardwareProfile.h 202 2012-08-09 14:17:18Z Vlad $
 */

#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H


/******************************************************************************************/
#define GetSystemClock()		(64000000ul)      // Hz
#define GetInstructionClock()	(GetSystemClock()/4)
#define PIC_CLK 40000000ul

#define BAUD_RATE		9600 //115200
#define USE_USART1

/******************************************************************************************/

#define BUZ_ON		LATAbits.LATA4
#define BUZ_ON_TRIS	TRISAbits.TRISA4



#define TX_EN       LATCbits.LATC1
#define TX_EN_TRIS  TRISCbits.TRISC1



#define PCD8544_SCK     LATC3
#define PCD8544_DI      LATD2
#define PCD8544_DC      LATD3
#define PCD8544_SCE     LATC4
#define PCD8544_RES     LATC5

#define PCD8544_SCK_TRIS    TRISCbits.TRISC3
#define PCD8544_DI_TRIS     TRISDbits.TRISD2
#define PCD8544_DC_TRIS     TRISDbits.TRISD3
#define PCD8544_SCE_TRIS    TRISCbits.TRISC4
#define PCD8544_RES_TRIS    TRISCbits.TRISC5



// SENSORS CONNECTIONS
#define CH0_TRIS    &TRISA
#define CH0_LAT     &LATA
#define CH0_IO_BIT  3
#define CH0_AN_NUM  3

#define CH1_TRIS    &TRISD
#define CH1_LAT     &LATD
#define CH1_IO_BIT  7
#define CH1_AN_NUM  27

#define CH2_TRIS    &TRISE
#define CH2_LAT     &LATE
#define CH2_IO_BIT  1
#define CH2_AN_NUM  6

#define CH3_TRIS    &TRISE
#define CH3_LAT     &LATE
#define CH3_IO_BIT  2
#define CH3_AN_NUM  7



#endif  //HARDWARE_PROFILE_H
