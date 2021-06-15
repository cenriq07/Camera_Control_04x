#include "Encoder.h"

#include "spi.h"
#include "FreeRTOS.h"
#include "os_task.h"

static spiDAT1_t SPI3_data_configCh0;
static uint16 DatoSPI03[4] = {0x0, 0x0, 0x0, 0x0};
static uint16 CmmdSPI03[4] = {0x0, 0x0, 0x0, 0x0};

void EncoderInit() {
    SPI3_data_configCh0.CS_HOLD=FALSE;
    SPI3_data_configCh0.WDEL=TRUE;
    SPI3_data_configCh0.DFSEL=SPI_FMT_0;
    SPI3_data_configCh0.CSNR=SPI_CS_0;
}

float EncoderRead() {
    CmmdSPI03[0] = 0xFF;
    spiSendAndGetData(spiREG3, &SPI3_data_configCh0,(uint32) 1, CmmdSPI03, DatoSPI03);
    vTaskDelay(1 /portTICK_RATE_MS);

    int16_t high = DatoSPI03[0] >> 6;
    int16_t lowd = DatoSPI03[0] && 0x003F;

    return high * 360 / 1024.0;
}
