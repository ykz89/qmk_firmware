CFLAGS += -Wno-array-bounds
LINKER_FLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map
LDFLAGS += -Wl,-z,noexecstack
