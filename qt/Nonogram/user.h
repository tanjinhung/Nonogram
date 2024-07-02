#ifndef USER_H
#define USER_H

#include <string>


class User
{
public:
    User(
        int userId,
        const std::string &name,
        int imageId,
        int levelCompleted,
        const clock_t fastestCompleted,
        const time_t totalTimePlayed
        );


    int getUserId() const;

    std::string getName() const;
    void setName(const std::string &newName);
    int getImageId() const;
    void setImageId(int newImageId);
    int getLevelCompleted() const;
    void setLevelCompleted(int newLevelCompleted);
    clock_t getFastestCompleted() const;
    void setFastestCompleted(clock_t newFastestCompleted);
    time_t getTotalTimePlayed() const;
    void setTotalTimePlayed(time_t newTotalTimePlayed);

private:
    int userId;
    std::string name;
    int imageId;
    int levelCompleted;
    clock_t fastestCompleted;
    time_t totalTimePlayed;
};

#endif // USER_H
