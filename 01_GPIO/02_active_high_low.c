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

int main(void)
{

	int leds[2] = {LED0, LED1};
	int cnt = sizeof(leds) / sizeof(leds[0]);

	if(wiringPiSetup() == -1) return -1; // WiringPi 기준
	// if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준
	// if(wiringPiSetupGpio() == -1) return -1; // BCM chip 기준
	
	for (int i = 0; i < cnt; i++) {
		pinMode(leds[i], OUTPUT); // OUTPUT : 1 | INPUT : 0
	}

	while (1) {

		// 점차 밝아졌다 점차 어두워지기
		for (int i = 0; i < 10000; i += 50)
		{
			digitalWrite(LED0, HIGH); // HIGH : 1
			digitalWrite(LED1, LOW);
			delayMicroseconds(i);
			digitalWrite(LED0, LOW); // LOW : 0
			digitalWrite(LED1, HIGH);
			delayMicroseconds(10000 - i);
		}
		
	}
	
	return 0;
}