#include <main.h>

TaskHandle_t task1Handle;
TaskHandle_t task2Handle;
TaskHandle_t task3Handle;

#define LED_PIN 2
#define LED GPIO_NUM_32

void print_Hello(void* param){
    while(1){
        printf("Hello World!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void led_hello(void* param){
    
    // Set GPIO
    gpio_set_direction(LED,GPIO_MODE_OUTPUT);
    
    while(1){
        gpio_set_level(LED,0);
        printf("LED Mati!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LED,1);
        printf("LED Nyala!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void led_bawaan(void* param){
    
    // Set GPIO
    gpio_set_direction(LED_PIN,GPIO_MODE_OUTPUT);
    
    while(1){
        gpio_set_level(LED_PIN,0);
        printf("LED Bawaan Mati!\n");
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN,1);
        printf("LED Bawaan Nyala!\n");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main() {
    xTaskCreate(print_Hello, "task1", 1024, NULL, 1, &task1Handle);
    xTaskCreate(led_bawaan, "task3", 2048, NULL, 2, &task3Handle);

    // Ini bisa setting core keberapa yg mau dipake 0 atau 1
    xTaskCreatePinnedToCore(led_hello, "task2", 2048, NULL, 1, &task2Handle, 1);
}