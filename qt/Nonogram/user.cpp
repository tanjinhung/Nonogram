#include "user.h"

User::User(int userId, const QString &name, int imageId, int levelCompleted, qint64 fastestCompleted, qint64 totalTimePlayed)
    : userId(userId), name(name), imageId(imageId), levelCompleted(levelCompleted), fastestCompleted(fastestCompleted), totalTimePlayed(totalTimePlayed)
{

}

int User::getUserId() const
{
    return userId;
}

QString User::getName() const
{
    return name;
}

void User::setName(const QString &newName)
{
    name = newName;
}

int User::getImageId() const
{
    return imageId;
}

void User::setImageId(int newImageId)
{
    imageId = newImageId;
}

int User::getLevelCompleted() const
{
    return levelCompleted;
}

void User::setLevelCompleted(int newLevelCompleted)
{
    levelCompleted = newLevelCompleted;
}

qint64 User::getFastestCompleted() const
{
    return fastestCompleted;
}

void User::setFastestCompleted(qint64 newFastestCompleted)
{
    fastestCompleted = newFastestCompleted;
}

qint64 User::getTotalTimePlayed() const
{
    return totalTimePlayed;
}

void User::setTotalTimePlayed(qint64 newTotalTimePlayed)
{
    totalTimePlayed = newTotalTimePlayed;
}

QTime User::getFastestCompletedTime() const
{
    return QTime::fromMSecsSinceStartOfDay(static_cast<int>(fastestCompleted));
}

QTime User::getTotalTimePlayedTime() const
{
    return QTime::fromMSecsSinceStartOfDay(static_cast<int>(totalTimePlayed));
}
