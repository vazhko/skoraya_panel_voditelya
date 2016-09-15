#include <xc.h>
#include "PCD8544.h"


//http://aterlux.ru/index.php?page=article&art=pcd8544
//http://roboforum.ru/forum2/topic5192.html

void pcd8544_send_byte(BYTE data){
    BYTE i;

    PCD8544_SCE = 0; // Низкий уровень на линии SCE
    Nop();
    for(i = 0; i < 8; i ++){
        PCD8544_SCK = 0; // Низкий уровень на линии SCK
        Nop();
        if(data & 0x80){
            PCD8544_DI = 1; // Передача 1
        } else {
            PCD8544_DI = 0; // Передача 0
        }
        data <<= 1;
        Nop();
        PCD8544_SCK = 1; // Высокий уровень на линии SCK
    }
    PCD8544_SCE = 1; // Высокий уровень на линии SCE
}

void pcd8544_data(BYTE data){
    PCD8544_DC = 1; // Высокий уровень на линии DC: данные
    pcd8544_send_byte(data);
}

void pcd8544_cmd(BYTE data){
    PCD8544_DC = 0; // Низкий уровень на линии DC: инструкция
    pcd8544_send_byte(data);
}

void pcd8544_init(void){
    PCD8544_RES = 0; // Низкий уровень на линии RES
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    PCD8544_RES = 1; // Высокий уровень на линии RES
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    pcd8544_cmd(0x21); // расширенный набор команд
    pcd8544_cmd(0x80 + 58); // напряжение смещения

    pcd8544_cmd(0x04); // Режим температурной коррекции 0
    pcd8544_cmd(0x13); // схема смещения 1:48
    pcd8544_cmd(0x20);
    pcd8544_cmd(0x0c); // Нормальное отображение
}


// Выбирает страницу и горизонтальную позицию для вывода

void pcd8544_setpos(BYTE page, BYTE x){
    pcd8544_cmd(0x40 | (page & 7));
    pcd8544_cmd(0x80 | x);
}

/* Очищает экран, устанавливает курсор в левый верхний угол */
void pcd8544_clear(void){
    BYTE x, y;

    pcd8544_setpos(0, 0);
    for(y = 0; y < 6; y ++){
        for(x = 0; x < 84; x ++){
            pcd8544_data(0);
        }
    }
    pcd8544_setpos(0, 0);
}