#include "score.h"

Score::Score(int scoreId, const QString &userName, qint64 completionTime, const QString &levelDifficulty)
    : scoreId(scoreId), userName(userName), completionTime(completionTime), levelDifficulty(levelDifficulty)
{

}

int Score::getScoreId() const
{
    return scoreId;
}

QString Score::getUserName() const
{
    return userName;
}

qint64 Score::getCompletionTime() const
{
    return completionTime;
}

QString Score::getLevelDifficulty() const
{
    return levelDifficulty;
}

QString Score::printScore() const
{
    return QString::number(scoreId) + ": " + userName + ", " + QString::number(completionTime) + " @ " + levelDifficulty;
}
