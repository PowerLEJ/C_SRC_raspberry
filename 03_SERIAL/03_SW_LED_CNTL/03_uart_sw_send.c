#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define ON      1
#define OFF     0
#define SW0     26

int main(void)
{   
    int serial;
    int status_led0 = OFF;
    int sw0_pre = LOW, sw0_cur = LOW;

    serial = serialOpen("/dev/ttyS0", 9600); // serialOpen(장치, 통신속도)
    
    if( serial < 0 ) {
        printf("error\n");
        exit(1);
    }

    if(wiringPiSetupPhys() == -1) return -1; // Physical 기준

    pinMode(SW0, INPUT);

    while (1)
    {
        sw0_cur = digitalRead(SW0);

        if(sw0_pre == LOW && sw0_cur == HIGH) // rising edge check
        {
            // 상태값 변경
            if(status_led0 == ON){
                status_led0 = OFF;
                serialPutchar(serial,'X');
            }
            else{
                status_led0 = ON;
                serialPutchar(serial,'O');
            }
            delay(100);
        }
        sw0_pre = sw0_cur;

    }

    return 0;
}