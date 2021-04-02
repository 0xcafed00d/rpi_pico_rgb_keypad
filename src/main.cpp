
#include <stdio.h>
#include "pico/binary_info.h"
#include "pico/stdlib.h"

#include "pico_rgb_keypad.hpp"

using namespace pimoroni;

PicoRGBKeypad pico_keypad;

const uint LED_PIN = PICO_DEFAULT_LED_PIN;

int main() {
	bi_decl(bi_program_description("pimoroni rgb keypad project"));

	stdio_init_all();

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	pico_keypad.init();

	uint32_t count = 1;

	pico_keypad.illuminate(0, 255, 255, 255);

	while (true) {
		gpio_put(LED_PIN, count & 1);
		printf("%d\n", count);
		sleep_ms(100);
		count++;

		pico_keypad.set_brightness((count & 0xf) / 16.0f);
		pico_keypad.update();
	}
}
