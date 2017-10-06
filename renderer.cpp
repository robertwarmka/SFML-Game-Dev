#include "renderer.hpp"

Renderer::Renderer() : button_list(), handle_events(true) {}

Renderer::~Renderer() {
    handle_events = false;
}

void Renderer::HandleEvents() {
    /*Event event;
    while(handle_events) {
        if(window.waitEvent(event)) {
            boost::shared_lock<boost::shared_mutex> lock(_access);
            Action(event);
            // Might be unnecessary, lock almost guaranteed to be released when it leaves scope upon exiting the if statement
            lock.release();
        }
    }*/
}

void Renderer::Animate(Vector2i& mouse_pos) {
    #pragma omp parallel
    #pragma omp single
    {
        for(auto it = button_list.begin(); it != button_list.end(); ++it) {
            #pragma omp task firstprivate(it)
            {
                (*it)->Animate(mouse_pos.x, mouse_pos.y);
            }
        }
        #pragma omp taskwait
    }
}

State Renderer::Action(Event& event) {
    State state = State::NO_CHANGE;
    State temp_state;
    #pragma omp parallel
    #pragma omp single
    {
        for(auto it = button_list.begin(); it != button_list.end(); ++it) {
            #pragma omp task firstprivate(it) private(temp_state) shared(state)
            {
                temp_state = (*it)->Action(event);
                if(temp_state != State::NO_CHANGE) {
                    state = temp_state;
                }
            }
        }
        #pragma omp taskwait
    }
    return state;
}

State Renderer::Render(RenderWindow& window) {
    // Clear window before drawing
    /*if(!valid_button_list) {

    }*/
    window.clear(Color::Black);
    for(auto it = button_list.begin(); it != button_list.end(); ++it) {
        (*it)->Draw(window);
    }
    return State::NO_CHANGE;
}

void Renderer::AddButton(Button* button) {
    //boost::unique_lock<boost::shared_mutex> lock(_access);
    button_list.push_back(button);
}

void Renderer::SetButtonList(vector<Button*>& button_list) {

    //valid_button_list = true;
    this->button_list = button_list;
}

// Clear all object lists
void Renderer::Clear() {
    boost::unique_lock<boost::shared_mutex> lock(_access);
    //valid_button_list = false;
    button_list.clear();
}
