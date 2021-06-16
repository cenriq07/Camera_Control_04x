#include "PWM.h"
#include "MPU9250.h"
#include "Encoder.h"
#include "CameraControl.h"

#include "sci.h"

#include <math.h>

#define MOTOR_PWM   pwm0

char command[80];

static int INIT = 0;

static hetSIGNAL_t MOTOR;
static int16_t DATOS_MAGNETOMETRO[3] = {0,0,0};

void CameraControl_Init() {
    if (INIT == 0) {
        MPUInit();
        EncoderInit();
        MOTOR.period = 20000;
        INIT = 1;
    }
}

void CameraControl_Execute() {
    // Obtener angulo magnetico
    mpuGetMagnetometer(spiREG1, &SPI1_data_configCh0, DATOS_MAGNETOMETRO);
    float mX = (DATOS_MAGNETOMETRO[X] - vX) / B;
    float mY = (DATOS_MAGNETOMETRO[Y] - vY) / B;
    float angMag = (atan2((-1) * mY, mX)) * 180 / 3.14159;
    if (angMag < 0)
        angMag += 360;

    // Obtener lectura del encoder
    float angEnc = EncoderRead();

    // Convertir angulos a radianes
    angEnc *= M_PI / 180.0;
    angMag *= M_PI / 180.0;

    // Calcular error
    const float tolerancia = 0.349066 / 2;
    float error = atan2(sin(angMag - angEnc), cos(angMag - angEnc));

    // Mover motor mientras exista un error
    CameraControl_MoverMotor(750 + (error * 150 / M_PI));

    // Mandar datos por serial
    sciSend(scilinREG, sprintf(command,"Encoder=%.2f \t Magnetometro=%.2f \t Error=%.2f\r\n", angEnc, angMag, error), (uint8*) command);
}

void CameraControl_MoverMotor(const int duty) {
    MOTOR.duty = duty;
    pwmSetSignal10e3(hetRAM1, pwm0, MOTOR);
}
