#include <kilolib.h>

int message_sent = 0;
message_t message;
uint32_t message_last_changed = 0;
int odd = 0;

void setup()
{
}

void loop()
{
    // Toggle even/odd message every 64 clock ticks (roughly 2 seconds).
    if (kilo_ticks > message_last_changed + 64)
    {
        message_last_changed = kilo_ticks;
        
        if (odd == 0)
        {
            message.type = NORMAL;
            message.data[0] = 0;
            message.crc = message_crc(&message);
            
            // Update odd for next time.
            odd = 1;
        }
        else
        {
            message.type = NORMAL;
            message.data[0] = 1;
            message.crc = message_crc(&message);
            
            // Update odd for next time.
            odd = 0;
        }
    }
    
    // Blink the LED magenta whenever a message is sent.
    if (message_sent)
    {
        message_sent = 0;
        
        set_color(RGB(1, 0, 1));
        delay(100);
        set_color(RGB(0, 0, 0));
    }
}

message_t *message_tx()
{
    return &message;
}

void message_tx_succes()
{
    message_sent = 1;
}

int main()
{
    kilo_init();
    kilo_message_tx = message_tx;
    kilo_message_tx_success = message_tx_succes;
    kilo_start(setup, loop);

    return 0;
}
