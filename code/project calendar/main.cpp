//
//  main.cpp
//  project calendar
//
//  Created by Antoine Jeannot on 01/05/2015.
//  Copyright (c) 2015 Antoine Jeannot. All rights reserved.
//

#include <iostream>
#include "Manager.h"

class test{
    int n;
};

int main(int argc, const char * argv[]) {

    std::cout << "Hello, World!\n";
    Manager<int>& m = Manager<int>::getInstance();
    return 0;
}
