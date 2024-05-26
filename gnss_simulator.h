#ifndef GNSS_H
#define GNSS_H

// Define max message size
#define MAX_MESSAGE_SIZE 512

// Standard includes
#include <stdio.h>
#include <string.h>

// FreeRTOS includes
#include "task.h"
#include "stream_buffer.h"
#include "FreeRTOS.h"

// Hardcoded GNSS data include
#include "nmea_data.h"

// GNSS data simulator function definitions 
int get_gnss_message(uint8_t *message, uint8_t **start, uint8_t *end);
int send_boot_info(uint8_t *message, uint8_t **start, uint8_t *end);
void gnss_uart_rx(uint8_t data);

// Create stream buffer
static StreamBufferHandle_t gnssStreamBuffer = NULL;

#endif