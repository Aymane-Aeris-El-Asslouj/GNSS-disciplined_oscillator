#ifndef GNSS_PPS_H_
#define GNSS_PPS_H_

// gnss pps input pin
#define PPS_PIN 36

// Initialize gnss pps input handler
void GNSS_PPS_init();

// print gnss time offset information
void print_gnss_offset();

// Return gnss time point
int gnss_pps_get_time_point();

#endif