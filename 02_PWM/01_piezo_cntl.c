#include <stdio.h>
#include <wiringPi.h>

#define HZ 261.63
#define PERIOD 1.0 / HZ

#define PIEZO 18

int main(void) 
{
    if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준

    pinMode(PIEZO, OUTPUT);

    while (1) {   
        digitalWrite(PIEZO, HIGH);
        delay((PERIOD/2.0) * 1000);

        digitalWrite(PIEZO, LOW);
        delay((PERIOD/2.0) * 1000);
    }
    
    return 0;
}