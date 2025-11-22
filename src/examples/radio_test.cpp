#include "CustomRadio.h"
#include <Arduino.h>

#define RADIO_CS_PIN PA4
#define RADIO_GD0_PIN PB0

CustomRadio radio(RADIO_CS_PIN, RADIO_GD0_PIN);


void setup() {
	Serial1.begin(115200, SERIAL_8E1);
	Status status = radio.begin();

	if (status == Status::STATUS_OK)
		Serial1.println("radio init - success");
	else {
		Serial1.print("radio init - fail (");
		Serial1.print(status);
		Serial1.print(")");
	}
}

void loop() {
	uint8_t dataToSend[] = "Hello, World!";
	Status txStatus = radio.transmit(dataToSend, sizeof(dataToSend));

	if (txStatus == Status::STATUS_OK) {
		Serial1.println("Data transmitted successfully");
	} else {
		Serial1.print("Transmission failed (");
		Serial1.print(txStatus);
		Serial1.println(")");
	}

	delay(1000);
}
