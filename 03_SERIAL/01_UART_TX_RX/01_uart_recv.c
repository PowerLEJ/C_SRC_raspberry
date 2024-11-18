#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(void)
{
    int serial;

    serial = serialOpen("/dev/ttyS0", 9600); // serialOpen(장치, 통신속도)

    if( serial < 0 ) {
        printf("error\n");
        exit(1);
    }

    if(wiringPiSetupPhys() == -1) return -1; // Physical 기준

    while (1)
    {
        if(serialDataAvail(serial)) { // Data 들어왔는지 안들어왔는지 Check
            printf("%c\n", serialGetchar(serial));
            fflush(stdout); // 
        }
    }

    return 0;
}