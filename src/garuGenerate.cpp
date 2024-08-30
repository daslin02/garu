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

std::string getTextError(int error)
{
    switch (error)
    {
    case -2:
        return "ERROR_FORMAT\n";
    case -1:
        return "ERROR_ISOPEN\n";
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