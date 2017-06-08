#include <avr/interrupt.h>

#include "events.hpp"

volatile bool NearSensorEvent = false;
volatile bool FarSensorEvent = false;
volatile bool MidiNoteEvent = false;

volatile uint8_t MidiBendState = 0;
volatile uint8_t MidiNoteIntensity = 0;
volatile uint32_t UniversalTime = 0;
