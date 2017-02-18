include properties.mk

all:
	+$(MAKE) -C core-avr-logging
	+$(MAKE) -C core-avr-data
	#+$(MAKE) -C core-avr-messaging