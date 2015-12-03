//
// Created by zealot on 11/30/15.
//

#include "LameBook.h"

LameBook::LameBook(std::string filePath)
{
    m_filePath=filePath;
    std::ifstream inFile(m_filePath);
    std::string tempstring="temp";
    if (inFile.is_open())
    {

        for (std::forward_list<User>::iterator seeker = m_Users.before_begin(); !inFile.eof(); )
        {
            m_Users.emplace_after(seeker);
            inFile >> *(++seeker);

        }
    }
    frontEnd();
}

LameBook::~LameBook()
{
    std::ofstream outFile(m_filePath,std::ios_base::trunc);
    for(auto seeker=m_Users.begin();seeker!=m_Users.end();++seeker)
    {
        outFile<<*seeker;
    }
}

void LameBook::frontEnd()
{
    int menuChoice=0;
    std::cout<<std::endl;
    while(menuChoice!=4)
    {
        std::cout<<"Welcome to LameBook! Choose the number of the option you'd like!"<<std::endl;
        std::cout<<"1:Login to account\n2:Create an account\n3:Display curent users\n4:Exit LameBook\n";
        std::cin>>menuChoice;
        std::cin.ignore();//clear the stream to prevent unwanted behavior
        switch (menuChoice)
        {
            case 1:
                login();
                break;
            case 2:
                newUser();
                break;
            case 3:
                printUsers();
                break;
            case 4:
                return;
            default:
                std::cout<<"Sorry, input not recognised!"<<std::endl;
        }
    }
}

void LameBook::login()
{
    std::string user;
    std::cout<<"Welcome back! what's your user name?"<<std::endl;
    getline(std::cin,user);
    for(auto seeker=m_Users.begin();seeker!=m_Users.end()&&seeker->getName()<=user;++seeker)
    {
        if(seeker->getName()==user)//if the user was found, go to their dashboard
        {
            userDashboard(*seeker);
            return;
        }
    }
    std::cout<<"Sorry! That user wasn't found!"<<std::endl;
}

void LameBook::newUser()
{
    std::string user;
    std::cout<<"Awesome! Enter your new user name!"<<std::endl;
    getline(std::cin,user);
    auto trailer=m_Users.before_begin();
    for(auto seeker=m_Users.begin();seeker!=m_Users.end()&&seeker->getName()<=user;trailer=seeker++)
    {
        if (seeker->getName() == user)//if the user already exists, let them know
        {
            std::cout << "One of your new friends already has that username, sorry!" << std::endl;
            return;
        }
    }
    User newUser(user);
    m_Users.insert_after(trailer,newUser);
}

void LameBook::printUsers()const
{
    std::cout<<"Current users: \n";
    for(auto seeker=m_Users.begin();seeker!=m_Users.end();++seeker)
    {
        std::cout<<seeker->getName()<<std::endl;
    }
    std::cout<<std::endl;
}

void LameBook::userDashboard(User &current)
{
    int menuChoice=0;
    current.processFriendRequests();
    while(menuChoice!=7)
    {
        std::cout<<"What would you like to do next?\n";
        std::cout<<"1.Print your status\n2:Set your status\n3:Print all your statuses\n4:Add a friend\n5:Print a friend's status\n6:Print friend list\n7:Logout\n";
        std::cin>>menuChoice;
        std::cin.ignore();
        switch (menuChoice)
        {
            case 1:
                current.printStatus();
                break;
            case 2:
                current.setStatus();
                break;
            case 3:
                current.printAllStatuses();
                break;
            case 4:
                newFriend(current);
                break;
            case 5:
                printFriendStatus(current);
                break;
            case 6:
                current.printFriendList();
                break;
            case 7:
                return;
            default:
                std::cout<<"Sorry, input not recognised!"<<std::endl;
        }
    }

}

void LameBook::newFriend(User &current)
{
    std::string input;
    printUsers();
    std::cout<<"Great! Who's your new friend?"<<std::endl;
    getline(std::cin,input);
    if(current.hasFriend(input))
    {
        std::cout<<"You're already friends with them!"<<std::endl;
        return;
    }
    if(current.getName()==input)
    {
        std::cout<<"You can't be friends with yourself!"<<std::endl;
    }
    for(auto seeker=m_Users.begin();seeker!=m_Users.end()&&seeker->getName()<=input;++seeker)
    {
        if(seeker->getName()==input)
        {
            seeker->addFriendRequest(&current);
            std::cout<<"Your friend request has been sent!\n";
            return;
        }
    }
    std::cout<<"User not found! Check spelling and capitalization\n";
}

void LameBook::printFriendStatus(User &current)
{
    unsigned long userChoice;
    current.printFriendList();
    std::cout<<"Enter the number coresponding to the friend you want to see"<<std::endl;
    std::cin >> userChoice;
    std::cin.ignore();
    if(userChoice < 0 || userChoice > current.numberOfFriends())
    {
        std::cout<<"Sorry! That wasn't a valid choice!"<<std::endl;
        return;
    }
    std::string targetUser(current.getFriend(userChoice));
    for(auto seeker=m_Users.begin();seeker!=m_Users.end();++seeker)
    {
        if(seeker->getName()==targetUser)
        {
            seeker->printStatus();
            return;
        }
    }
    std::cout<<"Internal error processing request! Sorry!"<<std::endl;
}
