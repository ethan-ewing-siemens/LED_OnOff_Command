// uart_utils.c
#include "app_uart_utils.h"


// Transmit a message asking the User for a command
void SendUserPrompt(UART_HandleTypeDef* huart)
{
    uint8_t msg[] = "Enter 'on', 'off', or 'status':\r\n";
    HAL_UART_Transmit(huart, msg, sizeof(msg)-1, HAL_MAX_DELAY);
}


// Read a line from the UART until a newline or carriage return is encountered
void read_uart_line(UART_HandleTypeDef *huart, uint8_t *buffer, uint16_t max_len) 
{
    uint8_t idx = 0;
    uint8_t ch;
    while (idx < max_len - 1) {
        HAL_UART_Receive(huart, &ch, 1, HAL_MAX_DELAY);
        if (ch == '\r' || ch == '\n') {
            break;
        }
        buffer[idx++] = ch;
    }
    buffer[idx] = '\0';
}


// Parse the input string and return the corresponding command
Command getCommand(const char * input) 
{
    if (strncmp(input, "on", strlen("on")) == 0) return CMD_ON;
    if (strncmp(input, "off", strlen("off")) == 0) return CMD_OFF;
    if (strncmp(input, "status", strlen("status")) == 0) return CMD_STATUS;
    return CMD_INVALID;
}

