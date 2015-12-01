//
// Created by zealot on 11/30/15.
//

#ifndef CSCI2421_PA8_LEE_LAMEBOOK_H
#define CSCI2421_PA8_LEE_LAMEBOOK_H

#include <forward_list>
#include "User.h"

class LameBook
{
public:
    LameBook();
    ~LameBook();


private:
    void frontEnd();
    void login();
    void newUser();
    void printUsers();
    void userDashboard(User& current);
    void printFriendStatus(std::string target);
    std::forward_list<User> m_users;
};


#endif //CSCI2421_PA8_LEE_LAMEBOOK_H
