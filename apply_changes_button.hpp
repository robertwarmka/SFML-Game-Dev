#ifndef APPLY_CHANGES_BUTTON_H_
#define APPLY_CHANGES_BUTTON_H_

#include "general.hpp"
#include "config_handler.hpp"
#include "transition_button.hpp"
#include "state_button.hpp"

class ApplyChangesButton : public TransitionButton {
public:
    explicit ApplyChangesButton(ButtonTextData&, Vector2u, float, float, State,
        ConfigHandler&, RenderWindow&, vector<StateButton*>&, vector<Button*>&);
    State Action(Event);
protected:
    ConfigHandler& config;
    RenderWindow& window;
    vector<StateButton*>& save_button_list;
    vector<Button*>& button_list;
};

#endif // APPLY_CHANGES_BUTTON_H_
