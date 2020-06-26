  
#include "mbed.h"
#include "arm_math.h"
#include "FXOS8700CQ.h"
#include "bbcar.h"
#include <math.h>
#include <stdlib.h>

Ticker servo_ticker;
Ticker encoder_ticker_left;
Ticker encoder_ticker_right;

PwmOut pin8(D8), pin9(D9);
DigitalIn pin2(D2);
DigitalIn pin3(D3);

BBCar car(pin8, pin9, servo_ticker);

int main(){
    parallax_encoder encoder0(pin2, encoder_ticker_left);
    parallax_encoder encoder1(pin3, encoder_ticker_right);
    encoder0.reset();
    encoder1.reset();    

    car.goStraight(100);
    while(encoder1.get_cm()<80) wait_ms(50);
    car.stop();
    return 0;
}