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
#include <pthread.h>

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

#define KEYPAD_R1 12
#define KEYPAD_R2 13
#define KEYPAD_R3 16
#define KEYPAD_R4 18

#define KEYPAD_C1 22
#define KEYPAD_C2 24
#define KEYPAD_C3 26
#define KEYPAD_C4 28

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
const int keypad_r[4] = {KEYPAD_R1, KEYPAD_R2, KEYPAD_R3, KEYPAD_R4}; // 출력
const int keypad_c[4] = {KEYPAD_C1, KEYPAD_C2, KEYPAD_C3, KEYPAD_C4}; // 입력

int value = 0;

// 함수 선언
void fnd_display(int num);
void fnd4_display(int num);

// thread 함수 선언
void* thread_keypad(void *arg);
void* thread_fnd4(void *arg);

int main(void)
{
    pthread_t t_id, t2_id;

	// 하드웨어 셋업
	if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준

    // 초기화
    for (int i = 0; i < 4; i++) {
        pinMode(keypad_r[i], OUTPUT); // 출력
        pinMode(keypad_c[i], INPUT); // 입력

        digitalWrite(keypad_r[i], LOW);

        pullUpDnControl(keypad_c[i], PUD_DOWN); // 풀다운 저항 설정
    }

    for (int i = 0; i < 8; i++) {
        pinMode(fnd_pin[i], OUTPUT);  // 7세그먼트 디스플레이 핀 설정
        digitalWrite(fnd_pin[i], LOW);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(fnd_digit[i], OUTPUT);  // 자리수 제어 핀 설정
        digitalWrite(fnd_digit[i], LOW);
    }

    // thread 생성
    if(pthread_create(&t2_id, NULL, thread_keypad, NULL) != 0) {
        printf("pthread_create() error\n");
        return -1;
    }

    // thread 생성
	if(pthread_create(&t_id, NULL, thread_fnd4, NULL) != 0) {
		printf("pthread_create() error\n");
		return -1;
	}

    while (1) {

    }

    return 0;
}

void fnd_display(int num) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(fnd_pin[i], fnd_data[num][7-i]);
    }
}

void fnd4_display(int num) {

    int digit[4] = {0, };
    int out[4] = {~0x08, ~0x04, ~0x02, ~0x01}; // (0x08 >> j) 로 할 때

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
            digitalWrite(fnd_digit[j], out[i] & (0x08 >> j)); // (0x08 >> j) 로 할 때
        }
        delay(1);
    }
}

// thread 함수 구현
void* thread_keypad(void *arg) {

    while (1)
    {
        // 행에 대한 for문
        for (int row = 0; row < 4; row++)
        {
            digitalWrite(keypad_r[row], HIGH); // 이렇게만 해도 됨

            // 행의 for문 안에 열에 대한 for문
            for (int col = 0; col < 4; col++)
            {
                if(digitalRead(keypad_c[col]) == HIGH) {
                    value = (row * 4) + (col + 1);
                    printf("SW%d\n", value);
                }
            }

            digitalWrite(keypad_r[row], LOW); // 이렇게만 해도 됨
        }
        delay(200);
    }
    
	return NULL;
}

// thread 함수 구현
void* thread_fnd4(void *arg) {
    while (1)
    {
        fnd4_display(value);
    }
    
    return NULL;
}