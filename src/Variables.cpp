/*
 *
 */
#include "rc8server.h"
#include <stdlib.h>
#include <yaml-cpp/yaml.h>

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <locale>
#include <codecvt>

#define GET_HANDLE(h)    (h & 0x0ff)

/*
 * Variables
 */
int32_t I_Values[100]={
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0};

float F_Values[100]={
	  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


BSTR ErrorCode=L"00000000";

VARIANT ControllerValues[]={
   {0, 0}, 
   {VT_I4, 100}, {VT_I4, 100}, {VT_I4, 0}, {VT_I4, 0}, {VT_I4, 0}, 
   {VT_I4, 0}, {VT_I4, 0}, {VT_I4, 0}, {VT_I4, 0}, 
   {VT_I4, 3}, {VT_BOOL, 0}, {VT_I4, 0}, {VT_DATE, 0}, {VT_BOOL, 0}, 
   {VT_BOOL, 0}, {VT_BOOL, 1}, 
   {VT_I8, 0},
   //{VT_BSTR, .bstrVal=ErrorCode},
   {VT_BSTR, 0},
   {VT_BSTR, 0}, {VT_BOOL, 0},
   {VT_BOOL, 0}, {VT_BOOL, 1}, {VT_BSTR, 0}, {VT_BSTR, 0}, {VT_BSTR, 0}, 
   {VT_BSTR, 0}, {VT_BOOL, 0} 
 };

VARIANT RobotValues[]={
   {0, 0}, {VT_ARRAY|VT_R8, 0}, {VT_ARRAY|VT_R8, 0},
   {VT_BOOL, 0}, {VT_BOOL, 0}, {VT_BSTR, 0}, {VT_I4, 0},
   {VT_ARRAY|VT_R8, 0}, {VT_I4, 0}, {VT_I4, 0}, {VT_R4, 0},
   {VT_R4, 0}, {VT_R4, 0}, {VT_R4, 0}, {VT_R4, 0}, {VT_R4, 0},
   {VT_R4, .fltVal=10}, {VT_R4, 0}, {VT_R4, 0},
   {VT_ARRAY|VT_R8, 0}, {VT_ARRAY|VT_R8, 0}, {VT_ARRAY|VT_R8, 0},
   {VT_ARRAY|VT_R8, 0}, {VT_ARRAY|VT_R8, 0}, {VT_ARRAY|VT_R8, 0},
};

VARIANT TaskValues[]={
   {0,0}, {VT_I4, 0}, {VT_I4, 0},
   {VT_I4|VT_ARRAY, 0}, {VT_I4, 0}, {VT_I4, 0},
   {VT_I4, 0}, {VT_I4, 0}, {VT_I4, 0},
};

std::map<std::wstring, int> ControllerVariables={
  { L"@VAR_I_LEN", 1 }, { L"@VAR_F_LEN", 2 }, { L"@VAR_D_LEN", 3 },
  { L"@VAR_V_LEN", 4 }, { L"@VAR_J_LEN", 5 }, { L"@VAR_P_LEN", 6 },
  { L"@VAR_T_LEN", 7 }, { L"@VAR_S_LEN", 8 }, { L"@VAR_IO_LEN", 9 },
  { L"@MODE", 10 }, { L"@LOCK", 11 }, { L"@TIME", 12 },
  { L"@CURRENT_TIME", 13 }, { L"@BUSY_STATUS", 14 },
  { L"@TSR_BUSY_STATUS", 15 }, { L"@NORMAL_STATUS", 16 },
  { L"@ERROR_CODE", 17 }, { L"@ERROR_CODE_HEX",18},
  { L"@ERROR_DESCRIPTION", 19}, { L"@EMERGENCY_STOP", 20},
  { L"@DEADMAN_SW", 21}, { L"@AUTO_ENABLE", 22},
  { L"@MAKER_NAME", 23}, { L"@TYPE", 24}, { L"@VARSION", 25},
  { L"@SERIAL_NO", 26}, { L"@PROTECTIVE_STOP", 27}
};

std::map<std::wstring, int> RobotVariables={
  { L"@CURRENT_POSITION", 1 }, { L"@CURRENT_ANGLE", 2 }, { L"@SERVO_ON", 3 },
  { L"@BUSY_STATUS", 4 }, { L"@TYPE_NAME", 5 }, { L"@TYPE", 6 },
  { L"@CURRENT_TRANS", 7 }, { L"@CURRENT_TOOL", 8}, { L"@CURRENT_WORK", 9 },
  { L"@SPEED", 10 }, { L"@ACCEL", 11 }, { L"@DECEL", 12 },
  { L"@JSPEED", 13 }, { L"@JACCEL", 14 }, { L"@JDECEL", 15 },
  { L"@EXTSPEED", 16 }, { L"@EXTACCEL", 17 }, { L"@EXTDECEL", 18 },
  { L"@HIGH_CURRENT_POSITION", 19 },
  { L"@HIGH_CURRENT_ANGLE", 20 },
  { L"@HIGH_CURRENT_TRANS", 21 },
  { L"@DEST_ANGLE", 22 }, { L"@DEST_POSITION", 23 }, { L"@DEST_TRANS", 24 },
};

std::map<std::wstring, int> TaskVariables={
  { L"@STATUS", 1 },
  { L"@PRIORITY", 2 },
  { L"@LINE_NO", 3 },
  { L"@CYCLE_TIME", 4 },
  { L"@START", 5 },
  { L"@STOP", 6 },
  { L"@ELAPSED_TIME", 7 },
  { L"@STATUS_DETAILS", 8 }
};

/**********************************************/
#if 0
YAML::Node
load_param_file(const char *fname)
{
  YAML::Node m_config;
  try{
    m_config=YAML::LoadFile(fname);
  }catch(...){
    std::cerr << "Fail to load: " << fname << std::endl;
  }
  return m_config;
}
#endif

std::string ConvertWstringToUTF8(std::wstring& src) {
  std::wstring_convert<std::codecvt_utf8<wchar_t> > converter;
  return converter.to_bytes(src);
}

std::vector<std::string>
load_csv_file(std::string fname)
{
  std::string str_buf;
  std::string str_comma_buf;
  std::ifstream ifs(fname);
  int i=0;
  std::vector<std::string> res;

  while(getline(ifs, str_buf)){
    std::istringstream i_stream(str_buf);
    while(getline(i_stream, str_comma_buf, ',')){
        res.push_back(str_comma_buf); 
    }
  }
  return res;
}

void
load_int_value(std::string fname)
{
#if DEBUG
  std::cerr << "load_int_value: " << fname << std::endl;
#endif
  auto v = load_csv_file(fname);
  int i=0;
  std::for_each(v.begin(), v.end(), [&i](const std::string& x) {
    if (i < 100){
      I_Values[i++] = std::stoi(x);
    }
  });
  return;
}

void
load_float_value(std::string fname)
{
#if DEBUG
  std::cerr << "load_float_value: " << fname << std::endl;
#endif
  auto v = load_csv_file(fname);
  int i=0;
  std::for_each(v.begin(), v.end(), [&i](const std::string& x) {
    if (i < 100){  F_Values[i++] = std::stof(x); }
  });
  return;
}

void
save_csv_file(std::string fname, std::vector<std::string> v)
{
  std::ofstream ofs(fname);
  int i=0;

  std::for_each(v.begin(), v.end(), [&i, &ofs](const std::string& x) {
    ofs << x << ",";
    i++;
    if( (i % 10 ) == 0){
      ofs << std::endl;
    }
  });

  return;
}

void 
save_int_value(std::string fname){
  std::vector<std::string> val;
  for(int i=0; i<100;i++){
    val.push_back(std::to_string(I_Values[i]));
  }
  save_csv_file(fname, val);
#if DEBUG
  std::cerr << "save_int_value: " << fname << std::endl;
#endif
  return;
}

void 
save_float_value(std::string fname){
  std::vector<std::string> val;
  for(int i=0; i<100;i++){
    val.push_back(std::to_string(F_Values[i]));
  }
  save_csv_file(fname, val);
#if DEBUG
  std::cerr << "save_float_value: " << fname << std::endl;
#endif
  return;
}

wchar_t* convToWString(const std::string& in)
{
  wchar_t* buffer = new wchar_t[in.size() +1];
  mbstowcs(buffer, in.c_str(), in.size());
  return buffer;
}

wchar_t *intToWstring(int v)
{
  std::ostringstream ss;
  ss << std::setw(8) << std::setfill('0') << std::hex << v;
  return convToWString(ss.str());
}

/**************************************/
HRESULT
get_controller_variable_handle(int32_t *handle, BSTR bstr)
{
  int32_t val;
  std::wstring name(bstr);

  if(name.compare(0,1, L"@")==0){
    auto it = ControllerVariables.find(name);
    if (it != ControllerVariables.end()){
      val = it->second | CTRL_VAL;
    }else{
      return (HRESULT)(-1); 
    }

  }else if(name.compare(0,1, L"I")==0){
    try{
      val=std::stoi(name.substr(1));
      val |= I_VAL;
    }catch(...){
      std::cerr << "===ERROR in get_variable_handle " << ConvertWstringToUTF8(name)
	       << std::endl;
      return -1;
    }

  }else if(name.compare(0,1, L"F")==0){
    try{
      val=std::stoi(name.substr(1));
      val |= F_VAL;
    }catch(...){
      std::cerr << "===ERROR in get_variable_handle " << ConvertWstringToUTF8(name)
	      << std::endl;
      return -1;
    }
  }
  *handle = val;

  return S_OK;
}

HRESULT
get_robot_variable_handle(int32_t *handle, BSTR bstr)
{
  int32_t val;
  std::wstring name(bstr);

  if(name.compare(0,1, L"@")==0){
    auto it = RobotVariables.find(name);
    if (it != RobotVariables.end()){
      val = it->second | ROBOT_VAL;
      *handle = val;
    }else{
      return (HRESULT)(-1); 
    }
  }
  return S_OK;
}

HRESULT
get_task_variable_handle(int32_t *handle, BSTR bstr)
{
  int32_t val;
  std::wstring name(bstr);

  if(name.compare(0,1, L"@")==0){
    auto it = TaskVariables.find(name);
    if (it != TaskVariables.end()){
      val = it->second | TASK_VAL;
      *handle = val;
    }else{
      return (HRESULT)(-1); 
    }
  }
  return S_OK;
}

void
get_variable_value(int32_t h, VARIANT *v)
{
  if(h & I_VAL){
    h = GET_HANDLE(h);
    v->vt = VT_I4;
    v->lVal = I_Values[h];
#if DEBUG
    std::cerr << "Gut I" << h << " = " <<v->lVal << std::endl;
#endif

  }else if(h & F_VAL){
    h = GET_HANDLE(h);
    v->vt = VT_R4;
    v->fltVal = F_Values[h];

  }else if(h & CTRL_VAL){
    h = GET_HANDLE(h);

    if (h == 18){
      int code = (ControllerValues+17)->lVal;
      v->vt = VT_BSTR;
      v->bstrVal = intToWstring(code);
    }else{
      VariantCopy(v, ControllerValues+h);
    }

  }else if(h & ROBOT_VAL){
    h = GET_HANDLE(h);
    VariantCopy(v, RobotValues+h);

  }else if(h & TASK_VAL){
    h = GET_HANDLE(h);
    VariantCopy(v, TaskValues+h);

  }else{
    printf("Unknown %d\n", h);
  }
  return;
}

void
put_variable_value(int32_t h, VARIANT v)
{
  if(h & I_VAL){
    h = GET_HANDLE(h);
    I_Values[h]=v.lVal;
#if DEBUG
    std::cerr << "Put I" << h << " = " <<v.lVal << std::endl;
#endif

  }else if(h & F_VAL){
    h = GET_HANDLE(h);
    if (v.vt == VT_R4){
      F_Values[h]=v.fltVal;
    }else if (v.vt == VT_R8){
      F_Values[h]=(float)v.dblVal;
    }else if (v.vt == VT_I4){
      F_Values[h]=(float)v.lVal;
    }

  }else if(h & CTRL_VAL){
    h = GET_HANDLE(h);
    VariantCopy(ControllerValues+h, &v);

    if (h == 17 && v.lVal == 0){
      VARIANT val2 = {VT_BSTR, 0};
      VariantCopy(ControllerValues+19, &val2);
    }
   

  }else if(h & ROBOT_VAL){
    h = GET_HANDLE(h);
    VariantCopy(RobotValues+h, &v);

  }else if(h & TASK_VAL){
    h = GET_HANDLE(h);
    VariantCopy(TaskValues+h, &v);

  }
  return;
}
