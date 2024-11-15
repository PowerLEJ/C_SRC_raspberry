#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(void)
{   
    int serial;
    unsigned long time = 0; // 통신 Delay 시간

    serial = serialOpen("/dev/ttyS0", 9600); // serialOpen(장치, 통신속도)
    
    if( serial < 0 ) {
        printf("error\n");
        exit(1);
    }

    if(wiringPiSetupPhys() == -1) return -1; // Physical 기준

    while (1)
    {
        if(millis() - time >= 1000) { // 1초마다
            serialPutchar(serial, 'A');
            time = millis();
        }
    }

    return 0;
}