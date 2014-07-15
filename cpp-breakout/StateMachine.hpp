// The header file should have a header guard to prevent multiple inclusion errors.
// header guard at start of header file
#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "GameState.hpp"

#include <SFML/System.hpp>

#include <iostream>
#include <memory>
#include <stack>


class GameState;

namespace sf {
    class RenderWindow;
}

class StateMachine {
public:
    StateMachine();

    void run(std::unique_ptr<GameState> state);

    void nextState();
    void lastState();
    
    void processEvents();
    void update(sf::Time deltaTime);
    void draw();

    bool running() { return m_running; }
    void quit() { m_running = false; }

    template <typename T>
    static std::unique_ptr<T> build(StateMachine& machine, sf::RenderWindow& window, bool replace = true );
private:
    // The stack of states
    std::stack<std::unique_ptr<GameState>> m_states;

    bool m_resume;
    bool m_running;
};

template <typename T>
std::unique_ptr<T> StateMachine::build(StateMachine& machine, sf::RenderWindow& window, bool replace) {
    return std::move(std::unique_ptr<T>(new T(machine, window, replace)));
}
// end header guard at bottom of header file
#endif // STATEMACHINE_HPP