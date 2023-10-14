#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "Freenove_WS2812_Lib_for_ESP32.h"

#define UART_NUM UART_NUM_0
#define TX_PIN 43
#define RX_PIN 44
#define BUF_SIZE 1024
#define TASK_MEMORY 1024

#define LEDS_COUNT 1
#define LED 18
#define CHANNEL 0
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL);

int delay_ms=500;

static const void uart_task(void *pvTasks){
    uint8_t  *data (uint8_t *) malloc(BUF_SIZE) 
    while(1){
        int bytes_read = uart_read_bytes(UART_NUM, data, BUF_SIZE, pdMS_TO_TICKS(100));
        
        if(bytes_read>0){
            uart_write_bytes(UART_NUM, (const char *)data, bytes_read)\<
            data[bytes_read]='\0';
            int delay_rate = atoi((const char *) data);
            if (dela_rate>0){
                delay_ms = dela_rate;
            }
        }
        strip.setLedColorData(0,0,0,255);
        vTaskDelay(delay_ms);
        strip.setLedColorData(0,255,0,0);
        vTaskDelay(delay_ms);



    }
    
}

static const void config_led(void){
    strip.begin();
  strip.setBrightness(15);


}

static const void init_uart(void){
    uart_config_t uart_config ={
        .baud_rate 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM, &uart_config );
    uart_set_pin(UART_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM,BUF_SIZE,BUF_SIZE,0,NULL,0);
    xTaskCreate(uart_task, "uart_task",TASK_MEMORY_NULL,5,NULL);
    ESP_LOGI(TAG,"Init UART completed");


}


void app_main() {
    config_led();
    init_uart();

}