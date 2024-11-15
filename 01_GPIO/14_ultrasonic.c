#include <stdio.h>
#include <wiringPi.h>

#define TRIG 16
#define EHCO 18

int main(void)
{
    unsigned int start_time = 0, end_time = 0;
    double distance = 0.0;

    if(wiringPiSetupPhys() == -1) return -1; // Physical pin 기준

    pinMode(TRIG, OUTPUT); // 출력 // 발신
    pinMode(EHCO, INPUT); // 입력 // 수신

    digitalWrite(TRIG, LOW); // 초기화

    while(1) {
        
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG, LOW);

        while (digitalRead(EHCO) == LOW); // HIGH가 입력될 때까지 대기
        start_time = micros();

        while (digitalRead(EHCO) == HIGH); // LOW가 입력될 때까지 대기
        end_time = micros();
        
        // 마이크로초(microsecond, μs) or 마이크로세컨드 : 백만 분의 1초
        distance = (end_time - start_time) / 58.0; // 공식: uS / 58 = centimeters
        printf("distance %.2f cm\n", distance);

        delay(1000); // 1초마다 거리 측정
    }

    return 0;
}