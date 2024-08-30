#include <garuGenerate.hpp>

std::string GaruTypeClass[] = {"int" , "str" , "bool" , "float" , "none" ,"list" , "dict"}; 
std::string GaruTypeOperator[] = {"=" , "==" , "*" , "/" , "%" , "!=" , "++" , "--" , "+=" , "-=" , "*=" , "/=" , "in" , "!" };
std::string GaruTypeFunction[] = {"print" , "input" };

GaruType isValiable(const std::string &PathFile)
{
    std::fstream script(PathFile);
    if(!script.is_open())
    {
        return GaruType::ERROR_ISOPEN;
    }
    
    std::string type;
    for (int i = PathFile.size()-4;i< PathFile.size() ; i++)
    {
        if (true){
            type += PathFile[i];
        }
    }
    if (type != "garu")
    {
        return GaruType::ERROR_FORMAT;
    }

    return GaruType::ASSURE_VALIABLE;
}

std::string getTextType(int error)
{
    switch (error)
    {
    case -3:
        return "ERROR_FOUND\n";
    case -2:
        return "ERROR_FORMAT\n";
    case -1:
        return "ERROR_ISOPEN\n";
    case 1:
        return "ASSURE_VALIABLE\n";
    case 2:
        return "UNDEFINED_TYPE\n";

    default:
        return "not find error\n";
    }
}
requests inGaruCOF(const std::string &obj)
{

    for (const std::string &element : GaruTypeClass)
    {
        if(element == obj)
        {
            requests req;
            req.status = GaruType::ASSURE_VALIABLE;
            req.GType = GaruType::GARU_TYPE_CLASS;
            req.Type= element;
            req.value = obj;
            req.msg = "is succes";
            return req;
        }
    }

    for (const std::string &element : GaruTypeFunction)
    {
        if(element == obj)
        {
            requests req;
            req.status = GaruType::ASSURE_VALIABLE;
            req.GType = GaruType::GARU_TYPE_FUNCTION;
            req.Type= element;
            req.value = obj;
            req.msg = "is succes type function";
            return req;
        }
    }

    for (const std::string &element : GaruTypeOperator)
    {
        if(element == obj)
        {
            requests req;
            req.status = GaruType::ASSURE_VALIABLE;
            req.GType = GaruType::GARU_TYPE_OPERATOR;
            req.Type= element;
            req.value = obj;
            req.msg = "is succes type operator";
            return req;
        }
    }
    requests req;
    req.status = GaruType::UNDEFINED_TYPE;
    req.GType = GaruType::GARU_TYPE_NAME;
    req.Type= "name";
    req.value = obj;
    req.msg = "is not found \'obj\' in garu types so a new name was created";
    return req;
}
Token convertrReqInTok(requests req)
{
    Token tok;
    tok.GType = req.GType;
    tok.Type = req.Type;
    tok.value = req.value;
    return tok;
}
std::string getText(GaruType Gtype)
{
    if (Gtype == GaruType::GARU_TYPE_NONE)
    {
        return "GARU_TYPE_NONE";
    }
    else if (Gtype == GaruType::GARU_TYPE_INT)
    {
        return "GARU_TYPE_INT";
    }
    else if (Gtype == GaruType::GARU_TYPE_FLOAT)
    {
        return "GARU_TYPE_FLOAT";
    }
    else if (Gtype == GaruType::GARY_TYPE_STRING)
    {
        return "GARU_TYPE_STRING";
    }
    else if (Gtype == GaruType::GARU_TYPE_BOOL)
    {
        return "GARU_TYPE_BOOL";
    }
    else if (Gtype == GaruType::GARU_TYPE_OPERATOR)
    {
        return "GARU_TYPE_OPERATOR";
    }
    else if (Gtype == GaruType::GARU_TYPE_FUNCTION)
    {
        return "GARU_TYPE_FUNCTION";
    }
    else if (Gtype == GaruType::GARU_TYPE_TYPE)
    {
        return "GARU_TYPE_TYPE";
    }
    else if (Gtype == GaruType::GARU_TYPE_CLASS)
    {
        return "GARU_TYPE_CLASS";
    }

    else if (Gtype == GaruType::GARU_TYPE_NAME)
    {
        return "GARU_TYPE_NAME";
    }
    else
    {
        return "UNKNOWN_GARU_TYPE";
    }
}
void printTokenType(TokenType type)
{
    auto visitor = [](auto&& arg)
    {
        std::cout << arg <<std::endl;
    };
    std::visit(visitor , type);
}

GenerateLexer::GenerateLexer()
{
    
}
GaruType GenerateLexer::openFile(const std::string &path)
{
    std::fstream scriptText(path);
    GaruType result = isValiable(path);
    if(result == GaruType::ASSURE_VALIABLE)
    {   
        std::string line;
        this->file.open(path);
        while (std::getline(file , line)){
            this->code.append(line);
        }

        return GaruType::ASSURE_VALIABLE;
    }
    else
    {
        return result;
    }
    
}
std::string GenerateLexer::getCode()
{
    if (code != "")
    {
        return code;
    }
    else
    {
        throw std::runtime_error("not open file or file empty");
    }
}
void GenerateLexer::genLexer()
{
    file.clear();
    file.seekg(0);
    std::string line;
    std::vector<Token> lineLexer;
    
    int index = 0;
    while (std::getline(file , line))
    {   
        std::string obj;
        for(char element :line)
        {
            if(!(element == ';'))
            {   
                if (element == '#') break;
                Token el ;
                requests result = inGaruCOF(obj); 
                if (result.status == GaruType::ASSURE_VALIABLE)
                {
                    Token lineObj = convertrReqInTok(result);
                    lineLexer.push_back(lineObj);
                }
                else
                {
                    
                }
                
            }
            else
            {
                break;
            } 
        }
        
        tokens.push_back(lineLexer);
        lineLexer.clear();
        obj.clear();
    }
}
void GenerateLexer::printLexer()
{
    int *index = new int;
    for( std::vector line : tokens)
    {   
        for (Token tok : line)
        {   

            std::cout << index << getText(tok.GType)<< "\t" << tok.Type << "\t" ;
            printTokenType(tok.Type);
            index++;
        }
        index = 0;
    }
    delete index;
}