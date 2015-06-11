#include <kilolib.h>

#define LEFT 0
#define RIGHT 1

#define THRESH_LO = 300;
#define THRESH_HI = 600;

int current_direction;
int current_light = 0;

// The ambient light sensor gives noisy readings. To mitigate this,
// we take the average of 300 samples in quick succession.
void sample_light()
{
    int number_of_samples = 0;
    int sum = 0;

    while (number_of_samples < 300) {
        int sample = get_ambientlight();
        
        // -1 indicate a failed sample, which should be discarded.
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

void loop() {
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

int main() {
    kilo_init();
    kilo_start(setup, loop);

    return 0;
}
