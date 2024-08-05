#include <garuEditor.hpp>

<<<<<<< HEAD
void prints(){
    std::cout<<"is valiable"<<std::endl;

=======

int isValiable(const std::string &PathFile){
    std::fstream script(PathFile);
    if(!script.is_open()){
        return ERROR_ISOPEN;
    }
    
    std::string type;
    for (int i = PathFile.size()-4;i< PathFile.size() ; i++){
        if (true){
            type += PathFile[i];
        }
    }
    if (type != "garu"){
        return ERROR_FORMAT;
    }
    std::cout <<"type: " <<type << std::endl;

    return ASSURE_VALIABLE;
}

void prints(){
    std::cout<<"is valiable"<<std::endl;

}
std::string getTextError(int error){
    switch (error)
    {
    case ERROR_FORMAT:
        return "ERROR_FORMAT";
    case ERROR_ISOPEN:
        return "ERROR_ISOPEN";
    default:
        return "not find error";
    }
>>>>>>> main
}