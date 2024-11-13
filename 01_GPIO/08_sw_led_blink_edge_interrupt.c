// 스위치 컨트롤
// Interrupt Blink(0.3초마다) Rising Edge Check를 이용한 점멸 프로그램
/*
	Active High						Active High
	Switch A : 24(phys)		LED 10(phys)		AND
	Switch B : 26(phys)		LED 36(phys)		OR
*/
/*
LED 0 : 16 (wPi)	10(phys)
LED 1 : 27 (wPi)	36(phys)
LED 2 :  0 (wPi)	11(phys)
LED 3 : 22 (wPi)	31(phys)
LED 4 : 24 (wPi)	35(phys)
LED 5 : 28 (wPi)	38(phys)
LED 6 : 26 (wPi)	32(phys)
LED 7 :  3 (wPi)	15(phys)

SW0 :   10 (wPi)	24(phys)
SW1 :   11 (wPi)	26(phys)
SW2 :   31 (wPi)	28(phys)
*/

// 주파수 헤르츠 f = 1 / 주기 T(s) 

#include <stdio.h>
#include <wiringPi.h>

#define ON 1
#define OFF 0

#define LED0 10
#define LED1 36

#define SW0 24
#define SW1 26

// 전역변수 선언
int status_led0 = OFF;
int status_led1 = OFF;

void btn_interrupt() {

	// 상태값 변경
	if(status_led0 == ON) {
		status_led0 = OFF;
	} else {
		status_led0 = ON;
	}

}

void btn_interrupt_2() {

	// 상태값 변경
	if(status_led1 == ON) {
		status_led1 = OFF;
	} else {
		status_led1 = ON;
	}

}

int main(void)
{	
	// 하드웨어 셋업
	if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준
	
	pinMode(SW0, INPUT); // OUTPUT : 1 | INPUT : 0
	pinMode(SW1, INPUT); // OUTPUT : 1 | INPUT : 0

	pinMode(LED0, OUTPUT);
	pinMode(LED1, OUTPUT);

	digitalWrite(LED0, LOW);
	digitalWrite(LED1, LOW);

	// ISR 함수
	if(wiringPiISR(SW0, INT_EDGE_RISING, &btn_interrupt) < 0) {
		printf("interrupt error [1]\n");
	}

	if(wiringPiISR(SW1, INT_EDGE_RISING, &btn_interrupt_2) < 0) {
		printf("interrupt error [2]\n");
	}

	while (1) {
		
		// 상태값에 따른 동작 구현
		if(status_led0 == ON) {
			digitalWrite(LED0, !digitalRead(LED0));
			delay(300);
		} else {
			digitalWrite(LED0, LOW);
		}

		if(status_led1 == ON) {
			digitalWrite(LED1, !digitalRead(LED1));
			delay(300);
		} else {
			digitalWrite(LED1, LOW);
		}

	}
	
	return 0;
}