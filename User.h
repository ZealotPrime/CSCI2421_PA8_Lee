//
// Created by zealot on 11/26/15.
//

#ifndef CSCI2421_PA8_LEE_USER_H
#define CSCI2421_PA8_LEE_USER_H

#include <iostream>
#include <string>
#include <vector>
#include <forward_list>
#include <deque>
#include <sstream>
class User
{
public:
    User()= delete;//default constructor removed
    User(std::string name);//constructor taking name of new user

    //input functions
    void setStatus();
    void addFriendRequest(std::string name);
    void processFriendRequests();
    std::istream& operator>>(std::istream& is);

    //output/get functions
    std::string getName(){return m_userName;}
    void printStatus();
    void printAllStatuses();
    void printFriendList();
    bool hasFriend(std::string target);
    std::ostream& operator<<(std::ostream& os);

private:
    std::string m_userName;
    std::forward_list<std::string> m_status;
    std::vector<std::string> m_friendsList;
    std::deque<std::string> m_friendRequests;
    void addFriend(std::string name);
};


#endif //CSCI2421_PA8_LEE_USER_H
