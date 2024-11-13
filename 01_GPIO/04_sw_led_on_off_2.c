// 스위치 컨트롤
// digitalRead 변수를 이용한 점멸 프로그램
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

#define LED0 10
#define LED1 36

#define SW0 24
#define SW1 26

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

	while (1) {
		// printf("%d\n", digitalRead(SW0));
		// printf("%d\n", digitalRead(SW1));

		if(HIGH == digitalRead(SW0)) {
			if(digitalRead(LED0) == HIGH) {
				digitalWrite(LED0, LOW);
			} else {
				digitalWrite(LED0, HIGH);
			}
			delay(300);
		}

		if(HIGH == digitalRead(SW1)) {
			if(digitalRead(LED1) == HIGH) {
				digitalWrite(LED1, LOW);
			} else {
				digitalWrite(LED1, HIGH);
			}
			delay(300);
		}

	}
	
	return 0;
}