#pragma once

#include <Arduino.h>

#include "utils/utils.h"
#include "utils/telemetry.h"

class Logger {
public:
	enum class LoggingLevel {
		ECHO = 0,
		DEBUG,
		INFO,
		WARNING,
		ERROR
	};

private:
	String _name;
	HardwareSerial *_UART;
	LoggingLevel _loglevel;
	State _state;

	String formatEntry(String text, LoggingLevel loglevel);
	static String logLevelToString(LoggingLevel loglevel);

public:
	Logger(HardwareSerial &serial, String name = "Unnamed");
	
	void begin(uint32_t baudrate, byte parity);

	void setLogLevel(LoggingLevel loglevel);
	void enable();
	void disable();

	void echo(String text);
	void debug(String text);
	void info(String text);
	void warn(String text);
	void error(String text);
	void write(String text, LoggingLevel loglevel);

	void logTelemetry(const telemetry &t);
	void wait();
};
