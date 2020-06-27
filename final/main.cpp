  
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
DigitalIn pin3(D3);
DigitalIn pin4(D4);
Serial xbee(D12, D11);
Serial uart(D1,D0); //tx,rx

BBCar car(pin8, pin9, servo_ticker);

Thread t;
char* status_log;
void send_log(){
    while(1){
        xbee.printf("%s\r\n", status_log);
        wait_ms(1000);
    }
};
int main(){
    parallax_encoder encoder0(pin3, encoder_ticker_left);
    parallax_encoder encoder1(pin4, encoder_ticker_right);
    encoder0.reset();
    encoder1.reset();    
    t.start(send_log);

   
    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    while(encoder1.get_cm()<110) wait_ms(50);
    car.stop();
    wait(0.5);

/*
    car.turn(100,0.3);
    status_log = "turn Left";
    //xbee.printf("%s\r\n", status_log);
    encoder1.reset();
    while(encoder1.get_cm()<1.9*10.2*2*PI/4) wait_ms(50);
    car.stop();


    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    encoder1.reset();
    while(encoder1.get_cm()<100) wait_ms(50);
    car.stop();
    wait(0.5);

    car.turn(100,0.3);
    status_log = "turn Left";
    //xbee.printf("%s\r\n", status_log);
    encoder1.reset();
    while(encoder1.get_cm()<1.9*10.2*2*PI/4) wait_ms(50);
    car.stop();

    //scan 
    status_log = "Image Classification";
    //xbee.printf("%s\r\n", status_log);
    char s[21];
    sprintf(s,"image_classification");
    uart.puts(s);

    while(1){
        if(uart.readable()){
            char recv = uart.getc();
            xbee.printf("The image is: %c\r\n", recv);
            break;
        }
    }

    wait(1);


    car.turn(100,0.3);
    status_log = "turn Left";
    //xbee.printf("%s\r\n", status_log);
    encoder1.reset();
    while(encoder1.get_cm()<1.9*10.2*2*PI/4) wait_ms(50);
    car.stop();
    wait(0.5);

    car.turn(-100,-0.3);
    status_log = "back turning right";
    //xbee.printf("%s\r\n", status_log);
    encoder0.reset();
    while(encoder0.get_cm()<1.5*10.2*2*PI/4) wait_ms(50);
    car.stop();
    wait(0.5);

    car.goStraight(-100);
    encoder1.reset();
    status_log = "reverse parking";
    //xbee.printf("%s\r\n", status_log);
    while(encoder1.get_cm()<25) wait_ms(50);
    car.stop();

    wait(2);

    car.goStraight(100);
    encoder1.reset();
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    while(encoder1.get_cm()<25) wait_ms(50);
    car.stop();
    wait(0.5);

    car.turn(100,-0.3);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    encoder0.reset();
    while(encoder0.get_cm()<1.8*10.2*2*PI/4) wait_ms(50);
    car.stop();

    car.goStraight(100);
    encoder1.reset();
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    while(encoder1.get_cm()<75) wait_ms(50);
    car.stop();
    wait(0.5);

    //mission 1 complete

    car.turn(100,-0.3);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    encoder0.reset();
    while(encoder0.get_cm()<1.5*10.2*2*PI/4) wait_ms(50);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    encoder1.reset();
    while(encoder1.get_cm()<125) wait_ms(50);
    car.stop();
    wait(0.5);

    car.turn(100,-0.3);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    encoder0.reset();
    while(encoder0.get_cm()<1.5*10.2*2*PI/4) wait_ms(50);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    encoder1.reset();
    while(encoder1.get_cm()<50) wait_ms(50);
    car.stop();
    wait(0.5);

    car.turn(100,-0.3);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    encoder0.reset();
    while(encoder0.get_cm()<1.5*10.2*2*PI/4) wait_ms(50);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    encoder1.reset();
    while(encoder1.get_cm()<25) wait_ms(50);
    car.stop();
    wait(0.5);

    car.turn(100,-0.3);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    encoder0.reset();
    while(encoder0.get_cm()<1.9*10.2*2*PI/4) wait_ms(50);
    car.stop();

    //scan
    
    status_log = "Identify Item";
    wait(3);
    //xbee.printf("%s\r\n", status_log);

    car.turn(100,-0.3);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    encoder0.reset();
    while(encoder0.get_cm()<1.5*10.2*2*PI/4) wait_ms(50);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    encoder1.reset();
    while(encoder1.get_cm()<25) wait_ms(50);
    car.stop();
    wait(0.5);

    car.turn(100,-0.3);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    encoder0.reset();
    while(encoder0.get_cm()<1.5*10.2*2*PI/4) wait_ms(50);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    encoder1.reset();
    while(encoder1.get_cm()<50) wait_ms(50);
    car.stop();
    wait(0.5);

    car.turn(100,-0.3);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    encoder0.reset();
    while(encoder0.get_cm()<1.5*10.2*2*PI/4) wait_ms(50);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    encoder1.reset();
    while(encoder1.get_cm()<125) wait_ms(50);
    car.stop();
    wait(0.5);

    status_log = "End";
    xbee.printf("%s\r\n", status_log);
*/   
}