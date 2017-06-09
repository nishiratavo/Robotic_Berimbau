/*
typedef enum {
  Boot;
  Idle;
  CCW_End;
  CCW_Middle;
  NearString;
  CW_Middle;
} state;
*/

#include "events.hpp"
#include "statemachine.hpp"
#include "dcmotor.hpp"
#include "gpiodef.hpp"

using namespace dcmotor;

static DCMotor Stick;

/*
 * Change state and reset flags
 */

void StateMachine::change_state(state new_state) {
  this->State = new_state;
  this->transition = true;
  // Reset all interrupt flags
  NearSensorEvent = false;
  FarSensorEvent = false;
  MidiNoteEvent = false;
}

/*
 * Operate state machine
 */


void StateMachine::operate() {

  switch (this->State) {
    case Boot:
      LedM1ON();
      LedM2ON();
      LedMIDION();
      LedNearStringON();
      LedSensorNearON();
      LedSensorFarON();
      Stick.Action(TurnCW, 255);

      this->initial_time = UniversalTime; // Get timer
      this->timeout = 1000;

      while ( (UniversalTime - this->initial_time) < this->timeout);
      LedM1OFF();
      LedM2OFF();
      LedMIDIOFF();
      LedNearStringOFF();
      LedSensorNearOFF();
      LedSensorFarOFF();

      this->change_state(Idle);

      break;

    case Idle:
      Stick.Action(OFF,0);
      if (MidiNoteEvent) {
        this->change_state(CCW_End);
      }
      if (FarSensorEvent) {
        this->change_state(CW_Middle);
      }
      // If valid MIDI message: Next state CCW_End
      // IRQ EndPos: CW_Middle
      break;


    case CCW_End:
      Stick.Action(TurnCCW, MidiNoteIntensity);
      if (this->transition == true) {
        this->initial_time = UniversalTime;
        this->timeout = 500;
        this->transition = false;
      }

      if ((UniversalTime - this->initial_time) >= this->timeout)
        this->change_state(CW_Middle);
      if (FarSensorEvent)
        this->change_state(CCW_Middle);

      // Motor CCW
      // Timeout: 0.5s => CW_Midle
      // IRQ endpos => CCW_Middle
      break;

    case CCW_Middle:
      Stick.Action(TurnCCW, MidiNoteIntensity);
      if (this->transition == true) {
        this->initial_time = UniversalTime;
        this->timeout = 500;
        this->transition = false;
      }

      if ((UniversalTime - this->initial_time) >= this->timeout)
        this->change_state(CW_Middle);
      if (NearSensorEvent)
        this->change_state(NearString);

      // Motor CCW
      // Timeout 0.5s => CW_Middle
      // IRQ nearstring => NearString
      break;

    case NearString:
      Stick.Action(OFF, 0);
      if (this->transition == true) {
        this->initial_time = UniversalTime;
        this->timeout = 50;
        this->transition = false;
      }

      if ((UniversalTime - this->initial_time) >= this->timeout)
        this->change_state(CW_Middle);
      if (NearSensorEvent)
        this->change_state(CW_Middle);

     // Motor OFF
      // Timeout 0.01s =-> CW_Middle
      // IRQ nearstring => CW_Middle
      break;


    case CW_Middle:
      M2ON();
      Stick.Action(TurnCW, 255);
      if (transition) {
        initial_time = UniversalTime;
        timeout = 500;
        this->transition = false;
      }

      if (MidiNoteEvent)
        this->change_state(CCW_Middle);
      if ((UniversalTime - this->initial_time) > this->timeout) {
        this->change_state(Idle);
      }
      if (NearSensorEvent)
        this->change_state(Idle);


      // Motor CW
      // IRQ EndPos => Idle
      // Timeout 0.5s => Idle
      break;

    default:
      this->State = Boot;
      break;
  }

}

