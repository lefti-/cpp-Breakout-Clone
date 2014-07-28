/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef HIGHSCORE_HPP
#define HIGHSCORE_HPP

#include "HighScoreEntry.hpp"

#include <vector>
#include <sstream>
#include <fstream>
#include <ostream>
#include <iostream>
#include <string>
#include <algorithm>

//Creating a struct (something that will contain data about players):


namespace HighScore {
    void writeFile(HighScoreEntry a);
}
#endif