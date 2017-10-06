#ifndef STATE_BUTTON_H_
#define STATE_BUTTON_H_

#include "general.hpp"
#include "data_button.hpp"

class StateButton : public DataButton {
protected:
    State state;
    bool display_state;
public:
    explicit StateButton(ButtonTextData&, Vector2u, float, float, State, bool);
    State Action(Event);
    void Draw(RenderWindow&);
    void UpdateState(int);
    virtual string GetState() = 0;
    string ConcatStrings();
    String ConcatDisplayStrings();
};

#endif // STATE_BUTTON_H_
