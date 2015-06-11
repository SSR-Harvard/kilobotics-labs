#include <kilolib.h>

message_t message;

void setup() {
  // Initialize message:
  
  // The type is almost always NORMAL.
  message.type = NORMAL;

  // Some dummy data as an example.
  message.data[0] = 0;

  // It's important that the CRC is computed
  // *after* all the data has been set (otherwise it will be wrong).
  message.crc = message_crc(&message);
}

void loop()
{
}

message_t *message_tx() {
  return &message;
}

void message_tx_success()
{
	// Blink LED magenta whenever a message is sent.
	set_color(RGB(1,0,1));
	delay(20);
	set_color(RGB(0,0,0));
}

int main() {
  kilo_init();

  // Register message_tx function.
  kilo_message_tx = message_tx;
  // Register message_tx_success function.
  kilo_message_tx_success = message_tx_success;

  kilo_start(setup, loop);

  return 0;
}
