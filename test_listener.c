#include <kilolib.h>

// Flag to keep track of new messages.
int new_message = 0;

void setup()
{
}

void loop()
{
    // Blink the LED yellow whenever a message is received.
    if (new_message == 1)
    {
        // Reset the flag so the LED is only blinked once per message.
        new_message = 0;
        
        set_color(RGB(1, 1, 0));
        delay(100);
        set_color(RGB(0, 0, 0));
    }
}

void message_rx(message_t *message, distance_measurement_t *distance)
{
    // Set the flag on message reception.
    new_message = 1;
}

int main()
{
    kilo_init();
    // Register the message_rx callback function.
    kilo_message_rx = message_rx;
    kilo_start(setup, loop);
    
    return 0;
}
