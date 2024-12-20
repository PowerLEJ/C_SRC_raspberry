#include <stdio.h>
#include <wiringPi.h>

// LCD의 핀 번호 정의 (Raspberry Pi 핀 번호)
#define LCD_D4  22  // (Phy - 22) - (LCD - 11)
#define LCD_D5  24  // (Phy - 24) - (LCD - 12)
#define LCD_D6  26  // (Phy - 26) - (LCD - 13)
#define LCD_D7  28  // (Phy - 28) - (LCD - 14)
#define LCD_RS  11  // (Phy - 11) - (LCD - 4)
#define LCD_RW  13  // (Phy - 13) - (LCD - 5)
#define LCD_E   15  // (Phy - 15) - (LCD - 6)

void clcd_config(void);
void clcd_init(void);  // LCD 초기화 함수 선언
void clcd_write(unsigned char rs, char data);  // LCD에 데이터 쓰기 함수 선언
void clcd_string(char *str);

int lcd_data[4] = {LCD_D4, LCD_D5, LCD_D6, LCD_D7};  // LCD 데이터 핀 배열

int main()
{
    // wiringPi 라이브러리 초기화 (Physical 핀 번호 기준)
    if(wiringPiSetupPhys() == -1) return -1;  // 실패시 -1 리턴

    clcd_config(); // gpio 핀 설정

    clcd_init(); // LCD 초기화

    // 문자열을 LCD에 출력
    // clcd_write(1, 'H');
    // clcd_write(1, 'e');
    // clcd_write(1, 'l');
    // clcd_write(1, 'l');
    // clcd_write(1, 'o');
    // clcd_write(1, 'A');
    // clcd_write(1, 'P');
    // clcd_write(1, 'P');
    // clcd_write(1, 'L');
    // clcd_write(1, 'E');

    clcd_string("Hello World!");
    clcd_write(0, 0xC0); // 1100 0000 위치로 이동
    clcd_string("I Like Apple!");

    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            delay(1000);
            clcd_write(0, 0x18); // Cursor or display shift // 0001 1000
        }

        for (int i = 0; i < 4; i++)
        {
            delay(1000);
            clcd_write(0, 0x1C); // Cursor or display shift // 0001 1100
        }
        
    }
    


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



    // 무한 루프 (LCD 출력 이후 프로그램이 종료되지 않도록)
    while(1) {
    }

    return 0;
}

void clcd_config(void)
{
    // LCD 제어 핀을 출력으로 설정
    pinMode(LCD_E, OUTPUT);
    pinMode(LCD_RS, OUTPUT);
    pinMode(LCD_RW, OUTPUT);
    digitalWrite(LCD_E, LOW);  // E 핀 초기화 (LOW)
    digitalWrite(LCD_RS, LOW);  // RS 핀 초기화 (LOW)
    digitalWrite(LCD_RW, LOW);  // RW 핀 초기화 (LOW)

    // LCD 데이터 핀을 출력으로 설정하고 초기화 (LOW)
    for (int i = 0; i < 4; i++)
    {
        pinMode(lcd_data[i], OUTPUT);
        digitalWrite(lcd_data[i], LOW);
    }
}

// LCD 초기화 함수
void clcd_init(void)
{
    digitalWrite(LCD_E, LOW);  // E 핀 LOW 설정

    // LCD 초기화 명령어 순차적으로 전송
    clcd_write(0, 0x33); // 초기화 명령 (기본 설정을 위한 두 번째 명령) // 0011 0011
    clcd_write(0, 0x32); // 4비트 모드 설정 // 0011 0010
    clcd_write(0, 0x28); // 화면 크기 설정 (4비트 2행 5x8 문자) // 0010 1000
    clcd_write(0, 0x0F); // 디스플레이 켜고 커서 설정 (깜빡이는 상태로) // 1111     // clcd_write(0, 0x0E); // 디스플레이 켜고 커서 설정 (깜빡이지 않는 상태로) // 1110
    clcd_write(0, 0x01); // 화면 클리어 // 0001
    clcd_write(0, 0x06); // 커서 오른쪽으로 이동, 화면 자동 갱신 // 0110
    clcd_write(0, 0x02); // 커서 초기 위치로 이동 // 0010
}

// LCD에 데이터 쓰는 함수
// rs: 0이면 명령, 1이면 데이터
// data: 전송할 데이터
void clcd_write(unsigned char rs, char data)
{
    digitalWrite(LCD_RS, rs);  // RS 핀 설정 (명령/데이터 구분)
    digitalWrite(LCD_E, LOW);  // E 핀 LOW로 설정 (데이터 전송 대기)

    delayMicroseconds(2);  // 짧은 시간 대기 (이후 신호를 안정적으로 전송하기 위함)

    // 상위 4비트 데이터 전송
    digitalWrite(lcd_data[0], (data>>4) & 0x01);
    digitalWrite(lcd_data[1], (data>>5) & 0x01);
    digitalWrite(lcd_data[2], (data>>6) & 0x01);
    digitalWrite(lcd_data[3], (data>>7) & 0x01);

    digitalWrite(LCD_E, HIGH);  // E 핀 HIGH로 설정 (데이터 전송 시작)
    delayMicroseconds(2);  // 데이터가 전송될 시간을 기다림
    digitalWrite(LCD_E, LOW);  // E 핀 LOW로 설정 (전송 종료)

    delayMicroseconds(2);  // 잠시 대기 후, 하위 4비트 데이터 전송 준비

    // 하위 4비트 데이터 전송
    digitalWrite(lcd_data[0], (data>>0) & 0x01);
    digitalWrite(lcd_data[1], (data>>1) & 0x01);
    digitalWrite(lcd_data[2], (data>>2) & 0x01);
    digitalWrite(lcd_data[3], (data>>3) & 0x01);

    digitalWrite(LCD_E, HIGH);  // E 핀 HIGH로 설정 (하위 데이터 전송 시작)
    delayMicroseconds(2);  // 데이터가 전송될 시간을 기다림
    digitalWrite(LCD_E, LOW);  // E 핀 LOW로 설정 (전송 종료)

    delay(2);  // 잠시 대기 (LCD가 명령을 처리하는 시간을 기다림)
}

void clcd_string(char *str)
{
    int i = 0;

    while (*(str + i) != 0)
    {
        clcd_write(1, *(str + i));
        i++;
    }
    
}