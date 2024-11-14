#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>

#define PIEZO 18

const int melody[8] = {262, 294, 330, 349, 392, 440, 494, 523}; // 4옥타브 {도레미파솔라시도}

int main(void) 
{
    if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준

    softToneCreate(PIEZO);

    while (1)
    {
        for (int i = 0; i < 8; i++)
        {
            softToneWrite(PIEZO, melody[i]);
            delay(1000);
        }
    }
    
    return 0;
}