#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <variant>


extern std::string GaruTypeClass[];
extern std::string GaruTypeOperator[];
extern std::string GaruTypeFunction[];
// constant
enum  class GaruType 
{
    ERROR_ISOPEN =-1,
    ERROR_FORMAT =-2,
    ERROR_FOUND =-3,
    ASSURE_VALIABLE =1,
    UNDEFINED_TYPE = 2,
    GARU_TYPE_NONE =0x0,
    GARU_TYPE_INT =0x1,
    GARU_TYPE_FLOAT =0x2,
    GARY_TYPE_STRING =0x3,
    GARU_TYPE_BOOL =0x4,
    GARU_TYPE_OPERATOR =0x5,
    GARU_TYPE_FUNCTION =0x6,
    GARU_TYPE_TYPE =0x7,
    
    GARU_TYPE_CLASS =0x8,
    GARU_TYPE_NAME =0x9
    
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
    std::string Type;
    TokenType value;
};


// function
GaruType isValiable(const std::string &PathFile);
std::string getTextError(int error);
requests inGaruCOF(const std::string &obj);
Token convertrReqInTok(requests req);
std::string getText(GaruType Gtype);
void printTokenType(TokenType type);
// class
class GenerateLexer
{
    private:
        std::fstream file;
        std::string code;
        std::vector<std::vector<Token>> tokens;
    public:
        GenerateLexer();
        GaruType openFile(const std::string &path);
        void genLexer();
        std::string getCode();
        void printLexer();
};