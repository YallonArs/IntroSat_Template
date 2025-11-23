#include <stdint.h>

#include "utils/utils.h"

class GPIOTool {
public:
	GPIOTool(uint16_t pin, bool inverted = false);

	void on();
	void off();
	void toggle();
	
	void pulse(uint32_t delayMs);
	void startPWM(uint16_t frequency, uint8_t dutyCycle) const;
	void stopPWM() const;
	bool isOn() const;

private:
	uint16_t _pin;
	bool _inverted = false;
	State _state = Disabled;
};
