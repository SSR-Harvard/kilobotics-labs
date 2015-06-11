#include <kilolib.h>

uint8_t new_message = 0;

void setup()
{
}

void loop()
{
    // Blink LED yellow whenever a message is received.
    if (new_message == 1)
    {
        // Reset flag so LED is only blinked once per message.
        new_message = 0;
        
        set_color(RGB(1, 1, 0));
        delay(100);
        set_color(RGB(0, 0, 0));
    }
}

// Set flag on message reception.
void message_rx(message_t *message, distance_measurement_t *distance)
{
    new_message = 1;
}

int main()
{
    kilo_init();
    // Register message_rx callback function.
    kilo_message_rx = message_rx;
    kilo_start(setup, loop);
    
    return 0;
}
