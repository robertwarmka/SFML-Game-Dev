#ifndef TRANSITION_BUTTON_H_
#define TRANSITION_BUTTON_H_

#include "general.hpp"
#include "text_button.hpp"

class TransitionButton : public TextButton {
protected:
    State state;
public:
    explicit TransitionButton(ButtonTextData&, Vector2u, float, float, State);
    State Action(Event);
    void Draw(RenderWindow&);
private:
};

#endif
