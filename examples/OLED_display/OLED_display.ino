
/**************************************************
0.96 OLED
**************************************************/

#include <oled.h>

OLED oled(D0,D1,D2,D3);


void setup()
{
    oled.begin();
    delay(100);
    oled.OLED_Fill(0xff);
    delay(1000);
    oled.OLED_CLS();
}


void loop()
{
    oled.OLED_8x16Str(0,0,"abcdefghijk"); // 8*16
    delay(1000);
    oled.OLED_CLS();
    oled.OLED_6x8Str(0,0,"intorobot team"); // 8*16
    delay(1000);
    oled.OLED_CLS();
}
