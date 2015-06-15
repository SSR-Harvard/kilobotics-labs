#include <kilolib.h>

void setup()
{
}

void loop()
{
    // Set the LED green.
    set_color(RGB(0, 1, 0));
    // Spinup the motors to overcome friction.
    spinup_motors();
    // Move straight for 2 seconds (2000 ms).
    set_motors(kilo_straight_left, kilo_straight_right);
    delay(2000);
    
    // Set the LED red.
    set_color(RGB(1, 0, 0));
    // Spinup the motors to overcome friction.
    spinup_motors();
    // Turn left for 2 seconds (2000 ms).
    set_motors(kilo_turn_left, 0);
    delay(2000);
    
    // Set the LED blue.
    set_color(RGB(0, 0, 1));
    // Spinup the motors to overcome friction.
    spinup_motors();
    // Turn right for 2 seconds (2000 ms).
    set_motors(0, kilo_turn_right);
    delay(2000);
    
    // Set the LED off.
    set_color(RGB(0, 0, 0));
    // Stop for half a second (500 ms).
    set_motors(0, 0);
    delay(500);
}

int main()
{
    kilo_init();
    kilo_start(setup, loop);
    
    return 0;
}
