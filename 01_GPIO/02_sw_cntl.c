// 스위치 컨트롤
/*
LED 0 : 16 (wPi)
LED 1 : 27 (wPi)
LED 2 :  0 (wPi)
LED 3 : 22 (wPi)
LED 4 : 24 (wPi)
LED 5 : 28 (wPi)
LED 6 : 26 (wPi)
LED 7 :  3 (wPi)

SW0 : 10 (wPi)
SW1 : 11 (wPi)
SW2 : 31 (wPi)
*/

// 주파수 헤르츠 f = 1 / 주기 T(s) 

#include <stdio.h>
#include <wiringPi.h>

#define SW0 10

int main(void)
{
	if(wiringPiSetup() == -1) return -1; // WiringPi 기준
	
	pinMode(SW0, INPUT); // OUTPUT : 1 | INPUT : 0

	while (1) {
		printf("%d\n", digitalRead(SW0));
	}
	
	return 0;
}