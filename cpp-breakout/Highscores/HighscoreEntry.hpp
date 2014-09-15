/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/

#ifndef HIGHSCOREENTRY_HPP
#define HIGHSCOREENTRY_HPP

#include <string>

struct HighscoreEntry {
    int score;
    std::string name;

    // Override the < operator, for comparing scores, from highest to lowest.
    bool operator<(const HighscoreEntry& a) const {
        return score > a.score;
    }
};
#endif
