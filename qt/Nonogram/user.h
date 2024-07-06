#ifndef USER_H
#define USER_H

#include <QString>
#include <QTime>

class User
{
public:
    User(
        int userId,
        const QString &name,
        int imageId,
        int levelCompleted,
        qint64 fastestCompleted,
        qint64 totalTimePlayed
        );

    int getUserId() const;

    QString getName() const;
    void setName(const QString &newName);
    int getImageId() const;
    void setImageId(int newImageId);
    int getLevelCompleted() const;
    void setLevelCompleted(int newLevelCompleted);
    qint64 getFastestCompleted() const;
    void setFastestCompleted(qint64 newFastestCompleted);
    qint64 getTotalTimePlayed() const;
    void setTotalTimePlayed(qint64 newTotalTimePlayed);

    QTime getFastestCompletedTime() const;
    QTime getTotalTimePlayedTime() const;

private:
    int userId;
    QString name;
    int imageId;
    int levelCompleted;
    qint64 fastestCompleted;
    qint64 totalTimePlayed;
};

#endif // USER_H
