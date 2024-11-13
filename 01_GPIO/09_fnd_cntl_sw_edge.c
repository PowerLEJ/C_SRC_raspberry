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

#define SW0 24  // 증가 버튼
#define SW1 26  // 감소 버튼

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
static int sw0_state = LOW;    // SW0 버튼 상태
static int sw1_state = LOW;    // SW1 버튼 상태

// 함수 선언
void fnd_display(void);
void fnd_display_increment(void);
void fnd_display_decrement(void);

int main(void)
{
    // 하드웨어 셋업
    if (wiringPiSetupPhys() == -1) return -1; // Physical pin 기준

    for (int i = 0; i < 8; i++) {
        pinMode(fnd_pin[i], OUTPUT);
        digitalWrite(fnd_pin[i], LOW);  // Initialize FND pins
    }

    pinMode(SW0, INPUT);  // OUTPUT : 1 | INPUT : 0
    pinMode(SW1, INPUT);  // OUTPUT : 1 | INPUT : 0
    pullUpDnControl(SW0, PUD_UP);  // Enable pull-up resistor for SW0
    pullUpDnControl(SW1, PUD_UP);  // Enable pull-up resistor for SW1

    // Main loop - 지속적으로 버튼 상태 확인
    while (1) {
        // SW0 상태 확인 (증가 버튼)
        int current_sw0_state = digitalRead(SW0);
        if (current_sw0_state == HIGH && sw0_state == LOW) {  // 버튼이 눌렸을 때만 동작
            fnd_display_increment();
            sw0_state = HIGH;  // 상태를 눌림으로 업데이트
        } else if (current_sw0_state == LOW) {
            sw0_state = LOW;  // 버튼 떼었을 때 상태 초기화
        }

        // SW1 상태 확인 (감소 버튼)
        int current_sw1_state = digitalRead(SW1);
        if (current_sw1_state == HIGH && sw1_state == LOW) {  // 버튼이 눌렸을 때만 동작
            fnd_display_decrement();
            sw1_state = HIGH;  // 상태를 눌림으로 업데이트
        } else if (current_sw1_state == LOW) {
            sw1_state = LOW;  // 버튼 떼었을 때 상태 초기화
        }

        delay(50);  // 버튼 상태 확인 주기 (debouncing 효과를 위해 적당히 조정)
    }

    return 0;
}

void fnd_display(void) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(fnd_pin[i], fnd_data[current_number][7-i]);
    }
}

void fnd_display_increment(void) {
    current_number = (current_number + 1) % 16;  // 숫자 증가 (0~15 사이 순환)
    fnd_display();  // 숫자 변경
}

void fnd_display_decrement(void) {
    current_number = (current_number - 1 + 16) % 16;  // 숫자 감소 (0~15 사이 순환)
    fnd_display();  // 숫자 변경
}