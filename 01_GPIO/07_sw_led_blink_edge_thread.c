// 스위치 컨트롤
// Thread Blink(0.3초마다) Rising Edge Check를 이용한 점멸 프로그램
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
#include <pthread.h>

#define ON 1
#define OFF 0

#define LED0 10
#define LED1 36

#define SW0 24
#define SW1 26

// 함수 선언
void* thread_led_blink(void *arg);
void* thread_led_blink_2(void *arg);

void* thread_sw_edge(void *arg);
void* thread_sw_edge_2(void *arg);

// 전역변수 선언
int sw0_pre = LOW, sw0_cur = LOW;
int sw1_pre = LOW, sw1_cur = LOW;

int main(void)
{	
	// 지역변수 선언
	int status_led0 = OFF;
	int status_led1 = OFF;

	pthread_t t_id, t_id_2, t_id_3, t_id_4;

	// 하드웨어 셋업
	if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준
	
	pinMode(SW0, INPUT); // OUTPUT : 1 | INPUT : 0
	pinMode(SW1, INPUT); // OUTPUT : 1 | INPUT : 0

	pinMode(LED0, OUTPUT);
	pinMode(LED1, OUTPUT);

	digitalWrite(LED0, LOW);
	digitalWrite(LED1, LOW);


	// thread 생성
	if(pthread_create(&t_id, NULL, thread_led_blink, (void*)&status_led0) != 0) {
		printf("pthread_create() error\n");
		return -1;
	}

	if(pthread_create(&t_id_2, NULL, thread_led_blink_2, (void*)&status_led1) != 0) {
		printf("pthread_create() error\n");
		return -1;
	}

	while (1) {

		// thread 생성
		if(pthread_create(&t_id_3, NULL, thread_sw_edge, (void*)&status_led0) != 0) {
			printf("pthread_create() error\n");
			return -1;
		}

		if(pthread_create(&t_id_4, NULL, thread_sw_edge_2, (void*)&status_led1) != 0) {
			printf("pthread_create() error\n");
			return -1;
		}

	}
	
	return 0;
}

// thread 함수 구현
void* thread_led_blink(void *arg) {

	while (1)
	{
		// 상태값에 따른 동작 구현
		if( *((int*)arg) == ON ) {
			digitalWrite(LED0, !digitalRead(LED0));
			delay(300);
		} else {
			digitalWrite(LED0, LOW);
		}	
	}
	
	return NULL;
}

// thread 함수 구현
void* thread_led_blink_2(void *arg) {

	while (1)
	{
		// 상태값에 따른 동작 구현
		if( *((int*)arg) == ON ) {
			digitalWrite(LED1, !digitalRead(LED1));
			delay(300);
		} else {
			digitalWrite(LED1, LOW);
		}
	}
	
	return NULL;
}

// thread 함수 구현
void* thread_sw_edge(void *arg) {

	int *status_led0 = (int*)arg;

	while (1)
	{
		sw0_cur = digitalRead(SW0);
		
		// 조건에 따른 상태값 변경
		if(LOW == sw0_pre && HIGH == sw0_cur) { // Rising Edge Check
			if((*status_led0) == ON) {
				(*status_led0) = OFF;
			} else {
				(*status_led0) = ON;
			}
			delay(1);
		}

		sw0_pre = sw0_cur;

	}
	
	return NULL;
}

// thread 함수 구현
void* thread_sw_edge_2(void *arg) {

	int *status_led1 = (int*)arg;

	while (1)
	{
		sw1_cur = digitalRead(SW1);

		if(LOW == sw1_pre && HIGH == sw1_cur) {
			if((*status_led1) == ON) {
				(*status_led1) = OFF;
			} else {
				(*status_led1) = ON;
			}
			delay(1);
		}

		sw1_pre = sw1_cur;
	}

	return NULL;
}