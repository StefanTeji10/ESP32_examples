/**
 * There are some disadvantages to using the freertos timer.
 * First disadvantage is taht it has only 1 milisecond resolution. 
 * Another thing is that the cllback task is a low priority task and also something we have to be careful about with not blocking. 
 * 
 * Hihg resolution timer. This is an API that is wrapped around.
 * The ESP IDF also has timer to interrupt, and these are lot more convinient to use.
 * 
 * 
 */ 

#include <stdio.h>
#include "esp_timer.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"


void timer_callback(void* args)
{
    //printf("fired after 20 micro secs");
    static bool on;
    on = !on;
    gpio_set_level(GPIO_NUM_4, on);
}

void app_main(void)
{
    gpio_pad_select_gpio(GPIO_NUM_4);
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);

    const esp_timer_create_args_t esp_timer_create_args = {
        .callback = timer_callback,
        .name = "My Timer",
    };
    esp_timer_handle_t esp_timer_handle;
    esp_timer_create(&esp_timer_create_args, &esp_timer_handle);
    //esp_timer_start_once(esp_timer_handle, 20);
    esp_timer_start_periodic(esp_timer_handle, 50);

    int x = 0;
    while(true)
    {
        esp_timer_dump(stdout);
        vTaskDelay(pdMS_TO_TICKS(10000));
        if(x++ == 5)
        {
            esp_timer_stop(esp_timer_handle);
            esp_timer_delete(esp_timer_handle);
        }
    }
}