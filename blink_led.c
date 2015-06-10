#include <kilolib.h>

void setup()
{
	// Put your setup code here. This is run once before entering the loop.
}

void loop()
{
	// Put your main code here. This is run repeatedly.

	// Turn LED blue.
	set_color(RGB(0, 0, 1));
	// Wait half a second (500 ms).
	delay(500);
	// Turn LED red.
	set_color(RGB(1, 0, 0));
	// Wait half a second (500 ms).
	delay(500);
}

int main()
{
	// Initialize the hardware.
	kilo_init();
	// Register your program.
	kilo_start(setup, loop);

	return 0;
}
