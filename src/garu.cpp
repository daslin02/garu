#include <iostream>
#include <garuGenerate.hpp>
#include <cctype>

int main(int arg ,char *argv[] )
{
    if (arg < 2 )
    {
        std::cout<<"Error not get all settings" << std::endl;
        return 0 ;
    }


    GaruType result = isValiable(argv[1]);

    GenerateLexer lexer;
    lexer.openFile(argv[1]);

    std::string code = lexer.getCode();
    lexer.genLexer();
    
    lexer.printLexer();


    return 0 ;
}
