#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define SERVO 18

int main(void)
{
    if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준

    softPwmCreate(SERVO, 0, 200); // (pin, LOW(0) or HIGH(1), 주기(단위 : 1 = 0.1ms, 200 = 20ms))
    
    // (예시) Create 시 200 의 2.5%로 설정하기 위해 값을 5으로 설정
    // softPwmWrite(SERVO, 5); // (pin, 값(한 주기에서의 DUTB %에 대한 값)) 

    while (1) {
        // 5 : 0도
        softPwmWrite(SERVO, 5); // 5 : 주기 200에 대한 2.5%
        delay(1000);

        // 25 : 180도
        softPwmWrite(SERVO, 25); // 25 : 주기 200에 대한 12.5%
        delay(1000);
    }
    
    // softPwmStop(SERVO); // (pin)

    return 0;
}