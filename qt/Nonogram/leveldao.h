#ifndef LEVELDAO_H
#define LEVELDAO_H

#include "editorlevel.h"
#include <vector>

class LevelDAO {
public:
    virtual ~LevelDAO() = default;
    virtual std::vector<EditorLevel> getAllLevels() const = 0;
    virtual void insert(const EditorLevel &editorLevel) = 0;
};

#endif // LEVELDAO_H
