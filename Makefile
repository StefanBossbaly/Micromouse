BOARD_TAG    = uno
MONITOR_PORT = /dev/ttyACM*
ARDUINO_LIBS = MemoryFree Wire
EXTRA_CXXFLAGS = -fshort-enums

include $(ARDMK_DIR)/Arduino.mk
