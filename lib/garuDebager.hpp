#include <garuGenerate.hpp>



class debug
{
    private:
        bool isDebug = false;
        std::vector<int> flags;
        int curentflag = 0;
    public:
        void print(std::string obj);
        void print(char* obj[]);
        void print(int obj);
        void print(float obj);
        void print(Token obj);
        void print(requests obj);
        void setFlag();
        void OnDebug();
        void offDebug();
};