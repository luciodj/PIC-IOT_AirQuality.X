/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include <stdint.h>
#include <math.h>
#include "airquality.h"
#include "adc1.h"


static double Rs_CleanAir;
static double Ro_Air = 5000;
static uint8_t isInitialized = 2;

void AirQuality_Initialize(void){

    double sensorValue;
    double sensorAverage;
    double sensorVoltage;
    double ratio;

    sensorValue = 0.0;

    // Use 16 for faster averaging
    int x;
    for(x = 0; x < 16; x++)
    {
        sensorValue = sensorValue + ADC1_GetConversion(AirQuality);
    }
    sensorAverage = sensorValue/16;

    //Scale 16-bit ADC reading to the voltage range
    sensorVoltage = (ADC_VREF * sensorAverage)/ADC_RANGE_VALUE;

    // Compute the value of Rs in clean air
    Rs_CleanAir = (ADC_VREF - sensorVoltage)/sensorVoltage;

    isInitialized = 1;
}

double AirQuality_GetReadings(void){

    double sensorValue;
    double sensorAverage;
    double sensorVoltage;

    double Rs_Air;
    double ratio;

    if (isInitialized != 1)
    {
        AirQuality_Initialize();
    }

    // Store the conversion result to sensorValue
    sensorValue = ADC1_GetConversion(AirQuality);

    // Convert the average to its equivalent voltage
    sensorVoltage = (ADC_VREF * sensorValue)/ADC_RANGE_VALUE;

    // Compute the value of RS in AirQuality
    Rs_Air = (ADC_VREF - sensorVoltage)/sensorVoltage;

    // Compute the ratio(Rs/Ro) in AirQuality
    ratio = Rs_Air/Ro_Air;

    return ratio;
}

double AirQuality_GetPPM(void){
    double PPM;
    double logPPM;
    double PPMratio;

    PPMratio = AirQuality_GetReadings();

    // Calculate the PPM. Values are computed from datasheet approximation
    logPPM = (log10(PPMratio) * -0.8)+ 0.9;
    PPM = pow(10,logPPM);

    return PPM;
}

