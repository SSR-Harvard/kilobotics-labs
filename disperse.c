#include <kilolib.h>

#define STOP 0
#define FORWARD 1
#define LEFT 2
#define RIGHT 3

int current_motion = STOP;
int new_message = 0;
message_t message;
uint32_t last_motion_update = 0;

// Function to handle motion.
void set_motion(int new_motion)
{
    // Only take an an action if the motion is being changed.
    if (current_motion != new_motion)
    {
        current_motion = new_motion;
        
        if (current_motion == STOP)
        {
            set_motors(0, 0);
        }
        else if (current_motion == FORWARD)
        {
            spinup_motors();
            set_motors(kilo_straight_left, kilo_straight_right);
        }
        else if (current_motion == LEFT)
        {
            spinup_motors();
            set_motors(kilo_turn_left, 0);
        }
        else if (current_motion == RIGHT)
        {
            spinup_motors();
            set_motors(0, kilo_turn_right);
        }
    }
}

void setup()
{
    // Initialize an empty message.
    message.type = NORMAL;
    message.crc = message_crc(&message);
}

void loop()
{
    if (kilo_ticks > last_motion_update + 32)
    {
        last_motion_update = kilo_ticks;
        
        // If a message was received within the last second, set a random motion.
        if (new_message == 1)
        {
            new_message = 0;
            
            // Generate an 8-bit random number (between 0 and 2^8 - 1 = 255).
            int random_number = rand_hard();
            
            // Compute the remainder of random_number when divided by 4.
            // This gives a new random number in the set {0, 1, 2, 3}.
            int random_direction = (random_number % 4);
            
            // There is a 50% chance of random_direction being 0 OR 1, in which
            // case set the LED green and move forward.
            if ((random_direction == 0) || (random_direction == 1))
            {
                set_color(RGB(0, 1, 0));
                set_motion(FORWARD);
            }
            // There is a 25% chance of random_direction being 2, in which case
            // set the LED red and move left.
            else if (random_direction == 2)
            {
                set_color(RGB(1, 0, 0));
                set_motion(LEFT);
            }
            // There is a 25% chance of random_direction being 3, in which case
            // set the LED blue and move right.
            else if (random_direction == 3)
            {
                set_color(RGB(0, 0, 1));
                set_motion(RIGHT);
            }
        }
        // If no messages were received within the last second, set the LED white
        // and stop moving.
        else
        {
            set_color(RGB(1, 1, 1));
            set_motion(STOP);
        }
    }
}

void message_rx(message_t *m, distance_measurement_t *d)
{
    new_message = 1;
}

message_t *message_tx()
{
    return &message;
}

int main()
{
    kilo_init();
    kilo_message_rx = message_rx;
    kilo_message_tx = message_tx;
    kilo_start(setup, loop);
    
    return 0;
}
