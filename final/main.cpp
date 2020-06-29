  
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
Timer t;


BBCar car(pin8, pin9, servo_ticker);

Thread t1;
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
    t1.start(send_log);
    redLED = 0;
    greenLED = 1;
    blueLED = 1;
 
    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(7790); // 106
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
    wait_ms(2456); // 30
    car.stop();
    wait(0.5);

    car.turn(100,0.1);
    status_log = "turn Left";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1300);
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
    wait_ms(3719); // 53
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
    wait_ms(6667); //95
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
    wait_ms(2456); // 30
    car.stop();
    wait(0.5);

    car.turn(100,-0.1);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1500);
    car.stop();

    wait(0.5);

    car.goStraight(100);
    status_log = "go Straight";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(701); // 15
    car.stop();
    wait(0.5);

    car.turn(100,-0.1);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1500);
    car.stop();

    //scan
    wait(2);
    car.turn(80,-0.1);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1000); //45
    car.stop();
    wait(1);
    greenLED = 0;
    car.turn(-80,-0.1);
    status_log = "Scanning";
    //wait_ms(1500); // rotate 90
    t.start();

    float k = 0,k_prev = 0, boundr = 0, boundl = 0, min = 100;
    k = (float)ping1;
    k_prev = k;
    while(t.read()<1.5){
        k = (float)ping1; 
        if(k_prev-k > 20) boundr = k;
        else if(k-k_prev > 20){
            boundl = k_prev;

        } 

        else{
            if(k < min){
                min = k;
            }
        }
        k_prev = k;

        wait(.01);
    }
    while(t.read()<1.5){
        wait(0.1);
    }
    //xbee.printf(" boundr = %.4f\r\n boundl = %.4f\r\n min = %.4f\r\n", boundr, boundl, min);
    if(fabs(boundl-boundr) < 5 && (fabs(boundr-min) < 0.5 || fabs(boundr-min) < 0.5)){
        xbee.printf("The object is V shape.\r\n");
    }
    else if(fabs(boundl-min) < 5 && fabs(boundr-min) < 5){
        xbee.printf("The object is Square.\r\n");
    }
    else if(boundr == 0 && boundl == 0){
        xbee.printf("The object is Isosceles Triangle.\r\n");
    }
    else{
        xbee.printf("The object is Right Triangle.\r\n");
    }
    car.stop();
    wait(0.5);

 
    car.turn(80,-0.1);
    status_log = "turn Right";
    //xbee.printf("%s\r\n", status_log);
    wait_ms(1000); //45
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
    wait_ms(701); // 10
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
    wait_ms(3859); // 55
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