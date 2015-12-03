//
// Created by zealot on 11/30/15.
//

#ifndef CSCI2421_PA8_LEE_LAMEBOOK_H
#define CSCI2421_PA8_LEE_LAMEBOOK_H

#include <forward_list>
#include <fstream>
#include "User.h"

class LameBook
{
public:
    LameBook()= delete;
    LameBook(std::string filePath);
    ~LameBook();


private:
    void frontEnd();
    void login();
    void newUser();
    void printUsers()const;
    void userDashboard(User& current);
    void newFriend(User& current);
    void printFriendStatus(User& current);
    std::string m_filePath;
    std::forward_list<User> m_Users;
};


#endif //CSCI2421_PA8_LEE_LAMEBOOK_H
