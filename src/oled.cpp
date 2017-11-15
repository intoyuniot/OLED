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

#include "oled.h"

//Specifications Pin
OLED::OLED(uint16_t pinDC,uint16_t pinRST,uint16_t pinSDA,uint16_t pinSCL)
{
    _DC =  pinDC;
    _RST = pinRST;
    _SDA = pinSDA;
    _SCL = pinSCL;
}

//This function is called before use
void OLED::begin(void)
{
    pinMode(_RST,OUTPUT);
    pinMode(_DC,OUTPUT);
    pinMode(_SDA,OUTPUT);
    pinMode(_SCL,OUTPUT);

    delay(100);

    digitalWrite(_RST,0);
    delay(200);
    digitalWrite(_RST,1);

    OLED_Init();
}

//Write Data
void OLED::OLED_WrDat(unsigned char dat)
{
    unsigned char i;

    digitalWrite(_DC,1);


    for(i=0;i<8;i++)
    {
        if((dat << i) & 0x80)
        {
            digitalWrite(_SDA,1);
        }
        else
        {
            digitalWrite(_SDA,0);
        }

        digitalWrite(_SCL,0);
        digitalWrite(_SCL,1);
    }
}


//Write command
void OLED::OLED_WrCmd(unsigned char cmd)
{
    unsigned char i;

    digitalWrite(_DC,0);


    for(i=0;i<8;i++)
    {
        if((cmd << i) & 0x80)
        {
            digitalWrite(_SDA,1);
        }
        else
        {
            digitalWrite(_SDA,0);
        }

        digitalWrite(_SCL,0);
        digitalWrite(_SCL,1);
    }
}

//Set the display position
void OLED::OLED_SetPos(unsigned char x, unsigned char y)
{
    OLED_WrCmd(0xb0 + y);
    OLED_WrCmd(((x & 0xf0) >> 4)|0x10);
    OLED_WrCmd((x & 0x0f)|0x01);
}

//Full screen filled
void OLED::OLED_Fill(unsigned char bmp_dat)
{
    unsigned char y,x;

    for(y = 0; y < 8; y++)
    {
        OLED_WrCmd(0xb0+y);
        OLED_WrCmd(0x01);
        OLED_WrCmd(0x10);

        for(x = 0; x < X_WIDTH; x++)
        {
            OLED_WrDat(bmp_dat);
        }
    }
}

//Clear screen
void OLED::OLED_CLS(void)
{
    OLED_Fill(0x00);
}

//Initialization
void OLED::OLED_Init(void)
{
    OLED_WrCmd(0xae);
    OLED_WrCmd(0xae);//--turn off oled panel
    OLED_WrCmd(0x00);//---set low column address
    OLED_WrCmd(0x10);//---set high column address
    OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WrCmd(0x81);//--set contrast control register
    OLED_WrCmd(0xcf); // Set SEG Output Current Brightness
    OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0,0xa1
    OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0,0xc8
    OLED_WrCmd(0xa6);//--set normal display
    OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
    OLED_WrCmd(0x3f);//--1/64 duty
    OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WrCmd(0x00);//-not offset
    OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
    OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WrCmd(0xd9);//--set pre-charge period
    OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WrCmd(0xda);//--set com pins hardware configuration
    OLED_WrCmd(0x12);
    OLED_WrCmd(0xdb);//--set vcomh
    OLED_WrCmd(0x40);//Set VCOM Deselect Level
    OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WrCmd(0x02);//
    OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
    OLED_WrCmd(0x14);//--set(0x10) disable
    OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
    OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7)
    OLED_WrCmd(0xaf);//--turn on oled panel
    OLED_Fill(0x00);
    OLED_SetPos(0,0);

}

//Display 6x8 characters
void OLED::OLED_6x8Str(unsigned char x, unsigned char y, char *ch)
{
    unsigned char c = 0,i = 0,j = 0;

    while (ch[j] != '\0')
    {
        c = ch[j] - 32;

        if(x > 126)
        {
            x = 0;
            y++;
        }

        OLED_SetPos(x,y);

        for(i = 0; i < 6; i++)
        {
            OLED_WrDat(F6x8[c][i]);
        }

        x += 6;
        j++;
    }
}

//Display 8x16 characters
void OLED::OLED_8x16Str(unsigned char x, unsigned char y, char *ch)
{
    unsigned char c = 0,i = 0,j = 0;

    while (ch[j] != '\0')
    {
        c = ch[j] - 32;

        if(x > 120)
        {
            x = 0;
            //y++;
            y = y+2;
        }

        OLED_SetPos(x,y);

        for(i = 0; i < 8; i++)
        {
            OLED_WrDat(F8X16[c*16+i]);
        }

        OLED_SetPos(x,y+1);

        for(i=0;i<8;i++)
        {
            OLED_WrDat(F8X16[c*16+i+8]);
        }

        x += 8;
        j++;
    }
}
