#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_system.h"

/**
 * The timer itsel actually gets called by the idle task,
 * that means we do not want to delay this very much. 
 * We should not be putting any waits in here or vTaskDelays or waiting for queues or anything else like that.
 * 
 * 
 */ 


void on_timer(TimerHandle_t xTimer)
{
    printf("time hit %lld\n", esp_timer_get_time() / 1000);
}


void app_main(void)
{
    printf("app started %lld\n", esp_timer_get_time() / 1000);
    // 1. param: name of the timer
    // 2. param: Is the amount of time or the amount of ticks it's going to take before the timer kicks in
    // 3. param: is whether ot not we want this to repeat or to reload, whoch basically means do we want it to fire just once or we want to fire again nad again
    // 4. param: ID that we can set 
    // 5. param: callback that shoud happen or should fire once the actual timer is reached.
    TimerHandle_t xTimer = xTimerCreate("my Timer", pdMS_TO_TICKS(1000), true, NULL, on_timer);

    // necesary to start a timer
    xTimerStart(xTimer, 0);
} 