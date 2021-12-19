#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"

/**
 * 
 * Main difference between light sleep and deep sleep:
 * With light sleep program continues where it goes to sleep, 
 * and with depp sleep it just go fro the beginning, program acts as it is reset
 * Even the variables are not going to store their values
 * 
 * There is a way to acctualy record the information, even during deep sleep
 * For that we need to add this 
 * 
 */

#define BUTTON GPIO_NUM_25

// RTC_DATA_ATTR needs to be here to stare variable in persistant part of the memory
RTC_DATA_ATTR int timesWokenUp = 0;

void app_main(void)
{
    rtc_gpio_pullup_en(BUTTON);
    rtc_gpio_pulldown_dis(BUTTON);
    //Enabling the deep-sleep wakeup with the external interrupt.
    esp_sleep_enable_ext0_wakeup(BUTTON, 0);

    printf("going to sleep. Woken up %d\n", timesWokenUp++);

    esp_deep_sleep_start();
}