#ifndef SCORE_H
#define SCORE_H

#include <QString>

class Score
{
public:
    Score(
        int scoreId,
        const QString &userName,
        qint64 completionTime,
        const QString &levelDifficulty
    );

    int getScoreId() const;
    QString getUserName() const;
    qint64 getCompletionTime() const;
    QString getLevelDifficulty() const;

    QString printScore() const;

private:
    int scoreId;
    QString userName;
    qint64 completionTime;
    QString levelDifficulty;
};

#endif // SCORE_H
