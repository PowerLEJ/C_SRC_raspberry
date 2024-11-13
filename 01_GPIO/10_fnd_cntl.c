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

#define FND_D1 19
#define FND_D2 21
#define FND_D3 23
#define FND_D4 27

// 전역변수 선언
const int fnd_pin[8] = {FND_A, FND_B, FND_C, FND_D, FND_E, FND_F, FND_G, FND_DP};
const int fnd_digit[4] = {FND_D1, FND_D2, FND_D3, FND_D4};
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

void fnd_display(int num);
void fnd4_display(int num);

int main(void)
{
	// 하드웨어 셋업
	if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준
	
	for (int i = 0; i < 8; i++) { pinMode(fnd_pin[i], OUTPUT); }
    for (int i = 0; i < 4; i++) { pinMode(fnd_digit[i], OUTPUT); }

    for (int i = 0; i < 8; i++) { digitalWrite(fnd_pin[i], LOW); }
    for (int i = 0; i < 4; i++) { digitalWrite(fnd_digit[i], LOW); }

    int count = 0;
	while (1) {

        fnd4_display(1234);

        // fnd_display(1);
        // digitalWrite(fnd_digit[0], LOW);
        // digitalWrite(fnd_digit[1], HIGH);
        // digitalWrite(fnd_digit[2], HIGH);
        // digitalWrite(fnd_digit[3], HIGH);
        // delay(1);

        // fnd_display(2);
        // digitalWrite(fnd_digit[0], HIGH);
        // digitalWrite(fnd_digit[1], LOW);
        // digitalWrite(fnd_digit[2], HIGH);
        // digitalWrite(fnd_digit[3], HIGH);
        // delay(1);

        // fnd_display(3);
        // digitalWrite(fnd_digit[0], HIGH);
        // digitalWrite(fnd_digit[1], HIGH);
        // digitalWrite(fnd_digit[2], LOW);
        // digitalWrite(fnd_digit[3], HIGH);
        // delay(1);

        // fnd_display(4);
        // digitalWrite(fnd_digit[0], HIGH);
        // digitalWrite(fnd_digit[1], HIGH);
        // digitalWrite(fnd_digit[2], HIGH);
        // digitalWrite(fnd_digit[3], LOW);
        // delay(1);

	}

    return 0;
}

void fnd_display(int num) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(fnd_pin[i], fnd_data[num][7-i]);
    }
}

void fnd4_display(int num) {

    // fnd_display(digit[1 - 1]);
    // digitalWrite(fnd_digit[0], LOW);
    // digitalWrite(fnd_digit[1], HIGH);
    // digitalWrite(fnd_digit[2], HIGH);
    // digitalWrite(fnd_digit[3], HIGH);
    // delay(1);

    // fnd_display(digit[2 - 1]);
    // digitalWrite(fnd_digit[0], HIGH);
    // digitalWrite(fnd_digit[1], LOW);
    // digitalWrite(fnd_digit[2], HIGH);
    // digitalWrite(fnd_digit[3], HIGH);
    // delay(1);

    // fnd_display(digit[3 - 1]);
    // digitalWrite(fnd_digit[0], HIGH);
    // digitalWrite(fnd_digit[1], HIGH);
    // digitalWrite(fnd_digit[2], LOW);
    // digitalWrite(fnd_digit[3], HIGH);
    // delay(1);

    // fnd_display(digit[4 - 1]);
    // digitalWrite(fnd_digit[0], HIGH);
    // digitalWrite(fnd_digit[1], HIGH);
    // digitalWrite(fnd_digit[2], HIGH);
    // digitalWrite(fnd_digit[3], LOW);
    // delay(1);


    // int digit[4] = {0, };

    // // 자릿수 분리
    // digit[0] = num / 1000;      // 천의 자리
    // digit[1] = (num % 1000) / 100;  // 백의 자리
    // digit[2] = (num % 100) / 10;    // 십의 자리
    // digit[3] = num % 10;         // 일의 자리

    // // 4자리 디스플레이 순차적으로 처리
    // for (int i = 0; i < 4; i++) {
    //     // 현재 자릿수의 숫자를 7세그먼트 디스플레이에 표시
    //     fnd_display(digit[i]);

    //     // 모든 자리를 끄고, 현재 자릿수만 선택
    //     for (int j = 0; j < 4; j++) {
    //         if (j == i) {
    //             digitalWrite(fnd_digit[j], LOW);  // 현재 자릿수 비활성화
    //         } else {
    //             digitalWrite(fnd_digit[j], HIGH);   // 나머지 자리는 활성화
    //         }
    //     }

    //     // 작은 딜레이를 주어 자릿수가 제대로 전환될 수 있도록 함
    //     delay(1);
    // }


    int digit[4] = {0, };
    int out[4] = {0x0E, 0x0D, 0x0B, 0x07}; // 1110, 1101, 1011, 0111
    // int out[4] = {~0x08, ~0x04, ~0x02, ~0x01}; // (0x08 >> j) 로 할 때

    // 자릿수 분류
    digit[0] = num / 1000;
    digit[1] = (num % 1000) / 100;
    digit[2] = (num % 100) / 10;
    digit[3] = num % 10;

    for (int i = 0; i < 4; i++)
    {
        fnd_display(digit[i]);

        for (int j = 0; j < 4; j++)
        {
            /*
            out[0] = 0x0E = 1110
            out[1] = 0x0D = 1101
            out[2] = 0x0B = 1011
            out[3] = 0x07 = 0111

            (0x01 << 0) = 0001
            (0x01 << 1) = 0010
            (0x01 << 2) = 0100
            (0x01 << 3) = 1000
            */
            digitalWrite(fnd_digit[j], out[i] & (0x01 << j)); 
            // digitalWrite(fnd_digit[j], out[i] & (0x08 >> j)); // (0x08 >> j) 로 할 때
        }
        delay(1);
    }


}

