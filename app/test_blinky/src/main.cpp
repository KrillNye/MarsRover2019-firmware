#include "mbed.h"
#include "CANMsg.h"
#include "rover_config.h"
#include "PinNames.h"
#include "tutorial_servo.h"

long DEFAULT_BAUD = 500000;
CAN can(CAN_RX, CAN_TX, DEFAULT_BAUD);
Serial pc(USBTX, USBRX, 9600);

CANMsg rxMsg;

TutorialServo servo(PA_1, 180);

Timer timer;

float pos = 1;

int main(){

    timer.start();
    servo.setRangeInDegrees(180);

    while(1) {

        if(timer.read_ms() > 2000){
            pc.printf("%f \n", pos);
            timer.reset();
        }

        if(can.read(rxMsg)){
            rxMsg >> pos;
            servo.setPositionInDegrees(pos);
        }
    }
}
