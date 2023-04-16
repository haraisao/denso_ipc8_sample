#include "bCAPServerSample.h"
#include <cstdlib>
#include <dirent.h>


std::vector<std::string>
GetTaskNames(const char*path)
{
    std::vector<std::string>lst;
    DIR *dp;
    dp=opendir(path);
    if(dp==NULL) { return lst; }
    dirent * entry = readdir(dp);
    while (entry != NULL){
        if(entry != NULL){
            std::string name(entry->d_name);
            auto pos=name.find(".scr");
            if (pos != std::string::npos){
              lst.push_back(name.substr(0, pos));
            }
        }
        entry=readdir(dp);
    }
    return lst;
}
