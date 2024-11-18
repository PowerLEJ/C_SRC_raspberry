#include <stdio.h>
#include <wiringPi.h>

#define LCD_D4  22  // (Phy - 22) - (LCD - 11)
#define LCD_D5  24  // (Phy - 24) - (LCD - 12)
#define LCD_D6  26  // (Phy - 26) - (LCD - 13)
#define LCD_D7  28  // (Phy - 28) - (LCD - 14)
#define LCD_RS  11  // (Phy - 11) - (LCD - 4)
#define LCD_RW  13  // (Phy - 13) - (LCD - 5)
#define LCD_E   15  // (Phy - 15) - (LCD - 6)

void clcd_init(void);
void clcd_write(unsigned char rs, char data);

int lcd_data[4] = {LCD_D4,LCD_D5,LCD_D6,LCD_D7};

int main()
{
	if(wiringPiSetupPhys() == -1)	return -1;	// Physical 기준

    pinMode(LCD_E, OUTPUT);
    pinMode(LCD_RS, OUTPUT);
    pinMode(LCD_RW, OUTPUT);
    digitalWrite(LCD_E, LOW);
    digitalWrite(LCD_RS, LOW);
    digitalWrite(LCD_RW, LOW);    

    for (int i = 0; i < 4; i++)
    {
        pinMode(lcd_data[i], OUTPUT);
        digitalWrite(lcd_data[i], LOW);
    }   

    clcd_init();
    
    clcd_write(1, 'H');
    clcd_write(1, 'e');
    clcd_write(1, 'l');
    clcd_write(1, 'l');
    clcd_write(1, 'o');
    clcd_write(1, ' ');
    clcd_write(1, 'G');
    clcd_write(1, 'o');
    clcd_write(1, ' ');
    clcd_write(1, '?');
    clcd_write(1, '!');
    clcd_write(1, '<');
    clcd_write(1, '.');
    clcd_write(1, '}');
    clcd_write(1, '_');
    clcd_write(1, '+');

    /*
        A 라는 글자를 보여주기
        A는 아스키코드로 65이다.
        65는 2진수로 0100 0001 이다.
    */
    // digitalWrite(LCD_RS, HIGH);
    // // HIGH bits       
    // digitalWrite(lcd_data[0], LOW);
    // digitalWrite(lcd_data[1], LOW);
    // digitalWrite(lcd_data[2], HIGH);
    // digitalWrite(lcd_data[3], LOW);
    // digitalWrite(LCD_E, HIGH);
    // delayMicroseconds(1);
    // digitalWrite(LCD_E, LOW);
    // delayMicroseconds(1);
    // // LOW bits
    // digitalWrite(lcd_data[0], HIGH);
    // digitalWrite(lcd_data[1], LOW);
    // digitalWrite(lcd_data[2], LOW);
    // digitalWrite(lcd_data[3], LOW);
    // digitalWrite(LCD_E, HIGH);
    // delayMicroseconds(1);
    // digitalWrite(LCD_E, LOW); 
	
	while(1){
        
	}

	return 0;
}

void clcd_init(void)
{
    digitalWrite(LCD_E, LOW);
    clcd_write(0, 0x33);
    clcd_write(0, 0x32);
    clcd_write(0, 0x28);
    clcd_write(0, 0x0F);
    clcd_write(0, 0x01);
    clcd_write(0, 0x06);
    clcd_write(0, 0x02);
}

void clcd_write(unsigned char rs, char data)
{
    digitalWrite(LCD_RS, rs);
    digitalWrite(LCD_E, LOW);
    delayMicroseconds(2);

    digitalWrite(lcd_data[0], (data>>4) & 0x01);
    digitalWrite(lcd_data[1], (data>>5) & 0x01);
    digitalWrite(lcd_data[2], (data>>6) & 0x01);
    digitalWrite(lcd_data[3], (data>>7) & 0x01);

    digitalWrite(LCD_E, HIGH);
    delayMicroseconds(2);
    digitalWrite(LCD_E, LOW);
    delayMicroseconds(2);

    digitalWrite(lcd_data[0], (data>>0) & 0x01);
    digitalWrite(lcd_data[1], (data>>1) & 0x01);
    digitalWrite(lcd_data[2], (data>>2) & 0x01);
    digitalWrite(lcd_data[3], (data>>3) & 0x01);

    digitalWrite(LCD_E, HIGH);
    delayMicroseconds(2);
    digitalWrite(LCD_E, LOW);
    delay(2);
}