#include "hardware/CustomRadio.h"

CustomRadio::CustomRadio(uint8_t csPin, uint8_t gd0) : Radio(csPin, gd0) {}

Status CustomRadio::begin() {
	Status status = Radio::begin();

	if (status != Status::STATUS_OK)
		return status;

	this->setModulation(CC1101::MOD_2FSK);
	this->setFrequency(433.8);
	this->setDataRate(0.1);
	this->setOutputPower(10);

	this->setPacketLengthMode(CC1101::PKT_LEN_MODE_VARIABLE);
	this->setAddressFilteringMode(CC1101::ADDR_FILTER_MODE_NONE);
	this->setPreambleLength(64);
	this->setSyncWord(0x1234);
	this->setSyncMode(CC1101::SYNC_MODE_16_16);
	this->setCrc(true);
	this->setDataWhitening(true);
	this->setManchester(false);
	this->setFEC(false);

	return status;
}
