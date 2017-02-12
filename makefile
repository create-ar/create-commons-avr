all:
	# make each subproject in order
	+$(MAKE) -C core-avr-logging
	+$(MAKE) -C core-avr-messaging
	+$(MAKE) -C core-avr-data