#ifndef TIMER_PPS_H_
#define TIMER_PPS_H_


#define TIMER_RESOLUTION 40000000
#define TIMER_CLK_SRC GPTIMER_CLK_SRC_APB

#define MINIMUM_SAMPLES_FOR_TUNING 3

// Inverse of PID controller's gains
#define a -2
#define b -10
#define c -100


// Initialize 1PPS timer
void timer_PPS_init();

// Get current pps timer counter value
int timer_pps_get_time();

// Print alarm period
void print_alarm_period();


// Start timer
void timer_pps_start_timer();


// Return alarm period
int timer_pps_get_alarm_period();
#endif