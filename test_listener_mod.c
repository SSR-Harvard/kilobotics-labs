#include <kilolib.h>

int new_message = 0;
int distance = 0;
int odd = 0;

void setup()
{
}

void loop()
{
    if (new_message == 1)
    {
        new_message = 0;
        
        // Near ...
        if (distance <= 50)
        {
            // ... and even: set the LED red.
            if (odd == 0)
            {
                set_color(RGB(1, 0, 0));
            }
            // ... and odd: set the LED green.
            else
            {
                set_color(RGB(0, 1, 0));
            }
        }
        // Far ...
        else
        {
            // ... and even: set the LED blue.
            if (odd == 0)
            {
                set_color(RGB(0, 0, 1));
            }
            // ... and odd: set the LED yellow.
            else
            {
                set_color(RGB(1, 1, 0));
            }
        }
        
        // Wherever you are: set LED off after 100 ms to achieve blink effect.
        delay(100);
        set_color(RGB(0, 0, 0));
    }
}

void message_rx(message_t *message, distance_measurement_t *distance_measurement)
{
    // Set flag on message reception.
    new_message = 1;
    
    distance = estimate_distance(distance_measurement);
    odd = message->data[0];
}

int main()
{
    kilo_init();
    kilo_message_rx = message_rx;
    kilo_start(setup, loop);
    
    return 0;
}
