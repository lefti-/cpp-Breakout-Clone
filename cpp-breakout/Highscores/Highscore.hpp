/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef HIGHSCORE_HPP
#define HIGHSCORE_HPP

#include "HighscoreEntry.hpp"

#include <vector>
#include <sstream>
#include <fstream>
#include <ostream>
#include <iostream>
#include <string>
#include <algorithm>

//Creating a struct (something that will contain data about players):


namespace Highscore {
    void writeFile(HighscoreEntry a);
    const int MAX_ENTRIES = 10;
}
#endif
