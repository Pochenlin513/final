  
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
DigitalInOut pin10(D10);
Serial xbee(D12, D11);
Serial uart(D1,D0); //tx,rx
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
DigitalOut blueLED(LED3);



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
    parallax_ping  ping1(pin10);

    encoder0.reset();
    encoder1.reset();    
    t.start(send_log);
    redLED = 0;
    greenLED = 1;
    blueLED = 1;
  
    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(7579); // 106
    car.stop();
    wait(0.5);

    car.turn(100,0.1);
    status_log = "turn Left";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1500);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(2105); // 30
    car.stop();
    wait(0.5);

    car.turn(100,0.1);
    status_log = "turn Left";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1500);
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

    car.turn(100,-0.1);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1500);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(2597); // 37
    car.stop();
    wait(0.5);

    car.turn(100,-0.1);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1500);
    car.stop();

    car.goStraight(-100);
    status_log = "reverse parking";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(2245); //32
    car.stop();

    wait(2);

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(2386); //34
    car.stop();
    wait(0.5);

    car.turn(100,-0.1);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1500);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(3509); // 50
    car.stop();
    wait(0.5);

    //mission 1 complete
    greenLED = 0;

    car.turn(100,-0.1);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1500);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(7229); //103
    car.stop();
    wait(0.5);

    car.turn(100,-0.1);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1500);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(2596); // 37
    car.stop();
    wait(0.5);

    car.turn(100,-0.3);
    status_log = "Right U turn";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(5000);
    car.stop();


    //scan
    status_log = "Identify Item";
     while(1){
         if((float)ping1>10) redLED = 1;
         else{
             redLED = 0;
             break;
         }
         wait(.01);
     }
    //xbee.printf("%s\r\n", status_log);

    car.turn(100,-0.3);
    status_log = "Right U turn";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(5000);
    car.stop();


    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(3158); // 45
    car.stop();
    wait(0.5);


    //mission2 complete
    blueLED = 0;

    car.turn(100,-0.1);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1500);
    car.stop();

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(7719); //110
    car.stop();
    wait(0.5);

    status_log = "End";
    xbee.printf("%s\r\n", status_log);
 
}