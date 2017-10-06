#ifndef OVERLAY_H_
#define OVERLAY_H_

#include "general.hpp"
#include "drawable.hpp"
#include "game_state.hpp"
#include "choice_button.hpp"
#include "state_button.hpp"
#include "config_handler.hpp"

class GameState;

class Overlay : public Drawable {
protected:
    GameState* menu;
    RectangleShape rect;
    View view, static_view;
    Vector2u window_size;
    float x_scale, y_scale;
    float lu_x, lu_y, rl_x, rl_y;
    float view_top, view_bottom;
    float view_y_center, y_shift;
    float y_pos;
    vector<Button*> buttons;
    ButtonTextData bt_data;
    OverlayData od;
    Button* selected_button;
public:
    explicit Overlay(Vector2u, GameState*, ButtonTextData&, OverlayData&);
    virtual ~Overlay();
    virtual State Action(Event) = 0;
    virtual void AddButton(Button*) = 0;
    virtual void UpdateWindowSize(Vector2u) = 0;
    void Draw(RenderWindow&);
    void Animate(float, float);
    void ScrollView(float);
    float MouseScrollOffset();
    void ClearData();
};

#endif
