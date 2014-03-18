# avr-sn74hc135n-tsl235r

A small project about sampling data from the TSL235R light-to-frequency converter over an SN74HC135N two-channel 4-to-1 mux on the ATmega328P.

Data will be sampled using timer/counter 0 and 1 for a configurable time (determined using timer2) and then streamed out in a human-readable format over UART at 115200 baud.