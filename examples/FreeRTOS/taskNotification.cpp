#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


// Task notification require that we actually have a handler on these taskes that we create. 

// Task handler
static TaskHandle_t receiverHandler = NULL;



void sender(void * params)
{
    while(true)
    {
        //Notifying receiver that something need to happend
        xTaskNotifyGive(receiverHandler);
        xTaskNotifyGive(receiverHandler);
        xTaskNotifyGive(receiverHandler);
        xTaskNotifyGive(receiverHandler);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void receiver(void * params)
{
    while(true)
    {
        // in order receiver to be triggered  
        // parameter pdFALSE --> prolazi kroz poziv onoliko puta koliko je pozvan, dok pdTRUE prolazi jednom, a belezi koliko puta je pozvan. 
        // parametar portMAX_DELAY --> timer, so task receiver will never progress in case it is not Notified be task receiver
        int count = ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
        printf("received notification %d times\n", count);
    }
}

void app_main(void)
{
    // task with handler
    xTaskCreate(&receiver, "sender", 2048, NULL, 2, &receiverHandler);
    xTaskCreate(&sender, "receiver", 2048, NULL, 2, NULL);
}