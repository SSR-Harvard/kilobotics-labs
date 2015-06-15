#include <kilolib.h>

// Declare constants.
#define LEFT_RED 0
#define RIGHT_BLUE 1
#define FORWARD_GREEN 2

// Declare variables.
int state;
// We need an unsigned 32-bit integer to store clock ticks;
// a regular int would overflow.
uint32_t last_state_update;

void setup()
{
    state = FORWARD_GREEN;
    last_state_update = kilo_ticks;
}

void loop()
{
    // Update the state every 64 clock ticks (roughly 2 seconds).
    if (kilo_ticks > (last_state_update + 64))
    {
        last_state_update = kilo_ticks;
        
        if (state == FORWARD_GREEN)
        {
            set_color(RGB(0, 1, 0));
            spinup_motors();
            set_motors(kilo_straight_left, kilo_straight_right);
            
            // Set the next state.
            state = LEFT_RED;
        }
        else if (state == LEFT_RED)
        {
            set_color(RGB(1, 0, 0));
            spinup_motors();
            set_motors(kilo_turn_left, 0);
            
            // Set the next state.
            state = RIGHT_BLUE;
        }
        else if (state == RIGHT_BLUE)
        {
            set_color(RGB(0, 0, 1));
            spinup_motors();
            set_motors(0, kilo_turn_right);
            
            // Set the next state.
            state = FORWARD_GREEN;
        }
    }
}

int main()
{
    kilo_init();
    kilo_start(setup, loop);
    
    return 0;
}
