#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define SAMPLE_RATE 1000
#define CARRIER_FREQ 100
#define BIT_DURATION 1.0  // in seconds
#define NUM_BITS 8

/*
 * Amplitude Shift Keying (ASK) Simulation in C
 * --------------------------------------------
 * This program demonstrates a basic simulation of Amplitude Shift Keying (ASK),
 * a type of digital modulation where binary data is transmitted by varying the 
 * amplitude of a carrier wave.
 *
 * Modulation:
 * - Binary '1' is represented by a carrier sine wave.
 * - Binary '0' is represented by no signal (zero amplitude).
 *
 * Demodulation:
 * - The received signal is analyzed for its energy (squared amplitude sum).
 * - If the energy is above a threshold, it is decoded as '1'; otherwise '0'.
 *
 * Notes:
 * - This is a conceptual simulation and does not handle noise, filtering, or real-time processing.
 * - Useful for learning how ASK works at a basic signal level.
 */

// Example binary message
int binary_data[NUM_BITS] = {1, 0, 1, 1, 0, 0, 1, 0};

// Simulate ASK modulation
void ask_modulate(double modulated_signal[], int binary_data[], int num_bits) {
    int samples_per_bit = (int)(SAMPLE_RATE * BIT_DURATION);
    for (int i = 0; i < num_bits; i++) {
        for (int j = 0; j < samples_per_bit; j++) {
            double t = j / (double)SAMPLE_RATE;
            int index = i * samples_per_bit + j;

            if (binary_data[i] == 1) {
                // Transmit carrier
                modulated_signal[index] = sin(2 * PI * CARRIER_FREQ * t);
            } else {
                // Transmit nothing (0 amplitude)
                modulated_signal[index] = 0;
            }
        }
    }
}

// Simple ASK demodulation: detect if signal is present or not
void ask_demodulate(int demodulated_data[], double modulated_signal[], int num_bits) {
    int samples_per_bit = (int)(SAMPLE_RATE * BIT_DURATION);
    for (int i = 0; i < num_bits; i++) {
        double energy = 0.0;
        for (int j = 0; j < samples_per_bit; j++) {
            int index = i * samples_per_bit + j;
            energy += modulated_signal[index] * modulated_signal[index];  // power estimation
        }

        // Threshold to detect presence of signal
        if (energy > 1.0) {
            demodulated_data[i] = 1;
        } else {
            demodulated_data[i] = 0;
        }
    }
}

int main() {
    int samples_per_bit = (int)(SAMPLE_RATE * BIT_DURATION);
    int total_samples = NUM_BITS * samples_per_bit;

    double modulated_signal[total_samples];
    int demodulated_data[NUM_BITS];

    // ASK modulation
    ask_modulate(modulated_signal, binary_data, NUM_BITS);

    // ASK demodulation
    ask_demodulate(demodulated_data, modulated_signal, NUM_BITS);

    // Output results
    printf("Original data:     ");
    for (int i = 0; i < NUM_BITS; i++) {
        printf("%d ", binary_data[i]);
    }

    printf("\nDemodulated data:  ");
    for (int i = 0; i < NUM_BITS; i++) {
        printf("%d ", demodulated_data[i]);
    }

    printf("\n");

    return 0;
}
