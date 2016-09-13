/*
$Id: Main.c 201 2012-08-09 14:15:36Z Vlad $
 */

#include    "Main.h"

//#include	"font13.h"
//#include	"font23.h"
//#include	"cour13.h"


//#define SHOW_PACKETS  
/***GLOBAL VAR*****************************************************************/

volatile int sys_tick = 0;
extern unsigned char ow_bit;


/** LOCAL PROTOTYPES **********************************************************/
void tsk_process_btn(void);
void tsk_display(void);
void tsk_ds18b20(void);
void tsk_rx(void);
void tsk_btn(void);
void tsk_int(void);

/****************************************************************************/
EEPROM_INIT;

/****************************************************************************/
status_t stat;


char str[40];
char out_packet[27] ; // ">Vom@B1=1 B2=1 B3=1 B4=1$\r";
char in_packet[54];// = ">Vodi@V1=00.0 V2=00.0 Con=0 220=0 LRi=0 LRe=0 Fus=0$\r";


void main(void){

    Nop();
    InitMessages();
    InitializeSystem();
    pcd8544_init();
    
    Nop();
    Nop();


    //INTCONbits.GIE = 1;

    Beep(10);



    while(1){


        tsk_display();
        tsk_process_btn();
        tsk_rx();
        tsk_btn();


        Nop();
        Nop();


        if((FERR) || (OERR)){
            CREN = 0;
            NOP();
            CREN = 1;
        }
        TX_EN = 0;

        if(SWDTEN == 0){
            //SWDTEN = 1;
        }
        ClrWdt();

        if(INTCONbits.GIE == 0){
            INTCONbits.GIE = 1;
        }

        // обработчик state machine
        ProcessMessages();

    }
}

/******************************************************************************************/
// обработка кнопок

void tsk_process_btn(void){
    static int prev_tick, i;
    static BYTE b_long = 0;

    // Decode all controls.
    MTouchDecode();


    // з
    if(BTN_PRESSED(KEY_1)){
        Beep(10);
        stat.st_btn1 = 1;
    }

    //
    if(BTN_PRESSED(KEY_2)){
        Beep(10);
        stat.st_btn2 = 1;

    }

    // 
    if(BTN_PRESSED(KEY_3)){
        //Beep(10);
        stat.st_btn3 = 1;

    }

    //
    if(BTN_PRESSED(KEY_4)){
        //Beep(10);
        stat.st_btn4 = 1;

    }




}

/******************************************************************************************/
void tsk_display(void){

    OS_TaskInit();


    OS_TaskStart();
    // обновление показаний 500мс
    OS_Delay(500);
    //blink ++;





    OS_Yield();


#ifdef SHOW_PACKETS
    OS_Yield();

    sprintf(str, "L%1u H%1u S%1u R%1u N%1u L%2u B%1u F%1u C%1u",
            stat.st_12V, stat.st_220V, stat.st_lt_side, stat.st_lt_back, stat.st_lt_noshy,
            stat.st_lt_salon, stat.st_lt_blue, stat.st_fan, stat.st_kond);
    LabelSetTxt(&lb_paket_out, str);

    OS_Yield();

    sprintf(str, "%2.1f %2.1f C%1u H%1u S%1u R%1u F%1u",
            stat.U1, stat.U2, stat.batt_k, stat.HV_k, stat.st_k_side,
            stat.st_k_back, stat.st_fuse);
    LabelSetTxt(&lb_paket_in, str);
#endif


    OS_Yield();

    OS_TaskEnd();



}

/******************************************************************************************/
void tsk_rx(void){
  
        if(GetMessage(MES_RX)){
            Nop();
            Nop();
            
            
            //>Vom@B1=1 B2=1 B3=1 B4=1$
            sprintf(out_packet, ">Bom@B1=%u B2=%u B3=%u B4=%u$\r",
                    stat.st_btn1, stat.st_btn2, stat.st_btn3, stat.st_btn4);

            // ответ
            putstrc(out_packet);

            // расшифровка
            sprintf(str, "%c%c.%c", in_packet[9], in_packet[10], in_packet[12]);
            stat.U1 = atof(str);
            sprintf(str, "%c%c.%c", in_packet[17], in_packet[18], in_packet[20]);
            stat.U2 = atof(str);


            if(in_packet[26] == '1'){
                stat.batt_k = 1;
            } else {
                stat.batt_k = 0;
            }
            // 220В включается нулем
            if(in_packet[32] == '0'){
                stat.HV_k = 1;
            } else {
                stat.HV_k = 0;
            }
            if(in_packet[38] == '1'){
                stat.side = 1;
            } else {
                stat.side = 0;
            }
            if(in_packet[44] == '1'){
                stat.back = 1;
            } else {
                stat.back = 0;
            }
            if(in_packet[50] == '1'){
                stat.st_fuse = 1;
            } else {
                stat.st_fuse = 0;
            }
            
            stat.st_btn1 = 0;
            stat.st_btn2 = 0;
            stat.st_btn3 = 0;
            stat.st_btn4 = 0;
        }


}

/******************************************************************************************/
void tsk_btn(void){
    static int prev_tick;

    if(prev_tick == sys_tick) return;
    prev_tick = sys_tick;

    //MTouchAcquisition();
}