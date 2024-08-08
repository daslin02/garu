#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <variant>


// constant
enum GaruType 
{
    #define ERROR_ISOPEN -1
    #define ERROR_FORMAT -2
    #define ASSURE_VALIABLE 1
    #define GARU_TYPE_INT 0x1
    #define GARU_TYPE_FLOAT 0x2
    #define GARY_TYPE_STRING 0x3
    #define GARU_TYPE_BOOL 0x4
    #define GARU_TYPE_OPERATOR 0x5
};

using TokenType = std::variant<int , float , std::string , char , bool>;

struct Token
{
    GaruType type;
    TokenType value;
};


// function
int isValiable(const std::string &PathFile);
std::string getTextError(int error);
void prints();

// class
class GenerateLexer
{
    private:
        std::vector<char> lexer;
    public:
        GenerateLexer();
        std::fstream openFile(const std::string &path);

};