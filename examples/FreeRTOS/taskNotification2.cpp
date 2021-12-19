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
        xTaskNotify(receiverHandler, (1<<0), eSetBits); 
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler, (1<<1), eSetBits);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler, (1<<2), eSetBits);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler, (1<<3), eSetBits);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        // with eSetValueWithOverride, is setting binari values (1<<x) but before that it is clearing the register (variable)
        // with eSetBits it is keeping the previous state
    }
}

void receiver(void * params)
{
    while(true)
    {
        uint state;
        // da bi mogli da znamo od kog xTaskNotify je dosla poruka
        // parametri u xTaskNotifyWait, prvi parametar sluzi da resetuje registar koji je upisan od strane taska koji zove xTaskNotify
        // mozemo da sa maskom bitamo koji ce bit biti izbrisan
        xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
        printf("received state %d times\n", state);
        // Instead of actually printing out the receive notification amount of times, 
        // in the real time scenarion we can pass a state to switch statement and act accordingly

    }
}

void app_main(void)
{
    // task with handler
    xTaskCreate(&receiver, "sender", 2048, NULL, 2, &receiverHandler);
    xTaskCreate(&sender, "receiver", 2048, NULL, 2, NULL);
}