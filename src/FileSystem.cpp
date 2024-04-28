/*
 *
 */
#include "rc8server.h"
#include <cstdlib>
#include <dirent.h>
#include <algorithm>
#include <fstream>

std::map<std::string, int> TaskList = {
    {"None", 0},
};


int
GetTaskTime(std::string name)
{
  decltype(TaskList)::iterator it = TaskList.find(name);
  if (it == TaskList.end()) {
    std::cout << "No task found:" << name << std::endl;
    return 0;
  }
  return TaskList[name];
}

void
LoadTaskList()
{
  std::string cwd;
  char *dir_ = std::getenv("RC8SERVER_DIR");
  if (dir_){
    cwd = std::string(dir_);
  }else{
    cwd = std::string("/usr/local/rc8server/");
  }
  std::string script_dir = cwd + "config/scripts";
  std::vector<std::string> f_list = GetTaskNames(script_dir);

  for (auto it=f_list.begin(); it != f_list.end(); ++it) {
    std::string key = *it;
  
    decltype(TaskList)::iterator p = TaskList.find(key);
    if (p == TaskList.end()) {
      std::string fname=script_dir+"/"+key+".pcs";
      std::ifstream ifs(fname.c_str());
      std::string data;
      ifs >> data;
      int res = 0;
      try{
        res = stoi(data);
      }catch(...){
        std::cerr << "===ERROR: " << key << ":" << data << std::endl;
      }
      std::cerr << "Task[" << key << "] = "  << res << std::endl;
      TaskList[key] = res;
    }
  }

}

std::vector<std::string>
GetTaskNames(std::string path)
{
    std::vector<std::string>lst;
    DIR *dp;
    dp = opendir(path.c_str());
    if(dp == NULL) { return lst; }
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
ReadTaskTime(std::vector<std::string> f_list, std::string name)
{
  std::string cwd;
  char *dir_ = std::getenv("RC8SERVER_DIR");
  if (dir_){
    cwd = std::string(dir_);
  }else{
    cwd = std::string("/usr/local/rc8server/");
  }
  std::string script_dir = cwd + "config/scripts";

  auto result = std::find(f_list.begin(), f_list.end(), name);
  if (result == f_list.end()){
    std::cerr << "Not found:" <<  script_dir << std::endl;
    return 0;
  }else{
    std::cerr << "=== " << name ;
    std::string fname=script_dir+"/"+name+".pcs";
    std::ifstream ifs(fname.c_str());
    std::string data;
    ifs >> data;
    int res = 0;
    try{
      res = stoi(data);
    }catch(...){
      std::cerr << "===ERROR: " << name << "=" << data << std::endl;
    }

    return res;
  }
  return 0;
}

/*
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
    int res=0;
    try{
      res = stoi(data);
    }catch(...){
      std::cerr << "===ERROR: " << data << std::endl;
    }

    return res;
  }
  return 0;
}
*/
