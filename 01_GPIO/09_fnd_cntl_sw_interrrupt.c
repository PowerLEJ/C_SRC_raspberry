/*
LED 0 : 16 (wPi)	10(phys)     A:07(FND)
LED 1 : 27 (wPi)	36(phys)     B:06(FND)
LED 2 :  0 (wPi)	11(phys)     C:04(FND)
LED 3 : 22 (wPi)	31(phys)     D:02(FND)
LED 4 : 24 (wPi)	35(phys)     E:01(FND)
LED 5 : 28 (wPi)	38(phys)     F:09(FND)
LED 6 : 26 (wPi)	32(phys)     G:10(FND)
LED 7 :  3 (wPi)	15(phys)    DP:05(FND)

SW0 :   10 (wPi)	24(phys)
SW1 :   11 (wPi)	26(phys)
SW2 :   31 (wPi)	28(phys)

FND_D1 : 19(phys)
FND_D2 : 21(phys)
FND_D3 : 23(phys)
FND_D4 : 27(phys)
*/

#include <stdio.h>
#include <wiringPi.h>

#define FND_A 10
#define FND_B 36
#define FND_C 11
#define FND_D 31
#define FND_E 35
#define FND_F 38
#define FND_G 32
#define FND_DP 15

#define SW0 24
#define SW1 26

#define FND_D1 19
#define FND_D2 21
#define FND_D3 23
#define FND_D4 27

// 전역변수 선언
const int fnd_pin[8] = {FND_A, FND_B, FND_C, FND_D, FND_E, FND_F, FND_G, FND_DP};
const int fnd_data[16][8] = {
                                 {0,0,1,1,1,1,1,1}  // FND 0
                                ,{0,0,0,0,0,1,1,0}  // FND 1
                                ,{0,1,0,1,1,0,1,1}  // FND 2
                                ,{0,1,0,0,1,1,1,1}  // FND 3
                                ,{0,1,1,0,0,1,1,0}  // FND 4
                                ,{0,1,1,0,1,1,0,1}  // FND 5
                                ,{0,1,1,1,1,1,0,1}  // FND 6
                                ,{0,0,0,0,0,1,1,1}  // FND 7
                                ,{0,1,1,1,1,1,1,1}  // FND 8
                                ,{0,1,1,0,0,1,1,1}  // FND 9
                                ,{0,1,1,1,0,1,1,1}  // FND A
                                ,{0,1,1,1,1,1,0,0}  // FND b
                                ,{0,0,1,1,1,0,0,1}  // FND C
                                ,{0,1,0,1,1,1,1,0}  // FND d
                                ,{0,1,1,1,1,0,0,1}  // FND E
                                ,{0,1,1,1,0,0,0,1}  // FND F
                            };

static int current_number = 0; // 현재 숫자 (0~15)

// 함수 선언
void fnd_display(void);
void fnd_display_increment(void);
void fnd_display_decrement(void);

int main(void)
{
	// 하드웨어 셋업
	if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준
	
	for (int i = 0; i < 8; i++) {
        pinMode(fnd_pin[i], OUTPUT); 
        digitalWrite(fnd_pin[i], LOW); 
    }

    pinMode(SW0, INPUT);  // OUTPUT : 1 | INPUT : 0
    pinMode(SW1, INPUT);  // OUTPUT : 1 | INPUT : 0
    pullUpDnControl(SW0, PUD_UP);  // Enable pull-up resistor for SW0
    pullUpDnControl(SW1, PUD_UP);  // Enable pull-up resistor for SW1

    // ISR 함수
	if(wiringPiISR(SW0, INT_EDGE_RISING, &fnd_display_increment) < 0) {
		printf("interrupt error [1]\n");
	}

	if(wiringPiISR(SW1, INT_EDGE_RISING, &fnd_display_decrement) < 0) {
		printf("interrupt error [2]\n");
	}

    // Main loop - 인터럽트에서 동작 처리
	while (1) {
        delay(100);
	}

    return 0;
}

void fnd_display(void) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(fnd_pin[i], fnd_data[current_number][7-i]);
    }
}

void fnd_display_increment(void) {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();

    // 간단한 디바운스 처리
    if (interrupt_time - last_interrupt_time > 200) {  // 200ms 이상 차이날 때만 처리
        last_interrupt_time = interrupt_time;
        current_number = (current_number + 1) % 16;  // 숫자 증가 (0~15 사이 순환)
        fnd_display();  // 숫자 변경
    }
}

void fnd_display_decrement(void) {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();

    // 간단한 디바운스 처리
    if (interrupt_time - last_interrupt_time > 200) {  // 200ms 이상 차이날 때만 처리
        last_interrupt_time = interrupt_time;
        current_number = (current_number - 1 + 16) % 16;  // 숫자 감소 (0~15 사이 순환)
        fnd_display();  // 숫자 변경
    }
}