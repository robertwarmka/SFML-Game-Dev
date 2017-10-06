#ifndef TEXT_BOX_BUTTON_H_
#define TEXT_BOX_BUTTON_H_

#include "general.hpp"
#include "data_button.hpp"

class TextBoxButton : public DataButton {
protected:
    bool focused, blink;
    Color focused_color;
    sf::String text_data;
    ostringstream char_stream;
    double blink_animation = 500.0; // in millis
    time_point<steady_clock> blink_start;
    Text display_text;
public:
    explicit TextBoxButton(ButtonTextData&, Vector2u, float, float, const Color&);
    State Action(Event);
    void Draw(RenderWindow&);
    void Animate(float, float);
    bool Blink();
    string GetData();
    string ConcatStrings();
    void EraseTextData();
};

#endif //TEXT_BOX_BUTTON_H_
