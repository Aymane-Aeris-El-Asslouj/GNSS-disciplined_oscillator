

#include <stdio.h>
#include <inttypes.h>
#include "driver/gpio.h"
#include "driver/uart.h"
#include "gnss_receiver_read.h"



uint8_t data[400];
void gnss_receiver_read(uint8_t rx_pin_number)
{


    gpio_reset_pin(rx_pin_number);
    gpio_set_direction(rx_pin_number, GPIO_MODE_INPUT);
    gpio_set_pull_mode(rx_pin_number, GPIO_FLOATING);

    uart_config_t uart_config = {
        .baud_rate = 38400,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    // Configure UART parameters
    const int uart_buffer_size = (1024 * 2);
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, uart_buffer_size, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_2, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, UART_PIN_NO_CHANGE, rx_pin_number, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));



    int length = 0;
    int rxBytes = 0;
    uint8_t my_char;
    while(1)
    {
        rxBytes = uart_read_bytes(UART_NUM_2, &my_char, 1, 500 / portTICK_PERIOD_MS);
        data[rxBytes] = 0;
        printf("%c", my_char);
        //ESP_LOGI(TAG, "Read %d bytes: '%s'", rxBytes, data);
        //vTaskDelay(500 / portTICK_PERIOD_MS); 
    }
}