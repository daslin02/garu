#include <garuDebuger.hpp>

void debug::OnDebug()
{
    this->isDebug = true;
}
void debug::offDebug()
{
    this->isDebug = false;
}
void debug::print(std::string obj)
{
    if (this->isDebug)
    {
        std::cout << obj << std::endl; 
    }
}
void debug::print(int obj)
{
    if (this->isDebug)
    {
        std::cout << obj << std::endl; 
    }
}
void debug::print(float obj)
{
    if (this->isDebug)
    {
        std::cout << obj << std::endl; 
    }
}
void debug::print(char *obj[])
{
    if (this->isDebug)
    {
        size_t max = sizeof(obj) / sizeof(obj[0]);
        for (int i = 0 ;i < max ; i++ )
        {
            std::cout<<obj[i];
        }
        std::cout << std::endl;
    }
}
void debug::print(Token obj)
{
    if (this->isDebug)
    {
        std::cout << getText(obj.GType) << "\t" <<std::endl;
    }
}
void debug::print(requests obj)
{
    if (this->isDebug)
    {
        std::cout << "-------------PRINT REQUEST-------------" << std::endl;
        std::cout << "Status: " << getText(obj.status) << std::endl;
        std::cout << "GType: "<< getText( obj.GType) << std::endl;
        std::cout <<  "Value: " << obj.value << std::endl;
        std::cout << "Msg: " << obj.msg << std::endl;
    }
}
void debug::createFile()
{
    file.open("debuger.txt" , std::ios::out | std::ios::trunc);
}


