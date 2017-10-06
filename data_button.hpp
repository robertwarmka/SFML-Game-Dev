#ifndef DATA_BUTTON_H_
#define DATA_BUTTON_H_

#include "general.hpp"
#include "text_button.hpp"

class DataButton : public TextButton {
public:
    explicit DataButton(ButtonTextData&, Vector2u, float, float);
    virtual string ConcatStrings() = 0;
};

#endif // DATA_BUTTON_H_
