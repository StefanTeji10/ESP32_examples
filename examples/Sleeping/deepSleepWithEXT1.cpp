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

/**
 * Main difference between ext0 and ext1
 * Ext1 is giving us more capabilities then ext0
 * Ext0 asked us to put in the number as well as a high or low level
 * Ext1 is asking us for uint64 mask, this mask means that we can put multiple pins
 * second parameter is esp_sleep_ext1 wakeup mode, we have two options: ALL_LOW, ANY_HIGH
 * This means that we can put multiple buttons in our circuit and we can expect all of them to go low before the chip wakes up.
 * Or we can configure it that any go high for it to wake up. 
 * 
 */

#define BUTTON_1 GPIO_NUM_25
#define BUTTON_2 GPIO_NUM_26


// RTC_DATA_ATTR needs to be here to stare variable in persistant part of the memory
RTC_DATA_ATTR int timesWokenUp = 0;

void app_main(void)
{

    // To have option tu use this GPIO while we are wake
    // general gpio functions using the pin.
    rtc_gpio_deinit(BUTTON_1);
    rtc_gpio_deinit(BUTTON_2);
    // My code functionality whe esp32 is waked up


    // My code end

    // one of the primary differences between ext0 and ext1 is that ext0 actually turns on our RTC peripherals
    // whereas ext1 does not so we need to actually enable the RTC peripherals
    // we do that whit using the esp_sleep_pd_config function
    // First param is domain    -->     
    // Second param is option   -->    in light sleep AUTO will mean ON and in deep sleep in means OFF so we need to turn it ON  
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    // Kada dovodimo napon na pin treba nam pulldown, a kada dovodimo nulu na pin treba na pullup
    rtc_gpio_pullup_en(BUTTON_1);
    rtc_gpio_pulldown_dis(BUTTON_1);
    rtc_gpio_pullup_en(BUTTON_2);
    rtc_gpio_pulldown_dis(BUTTON_2);

    // creating a uint64 mask
    uint64_t mask = (1ULL << BUTTON_1) | (1ULL << BUTTON_2);


    //Enabling the deep-sleep wakeup with the external interrupt.
    esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ALL_LOW);


    printf("going to sleep. Woken up %d\n", timesWokenUp++);

    esp_deep_sleep_start();
}