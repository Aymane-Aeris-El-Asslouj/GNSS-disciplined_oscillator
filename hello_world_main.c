

#include <stdio.h>
//#include <inttypes.h>
//#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/gptimer.h"


#include "timer_PPS.h"
#include "GNSS_PPS.h"

#include "gnss_receiver_read.h"


void app_main(void)
{
    // // (For debugging) Reads gnss receiver NVMEA messages through UART2 
    // // to check on available satellites through RX2 pin 16
    // gnss_receiver_read(16);

    // Initialize 1PPS timer
    timer_PPS_init();

    // Initialize 1PPS input handler
    GNSS_PPS_init();

    // Print time points of GNSS relative to timer
    while(1){
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        print_alarm_period();
        print_gnss_offset();
        printf("\n");
    }


}
