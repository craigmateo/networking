#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
 * Filename: frame_transmission.c
 * Description: 
 *   This program demonstrates basic concepts of the Data Link Layer,
 *   focusing on cabling and frame transmission. It simulates how data
 *   frames are structured and transmitted over a physical medium,
 *   illustrating framing and error detection techniques typically
 *   found in Ethernet or similar protocols.
*/

#define MAX_FRAME_SIZE 256

// A simple frame structure: header, data, CRC (trailer)
typedef struct {
    char header[10];        // e.g., "FRAMEHDR"
    char data[200];         // payload
    unsigned short crc;     // simple CRC16 placeholder
} Frame;

// Simple CRC16 calculation (placeholder, not real CRC16)
unsigned short simple_crc16(const char *data, size_t length) {
    unsigned short crc = 0xFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) crc = (crc >> 1) ^ 0xA001;
            else crc >>= 1;
        }
    }
    return crc;
}

// Simulated CSMA/CD: check if "medium" is busy, if so, wait and retry
int csma_cd_send(Frame *frame) {
    int attempts = 0;
    int max_attempts = 5;

    while (attempts < max_attempts) {
        // Simulate checking if medium is busy
        int medium_busy = rand() % 2;  // 0 = free, 1 = busy

        if (!medium_busy) {
            printf("Medium free. Sending frame...\n");
            // "Send" frame - here we just print contents
            printf("Header: %s\n", frame->header);
            printf("Data: %s\n", frame->data);
            printf("CRC: 0x%04X\n", frame->crc);
            return 1; // success
        } else {
            printf("Medium busy, collision detected. Backing off and retrying...\n");
            attempts++;
            // Simulate random backoff wait
            int backoff = (rand() % 5) + 1;
            for (int i = 0; i < backoff * 1000000; i++) { } // busy wait (inefficient but illustrative)
        }
    }
    printf("Failed to send frame after %d attempts\n", max_attempts);
    return 0; // failure
}

int main() {
    srand(time(NULL));

    // Prepare a frame with header and data
    Frame frame;
    strcpy(frame.header, "FRAMEHDR");
    strcpy(frame.data, "This is a test payload from the network layer.");
    frame.crc = simple_crc16(frame.data, strlen(frame.data));

    // Simulate sending frame using CSMA/CD
    if (csma_cd_send(&frame)) {
        printf("Frame sent successfully.\n");
    } else {
        printf("Frame transmission failed.\n");
    }

    return 0;
}
