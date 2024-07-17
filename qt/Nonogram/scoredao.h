#ifndef SCOREDAO_H
#define SCOREDAO_H

#include "score.h"
#include <vector>

class ScoreDAO {
public:
    virtual ~ScoreDAO() = default;
    virtual std::vector<Score> getAllScores() const = 0;
    virtual void insert(const Score& score) = 0;
};

#endif // SCOREDAO_H
