#include <iostream>
#include <pigpiod_if2.h>

// Define the GPIO pin connected to the limit switch
const int LIMIT_SWITCH_PIN = 4;  // Example GPIO pin

// Callback function to be called when the switch state changes
void limitSwitchCallback(int pi, unsigned gpio, unsigned level, uint32_t tick, void* user_data) {

    std::cout << "GPIO: " << gpio << " Level: " << level << " Tick: " << tick << std::endl;

    if (level == PI_HIGH) {  // Level HIGH means the switch is pressed
        std::cout << "Limit switch pressed!" << std::endl;
    } else if (level == PI_LOW) {  // Level LOW means the switch is released
        std::cout << "Limit switch released!" << std::endl;
    }
}

int main() {
    // Connect to the pigpiod daemon
    int pi = pigpio_start(NULL, NULL);
    if (pi < 0) {
        std::cerr << "Failed to connect to pigpiod" << std::endl;
        return 1;
    }

    // Set the GPIO pin mode to input
    set_mode(pi, LIMIT_SWITCH_PIN, PI_INPUT);

    // Set pull-down resistor (you can also set pull-up if needed)
    set_pull_up_down(pi, LIMIT_SWITCH_PIN, PI_PUD_DOWN);

    // Register the callback for the limit switch
    int callback_id = callback_ex(pi, LIMIT_SWITCH_PIN, EITHER_EDGE, limitSwitchCallback,NULL);

    // Main program loop
    while (true) {
        time_sleep(0.1);  // Sleep for 100ms to avoid busy-waiting
    }

    // Cleanup
    pigpio_stop(pi);
    return 0;
}