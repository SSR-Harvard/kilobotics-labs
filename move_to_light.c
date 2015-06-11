#include <kilolib.h>

// Constants for light following.
#define THRESH_LO = 300;
#define THRESH_HI = 600;

// Constants for motion handling function.
#define STOP 0
#define FORWARD 1
#define LEFT 2
#define RIGHT 3

int current_motion;
int current_light = 0;

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

// Function for light sampling.
void sample_light()
{
    // The ambient light sensor gives noisy readings. To mitigate this,
    // we take the average of 300 samples in quick succession.
    
    int number_of_samples = 0;
    int sum = 0;

    while (number_of_samples < 300)
    {
        int sample = get_ambientlight();
        
        // -1 indicates a failed sample, which should be discarded.
        if (sample != -1)
        {
            average = average + sample;
            number_of_samples = number_of_samples + 1;
        }
    }

    current_light = sum / number_of_samples;
}

void setup()
{
}

void loop()
{
    sample_light();
    
    if (current_light < THRESH_LO)
    {
        set_motion(RIGHT);
    }
    else if (current_light > THRESH_HI)
    {
        set_motion(LEFT);
    }
}

int main()
{
    kilo_init();
    kilo_start(setup, loop);

    return 0;
}
