#include "user.h"

User::User(int userId, const std::string &name, int imageId, int levelCompleted, clock_t fastestCompleted, time_t totalTimePlayed)
    : userId(userId), name(name), imageId(imageId), levelCompleted(levelCompleted), fastestCompleted(fastestCompleted), totalTimePlayed(totalTimePlayed)
{

}

int User::getUserId() const
{
    return userId;
}

std::string User::getName() const
{
    return name;
}

void User::setName(const std::string &newName)
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

clock_t User::getFastestCompleted() const
{
    return fastestCompleted;
}

void User::setFastestCompleted(clock_t newFastestCompleted)
{
    fastestCompleted = newFastestCompleted;
}

time_t User::getTotalTimePlayed() const
{
    return totalTimePlayed;
}

void User::setTotalTimePlayed(time_t newTotalTimePlayed)
{
    totalTimePlayed = newTotalTimePlayed;
}
