#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define LED0 36

int main(void)
{
    int serial;
    char recv_ch = 0;

    serial = serialOpen("/dev/ttyS0", 9600); // serialOpen(장치, 통신속도)

    if( serial < 0 ) {
        printf("error\n");
        exit(1);
    }

    if(wiringPiSetupPhys() == -1) return -1; // Physical 기준
    
    pinMode(LED0, OUTPUT);
    digitalWrite(LED0, LOW);

    while (1)
    {
        if(serialDataAvail(serial)) { // 수신된 데이터가 있으면 참
            
            recv_ch = serialGetchar(serial);
            printf("%c\n", recv_ch);
            serialPutchar(serial, recv_ch);
            
            if(recv_ch == 'O'){
                digitalWrite(LED0, HIGH);
            }
            else if(recv_ch == 'X'){
                digitalWrite(LED0, LOW);
            }

            fflush(stdout);
        }
    }

    return 0;
}