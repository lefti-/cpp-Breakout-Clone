/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "GameState.hpp"


GameState::GameState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace)
    : state_machine(machine), m_window(window), m_replacing(replace) { }

GameState::~GameState() { }

std::unique_ptr<GameState> GameState::next() {
    return std::move(m_next);
}

bool GameState::isReplacing() {
    return m_replacing;
}