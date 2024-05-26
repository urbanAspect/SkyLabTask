#include "gnss_simulator.h"


#define sbiSTREAM_BUFFER_LENGTH_BYTES        ( ( size_t ) 100 )
#define sbiSTREAM_BUFFER_TRIGGER_LEVEL_10    ( ( BaseType_t ) 10 )



int get_gnss_message(uint8_t *message, uint8_t **start, uint8_t *end) {
    // Find the next $GPGGA by skipping the one we are currently at
    end = (uint8_t *)strstr((char *)(*start + strlen("$GPGGA")), "$GPGGA");
    int messageLength;

    if (end == NULL) {
        // If no more occurrences found, copy remaining characters to the EOF
        end = (uint8_t *)strchr((char *)(*start + 1), '\0'); /* Skip \0 from the previous message */
        messageLength = end - *start;
        memcpy(message, *start, messageLength);
        *start = NULL;
        return messageLength;
    } else {
        // Copy characters between occurrences to message
        memcpy(message, *start, end - *start);
        message[end - *start] = '\0';
        messageLength = end - *start;
        *start = end;
        return messageLength;
    }
}


int send_boot_info(uint8_t *message, uint8_t **start, uint8_t *end) {
    // Find first $GPGGA message and store everything
    // before it as a boot data in message variable 
    end = (uint8_t *)strstr((char *)*start, "$GPGGA");
    int messageLength = end - *start;
    memcpy(message, *start, end - *start);
    *start = end;
    return messageLength;
}

void gnss_uart_rx(uint8_t data) {
    uint8_t *end = NULL;
    
    // variable to which message is passed
    uint8_t message[MAX_MESSAGE_SIZE] = {0};

    // provided GNSS data in string format inside nmea_data.h file
    uint8_t *start = gnss_data;

    // Create stream buffer
    gnssStreamBuffer = xStreamBufferCreate(MAX_MESSAGE_SIZE, 1);


    // Write boot info into stream buffer
    int messageLength = send_boot_info(message, &start, end);
    xStreamBufferSendFromISR(gnssStreamBuffer, (void *)message, messageLength, NULL);
    vTaskDelay(pdMS_TO_TICKS(1000));

    // While gnss message is available
    // Send next gnss message 
    while (start != NULL) {
        messageLength = get_gnss_message(message, &start, end);
        xStreamBufferSendFromISR(gnssStreamBuffer, 
                                 (void *)message,
                                 messageLength, 
                                 NULL);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    // Once there is no more messages, kill task
    vTaskDelete(NULL);
}
