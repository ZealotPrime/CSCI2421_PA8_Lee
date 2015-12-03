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
    User(){};//default constructor removed
    User(std::string name);//constructor taking name of new user

    //input functions
    void setStatus();
    void addFriendRequest(User* target);
    void processFriendRequests();
    friend std::istream& operator>>(std::istream& is, User& target);

    //output/get functions
    std::string getName()const{return m_userName;}
    std::string getFriend(unsigned long target){return m_friendsList[target];}
    unsigned long numberOfFriends()const{return m_friendsList.size();}
    void printStatus()const;
    void printAllStatuses()const;
    void printFriendList()const;
    bool hasFriend(std::string target)const;
    friend std::ostream& operator<<(std::ostream& os, User& target);

private:
    std::string m_userName;
    std::forward_list<std::string> m_status;
    std::vector<std::string> m_friendsList;
    std::deque<User*> m_friendRequests;
    void addFriend(std::string name);
};


#endif //CSCI2421_PA8_LEE_USER_H
