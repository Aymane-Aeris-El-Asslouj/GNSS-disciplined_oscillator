# GNSS-disciplined oscillator

This repository contains the firmware code for my GNSS-disciplined oscillator. It uses the ESP32 microcontroller's timer as an oscillator running at the highest resolution. Then, using 1PPS pulses from a GNSS receiver, it adjusts the frequency of the oscillator to remove the error frequency offset. It uses a PID controller to remove the offset while minimizing the noise of the 1PPS signal.
