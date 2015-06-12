#include <kilolib.h>

// Maximum of an 8-bit number (since we're using 1 byte of the message to send
// the gradient value).
#define GRADIENT_MAX 255

int own_gradient = GRADIENT_MAX;
int received_gradient = 0;
int new_message = 0;
message_t message;

void setup()
{
    // If the ID is 42, the robot is the seed its gradient should be 0 rather
    // than GRADIENT_MAX.
    if (kilo_uid == 42)
    {
        own_gradient = 0;
    }
    
    // Compute the message.
    message.type = NORMAL;
    message.data[0] = own_gradient;
    message.crc = message_crc(&message);
}

void loop() {
    if (new_message == 1)
    {
        new_message = 0;
        
        if (own_gradient > received_gradient + 1)
        {
            own_gradient = received_gradient + 1;
            
            // Update the message whenever the gradient changes.
            message.type = NORMAL;
            message.data[0] = own_gradient;
            message.crc = message_crc(&message);
        }
    }
    
    // Set LED color based on gradient.
    if (own_gradient == 0)
    {
        set_color(RGB(1, 1, 1)); // White
    }
    else if (own_gradient == 1)
    {
        set_color(RGB(1, 0, 0)); // Red
    }
    else if (own_gradient == 2)
    {
        set_color(RGB(0, 1, 0)); // Green
    }
    else if (own_gradient == 3)
    {
        set_color(RGB(0, 0, 1)); // Blue
    }
    else if (own_gradient == 4)
    {
        set_color(RGB(1, 0, 1)); // Magenta
    }
    else if (own_gradient >= 5)
    {
        set_color(RGB(1, 1, 0)); // Yellow
    }
}

message_t *message_tx()
{
    return &message;
}

void message_rx(message_t *m, distance_measurement_t *d)
{
    new_message = 1;
    received_gradient = m->data[0];
}

int main()
{
    kilo_init();
    kilo_message_rx = message_rx;
    kilo_message_tx = message_tx;
    kilo_start(setup, loop);
    
    return 0;
}
