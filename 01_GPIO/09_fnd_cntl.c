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

void fnd_display(int num);

int main(void)
{
	// 하드웨어 셋업
	if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준
	
	for (int i = 0; i < 8; i++) { pinMode(fnd_pin[i], OUTPUT); }
    for (int i = 0; i < 8; i++) { digitalWrite(fnd_pin[i], LOW); }

	while (1) {
        for (int j = 0; j < 16; j++)
        {
            fnd_display(j);
            delay(1000);
        }
	}

    return 0;
}

void fnd_display(int num) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(fnd_pin[i], fnd_data[num][7-i]);
    }
}