#ifndef CHOICE_BUTTON_H_
#define CHOICE_BUTTON_H_

#include "general.hpp"
#include "text_button.hpp"

class ChoiceButton : public TextButton {
protected:
    int state;
public:
    explicit ChoiceButton(ButtonTextData&, Vector2u, float, float, int);
    ChoiceButton(const ChoiceButton&);
    State Action(Event);
    void Draw(RenderWindow&);
    int GetState();
};

#endif // CHOICE_BUTTON_H_
