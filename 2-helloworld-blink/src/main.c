#include <main.h>

TaskHandle_t task1Handle;
TaskHandle_t task2Handle;
TaskHandle_t task3Handle;

#define LED 36
#define LED_PIN 2

void print_Hello(void* param){
    while(1){
        printf("Hello World!");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void led_hello(void* param){
    gpio_pad_select_gpio(LED);
    gpio_set_direction(LED,GPIO_MODE_OUTPUT);
    while(1){
        gpio_set_level(LED,0);
        printf("LED Mati!");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LED,1);
        printf("LED Nyala!");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void led_bawaan(void* param){
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN,GPIO_MODE_OUTPUT);
    while(1){
        gpio_set_level(LED_PIN,0);
        printf("LED Bawaan Mati!");
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN,1);
        printf("LED Bawaan Nyala!");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main() {
    xTaskCreate(print_Hello, "task1", 1024, NULL, 1, &task1Handle);
    xTaskCreate(led_bawaan, "task3", 1024, NULL, 2, &task3Handle);
    xTaskCreatePinnedToCore(led_hello, "task2", 1024, NULL, 1, &task2Handle, 1);
}