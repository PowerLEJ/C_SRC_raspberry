#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define SERVO 18

#define MIN_0       5.0
#define MAX_180     25.0
#define STEP        (MAX_180 - MIN_0) / 180.0
#define DEGREE_0    MIN_0

int main(void)
{
    int angle = 0;

    if(wiringPiSetupPhys() == -1) return -1; // Physical 기준

    softPwmCreate(SERVO, 0, 200);
    softPwmWrite(SERVO, DEGREE_0);

    while(1) {
        printf("각도를 입력하세요 : ");
        scanf("%d", &angle);

        if(angle < 0 || angle > 180) {
            printf("각도는 0도 이상, 180도 이하로 입력해주세요.\n");
            continue;
        }
        softPwmWrite(SERVO, DEGREE_0 + (angle * STEP));
    }

    return 0;
}

/*
실수
int main(void)
{
    double angle = 0.0;

    if(wiringPiSetupPhys() == -1) return -1; // Physical 기준

    softPwmCreate(SERVO, 0, 200);
    softPwmWrite(SERVO, DEGREE_0);

    while(1) {
        printf("각도를 입력하세요 : ");
        scanf("%lf", &angle);

        if(angle < 0.0 || angle > 180.0) {
            printf("각도는 0도 이상, 180도 이하로 입력해주세요.\n");
            continue;
        }
        // 근데 softPwmWrite(int, int) 여서 angle을 double로 받을 수 없는 것 같기도 하고
        softPwmWrite(SERVO, DEGREE_0 + (angle * STEP));
    }

    return 0;
}
*/