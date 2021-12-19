#include <stdio.h>
#include "esp_log.h"


void app_main(void)
{

    // Those are going by levels so ESP_LOGE is the lowest level, and Verbose is the highes, 
    // if we choose level Debug all lower then that will show up

    //Changing log level from code
    esp_log_level_set("LOG", ESP_LOG_INFO);
    
    // We have formatted String inside the LOG functions so we can also print the numbers, and other variables
    int number = 0;
    //log error
    ESP_LOGE("LOG", "This is an error %d", number++);
    //log warning
    ESP_LOGW("LOG", "This is a warning");
    //log informational
    ESP_LOGI("LOG", "This is an info");
    //debug --> note: by default they are turned off, we need menuconfig to turn it on
    ESP_LOGD("LOG", "This is a debug");
    //Verbose --> note: by default they are turned off, we need menuconfig to turn it on
    ESP_LOGV("LOG", "This is Verbose");

    //Menuconfig
    // Component config --> Log output --> choose

}