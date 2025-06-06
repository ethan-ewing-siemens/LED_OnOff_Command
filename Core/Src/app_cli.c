#include "app_cli.h"
#include "string.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx_nucleo.h"
#include "app_uart_utils.h"


extern UART_HandleTypeDef hlpuart1;


void handleCommand(Command cmd) 
{
    switch (cmd) {
        case CMD_ON: {
            uint8_t resp[] = "You entered ON\r\n";
            HAL_UART_Transmit(&hlpuart1, resp, sizeof(resp)-1, HAL_MAX_DELAY);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            break;
        }
        case CMD_OFF: {
            uint8_t resp[] = "You entered OFF\r\n";
            HAL_UART_Transmit(&hlpuart1, resp, sizeof(resp)-1, HAL_MAX_DELAY);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            break;
        }
        case CMD_STATUS: {
            uint8_t resp[] = "LED is ";
            HAL_UART_Transmit(&hlpuart1, resp, sizeof(resp)-1, HAL_MAX_DELAY);
            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET) {
                uint8_t resp[] = "ON\r\n";
                HAL_UART_Transmit(&hlpuart1, resp, sizeof(resp)-1, HAL_MAX_DELAY);
            } else {
                uint8_t resp[] = "OFF\r\n";
                HAL_UART_Transmit(&hlpuart1, resp, sizeof(resp)-1, HAL_MAX_DELAY);
            }
            break;
        }
        default: {
            uint8_t resp[] = "Invalid input\r\n";
            HAL_UART_Transmit(&hlpuart1, resp, sizeof(resp)-1, HAL_MAX_DELAY);
            break;
        }
    }
}




void app_cli_process(void) 
{
    uint8_t rxBuffer[8] = {0};

    SendUserPrompt(&hlpuart1);                                  // Function to send a prompt to the user
    read_uart_line(&hlpuart1, rxBuffer, sizeof(rxBuffer));      // UART input reader function check
    Command cmd = getCommand((char*)rxBuffer);                  // Command parser function
    handleCommand(cmd);                                         // Command handler function   

    HAL_Delay(500);
}
