PRJ_NAME   = Berimbau
CC         = avr-gcc
CXX        = avr-g++
SRCDIR     = src
SRC        = $(wildcard $(SRCDIR)/*.c)
CPPSRC     = $(wildcard $(SRCDIR)/*.cpp)
ASRC       = $(wildcard $(SRCDIR)/*.S)
OBJ        = $(SRC:.c=.o) $(ASRC:.S=.o) $(CPPSRC:.cpp=.o)
OBJCOPY    = avr-objcopy
OBJDUMP    = avr-objdump
PGPORT    ?= /dev/ttyACM0
BAUDRATE  ?= 57600
AVRDUDE    = avrdude
PROGRAMMER = arduino
DEVICE     = atmega328p
OPTIMIZE   = -O2
FREQ       = 16000000
OPTIONS    = -fpack-struct -fshort-enums
CFLAGS     = -Wall -gdwarf-2 $(OPTIMIZE) -mmcu=$(DEVICE) -DF_CPU=$(FREQ) -std=c++11
ASFLAGS    = -Wall -gstabs -mmcu=$(DEVICE) -DF_CPU=$(FREQ)
LDFLAGS    = -Wl,-Map,$(PRJ_NAME).map
OBJFLAGS   = -R .eeprom -O ihex "$(PRJ_NAME).elf" "$(PRJ_NAME).hex"
DUDEFLAGS  = -c $(PROGRAMMER) -p $(DEVICE) -P $(PGPORT) -B $(BAUDRATE) -u -U flash:w:"$(PRJ_NAME).hex"
RSTFLAGS   = -c $(PROGRAMMER) -p $(DEVICE)

all: $(PRJ_NAME).elf $(PRJ_NAME).hex

$(PRJ_NAME).elf: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c $(DEPS)
	$(CC) -MMD -c $(CFLAGS) $< -o $@

%.o: %.cpp $(DEPS)
	$(CXX) -MMD -c $(CFLAGS) $< -o $@

%.o: %.S $(DEPS)
	$(CC) -MMD -c $(ASFLAGS) $< -o $@

-include $(SRCDIR)/*.d

$(PRJ_NAME).hex: $(PRJ_NAME).elf
	$(OBJCOPY) $(OBJFLAGS)

clean:
	rm -f $(OBJ) *.map *.elf *.hex $(SRCDIR)/*.d

burn:
	$(AVRDUDE) $(DUDEFLAGS)

rst:
	$(AVRDUDE) $(RSTFLAGS)

fast: all burn
