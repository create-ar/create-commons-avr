include properties.mk

all:
	+$(MAKE) -C core-avr-logging
	+$(MAKE) -C core-avr-database
	#+$(MAKE) -C core-avr-messaging

.PHONY: clean
clean:
	rm -rf core-avr-logging/build
	rm -rf core-avr-database/build
	rm -rf core-avr-messaging/build
	rm -rf libs