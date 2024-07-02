#ifndef PROFILECONTROLLER_H
#define PROFILECONTROLLER_H

#include <string>

class ProfileController
{
public:
    ProfileController();

    void registerUser();
    void confirmUserDeletion();

private:
    std::string username;
    int imageId;

    void verifyInput();
    void findUser();
};

#endif // PROFILECONTROLLER_H
