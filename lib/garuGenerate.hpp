#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <variant>
#include <cctype>


//value
extern int allSize;
extern int openBlock;
extern std::string GaruTypeClass[];
extern std::string GaruTypeOperator[];
extern std::string GaruTypeFunction[];
// constant
enum  class GaruType 
{
    ERROR_ISOPEN =-1,
    ERROR_FORMAT =-2,
    ERROR_FOUND =-3,
    ERROR_UNDEFINED = -4,
    ASSURE_VALIABLE =1,
    UNDEFINED_TYPE = 2,
    GARU_TYPE_NONE =0x00,
    GARU_TYPE_INT =0x10,
    GARU_TYPE_FLOAT =0x20,
    GARY_TYPE_STRING =0x30,
    GARU_TYPE_BOOL =0x40,
    GARU_TYPE_OPERATOR =0x50,
    GARU_TYPE_FUNCTION =0x60,
    GARU_TYPE_TYPE =0x70,
    GARU_TYPE_BLOCK = 0x35,
    
    GARU_TYPE_CLASS =0x80,
    GARU_TYPE_SPECIAL_CHAR = 0x010,
    GARU_TYPE_NAME =0x90
    
};

using TokenType = std::variant<int , float , std::string , char , bool>;

struct requests
{
    GaruType status;
    GaruType GType;
    std::string Type;
    std::string value ;
    std::string msg;
};
struct Token
{
    GaruType GType;
    std::string value;
};



// function
GaruType isValiable(const std::string &PathFile);
requests inGaruCOF(const std::string &obj);
Token convertrReqInTok(requests req);
std::string getText(GaruType Gtype);
void printTokenType(TokenType type);
bool isSpecialChar(char sp);

// class
class GenerateLexer
{
    private:
        std::fstream file;
        std::string code;
        std::vector<std::vector<Token>> tokens;
        std::vector<Token> GenerateTokens(const std::string line);
    public:
        GenerateLexer();
        GaruType openFile(const std::string &path);
        void ReadLiner();
        void genLexer();
        std::string getCode();
        void printLexer();
};