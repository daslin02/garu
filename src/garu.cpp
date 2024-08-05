#include <iostream>
#include <fstream>
#include <string>


int main(int arg ,char *argv[] ){
    if (arg < 2 ){
        std::cout<<"Error not get all settings" << std::endl;
        return 0 ;
    }

    std::cout << arg << std::endl;

    return 0 ;
}