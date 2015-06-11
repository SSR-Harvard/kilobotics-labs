#include <kilolib.h>

// declare variables
uint8_t new_message = 0;

// no setup code required
void setup() { }

void loop() {
    // Blink yellow when on message received
    if (new_message) {
        new_message = 0;
        set_color(RGB(1,1,0));
        delay(100);
        set_color(RGB(0,0,0));
    }
}

// turn flag on message reception
void message_rx(message_t *m, distance_measurement_t *d) {
    new_message = 1;
}

int main() {
    // initialize hardware
    kilo_init();
    // register message reception callback
    kilo_message_rx = message_rx;
    // register your program
    kilo_start(setup, loop);

    return 0;
}
