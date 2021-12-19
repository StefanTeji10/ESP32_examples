#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"

/**
 * @brief 
 * Main difference between light sleep and deep sleep:
 * With light sleep program continues where it goes to sleep, 
 * and with depp sleep it just go fro the beginning, program acts as it is reset
 * Even the variables are not going to store their values
 * 
 * There is a way to acctualy record the information, even during deep sleep
 * For that we need to add this 
 * 
 */

// RTC_DATA_ATTR needs to be here to stare variable in persistant part of the memory
RTC_DATA_ATTR int timesWokenUp = 0;

void app_main(void)
{
    // hibernation!!!
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);

    //sleeping for 5 seconds
    esp_sleep_enable_timer_wakeup(5 * 1000000);
    printf("going to sleep. Woken up %d\n", timesWokenUp++);

    esp_deep_sleep_start();
}