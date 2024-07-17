#ifndef CSVSCOREDAO_H
#define CSVSCOREDAO_H

#include "scoredao.h"
#include "score.h"
#include <vector>
#include <QString>

class CSVScoreDAO : public ScoreDAO {
public:
    CSVScoreDAO(const QString &filename);

    std::vector<Score> getAllScores() const override;
    void insert(const Score& score) override;
    int getNextScoreId() const;
    qint64 getMinTimeForUser(const QString &username) const;
    int getCountLevelForUser(const QString &username) const;

private:
    QString filename;
};

#endif // CSVSCOREDAO_H
