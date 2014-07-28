/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "HighScore.hpp"


void HighScore::readFile() {
    // Check if highscore file exists.
    if(std::ifstream("data/highscores.txt")) {
        // Read highscore.txt lines.
        std::ifstream hsFile("data/highscores.txt");
        std::string line;

        // Create temp struct which is used to fill vector.
        HighScoreEntry temp;

        std::vector<HighScoreEntry> entries;

        while(hsFile.good()) {

            std::getline(hsFile, line);

            // Split the line.
            // Get substring from index 0 to space and convert it to integer.
            std::string xx = line.substr(0, line.find(' '));
            int x = atoi(xx.c_str());
            temp.score = x;
            temp.name = line.substr(line.find(' ') + 1);    // Get substring from space and to the end of the string.
            entries.push_back(temp);                        // Add highscore to vector.
        }
        hsFile.close();

        std::sort(entries.begin(), entries.end());

        // Print highscores.
        for(unsigned int i = 0; i < entries.size(); i++) {
            std::cout << entries[i].score << " " << entries[i].name << std::endl;
        }
    }
}

void HighScore::writeFile(HighScoreEntry a) {
    // If file exists...
    if(std::ifstream("data/highscores.txt")) { 
        // Read highscore.txt lines.
        std::ifstream hsFileRead("data/highscores.txt");
        std::string line;

        // Create temp struct which is used to fill vector.
        HighScoreEntry temp;

        std::vector<HighScoreEntry> entries;

        while(hsFileRead.good()) {

            std::getline(hsFileRead, line);

            // Split the line.
            // Get substring from index 0 to space and convert it to integer.
            std::string xx = line.substr(0, line.find(' '));
            int x = atoi(xx.c_str());
            temp.score = x;
            temp.name = line.substr(line.find(' ') + 1);    // Get substring from space and to the end of the string.
            entries.push_back(temp);                        // Add highscore to vector.
        }
        hsFileRead.close();

        // Create new highscore entry and add to vector.
        temp.score = a.score;
        temp.name = a.name;
        entries.push_back(temp);

        // Sort from highest score to lowest.
        std::sort(entries.begin(), entries.end());

        // Write all high scores again.
        std::ofstream hsFileWrite("data/highscores.txt");
        for(int i = 0; i < entries.size(); ++i) {
            if(entries[i].score == 0) {}
            else {
                hsFileWrite << entries[i].score << " " << entries[i].name << '\n';
            }
        }
        hsFileWrite.close();

        // Print highscores.
        for(unsigned int i = 0; i < entries.size(); i++) {
            std::cout << entries[i].score << " " << entries[i].name << std::endl;
        }
    }
    // If file doesn't exist...
    else {
        // Create new.
        std::ofstream hsFile("data/highscores.txt");
        hsFile << a.score << " " << a.name << '\n';
        hsFile.close();
    }
}
