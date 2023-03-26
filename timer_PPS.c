#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "driver/gptimer.h"

#include "timer_PPS.h"
#include "GNSS_PPS.h"



gptimer_handle_t pps_timer_handle = NULL;

int alarm_period = TIMER_RESOLUTION * 1;

int captured_time_points = 0;
int old_err = 0;
int i_err = 0;
static bool IRAM_ATTR my_alarm (gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx){

    // Count the number of time points received
    if (captured_time_points < MINIMUM_SAMPLES_FOR_TUNING)
        captured_time_points++;

    // Get offset of 
    int err = gnss_pps_get_time_point();
    i_err += err;
    int d_err = err - old_err;
    old_err = err;


    // Adjust frequency if there are at least 2 gnss pps time points
    if(captured_time_points == MINIMUM_SAMPLES_FOR_TUNING)
    {

        alarm_period += d_err/a+err/b +i_err/c;
        gptimer_alarm_config_t alarm_config = {
            .alarm_count = 0, 
            .reload_count = alarm_period, 
            .flags.auto_reload_on_alarm = 1
        };
        gptimer_set_alarm_action(timer, &alarm_config);
    }

    return true;
}

// Initialize 1PPS timer
void timer_PPS_init()
{

    // Set timer to have maximum resolution counting down
    gptimer_config_t config =  {
        .resolution_hz = TIMER_RESOLUTION,
        .direction = GPTIMER_COUNT_DOWN,  /*!< Counter direction  */
        .clk_src = TIMER_CLK_SRC
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&config, &pps_timer_handle));


    // Set nominal 1Hz reloaded alarm
    gptimer_alarm_config_t alarm_config = {
        .alarm_count = 0, 
        .reload_count = alarm_period, 
        .flags.auto_reload_on_alarm = 1
    };
    gptimer_set_alarm_action(pps_timer_handle, &alarm_config);

    // Add alarm handler to timer
    gptimer_event_callbacks_t cbs = {
        .on_alarm = my_alarm, // register user callback
    };
    gptimer_register_event_callbacks(pps_timer_handle, &cbs, NULL);

}

// Start timer
void timer_pps_start_timer()
{
    // Start timer
    gptimer_enable(pps_timer_handle);
    gptimer_start(pps_timer_handle);
}

// Get current pps timer counter value
int timer_pps_get_time()
{
    int time_point;
    gptimer_get_raw_count(pps_timer_handle, &time_point);
    return time_point;
}

// Return alarm period
int timer_pps_get_alarm_period()
{
    return alarm_period;
}

int time_counter = 0;
// Print alarm period
void print_alarm_period()
{
    printf("%d - alarm period: %d,      int_err: %d                         ", time_counter++, alarm_period, i_err);
}