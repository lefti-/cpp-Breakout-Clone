/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "StateMachine.hpp"


StateMachine::StateMachine()
    :  m_running(false) {
    std::cout << "<< GameStateMachine initialized >>" << std::endl;
}

void StateMachine::run(std::unique_ptr<GameState> state) {
    m_running = true;
    m_states.push(std::move(state));
}

void StateMachine::nextState() {
    // There needs to be a state
    if(!m_states.empty()) {
        std::unique_ptr<GameState> temp = m_states.top()->next();

        // Only change states if there's a next one existing
        if(temp != nullptr) {
            // Replace the running state
            if(temp->isReplacing()) {
                m_states.pop();
            }

            m_states.push(std::move(temp));
        }
    }
}

void StateMachine::processEvents() {
    // Let the state process it's events
    m_states.top()->processEvents();
}

void StateMachine::update(sf::Time deltaTime) {
    // Let the state update the game
    m_states.top()->update(deltaTime);
}

void StateMachine::draw() {
    // Let the state draw the screen
    m_states.top()->draw();
}