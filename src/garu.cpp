#include <iostream>
#include <garuGenerate.hpp>



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
    // std::cout << getTextError(result);

    return 0 ;
}
