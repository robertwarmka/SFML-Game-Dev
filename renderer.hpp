#ifndef RENDERER_H_
#define RENDERER_H_

#include "general.hpp"
#include "button.hpp"

class Renderer : public Logger {
private:
    boost::shared_mutex _access;
    vector<Button*> button_list;
    bool handle_events;
public:
    explicit Renderer();
    ~Renderer();
    void HandleEvents();
    void Animate(Vector2i&);
    State Action(Event&);
    State Render(RenderWindow&);
    void AddButton(Button*);
    void SetButtonList(vector<Button*>&);
    void Clear();
};

#endif // RENDERER_H_
