#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>

#include <SFML/System.hpp>


class StateMachine;

namespace sf {
    class RenderWindow;
}

class GameState {
public:
    GameState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    virtual ~GameState();
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void processEvents() = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw() = 0;
    std::unique_ptr<GameState> next();
    bool isReplacing();
protected:
    StateMachine& state_machine;
    sf::RenderWindow& m_window;
    bool m_replacing;
    std::unique_ptr<GameState> m_next;
};
#endif // GAMESTATE_HPP