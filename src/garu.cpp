#include <iostream>
#include <garuGenerate.hpp>



int main(int arg ,char *argv[] )
{
    prints();
    if (arg < 2 )
    {
        std::cout<<"Error not get all settings" << std::endl;
        return 0 ;
    }
    int result = isValiable(argv[1]);
    std::cout << getTextError(result);
    std::cout << arg << std::endl;

    return 0 ;
}
