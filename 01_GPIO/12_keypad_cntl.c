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

KEY_R1 : 12(phys)
KEY_R2 : 13(phys)
KEY_R3 : 16(phys)
KEY_R4 : 18(phys)
KEY_C1 : 22(phys)
KEY_C2 : 24(phys)
KEY_C3 : 26(phys)
KEY_C4 : 28(phys)
*/

#include <stdio.h>
#include <wiringPi.h>

#define KEY_R1 12
#define KEY_R2 13
#define KEY_R3 16
#define KEY_R4 18
#define KEY_C1 22
#define KEY_C2 24
#define KEY_C3 26
#define KEY_C4 28

// 전역변수 선언
const int fnd_r[4] = {KEY_R1, KEY_R2, KEY_R3, KEY_R4}; // 출력
const int fnd_c[4] = {KEY_C1, KEY_C2, KEY_C3, KEY_C4}; // 입력

int main(void)
{
	// 하드웨어 셋업
	if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준

    for (int i = 0; i < 4; i++) {
        pinMode(fnd_r[i], OUTPUT); // 출력
        pinMode(fnd_c[i], INPUT); // 입력
    }

    int row_num = 0, col_num = 0;

    while (1) {

        // 행에 대한 for문
        for (int row = 0; row < 4; row++)
        {
            // fnd_r[0] ~ fnd_r[3] 에 대한 Write 설정
            for (int r_i = 0; r_i < 4; r_i++) {
                if (r_i == row) {
                    digitalWrite(fnd_r[r_i], HIGH);
                }
                else {
                    digitalWrite(fnd_r[r_i], LOW);
                }
            }

            // 행의 for문 안에 열에 대한 for문
            for (int col = 0; col < 4; col++)
            {
                int where = 0;

                if(digitalRead(fnd_c[col]) == HIGH && digitalRead(fnd_r[row]) == HIGH) {
                    
                    row_num = row + 1;
                    col_num = col + 1;
                    
                    if(1 == row_num) {
                        if(1 == col_num) { where = 1; }
                        if(2 == col_num) { where = 2; }
                        if(3 == col_num) { where = 3; }
                        if(4 == col_num) { where = 4; }
                    } else if(2 == row_num) {
                        if(1 == col_num) { where = 5; }
                        if(2 == col_num) { where = 6; }
                        if(3 == col_num) { where = 7; }
                        if(4 == col_num) { where = 8; }
                    } else if(3 == row_num) {
                        if(1 == col_num) { where = 9; }
                        if(2 == col_num) { where = 10; }
                        if(3 == col_num) { where = 11; }
                        if(4 == col_num) { where = 12; }
                    } else if(4 == row_num) {
                        if(1 == col_num) { where = 13; }
                        if(2 == col_num) { where = 14; }
                        if(3 == col_num) { where = 15; }
                        if(4 == col_num) { where = 16; }
                    }
                    printf("S%d 버튼입니다.\n", where);

                }
            }
        }

        delay(200);
    }

    return 0;
}