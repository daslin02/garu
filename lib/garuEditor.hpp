#include <fstream>
#include <string>
#include <iostream>


#define ERROR_ISOPEN -1
#define ERROR_FORMAT -2
#define ASSURE_VALIABLE 1


int isValiable(const std::string &PathFile);
std::string getTextError(int error);
void prints();
