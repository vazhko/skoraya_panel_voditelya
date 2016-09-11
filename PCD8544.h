/* 
 * File:   PCD8544.h
 * Author: Vlad
 *
 * Created on 10 вересня 2016, 21:59
 */

#ifndef PCD8544_H
#define	PCD8544_H

void pcd8544_send_byte(BYTE data);
void pcd8544_data(BYTE data);
void pcd8544_cmd(BYTE data);
void pcd8544_init(void);

#endif	/* PCD8544_H */

