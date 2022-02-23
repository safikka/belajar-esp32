// Import header dari folder /include
#include <main.h>

// Init task handler
TaskHandle_t task1handle;
TaskHandle_t task2handle;

// Define GPIO Led
#define LED GPIO_NUM_32

// Task 1 Hello World
void hello_wordl(void* param){
    
    // Cetak nama task yang sedang berjalan
    printf("Nama task: %s\n",pcTaskGetName(task1handle));
    int count = 0;

    while (1){
        // Print "Hello World" beserta counting keberapa kali print
        count++;
        printf("[%d] Hello World\n", count);
        vTaskDelay(1000 / portTICK_RATE_MS);

        // Mencoba suspend task (pause) berdasar counting
        if(count == 3){
            vTaskSuspend(task1handle);
            printf("Task1 sedang dipause / suspend\n");
        }

        // Mencoba resume task berdasar counting
        if(count == 6){
            vTaskResume(task1handle);
            printf("Task1 dilanjutkan / resume\n");
        }

        // Mencoba hapus task (delete) berdasar counting
        if(count == 10){
            vTaskDelete(task1handle);
            printf("Task1 dihapus (delete)\n");
        }
    }
    
}

void led_blink(void* param){
    // Setup GPIO Led
    gpio_set_direction(LED,GPIO_MODE_OUTPUT);
    
    
    while(1){
        
    }
}

void app_main() {

}