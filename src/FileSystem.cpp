/*
 *
 */
#include "rc8server.h"
#include <cstdlib>
#include <dirent.h>
#include <algorithm>
#include <fstream>


std::vector<std::string>
GetTaskNames(std::string path)
{
    std::vector<std::string>lst;
    DIR *dp;
    dp=opendir(path.c_str());
    if(dp==NULL) { return lst; }
    dirent * entry = readdir(dp);
    while (entry != NULL){
        if(entry != NULL){
            std::string name(entry->d_name);
            auto pos=name.find(".pcs");
            if (pos != std::string::npos){
              lst.push_back(name.substr(0, pos));
            }
        }
        entry=readdir(dp);
    }
    return lst;
}


int
ReadTaskTime(std::string name)
{
  std::string cwd;
  char *dir_ = std::getenv("RC8SERVER_DIR");
  if (dir_){
    cwd = std::string(dir_);
  }else{
    cwd = std::string("/usr/local/rc8server/");
  }
  std::string script_dir = cwd + "config/scripts";
  std::vector<std::string> f_list=GetTaskNames(script_dir);

  auto result=std::find(f_list.begin(), f_list.end(), name);
  if (result == f_list.end()){
    std::cerr << "Not found" << std::endl;
    return -1;
  }else{
    std::string fname=script_dir+"/"+name+".pcs";
    std::ifstream ifs(fname.c_str());
    std::string data;
    ifs >> data;
    return  stoi(data);
  }
  return 0;
}
