#include "parser.h"



static TaskHandle_t simulator_task = NULL;
static TaskHandle_t parser_task = NULL;
static TaskHandle_t consumer_task = NULL;

int main() {
    vTaskStartScheduler();

    // Create GNSS message simulator task,
    // parsing task and user notification task
    xTaskCreate(gnss_uart_rx,
                "GNSS Simulator",
                8192,
                NULL,
                3,
                &simulator_task);
    xTaskCreate(parse,
                "Parse task",
                8192,
                NULL,
                2,
                &parser_task);
    
    
    vTaskStartScheduler();

    return 0;
}
