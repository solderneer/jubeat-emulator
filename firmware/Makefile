CC      :=$(CROSS)gcc
CXX     :=$(CROSS)g++
LD      :=$(CROSS)g++
SIZE    :=$(CROSS)size
OBJCOPY :=$(CROSS)objcopy
OBJDUMP :=$(CROSS)objdump

BUILD_DIR=build/
TARGET=$(BUILD_DIR)io-board
MMCU?=
AVRDUDE_FLAGS?=-c usbasp -p m328p -U flash:w:

SOURCES=$(wildcard *.cpp) $(wildcard *.c)
INCLUDES=

SETTINGS=settings.h

OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS:=$(OBJECTS:.c=.o)

CSTD?=c99
COPT=-O2 -fdata-sections -ffunction-sections
CFLAGS=-mmcu=$(MMCU) -std=$(CSTD) $(COPT) -Wall
CFLAGS+=$(addprefix -I,$(INCLUDES))
CFLAGS+=-include "$(SETTINGS)"

CXXSTD?=c++98
CXXOPT=$(COPT) -fno-exceptions -fno-rtti
CXXFLAGS=-mmcu=$(MMCU) -std=$(CXXSTD) $(CXXOPT) -Wall
CXXFLAGS+=$(addprefix -I,$(INCLUDES))
CXXFLAGS+=-include "$(SETTINGS)"

LDFLAGS=-mmcu=$(MMCU) -Wl,--gc-sections -Wl,-Map=$(TARGET).map,--cref

.PHONY: all avrdude clean prebuild build
	
all: prebuild build

prebuild: 
	mkdir -p build

build: $(TARGET).hex $(TARGET).lst

$(TARGET).elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(addprefix $(BUILD_DIR),$^) -lm -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature $< $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary -R .eeprom -R .fuse -R .lock -R .signature $< $@

%.o: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) -MMD -MP -MF $(@:%.o=%.d) $< -c

%.o: %.c
	$(CC) -o $(BUILD_DIR)$@ $(CFLAGS) -MMD -MP -MF $(BUILD_DIR)$(@:%.o=%.d) $< -c

$(TARGET).lst: $(TARGET).elf
	$(OBJDUMP) -h -S $< > $@

avrdude:
	avrdude $(AVRDUDE_FLAGS)$(TARGET).hex

clean:
	rm -rf build
#	-rm -f $(addprefix $(TARGET), .elf .hex .bin .lst .map)
#	-rm -f $(addprefix build/,$(OBJECTS)) $(addprefix build/,$(OBJECTS:.o=.d))