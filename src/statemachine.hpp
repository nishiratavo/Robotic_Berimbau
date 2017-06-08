
#ifndef STATEMACHINEHPP_
#define STATEMACHINEHPP_

#include "events.hpp"
#include <stdint.h>

typedef enum {
  Boot,
  Idle,
  CCW_End,
  CCW_Middle,
  NearString,
  CW_Middle,
} state;


class StateMachine {
  private:
    state State = Boot;
    uint32_t timeout;
    uint32_t initial_time;
    bool transition;

    void change_state(state new_state);

  public:
    void operate();
};


#endif
