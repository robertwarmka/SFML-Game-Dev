#ifndef STATE_INT_BUTTON_H_
#define STATE_INT_BUTTON_H_

#include "general.hpp"
#include "state_button.hpp"

class StateIntButton : public StateButton {
public:
    explicit StateIntButton(ButtonTextData&, Vector2u, float, float, State, bool);
    string GetState();
};

#endif // STATE_INT_BUTTON_H_
