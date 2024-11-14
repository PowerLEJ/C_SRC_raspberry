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

KEYPAD_R1 : 12(phys)
KEYPAD_R2 : 13(phys)
KEYPAD_R3 : 16(phys)
KEYPAD_R4 : 18(phys)
KEYPAD_C1 : 22(phys)
KEYPAD_C2 : 24(phys)
KEYPAD_C3 : 26(phys)
KEYPAD_C4 : 28(phys)
*/

#include <stdio.h>
#include <wiringPi.h>

#define KEYPAD_R1 12
#define KEYPAD_R2 13
#define KEYPAD_R3 16
#define KEYPAD_R4 18

#define KEYPAD_C1 22
#define KEYPAD_C2 24
#define KEYPAD_C3 26
#define KEYPAD_C4 28

// 전역변수 선언
const int keypad_r[4] = {KEYPAD_R1, KEYPAD_R2, KEYPAD_R3, KEYPAD_R4}; // 출력
const int keypad_c[4] = {KEYPAD_C1, KEYPAD_C2, KEYPAD_C3, KEYPAD_C4}; // 입력

int main(void)
{
	// 하드웨어 셋업
	if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준

    // 초기화
    for (int i = 0; i < 4; i++) {
        pinMode(keypad_r[i], OUTPUT); // 출력
        pinMode(keypad_c[i], INPUT); // 입력

        digitalWrite(keypad_r[i], LOW);

        pullUpDnControl(keypad_c[i], PUD_DOWN); // 풀다운 저항 설정
    }

    while (1) {

        // 행에 대한 for문
        for (int row = 0; row < 4; row++)
        {
            digitalWrite(keypad_r[row], HIGH); // 이렇게만 해도 됨

            // 행의 for문 안에 열에 대한 for문
            for (int col = 0; col < 4; col++)
            {
                if(digitalRead(keypad_c[col]) == HIGH) printf("SW%d\n", (row * 4) + (col + 1));
            }

            digitalWrite(keypad_r[row], LOW); // 이렇게만 해도 됨
        }

        delay(200);
    }

    return 0;
}