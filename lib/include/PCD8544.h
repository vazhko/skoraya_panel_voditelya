/* 
 * File:   PCD8544.h
 * Author: Vlad
 *
 * Created on 10 ������� 2016, 21:59
 */

#ifndef PCD8544_H
#define	PCD8544_H

#include "GenericTypeDefs.h"


#define DISPLAY_WIDTH 84
#define DISPLAY_PAGES 6
#define DISPLAY_HEIGHT (DISPLAY_PAGES * 8)

#define ARRAYSIZE(array) (sizeof(array) / sizeof(array[0]))


void pcd8544_send_byte(BYTE data);
void pcd8544_data(BYTE data);
void pcd8544_cmd(BYTE data);
void pcd8544_setpos(BYTE page, BYTE x);
void pcd8544_init(void);
void pcd8544_clear(void);

#endif	/* PCD8544_H */

