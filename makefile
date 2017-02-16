all:
	# make each subproject in order
	+$(MAKE) -C core-avr-logging OUT_DIR=$(OUT_DIR) OBJ_DIR=$(OBJ_DIR)
	+$(MAKE) -C core-avr-data OUT_DIR=$(OUT_DIR) OBJ_DIR=$(OBJ_DIR)
	+$(MAKE) -C core-avr-messaging OUT_DIR=$(OUT_DIR) OBJ_DIR=$(OBJ_DIR)

.PHONY: buildtests
buildtests:
	+$(MAKE) buildtests -C core-avr-logging OUT_DIR=$(OUT_DIR) OBJ_DIR=$(OBJ_DIR) TESTINC=$(TESTINC)
	+$(MAKE) buildtests -C core-avr-data OUT_DIR=$(OUT_DIR) OBJ_DIR=$(OBJ_DIR) TESTINC=$(TESTINC)