#include "bios_dir.h"
#include "lcd_160x.h"

#if (LCD10_DISP)//Ϊ10�ַ���״̬��ǩ��ʾ��
#include "lcd_ht1621.c"
#elif (DD_LCD_16021)
#include "lcd_160x21.c"
#elif (DD_LCD_1601)
#include "lcd_160x1.c"
#elif (DD_ZIP)
#include "lcd_160x2.c"
#endif

