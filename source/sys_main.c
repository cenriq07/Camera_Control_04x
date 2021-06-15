/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
#include "FreeRTOS.h"
#include "os_task.h"
#include "spi.h"
#include "stdio.h"
#include "stdlib.h"
#include "sci.h"
#include "gio.h"
#include "het.h"
#include "adc.h"
#include "sys_core.h"
#include "drivers/Encoder.h"
#include "drivers/MPU9250.h"
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void vEncoder(void *pvParameters);
void vMPU(void *pvParameters);

char command[50];
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    // Inicializar sistemas de los perifericos del MCU
    gioInit();
    hetInit();
    spiInit();
    sciInit();

    xTaskCreate(vMPU, "MPU9250", 512, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1);


/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void vEncoder(void *pvParameters)
{
    while(1)
    {
        sciSend(scilinREG, sprintf(command,"%.2f\r\n", EncoderRead()), (uint8*)command);
        vTaskDelay(500/portTICK_RATE_MS);
    }
}
void vMPU(void *pvParameters)
{
    MPUInit();

    int32_t Gyro[3] = {0,0,0};
    int32_t Accel[3] = {0,0,0};
    int16_t Magnet[3] = {0,0,0};

    while(1)
    {
        mpuGetMagnetometer(spiREG1, &SPI1_data_configCh0, Magnet);
        sciSend(scilinREG, sprintf(command,"%d ",Magnet[0]), (uint8*)command);
        sciSend(scilinREG, sprintf(command,"%d ",Magnet[1]), (uint8*)command);
        sciSend(scilinREG, sprintf(command,"%d\n\r",Magnet[2]), (uint8*)command);
        vTaskDelay(500/portTICK_RATE_MS);
    }
}
/* USER CODE END */
