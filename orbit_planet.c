#include <kilolib.h>

// Constant for orbit control.
#define DESIRED_DISTANCE 60

// Constants for motion handling function.
#define STOP 0
#define FORWARD 1
#define LEFT 2
#define RIGHT 3

int current_motion = STOP;
int current_distance = 0;
int new_message = 0;
int distance;

// Function to handle motion.
void set_motion(int new_motion)
{
    // We only need to take an action if the motion is being changed.
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
    // Update motion whenever a message is received.
    if (new_message == 1)
    {
        new_message = 0;
        
        if (current_distance < DESIRED_DISTANCE)
        {
            set_motion(LEFT);
        }
        else
        {
            set_motion(RIGHT);
        }
    }
}

void message_rx(message_t *m, distance_measurement_t *d)
{
    new_message = 1;
    current_distance = estimate_distance(d);
}

int main()
{
    kilo_init();
    kilo_message_rx = message_rx;
    kilo_start(setup, loop);
    
    return 0;
}
