#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <map>
#include <string>

enum flag{
    EDITING = 1,
    DEFAULT = 0,
    CANCEL = -1
};

class GameController
{
public:

private:
    std::map<int, int>difficultyTable{{1,5}, {2,10}, {3,15}, {4,20}, {5,30}};
    std::string levelName = NULL;
    int difficulty;
    clock_t result;
    enum flag editorFlag = DEFAULT;
};

#endif // GAMECONTROLLER_H
