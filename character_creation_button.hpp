#ifndef CHARACTER_CREATION_BUTTON_H
#define CHARACTER_CREATION_BUTTON_H

#include "general.hpp"
#include "transition_button.hpp"
#include "character_handler.hpp"
#include "data_button.hpp"
#include "text_box_button.hpp"

class CharacterCreationButton : public TransitionButton {
public:
    explicit CharacterCreationButton(ButtonTextData&, Vector2u, float, float, State,
        CharacterHandler&, RenderWindow&, TextBoxButton&, vector<DataButton*>&);
    State Action(Event);
protected:
    CharacterHandler& char_handler;
    RenderWindow& window;
    TextBoxButton& character_name_button;
    vector<DataButton*>& save_button_list;
};

#endif // CHARACTER_CREATION_BUTTON_H
