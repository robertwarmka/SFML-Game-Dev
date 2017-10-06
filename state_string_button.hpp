#ifndef STATE_STRING_BUTTON_H_
#define STATE_STRING_BUTTON_H_

#include "general.hpp"
#include "state_button.hpp"

class StateStringButton : public StateButton {
public:
    explicit StateStringButton(ButtonTextData&, Vector2u, float, float,  State, bool);
    string GetState();
};

#endif // STATE_STRING_BUTTON_H_
