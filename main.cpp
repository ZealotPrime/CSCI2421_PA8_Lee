#include <iostream>
#include "User.h"
using namespace std;


int main()
{
    User testUser("Bob");
    testUser.setStatus();
    testUser.setStatus();
    testUser.getName();
    testUser.printStatus();
    testUser.printAllStatuses();
    return 0;
}