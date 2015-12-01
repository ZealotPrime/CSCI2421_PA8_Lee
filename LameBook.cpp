//
// Created by zealot on 11/30/15.
//

#include "LameBook.h"

LameBook::LameBook()
{
    std::ifstream inFile("/users.dat");
    User temp("temp");
    for(std::forward_list<User>::iterator seeker=m_Users.before_begin();!inFile.eof();++seeker)
    {
        inFile>>temp;
        m_Users.insert_after(seeker,temp);
    }
    frontEnd();
}

LameBook::~LameBook()
{
    std::ofstream outFile("/users.dat");
    m_Users.reverse();//reverse the list so it loads back from the file in order
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
        std::cin.clear();//clear the stream to prevent unwanted behavior
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
                break;
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
    for(auto seeker=m_Users.begin();seeker!=m_Users.end()&&seeker->getName()<user;++seeker)
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
    for(auto seeker=m_Users.begin();seeker!=m_Users.end()&&seeker->getName()<user;trailer=seeker++)
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

void LameBook::printUsers()
{
    for(auto seeker=m_Users.begin();seeker!=m_Users.end();++seeker)
    {
        std::cout<<seeker->getName()<<std::endl;
    }
    std::cout<<std::endl;
}

void LameBook::userDashboard(User &current)
{
    current.processFriendRequests();

}
