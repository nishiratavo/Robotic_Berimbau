/*
 * Global variables to signal events
 */

#ifndef EVENTS_HPP_
#define EVENTS_HPP_

#include <stdint.h>

extern volatile bool NearSensorEvent;
extern volatile bool FarSensorEvent;
extern volatile bool MidiNoteEvent;

extern volatile uint8_t MidiBendState;
extern volatile uint8_t MidiNoteIntensity;
extern volatile uint32_t UniversalTime;

#endif
