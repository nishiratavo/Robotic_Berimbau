/*
 * Global variables to signal events
 */

#ifndef EVENTS_HPP_
#define EVENTS_HPP_

#include <stdint.h>

extern volatile bool NearSensorEvent = false;
extern volatile bool FarSensorEvent = false;
extern volatile bool MidiNoteEvent = false;

extern volatile uint8_t MidiBendState = 0;
extern volatile uint32_t UniversalTime = 0;

#endif
