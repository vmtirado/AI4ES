#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#define UART_NUM UART_NUM_2
#define TX_PIN 17
#define RX_PIN 16
#define BUF_SIZE 1024
#define TASK_MEMORY 1024
#define LED 2

static const char *tag = "TAG";
int delay_ms=500;

static const void uart_task(void *pvTasks){
    uint8_t  *data = (uint8_t *) malloc(BUF_SIZE); 
    
    while(1){
        int bytes_read = uart_read_bytes(UART_NUM, data, BUF_SIZE, pdMS_TO_TICKS(100));
        
        if(bytes_read>0){
            uart_write_bytes(UART_NUM, (const char *)data, bytes_read)\<
            data[bytes_read]='\0';
            int delay_rate = atoi((const char *) data);
            if (delay_rate>0){
                delay_ms = delay_rate;
            }
        }
        gpio_set_level(LED,1);
        vTaskDelay(delay_ms);
        gpio_set_level(LED,0);
        vTaskDelay(delay_ms);



    }
    
}

static const void config_led(void){
  gpio_reset_pin(LED);
  gpio_set_direction(LED,GPIO_MODE_OUTPUT);

}

static const void init_uart(void){
    uart_config_t uart_config ={
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM, &uart_config );
    uart_set_pin(UART_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM,BUF_SIZE,BUF_SIZE,0,NULL,0);
    xTaskCreate(uart_task, "uart_task",TASK_MEMORY,NULL,5,NULL);
    ESP_LOGI(tag,"Init UART completed");


}


void app_main() {
    config_led();
    init_uart();

}