#include <kilolib.h>

uint8_t new_message = 0;
uint8_t distance = 0;
uint8_t odd = 0;

void setup()
{
}

void loop()
{
	if (new_message == 1)
	{
		new_message = 0;

		// Near ...
		if (distance <= 50)
		{
			// ... and odd: set LED blue.
			if (odd == 1)
			{
				set_color(RGB(0, 0, 1));
			}
			// ... and even: set LED red.
			else
			{
				set_color(RGB(1, 0, 0));
			}
		}
		// Far ...
		else
		{
			// ... and odd: set LED cyan.
			if (odd == 1)
			{
				set_color(RGB(0, 1, 1));
			}
			// ... and even: set LED magenta.
			else
			{
				set_color(RGB(1, 0, 1)); // blink magenta
			}
		}

		// Wherever you are: set LED off after 100 ms to achieve blink effect.
		delay(100);
		set_color(RGB(0, 0, 0));
	}
}

void message_rx(message_t *message,
		distance_measurement_t *distance_measurement)
{
	// Set message reception flag.
	new_message = 1;

	odd = message->data[0];
	distance = estimate_distance(distance_measurement);
}

int main()
{
	kilo_init();

	kilo_message_rx = message_rx;

	kilo_start(setup, loop);

	return 0;
}
