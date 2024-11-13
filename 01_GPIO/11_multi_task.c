/**
 * 1초마다 카운트
 */
#include <stdio.h>
#include <wiringPi.h>

const unsigned int t1_delay = 1000;
const unsigned int t2_delay = 500;

int main(void)
{
    unsigned int t1_prev = 0;
    unsigned int t2_prev = 0;

    unsigned int t1_now = millis();
    unsigned int t2_now = millis();

    int count_sec = 0;
    int count_msec = 0;

    while (1)
    {
        t1_now = millis();
        if(t1_now - t1_prev >= t1_delay) {
            t1_prev = t1_now;
            printf("count_sec = %ds\n", count_sec);
            count_sec++;
        }

        t2_now = millis();
        if(t2_now - t2_prev >= t2_delay) {
            t2_prev = t2_now;
            printf("count_msec = %dms\n", count_msec);
            count_msec++;
        }
    }

    return 0;
}