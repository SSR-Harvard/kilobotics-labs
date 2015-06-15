#include <kilolib.h>

void setup()
{
    // Put any setup code here. This is run once before entering the loop.
}

void loop()
{
    // Put the main code here. This is run repeatedly.
    
    // Set the LED red.
    set_color(RGB(1, 0, 0));
    // Wait half a second (500 ms).
    delay(500);
    // Set the LED blue.
    set_color(RGB(0, 0, 1));
    // Wait half a second (500 ms).
    delay(500);
}

int main()
{
    // Initialize the hardware.
    kilo_init();
    // Register the program.
    kilo_start(setup, loop);
    
    return 0;
}
