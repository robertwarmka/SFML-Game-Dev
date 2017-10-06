#include "image_button.hpp"

ImageButton::ImageButton(Texture& texture, Vector2u window_size, float x_percent, float y_percent) :
    Button(window_size, x_percent, y_percent, 1, 1, 0) {
    Vector2u tex_vec = texture.getSize();
    float x = (window_size.x * x_percent) - (tex_vec.x / 2.0f);
    float y = (window_size.y * y_percent);// - (tex_vec.y / 2.0f);
    sprite = Sprite(texture);
    left_upper = Vector2f(x, y);
    right_lower = Vector2f(x + tex_vec.x, y + tex_vec.y);
    sprite.setPosition(left_upper);
}

void ImageButton::Draw(RenderWindow& window) {
    window.draw(sprite);
}

void ImageButton::UpdateWindowSize(Vector2u window_size) {
    this->window_size = window_size;
    float x, y;
    Vector2u tex_vec = sprite.getTexture()->getSize();
    x = (window_size.x * x_percent) - (tex_vec.x / 2.0f);
    y = (window_size.y * y_percent) - (tex_vec.y / 2.0f);
    left_upper = Vector2f(x, y);
    right_lower = Vector2f(x + tex_vec.x, y + tex_vec.y);
    sprite.setPosition(left_upper);
}

void ImageButton::UpdateWindowSize(Vector2u window_size, Vector2u offset) {
    this->window_size = window_size;
    float x, y;
    Vector2u tex_vec = sprite.getTexture()->getSize();
    // TODO: Double check that just adding the offset gives the proper result
    x = (window_size.x * x_percent) - (tex_vec.x / 2.0f) + offset.x;
    y = (window_size.y * y_percent) - (tex_vec.y / 2.0f) + offset.y;
    left_upper = Vector2f(x, y);
    right_lower = Vector2f(x + tex_vec.x, y + tex_vec.y);
    sprite.setPosition(left_upper);
}

void ImageButton::Animate(float x, float y) {

}

State ImageButton::Action(Event event) {
    return State::NO_CHANGE;
}
