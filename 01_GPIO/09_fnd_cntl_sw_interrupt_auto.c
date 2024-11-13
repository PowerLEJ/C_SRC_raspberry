// 완전하지는 않음 (일회용)

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

#define SW0 24  // 증가 버튼 (0 -> E)
#define SW1 26  // 감소 버튼 (E -> 0)

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
void display_sequence(int start, int end, int increment);

int main(void)
{
    // 하드웨어 셋업
    if (wiringPiSetupPhys() == -1) return -1; // Physical pin 기준

    pinMode(SW0, INPUT);  // 증가 버튼 (0 -> E)
    pinMode(SW1, INPUT);  // 감소 버튼 (E -> 0)
    pullUpDnControl(SW0, PUD_UP);  // Enable pull-up resistor for SW0
    pullUpDnControl(SW1, PUD_UP);  // Enable pull-up resistor for SW1

    for (int i = 0; i < 8; i++) {
        pinMode(fnd_pin[i], OUTPUT);
        digitalWrite(fnd_pin[i], LOW);  // Initialize FND pins
    }

    // ISR 함수 설정
    if (wiringPiISR(SW0, INT_EDGE_RISING, &fnd_display_increment) < 0) {
        printf("Interrupt error [1]\n");
    }

    if (wiringPiISR(SW1, INT_EDGE_RISING, &fnd_display_decrement) < 0) {
        printf("Interrupt error [2]\n");
    }

    // Main loop - 인터럽트에서 동작 처리
    while (1) {
        delay(100);  // 인터럽트가 처리되도록 주기적 대기
    }

    return 0;
}

void fnd_display(void) {
    // 7-segment 디스플레이에 숫자를 표시하는 함수
    for (int i = 0; i < 8; i++) {
        digitalWrite(fnd_pin[i], fnd_data[current_number][7-i]);
    }
}

void fnd_display_increment(void) {
    // SW0를 눌렀을 때 숫자 0~F까지 증가
    display_sequence(0, 15, 1);  // 0부터 F까지 표시
}

void fnd_display_decrement(void) {
    // SW1을 눌렀을 때 숫자 F~0까지 감소
    display_sequence(15, 0, -1);  // F부터 0까지 표시
}

void display_sequence(int start, int end, int increment) {
    // 숫자 sequence를 표시하는 함수 (증가 / 감소)
    for (int num = start; num != end + increment; num += increment) {
        current_number = num;
        fnd_display();  // 숫자 변경
        delay(1000);     // 1초 대기
    }
}
