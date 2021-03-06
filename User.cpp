//
// Created by zealot on 11/26/15.
//



#include "User.h"

User::User(std::string name)//constructor for new user
{
    m_userName=name;
}



void User::setStatus()//sets the user's status, and archives the current one, if any
{
    std::string input;
    std::cout<<"What's on your mind...?"<<std::endl;
    getline(std::cin,input);
    m_status.push_front(input);
}

void User::addFriend(std::string name)//private function that adds a friend to user's list
{
    auto seeker=m_friendsList.begin();
    for(;seeker!=m_friendsList.end()&&*seeker<=name;++seeker)
    {
        if(*seeker==name)//end early if target user already a friend
        {
            std::cout<<name<<" is already a friend of "<<m_userName<<"."<<std::endl;
            return;
        }
    }
    m_friendsList.insert(seeker,name);//insert if they weren't a friend already
}

void User::addFriendRequest(User* target)//adds a friend request to the queue
{
    m_friendRequests.push_front(target);
}

void User::processFriendRequests()//prompts the user to accept or decline each friend request they have
{
    std::string input;
    std::cout<<"You have "<<m_friendRequests.size()<<" new friend request"<<(m_friendRequests.size()!=1?"s":"")<<std::endl;
    while(m_friendRequests.size()>0)
    {
        std::cout<<"Friend request from "<<m_friendRequests.back()->getName()<<std::endl<<"Accept? (Y/N)";
        std::cin>>input;
        std::cin.ignore();
        if(input[0]=='y'||input[0]=='Y')
        {
            addFriend((m_friendRequests.back()->getName()));
            m_friendRequests.back()->addFriend(this->getName());
            m_friendRequests.pop_back();
        }
        else if(input[0]=='n'||input[0]=='N')
        {
            m_friendRequests.pop_back();
        }
        else
            std::cout<<"Error: Input not recognised!"<<std::endl;
    }

}

void User::printStatus()const//prints current status
{
    std::cout<<std::endl;
    if(m_status.empty())
    {
        std::cout<<"You haven't posted any statuses yet!"<<std::endl;
        return;
    }
    std::cout<<m_status.front()<<std::endl<<std::endl;
}

void User::printAllStatuses()const//prints all statuses for user
{
    std::cout<<std::endl;
    if(m_status.empty())
    {
        std::cout<<"You haven't posted any statuses yet!\n\n";
        return;
    }
    for(auto seeker=m_status.begin();seeker!=m_status.end();++seeker)
    {
        std::cout<<*seeker<<std::endl;
    }
    std::cout<<std::endl;
}

void User::printFriendList()const//prints the user's friend list
{
    std::cout<<std::endl;
    if(m_friendsList.empty())
    {
        std::cout<<"You haven't added any of your friends yet!"<<std::endl;
        return;
    }
    for(std::size_t x=0;x<m_friendsList.size();++x)
    {
        std::cout<<x<<":"<<m_friendsList[x]<<std::endl;
    }
    std::cout<<std::endl;
}

std::ostream &operator<<(std::ostream &os, User& target)//outputs the user in a format suitable for later loading from file
{
    os<<target.m_userName<<std::endl;

    if(target.m_status.empty())
        os<<"____";
    else
    {
        target.m_status.reverse();//output the user's statuses in reverse order so they load correctly
        for(auto seeker=target.m_status.begin();seeker!=target.m_status.end();++seeker)
        {
            if(seeker!=target.m_status.begin())
                os<<",";
            os<<*seeker;

        }
        target.m_status.reverse();
    }
    os<<std::endl;

    if(target.m_friendsList.empty())
        os<<"____";
    else
        for(auto seeker=target.m_friendsList.begin();seeker!=target.m_friendsList.end();++seeker)//output friends list
        {
            if(seeker!=target.m_friendsList.begin())
                os<<",";//append comma if this isn't the start of the loop
            os<<*seeker;
        }
    return os;
}

std::istream &operator>>(std::istream &is, User& target)
{
    std::string worker;
    getline(is,target.m_userName);//get the username

    getline(is,worker);//getline to temp string
    std::stringstream workStream(worker);//put it into a stream for manipulation
    if(worker!="____")
        while(getline(workStream,worker,','))
        {
            target.m_status.push_front(worker);//fill statuses
        }
    workStream.clear();
    getline(is,worker);//getline to temp string
    workStream.str(worker);//put it into a stream for manipulation
    if(worker!="____")
        while(getline(workStream,worker,','))
        {
            target.m_friendsList.push_back(worker);//fill friends list
        }


    return is;
}


bool User::hasFriend(std::string target)const
{
    if(m_friendsList.empty())
        return false;
    for(auto seeker=m_friendsList.begin();seeker!=m_friendsList.end()&&*seeker<=target;++seeker)
    {
        if(*seeker==target)
            return true;
    }
    return false;
}
