#include <garuGenerate.hpp>


int isValiable(const std::string &PathFile)
{
    std::fstream script(PathFile);
    if(!script.is_open())
    {
        return ERROR_ISOPEN;
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
        return ERROR_FORMAT;
    }

    return ASSURE_VALIABLE;
}

std::string getTextError(int error)
{
    switch (error)
    {
    case ERROR_FORMAT:
        return "ERROR_FORMAT\n";
    case ERROR_ISOPEN:
        return "ERROR_ISOPEN\n";
    default:
        return "not find error\n";
    }
}


GenerateLexer::GenerateLexer()
{
    
}
int GenerateLexer::openFile(const std::string &path)
{
    std::fstream scriptText(path);
    int result = isValiable(path);
    if(result = ASSURE_VALIABLE)
    {   
        std::string line;
        this->file.open(path);
        while (std::getline(file , line)){
            this->code.append(line);
        }

        return ASSURE_VALIABLE;
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
        throw std::runtime_error("not open file");
    }
}
void GenerateLexer::genLexer()
{
    file.clear();
    file.seekg(0);
    std::string line;
    int index = 0;
    while (std::getline(file , line))
    {
        tokens[index].push_back(line);
    }
}