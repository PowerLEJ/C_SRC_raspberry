/*
LED 0 : 16 (wPi)
LED 1 : 27 (wPi)
LED 2 :  0 (wPi)
LED 3 : 22 (wPi)
LED 4 : 24 (wPi)
LED 5 : 28 (wPi)
LED 6 : 26 (wPi)
LED 7 :  3 (wPi)
*/

// 주파수 헤르츠 f = 1 / 주기 T(s) 

#include <stdio.h>
#include <wiringPi.h>

#define LED0 16
#define LED1 27
#define LED2 0
#define LED3 22
#define LED4 24
#define LED5 28
#define LED6 26
#define LED7 3

int main(void)
{

	int leds[8] = {LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7};
	int cnt = sizeof(leds) / sizeof(leds[0]);

	if(wiringPiSetup() == -1) return -1; // WiringPi 기준
	// if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준
	// if(wiringPiSetupGpio() == -1) return -1; // BCM chip 기준
	
	for (int i = 0; i < cnt; i++) {
		pinMode(leds[i], OUTPUT); // OUTPUT : 1 | INPUT : 0
	}

	while (1) {
		for (int i = 0; i < cnt; i++) {
			digitalWrite(leds[i], HIGH); // HIGH : 1	
		}
		delay(100);

		for (int i = 0; i < cnt; i++) {
			digitalWrite(leds[i], LOW); // LOW : 0
		}
		delay(900);
	}
	
	return 0;
}