#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Basic configurations */
#define configUSE_PREEMPTION            1
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configCPU_CLOCK_HZ              ((unsigned long) 80000000)
#define configTICK_RATE_HZ              ((TickType_t) 1000)
#define configMAX_PRIORITIES            5
#define configMINIMAL_STACK_SIZE        ((unsigned short) 128)
#define configTOTAL_HEAP_SIZE           ((size_t) (16 * 1024))
#define configMAX_TASK_NAME_LEN         16
#define configUSE_TRACE_FACILITY        1
#define configUSE_16_BIT_TICKS          0
#define configIDLE_SHOULD_YIELD         1
#define configUSE_MUTEXES               1

/* Memory allocation configurations */
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#define configSUPPORT_STATIC_ALLOCATION  0

/* Hook function related definitions */
#define configCHECK_FOR_STACK_OVERFLOW  2
#define configUSE_MALLOC_FAILED_HOOK    1

/* Runtime stats gathering definitions */
#define configGENERATE_RUN_TIME_STATS   0
#define configUSE_STATS_FORMATTING_FUNCTIONS 1

/* Co-routine related definitions */
#define configUSE_CO_ROUTINES           0
#define configMAX_CO_ROUTINE_PRIORITIES 2

/* Software timer related definitions */
#define configUSE_TIMERS                1
#define configTIMER_TASK_PRIORITY       (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH        10
#define configTIMER_TASK_STACK_DEPTH    (configMINIMAL_STACK_SIZE * 2)

/* Interrupt nesting behavior configuration */
#define configKERNEL_INTERRUPT_PRIORITY 255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 191

/* Define to trap errors during development */
#define configASSERT(x) if ((x) == 0) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* Optional functions */
#define INCLUDE_vTaskPrioritySet        1
#define INCLUDE_uxTaskPriorityGet       1
#define INCLUDE_vTaskDelete             1
#define INCLUDE_vTaskCleanUpResources   0
#define INCLUDE_vTaskSuspend            1
#define INCLUDE_vTaskDelayUntil         1
#define INCLUDE_vTaskDelay              1
#define INCLUDE_xTaskGetSchedulerState  1

#endif /* FREERTOS_CONFIG_H */
