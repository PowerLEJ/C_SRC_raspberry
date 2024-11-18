#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <pthread.h>

// 함수 선언
void* thread_uart_send(void *arg);
void* thread_uart_recv(void *arg);

int main(void)
{   
    // 지역변수 선언
    pthread_t t_id, t2_id;
    int serial;

    serial = serialOpen("/dev/ttyS0", 9600); // serialOpen(장치, 통신속도)
    
    if( serial < 0 ) {
        printf("error\n");
        exit(1);
    }

    // 하드웨어 셋업
	if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준

    // thread 생성
	if(pthread_create(&t_id, NULL, thread_uart_send, (void*)&serial) != 0) {
		printf("pthread_create() error\n");
		return -1;
	}

    if(pthread_create(&t2_id, NULL, thread_uart_recv, (void*)&serial) != 0) {
		printf("pthread_create() error\n");
		return -1;
	}

    while (1) {
        
    }

    return 0;
}

void* thread_uart_send(void *arg) {
    
    int serial = *((int*)arg);
    char str[100] = {0,};

    while (1) {
        fputs("Send Data : ", stdout);
        scanf("%s", str);
        serialPuts(serial, str);
    }
    
    return NULL;
}

void* thread_uart_recv(void *arg) {
    
    int serial = *((int*)arg);

    while (1) {
        if(serialDataAvail(serial)) { // Data 들어왔는지 안들어왔는지 Check
            printf("%c\n", serialGetchar(serial));
            fflush(stdout); // 표준출력스트림의 버퍼를 비움
        }
    }
    
    return NULL;
}
