#include "esp_log.h"
#include "nvs_flash.h"
#include "cJSON.h"
//#include "connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"


#define TAG "MQTT"

xSemaphoreHandle connectionSemaphore;

void onConnected(void *para)
{
    while(true)
    {
        if(xSemaphoreTake(connectionSemaphore, 10000 / portMAX_DELAY))
        {

        }
    }
}

void app_main()
{
    connectionSemaphore = xSemaphoreCreateBinary();
    wifiInit();
    xTaskCreate(&onConnected, "handle comms", 1024 * 5, NULL, 5, NULL);
}

