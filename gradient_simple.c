#include <kilolib.h>

// Since 1 byte (8 bits) of the message is used to communicate gradients, the
// maximum possible gradient is 2^8 - 1 = 255.
#define GRADIENT_MAX 255
// This is an arbitrary number, but it's important that exactly one robot in the
// group is calibrated to have this ID.
#define SEED_ID 42

int own_gradient = GRADIENT_MAX;
int received_gradient = 0;
int new_message = 0;
message_t message;

void setup()
{
    //If the robot is the seed, its gradient should be 0: overwrite the 
    // previously set value of GRADIENT_MAX.
    if (kilo_uid == SEED_ID)
    {
        own_gradient = 0;
    }
    
    // Set the transmission message.
    message.type = NORMAL;
    message.data[0] = own_gradient;
    message.crc = message_crc(&message);
}

void loop() {
    // Only pay attention to messages if this robot is not the seed.
    if (kilo_uid != SEED_ID)
    {
        if (new_message == 1)
        {
            // If a neighbor's gradient is 2 or more less than this robot's 
            // gradient, reduce the latter to the neighbor's gradient + 1.
            if (own_gradient > received_gradient + 1)
            {
                own_gradient = received_gradient + 1;
                
                // Update the transmission message whenever the gradient changes.
                message.type = NORMAL;
                message.data[0] = own_gradient;
                message.crc = message_crc(&message);
            }
            
            new_message = 0;
        }
    }
    
    // Set the LED color based on the gradient.
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
    // Only process this message if the previous one has been processed.
    if (new_message == 0)
    {
        new_message = 1;
        received_gradient = m->data[0];
    }
}

int main()
{
    kilo_init();
    kilo_message_rx = message_rx;
    kilo_message_tx = message_tx;
    kilo_start(setup, loop);
    
    return 0;
}
