/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/System.hpp>

#include <memory>


class StateMachine;

namespace sf {
    class RenderWindow;
}

class GameState {
public:
    GameState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    virtual ~GameState();
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
    int levelNumber;
};
#endif // GAMESTATE_HPP