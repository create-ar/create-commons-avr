all:
	# make each subproject in order
	+$(MAKE) -C core-avr-logging OUT_DIR=$(OUT_DIR) OBJ_DIR=$(OBJ_DIR)
	+$(MAKE) -C core-avr-messaging OUT_DIR=$(OUT_DIR) OBJ_DIR=$(OBJ_DIR)
	+$(MAKE) -C core-avr-data OUT_DIR=$(OUT_DIR) OBJ_DIR=$(OBJ_DIR)