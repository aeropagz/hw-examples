#include <pigpio.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    bool toggle = true;
    gpioInitialise();
    gpioSetMode(17, PI_OUTPUT);
    while(1){
        gpioWrite(17, toggle);
        toggle = !toggle;
    }
}
