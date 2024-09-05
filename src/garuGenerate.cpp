#include <garuGenerate.hpp>

std::string GaruTypeClass[] = {"int" , "str" , "bool" , "float" , "none" ,"list" , "dict"}; 
std::string GaruTypeOperator[] = {"=" , "==" , "*" , "/" , "%" , "!=" , "++" , "--" , "+=" , "-=" , "*=" , "/=" , "in" , "!" };
char scpecialCharacters[] ={'=' , '/','*','%','!','+','-', '(' , ')' , '{' , '.' ,'}' , '[' , ']'} ;
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

requests inGaruCOF(const std::string &obj)
{
    if (obj.empty())
    {
        requests req;
        req.status = GaruType::ERROR_UNDEFINED;
        req.GType = GaruType::ERROR_UNDEFINED;
        req.Type= "";
        req.value = "";
        req.msg = "is \'obj\' is empty";
        return req;
    }
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
    req.Type= obj;
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
    else if (Gtype == GaruType::ERROR_UNDEFINED){
        return "ERROR_UNDEFINED";
    }
    else if (Gtype == GaruType::ERROR_ISOPEN){
        return "ERROR_ISOPEN";
    }
    else if (Gtype == GaruType::ERROR_FORMAT){
        return "ERROR_FORMAT";
    }
    else if (Gtype == GaruType::ERROR_FOUND){
        return "ERROR_FOUND";
    }
    else if (Gtype == GaruType::ASSURE_VALIABLE){
        return "ASSURE_VALIABLE";
    }
    else if (Gtype == GaruType::UNDEFINED_TYPE){
        return "UNDEFINED_TYPE";
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
    bool noComent = false;
    int index = 0;
    char last = ' ';
    bool isObj= false;
    bool isLastSpecial= true;
    while (std::getline(file , line))
    {   
        std::string obj;
        for(char element :line)
        {
            if(element != ';' )
            {   
                if (element == '#') 
                {
                    noComent = true;
                    break;
                }
                if (std::isalpha(element))
                {
                    std::cout<<"ALPHA   " << obj+element << std::endl;
                    if (last == '\''|| last == '\"' )
                    {
                        obj = last + element;
                        last = element;
                        isLastSpecial = false;
                    }
                    else if (isLastSpecial)
                    {
                        obj = element;
                        last = element;
                        isLastSpecial = false;
                    }
                    else if (std::isalpha(last))
                    {
                        obj += element;
                        last = element;
                        isLastSpecial = false; 
                    }
                    else if (std::isdigit(obj[0]))
                    {
                        std::cerr << "can't add letter to a number";
                        std::exit(EXIT_FAILURE); 
                    }
                    
                }
                else if (std::isdigit(element))
                {
                    std::cout<<"DIGIT   " << obj+element << std::endl; 
                    if (last == '\''|| last == '\"' )
                    {
                        obj = last + element;
                        last = element;
                        isLastSpecial = false;
                    }
                    else if (isLastSpecial)
                    {
                        obj = element;
                        last = element;
                        isLastSpecial = false;
                    }
                    else if (std::isalpha(last) )
                    {
                        obj += element;
                        last = element;
                        isLastSpecial = false;
                    }else if (std::isdigit(last))
                    {
                        obj += element;
                        last = element;
                        isLastSpecial = false;
                    }
                }
                else if((obj[0] == '\'' || obj[0] == '\"') && (element== '\'' || element == '\"'))
                {
                    last = element;
                    obj += element;
                    isLastSpecial = false;
                    isObj = true;
                }
                else
                {
                    for (char SpecialChar : scpecialCharacters)
                    {
                        if (!obj.empty())
                        {
                            if (element == ';')
                            {
                                isObj =true;
                                break;
                            }
                            isObj = true;
                            break;
                        }
                        if(element==SpecialChar || element == ' ')
                        {
                            if (isLastSpecial && element ==SpecialChar )
                            {
                                obj = last + element;
                                last = element;
                                isObj = true;
                                break;
                            }
                            else if (isLastSpecial && element == ' ')
                            {
                                obj = last ;
                                last = element;
                                isObj = true;
                                break;
                            }
                            else if (last == ' ' && element == ' ')
                            {
                                isLastSpecial =true;
                                isObj = false;
                                break;
                            }
                            last = element;
                            isLastSpecial = true;
                            isObj = true;
                            break;
                        }
                    }
                }

                if (isObj)
                {
                    Token el ;
                    requests result = inGaruCOF(obj); 
                    if (result.status == GaruType::ASSURE_VALIABLE || result.status == GaruType::UNDEFINED_TYPE )
                    {
                        Token lineObj = convertrReqInTok(result);
                        std::cout << "lineObj GType: " << getText(lineObj.GType) << std::endl;
                        std::cout << "lineObj Type: " << lineObj.Type << std::endl;
                        std::cout << "lineObj Value: " ; printTokenType(lineObj.value) ;
                        lineLexer.push_back(lineObj);
                    }

                    isObj = false;
                    obj = "";
                }

            }
            else
            {
                if(!obj.empty())
                {
                    Token el ;
                    requests result = inGaruCOF(obj); 
                    if (result.status == GaruType::ASSURE_VALIABLE || result.status == GaruType::UNDEFINED_TYPE )
                    {
                        Token lineObj = convertrReqInTok(result);
                        std::cout << "lineObj GType: " << getText(lineObj.GType) << std::endl;
                        std::cout << "lineObj Type: " << lineObj.Type << std::endl;
                        std::cout << "lineObj Value: " ; printTokenType(lineObj.value) ;
                        lineLexer.push_back(lineObj);
                    }

                    isObj = false;
                    obj = "";
                }
                break;
            } 
        }
        if (noComent)
        {
            tokens.push_back(lineLexer);
            lineLexer.clear();
            obj.clear();
        }else{
            noComent = false;
        }
    }
}
void GenerateLexer::printLexer()
{
    int *index = new int;
    std::cout<< "------------------------------------------------------" << std::endl; 
    for( std::vector line : tokens)
    {   
        for (Token tok : line)
        {   

            std::cout << index <<"\t"<< getText(tok.GType)<< "\t" << tok.Type << "\t" ;
            printTokenType(tok.Type);
            index++;
        }
        index = 0;
    }
    delete index;
}