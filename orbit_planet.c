#include <kilolib.h>

// Constants for orbit control.
#define TOO_CLOSE_DISTANCE 40
#define DESIRED_DISTANCE 60

// Constants for motion handling function.
#define STOP 0
#define FORWARD 1
#define LEFT 2
#define RIGHT 3

int current_motion = STOP;
int distance;
int new_message = 0;

// Function to handle motion.
void set_motion(int new_motion)
{
    // Only take an action if the motion is being changed.
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
}

void loop()
{
    // Update the motion whenever a message is received.
    if (new_message == 1)
    {
        new_message = 0;
        
        // If too close, move forward to get back into orbit.
        if (distance < TOO_CLOSE_DISTANCE)
        {
            set_motion(FORWARD);
        }
        // If not too close, turn left or right depending on distance,
        // to maintain orbit.
        else
        {
            if (distance < DESIRED_DISTANCE)
            {
                set_motion(LEFT);
            }
            else
            {
                set_motion(RIGHT);
            }
        }
    }
}

void message_rx(message_t *m, distance_measurement_t *d)
{
    new_message = 1;
    distance = estimate_distance(d);
}

int main()
{
    kilo_init();
    kilo_message_rx = message_rx;
    kilo_start(setup, loop);
    
    return 0;
}
