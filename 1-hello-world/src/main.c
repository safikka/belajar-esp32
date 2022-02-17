#include <main.h>

void task_Hello1(void* param){
    while(1){
        printf("Hello - 1\n");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void task_Hello2(void* param){
    while (1){
        printf("Hello - 2\n");
        vTaskDelay(2000 / portTICK_RATE_MS);
    }
}

void app_main() {

    // NOTE Blocking loopnya
    // while(1){
    //     printf("Hello Blocking\n");
    //     vTaskDelay(500 / portTICK_RATE_MS);
    // }


    // NOTE Biar paralel pake FreeRTOS
    // parameternya itu (fungsiTask, namaTask, sizeStackTask, paramYgMauDiPassing, taskPriority, taskHandle)
    xTaskCreate(task_Hello1,"hello1",1024,NULL,1,NULL);
    xTaskCreate(task_Hello2,"hello2",1024,NULL,2,NULL);
}