// app_uart_utils.h
#ifndef APP_UART_UTILS_H
#define APP_UART_UTILS_H

#include "stm32g4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void SendUserPrompt(UART_HandleTypeDef* huart);


void read_uart_line(UART_HandleTypeDef *huart, uint8_t *buffer, uint16_t max_len);

typedef enum {
    CMD_ON,
    CMD_OFF,
    CMD_STATUS,
    CMD_INVALID
} Command;

Command getCommand(const char * input);


#ifdef __cplusplus
}
#endif

#endif // APP_UART_UTILS_H
