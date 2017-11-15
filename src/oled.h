/*
 ******************************************************************************

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation, either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, see <http://www.gnu.org/licenses/>.

 This library is a 0.96-inch OLED screen module

 ******************************************************************************
 */

#ifndef OLED_H_
#define OLED_H_

#include "Arduino.h"
#include "oled_codetab.h"


#define XLevelL             0x00
#define XLevelH             0x10
#define XLevel              ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column          128
#define Max_Row             64
#define Brightness          0xCF
#define X_WIDTH             128
#define Y_WIDTH             64

// 0.96 OLED screen SPI analog transmission
class OLED
{

    public:
        OLED(uint16_t pinDC,uint16_t pinRST,uint16_t pinSDA,uint16_t pinSCL);

        void begin(void);
        void OLED_WrDat(unsigned char dat);
        void OLED_WrCmd(unsigned char cmd);
        void OLED_SetPos(unsigned char x, unsigned char y);
        void OLED_Fill(unsigned char bmp_dat);
        void OLED_CLS(void);
        void OLED_Init(void);
        void OLED_6x8Str(unsigned char x, unsigned char y, char *ch);//unsigned char ch[]);
        void OLED_8x16Str(unsigned char x, unsigned char y, char *ch);//unsigned char ch[]);


    private:
        uint16_t _DC;
        uint16_t _RST;
        uint16_t _SDA;
        uint16_t _SCL;
};


#endif
