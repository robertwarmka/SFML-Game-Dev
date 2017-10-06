#ifndef IMAGE_BUTTON_H_
#define IMAGE_BUTTON_H_

#include "general.hpp"
#include "button.hpp"

class ImageButton : public Button {
protected:
    Sprite sprite;
public:
    explicit ImageButton(Texture&, Vector2u, float, float);
    void Draw(RenderWindow&);
    void Animate(float, float);
    State Action(Event);
    void UpdateWindowSize(Vector2u);
    void UpdateWindowSize(Vector2u, Vector2u);
private:
};

#endif
