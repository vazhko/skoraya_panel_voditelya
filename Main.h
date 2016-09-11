/*
$Id: Main.h 202 2012-08-09 14:17:18Z Vlad $
*/


//13.12.2012 v0.11 - ¬ычитаю темновые засветки перед делением.



#ifndef _MAIN_H
#define _MAIN_H


#include <xc.h>

#include "GenericTypeDefs.h"
#include "mTouchConfig.h"
#include "mTouch.h"


#include "messages.h"
#include "MessagesConfig.h"
#include "TimeDelay.h"
#include "usart.h"
#include "eeprom.h"
#include "time.h"
#include "oss.h"
#include "modbus_RTU.h"
#include "sub18.h"
#include "macro.h"
#include "PCD8544.h"


/***************************************************************************/
#define VER "v.1.0"

#define RS232_ADR	0x55
#define SOUND_ON



typedef enum {
    KEY_1 = 0,    
    KEY_2,
    KEY_3,           
    KEY_4, 
    
} KEYS;

typedef struct {
    BYTE st_btn1;
    BYTE st_btn2;
    BYTE st_btn3;
    BYTE st_btn4; 
    
    double U1;
    double U2;
    BYTE  batt_k;
    BYTE  HV_k;
    BYTE side;
    BYTE back;
    BYTE st_fuse;
    
}status_t;


#define BTN_PRESSED(x) (MTouchGetButtonState(x) == CONTROL_PRESSED)
#define BTN_RELEASED(x) (MTouchGetButtonState(x) == CONTROL_RELEASED)
#define BTN_SET(x) (MTouchGetButtonState(x) = CONTROL_PRESSED)


extern void InitializeSystem(void);
extern void Beep(BYTE );
extern void pwm4_load(WORD );


#endif // _MAINDEMO_H
