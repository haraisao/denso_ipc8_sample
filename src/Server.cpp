/*
 *
 */
#include "rc8server.h"


static int task_sleep_time=0;
static int task_status=0;
static int n_joints=6;
static double joint_angles[]={0,0,30,0,0,0};

time_t start_time;
/***************/
BSTR convToBstr(const std::string& input)
{
#if 0
  size_t i;
  wchar_t* buffer = new wchar_t[input.size()+1];
  mbstowcs(buffer, input.c_str(), input.size());
  return buffer;
#else
  wchar_t* chDest = NULL;
  const char *chSrc = input.c_str();
  int iLen = mbstowcs(NULL, chSrc, 0) + 1;
  if(iLen > 0) {
    chDest = (wchar_t*)malloc(sizeof(wchar_t)*iLen);
    if(chDest == NULL) return NULL;
    mbstowcs(chDest, chSrc, iLen);
  }
  return chDest;
#endif
}

char *convToStr(BSTR bstr)
{
#if 0
  size_t i;
  std::wstring ws(bstr);
  char *buffer=new char[ws.length() +1];
  memset(buffer,0, ws.length() +1);
  wcstombs(buffer, ws.c_str(), ws.size());
  return buffer;
#else
  char* chDest = NULL;
  int iLen = wcstombs(NULL, bstr, 0) + 1;
   if(iLen > 0) {
    chDest = (char*)malloc(iLen);
    if(chDest == NULL) return NULL;
    wcstombs(chDest, bstr, iLen);
  }
  return chDest;
#endif
}

void msleep(int msec)
{
  if(msec < 0) return;
  int sec = msec / 1000;
  int usec = (msec % 1000) * 1000;
  sleep(sec);
  usleep(usec);
  return;
}

double get_current_time()
{
   int ct = time(NULL) - start_time;
   return (double)ct*1000;
}

int
get_int_value_from_variant(VARIANT *vnt, int *val){
  int ret = 0;
  if (vnt->vt == VT_I2){
    *val = vnt->iVal;
  } else if (vnt->vt == VT_I4) {
     *val = vnt->lVal;
  } else if (vnt->vt == VT_I8) {
     *val = vnt->llVal;
  } else if (vnt->vt == VT_BOOL) {
     *val = vnt->boolVal;
  } else if (vnt->vt == VT_ERROR) {
     *val = vnt->scode;
  } else if (vnt->vt == VT_UI1) {
     *val = vnt->bVal;
  } else if (vnt->vt == VT_UI2) {
     *val = vnt->uiVal;
  } else if (vnt->vt == VT_UI4) {
     *val = vnt->ulVal;
  } else if (vnt->vt == VT_UI8) {
     *val = vnt->ullVal;
  } else{
    ret = -1;
  }
  return ret;
}

int
get_double_value_from_variant(VARIANT *vnt, double *val){
  int ret = 0;
  if (vnt->vt == VT_R4){
    *val = vnt->fltVal;
  } else if (vnt->vt == VT_R8) {
     *val = vnt->dblVal;
  } else{
    ret = -1;
  }
  return ret;
}

int
bstr_comp(VARIANT *vnt, const wchar_t *s){
  if (vnt->vt == VT_BSTR){
    return wcscmp(vnt->bstrVal, s);
  }
  return -1;
}

/**************/
HRESULT
ServiceStart(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ServiceStart", vntArgs, Argc);
  std::cerr << "ServiceStart ==>" << std::endl;
  return S_OK;
}

HRESULT
ServiceStop(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ServiceStop", vntArgs, Argc);
  std::cerr << "<== ServiceStop" << std::endl;
  return S_OK;
}

HRESULT
ControllerConnect(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ControllerConnect", vntArgs, Argc);
  std::cerr << "ControllerConnect ==>" << std::endl;

  vntRet->vt = VT_I4;
  vntRet->lVal = 1L;

  return S_OK;
}

HRESULT
ControllerDisconnect(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ControllerDisconnect", vntArgs, Argc);
  std::cerr << "<== ControllerDisconnect" << std::endl;
  return S_OK;
}

HRESULT
ControllerGetRobot(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ControllerGetRobot", vntArgs, Argc);
  std::cerr << "ControllerGetRobot ==>" << std::endl;
  ////
  vntRet->vt = VT_I4;
  vntRet->lVal = 4L;

  return S_OK;
}

HRESULT
ControllerGetTask(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ControllerGetTask", vntArgs, Argc);
  std::string name(convToStr(vntArgs[1].bstrVal));
  /**
  std::string cwd;
  char *dir_ = std::getenv("RC8SERVER_DIR");
  if (dir_){
    cwd = std::string(dir_);
  }else{
    cwd = std::string("/usr/local/rc8server/");
  }
  std::vector<std::string> f_list=GetTaskNames(cwd+"config/scripts");
  */
  int val = GetTaskTime(name);
  //int val = ReadTaskTime(f_list, name);
#if DEBUG
  std::cerr << "ControllerGetTask: " << name << "(" << val << ")" << std::endl;
#endif

  if (val < 0){ return HRESULT(-1); }

  task_sleep_time=val;
  task_status=2;
  ///
  vntRet->vt = VT_I4;
  vntRet->lVal = 5L;
  /// T.B.D.

  return S_OK;
}

HRESULT
ControllerGetVariable(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ControllerGetVariable", vntArgs, Argc);
  if(Argc < 3){ return (HRESULT)(-1); }

  vntRet->vt = VT_I4;
  vntRet->lVal = 6L;

  return get_controller_variable_handle(&vntRet->lVal, vntArgs[1].bstrVal);
}

HRESULT
ControllerGetTaskNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // T.B.D
  BSTR* pData;
  print_args("ControllerGetTaskNames", vntArgs, Argc);
#if DEBUG
  std::cerr << "ControllerGetTaskNames" << std::endl;
#endif

  std::string cwd;
  char *dir_ = std::getenv("RC8SERVER_DIR");
  if (dir_){
    cwd = std::string(dir_);
  }else{
    cwd = std::string("/usr/local/rc8server/");
  }
  std::vector<std::string> f_list=GetTaskNames(cwd+"config/scripts");
  LoadTaskList();

  vntRet->vt = VT_BSTR | VT_ARRAY;
  vntRet->parray = SafeArrayCreateVector(VT_BSTR, 0L, (int)f_list.size());
  SafeArrayAccessData(vntRet->parray, (void **) &pData);
  int i=0;
  std::for_each(f_list.begin(), f_list.end(), [&i, &pData](const std::string& x) {
    pData[i++] = convToBstr(x);
  });

  SafeArrayUnaccessData(vntRet->parray);

  return S_OK;
}

HRESULT
ControllerExecute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  //T.B.D
  print_args("ControllerExecute", vntArgs, Argc);
  // ClearError, GetErrorLogCount, GetErrorLog
  // GetOprLogCount, GetOprLog
  std::string cmd(convToStr(vntArgs[1].bstrVal));

  if (cmd == "GetErrorLogCount"){
    vntRet->vt = VT_I4;
    vntRet->lVal = 0L;

  }else if (cmd == "GetOprLogCount"){
    vntRet->vt = VT_I4;
    vntRet->lVal = 0L;

  }else if (cmd == "ClearError"){
    put_error_value(0);

  }else{
    std::cerr << "ControllerExecute:" <<  cmd << std::endl;
  }
  
  return S_OK;
}

HRESULT
RobotGetVariable(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("RobotGetVariable", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 12L;

  return get_robot_variable_handle(&vntRet->lVal, vntArgs[1].bstrVal);
}

/**
 *  slvMove: 
 *    S_OK：　0x00000000
 *    指令値生成遅延：　0x84291482
 *    S_BUF_FULL, バッファフル：　0x0F200501
 *    E_BUF_FULL, バッファオーバーフロー：　0x83201483
 */
HRESULT
RobotExecute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("RobotExecute", vntArgs, Argc);
  // TakeArm, GiveArm, Motor, ExtSpeed, OutRange, CurPos, CurJnt, CurFig
  std::string cmd(convToStr(vntArgs[1].bstrVal));
    
  if (cmd == "ExtSpeed"){
    get_variable_value( (16 & ROBOT_VAL), vntRet);
#if DEBUG
    std::cerr << "ExtSpeed:" << vntRet->fltVal << std::endl;
#endif
  }else if (cmd == "HighCurJntEx"){
    double *pData;
    vntRet->vt = VT_R8 | VT_ARRAY;
    vntRet->parray = SafeArrayCreateVector(VT_R8, 0, 7);
    SafeArrayAccessData(vntRet->parray, (void **) &pData);
    pData[0] = get_current_time();
    for(int i=1; i <= n_joints; i++){
      pData[i] = joint_angles[i-1];
    }
   SafeArrayUnaccessData(vntRet->parray);
  }else if (cmd == "slvMove"){
#if 1
    int32_t err = get_error_value();
    if (err > 0){
      std::cerr << "ERROR :" << err << std::endl;
      return err;
    }
#endif
    if (Argc == 3) {
      double *pData;
      if(vntArgs[2].vt == VT_R8 | VT_ARRAY){
        SafeArrayAccessData(vntArgs[2].parray, (void **) &pData);
	      for(int i=0;i<N_AXIS;i++){
          joint_angles[i] = pData[i];
      	}
        SafeArrayUnaccessData(vntArgs[2].parray);
      }
      vntRet->vt = VT_R8 | VT_ARRAY;
      vntRet->parray = SafeArrayCreateVector(VT_R8, 0, n_joints+2);
      SafeArrayAccessData(vntRet->parray, (void **) &pData);
      pData[0] = get_current_time();
      for(int i=0; i < n_joints; i++){
        pData[i] = joint_angles[i];
      }
      SafeArrayUnaccessData(vntRet->parray);
      usleep(6800);

      put_joint_values(pData);

    } else {
      return E_FAIL;
    }
  }else{
    std::cerr << ">>> RobotExecute:"  <<cmd << std::endl;
  }
  return S_OK;
}

HRESULT
RobotMove(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("RobotMove", vntArgs, Argc);

  int comp;
  if (get_int_value_from_variant(&vntArgs[1], &comp) < 0){
    std::cerr << "RobotMove: Invalid Comp..." << std::endl;
  };
  std::cerr << "RobotMove:" << std::endl;
  if (vntArgs[2].vt = (VT_ARRAY | VT_VARIANT)){
    
    void *pData;
    SafeArrayAccessData(vntArgs[2].parray, &pData);
    if (bstr_comp((VARIANT *)pData+1, L"J") == 0){
      double *data;
      VARIANT *vnt = (VARIANT *)pData;
      if(vnt->vt == VT_R8 | VT_ARRAY){
        SafeArrayAccessData(vnt->parray, (void **) &data);
        std::cerr << "  J: [";
        for(int i=0;i<6;i++){
          joint_angles[i] = data[i];
          std::cerr << data[i] << ", ";
      	}
        std::cerr << "]" << std::endl;
        SafeArrayUnaccessData(vnt->parray);
        usleep(1000*100);
        put_joint_values(data);
      }
    }else{
      print_variant(&vntArgs[2], 1);
      print_variant((VARIANT *)pData+1, 1);
      print_variant((VARIANT *)pData+2, 1);
    }
  }else{
    print_args2("RobotMove", vntArgs, Argc);
  }
  return S_OK;
}

HRESULT
RobotRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("RobotRelease", vntArgs, Argc);
  std::cerr << "<== RobotRelease" << std::endl;

  return S_OK;
}

HRESULT
TaskGetVariable(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("TaskGetVariable", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 13L;

  return get_task_variable_handle(&vntRet->lVal, vntArgs[1].bstrVal);
}

HRESULT
TaskExecute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("TaskExecute", vntArgs, Argc);
  // GetStatus
  std::string cmd(convToStr(vntArgs[1].bstrVal));
  if(cmd == "GetStatus"){
    vntRet->vt = VT_I4;
    vntRet->lVal = task_status;  // 0: Not exists, 1: Suspend, 2: Ready, 3: Running, 4: StepStop
#if DEBUG
    std::cerr << "TaskExecute: GetStatus" << std::endl;
#endif
  }else{
    std::cerr << "TaskExecite   " << cmd << std::endl;
  }
  return S_OK;
}

HRESULT
TaskStart(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // T.B.D
  print_args("TaskStart", vntArgs, Argc);
#if DEBUG
  std::cerr << "TaskStart: " << std::endl;
#endif
  task_status=3;
  msleep(task_sleep_time);
  task_status=2;
#if DEBUG
  std::cerr << "TaskStart: END" << std::endl;
#endif
  return S_OK;
}

HRESULT
TaskStop(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // T.B.D
  print_args("TaskStop", vntArgs, Argc);
  std::cerr << "TaskStop " <<  std::endl;

  return S_OK;
}

HRESULT
TaskRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // T.B.D
  print_args("TaskRelease", vntArgs, Argc);
  std::cerr << "<== TaskRelease" <<  std::endl;
  task_sleep_time=0;
  task_status=0;

  return S_OK;
}


HRESULT
VariableGetValue(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("VariableGetValue", vntArgs, Argc);
  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;
  get_variable_value( vntArgs[0].lVal, vntRet);
  return S_OK;
}

HRESULT
VariablePutValue(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("VariablePutValue", vntArgs, Argc);
  put_variable_value(vntArgs[0].lVal, vntArgs[1]);
  return S_OK;
}


HRESULT
VariableRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("VariableRelease", vntArgs, Argc);
  return S_OK;
}

void
SetCallFunctions()
{
  bCap_SetCallFunc(ID_SERVICE_START, &ServiceStart);
  bCap_SetCallFunc(ID_SERVICE_STOP, &ServiceStop);
  bCap_SetCallFunc(ID_CONTROLLER_CONNECT, &ControllerConnect);
  bCap_SetCallFunc(ID_CONTROLLER_DISCONNECT, &ControllerDisconnect);
  bCap_SetCallFunc(ID_CONTROLLER_GETEXTENSION, &ControllerGetExtension);
  bCap_SetCallFunc(ID_CONTROLLER_GETFILE, &ControllerGetFile);
  bCap_SetCallFunc(ID_CONTROLLER_GETROBOT, &ControllerGetRobot);
  bCap_SetCallFunc(ID_CONTROLLER_GETTASK, &ControllerGetTask);
  bCap_SetCallFunc(ID_CONTROLLER_GETVARIABLE, &ControllerGetVariable);
  bCap_SetCallFunc(ID_CONTROLLER_GETCOMMAND, &ControllerGetCommand);
  bCap_SetCallFunc(ID_CONTROLLER_GETEXTENSIONNAMES,
      &ControllerGetExtensionNames);
  bCap_SetCallFunc(ID_CONTROLLER_GETFILENAMES, &ControllerGetFileNames);
  bCap_SetCallFunc(ID_CONTROLLER_GETROBOTNAMES, &ControllerGetRobotNames);
  bCap_SetCallFunc(ID_CONTROLLER_GETTASKNAMES, &ControllerGetTaskNames);
  bCap_SetCallFunc(ID_CONTROLLER_GETVARIABLENAMES, &ControllerGetVariableNames);
  bCap_SetCallFunc(ID_CONTROLLER_GETCOMMANDNAMES, &ControllerGetCommandNames);
  bCap_SetCallFunc(ID_CONTROLLER_EXECUTE, &ControllerExecute);
  bCap_SetCallFunc(ID_CONTROLLER_GETMESSAGE, &ControllerGetMessage);
  bCap_SetCallFunc(ID_CONTROLLER_GETATTRIBUTE, &ControllerGetAttribute);
  bCap_SetCallFunc(ID_CONTROLLER_GETHELP, &ControllerGetHelp);
  bCap_SetCallFunc(ID_CONTROLLER_GETNAME, &ControllerGetName);
  bCap_SetCallFunc(ID_CONTROLLER_GETTAG, &ControllerGetTag);
  bCap_SetCallFunc(ID_CONTROLLER_PUTTAG, &ControllerPutTag);
  bCap_SetCallFunc(ID_CONTROLLER_GETID, &ControllerGetID);
  bCap_SetCallFunc(ID_CONTROLLER_PUTID, &ControllerPutID);
  bCap_SetCallFunc(ID_EXTENSION_GETVARIABLE, &ExtensionGetVariable);
  bCap_SetCallFunc(ID_EXTENSION_GETVARIABLENAMES, &ExtensionGetVariableNames);
  bCap_SetCallFunc(ID_EXTENSION_EXECUTE, &ExtensionExecute);
  bCap_SetCallFunc(ID_EXTENSION_GETATTRIBUTE, &ExtensionGetAttribute);
  bCap_SetCallFunc(ID_EXTENSION_GETHELP, &ExtensionGetHelp);
  bCap_SetCallFunc(ID_EXTENSION_GETNAME, &ExtensionGetName);
  bCap_SetCallFunc(ID_EXTENSION_GETTAG, &ExtensionGetTag);
  bCap_SetCallFunc(ID_EXTENSION_PUTTAG, &ExtensionPutTag);
  bCap_SetCallFunc(ID_EXTENSION_GETID, &ExtensionGetID);
  bCap_SetCallFunc(ID_EXTENSION_PUTID, &ExtensionPutID);
  bCap_SetCallFunc(ID_EXTENSION_RELEASE, &ExtensionRelease);
  bCap_SetCallFunc(ID_FILE_GETFILE, &FileGetFile);
  bCap_SetCallFunc(ID_FILE_GETVARIABLE, &FileGetVariable);
  bCap_SetCallFunc(ID_FILE_GETFILENAMES, &FileGetFileNames);
  bCap_SetCallFunc(ID_FILE_GETVARIABLENAMES, &FileGetVariableNames);
  bCap_SetCallFunc(ID_FILE_EXECUTE, &FileExecute);
  bCap_SetCallFunc(ID_FILE_COPY, &FileCopy);
  bCap_SetCallFunc(ID_FILE_DELETE, &FileDelete);
  bCap_SetCallFunc(ID_FILE_MOVE, &FileMove);
  bCap_SetCallFunc(ID_FILE_RUN, &FileRun);
  bCap_SetCallFunc(ID_FILE_GETDATECREATED, &FileGetDateCreated);
  bCap_SetCallFunc(ID_FILE_GETDATELASTACCESSED, &FileGetDateLastAccessed);
  bCap_SetCallFunc(ID_FILE_GETDATELASTMODIFIED, &FileGetDateLastModified);
  bCap_SetCallFunc(ID_FILE_GETPATH, &FileGetPath);
  bCap_SetCallFunc(ID_FILE_GETSIZE, &FileGetSize);
  bCap_SetCallFunc(ID_FILE_GETTYPE, &FileGetType);
  bCap_SetCallFunc(ID_FILE_GETVALUE, &FileGetValue);
  bCap_SetCallFunc(ID_FILE_PUTVALUE, &FilePutValue);
  bCap_SetCallFunc(ID_FILE_GETATTRIBUTE, &FileGetAttribute);
  bCap_SetCallFunc(ID_FILE_GETHELP, &FileGetHelp);
  bCap_SetCallFunc(ID_FILE_GETNAME, &FileGetName);
  bCap_SetCallFunc(ID_FILE_GETTAG, &FileGetTag);
  bCap_SetCallFunc(ID_FILE_PUTTAG, &FilePutTag);
  bCap_SetCallFunc(ID_FILE_GETID, &FileGetID);
  bCap_SetCallFunc(ID_FILE_PUTID, &FilePutID);
  bCap_SetCallFunc(ID_FILE_RELEASE, &FileRelease);
  bCap_SetCallFunc(ID_ROBOT_GETVARIABLE, &RobotGetVariable);
  bCap_SetCallFunc(ID_ROBOT_GETVARIABLENAMES, &RobotGetVariableNames);
  bCap_SetCallFunc(ID_ROBOT_EXECUTE, &RobotExecute);
  bCap_SetCallFunc(ID_ROBOT_ACCELERATE, &RobotAccelerate);
  bCap_SetCallFunc(ID_ROBOT_CHANGE, &RobotChange);
  bCap_SetCallFunc(ID_ROBOT_CHUCK, &RobotChuck);
  bCap_SetCallFunc(ID_ROBOT_DRIVE, &RobotDrive);
  bCap_SetCallFunc(ID_ROBOT_GOHOME, &RobotGoHome);
  bCap_SetCallFunc(ID_ROBOT_HALT, &RobotHalt);
  bCap_SetCallFunc(ID_ROBOT_HOLD, &RobotHold);
  bCap_SetCallFunc(ID_ROBOT_MOVE, &RobotMove);
  bCap_SetCallFunc(ID_ROBOT_ROTATE, &RobotRotate);
  bCap_SetCallFunc(ID_ROBOT_SPEED, &RobotSpeed);
  bCap_SetCallFunc(ID_ROBOT_UNCHUCK, &RobotUnchuck);
  bCap_SetCallFunc(ID_ROBOT_UNHOLD, &RobotUnhold);
  bCap_SetCallFunc(ID_ROBOT_GETATTRIBUTE, &RobotGetAttribute);
  bCap_SetCallFunc(ID_ROBOT_GETHELP, &RobotGetHelp);
  bCap_SetCallFunc(ID_ROBOT_GETNAME, &RobotGetName);
  bCap_SetCallFunc(ID_ROBOT_GETTAG, &RobotGetTag);
  bCap_SetCallFunc(ID_ROBOT_PUTTAG, &RobotPutTag);
  bCap_SetCallFunc(ID_ROBOT_GETID, &RobotGetID);
  bCap_SetCallFunc(ID_ROBOT_PUTID, &RobotPutID);
  bCap_SetCallFunc(ID_ROBOT_RELEASE, &RobotRelease);
  bCap_SetCallFunc(ID_TASK_GETVARIABLE, &TaskGetVariable);
  bCap_SetCallFunc(ID_TASK_GETVARIABLENAMES, &TaskGetVariableNames);
  bCap_SetCallFunc(ID_TASK_EXECUTE, &TaskExecute);
  bCap_SetCallFunc(ID_TASK_START, &TaskStart);
  bCap_SetCallFunc(ID_TASK_STOP, &TaskStop);
  bCap_SetCallFunc(ID_TASK_DELETE, &TaskDelete);
  bCap_SetCallFunc(ID_TASK_GETFILENAME, &TaskGetFileName);
  bCap_SetCallFunc(ID_TASK_GETATTRIBUTE, &TaskGetAttribute);
  bCap_SetCallFunc(ID_TASK_GETHELP, &TaskGetHelp);
  bCap_SetCallFunc(ID_TASK_GETNAME, &TaskGetName);
  bCap_SetCallFunc(ID_TASK_GETTAG, &TaskGetTag);
  bCap_SetCallFunc(ID_TASK_PUTTAG, &TaskPutTag);
  bCap_SetCallFunc(ID_TASK_GETID, &TaskGetID);
  bCap_SetCallFunc(ID_TASK_PUTID, &TaskPutID);
  bCap_SetCallFunc(ID_TASK_RELEASE, &TaskRelease);
  bCap_SetCallFunc(ID_VARIABLE_GETDATETIME, &VariableGetDateTime);
  bCap_SetCallFunc(ID_VARIABLE_GETVALUE, &VariableGetValue);
  bCap_SetCallFunc(ID_VARIABLE_PUTVALUE, &VariablePutValue);
  bCap_SetCallFunc(ID_VARIABLE_GETATTRIBUTE, &VariableGetAttribute);
  bCap_SetCallFunc(ID_VARIABLE_GETHELP, &VariableGetHelp);
  bCap_SetCallFunc(ID_VARIABLE_GETNAME, &VariableGetName);
  bCap_SetCallFunc(ID_VARIABLE_GETTAG, &VariableGetTag);
  bCap_SetCallFunc(ID_VARIABLE_PUTTAG, &VariablePutTag);
  bCap_SetCallFunc(ID_VARIABLE_GETID, &VariableGetID);
  bCap_SetCallFunc(ID_VARIABLE_PUTID, &VariablePutID);
  bCap_SetCallFunc(ID_VARIABLE_GETMICROSECOND, &VariableGetMicrosecond);
  bCap_SetCallFunc(ID_VARIABLE_RELEASE, &VariableRelease);
  bCap_SetCallFunc(ID_COMMAND_EXECUTE, &CommandExecute);
  bCap_SetCallFunc(ID_COMMAND_CANCEL, &CommandCancel);
  bCap_SetCallFunc(ID_COMMAND_GETTIMEOUT, &CommandGetTimeout);
  bCap_SetCallFunc(ID_COMMAND_PUTTIMEOUT, &CommandPutTimeout);
  bCap_SetCallFunc(ID_COMMAND_GETSTATE, &CommandGetState);
  bCap_SetCallFunc(ID_COMMAND_GETPARAMETERS, &CommandGetParameters);
  bCap_SetCallFunc(ID_COMMAND_PUTPARAMETERS, &CommandPutParameters);
  bCap_SetCallFunc(ID_COMMAND_GETRESULT, &CommandGetResult);
  bCap_SetCallFunc(ID_COMMAND_GETATTRIBUTE, &CommandGetAttribute);
  bCap_SetCallFunc(ID_COMMAND_GETHELP, &CommandGetHelp);
  bCap_SetCallFunc(ID_COMMAND_GETNAME, &CommandGetName);
  bCap_SetCallFunc(ID_COMMAND_GETTAG, &CommandGetTag);
  bCap_SetCallFunc(ID_COMMAND_PUTTAG, &CommandPutTag);
  bCap_SetCallFunc(ID_COMMAND_GETID, &CommandGetID);
  bCap_SetCallFunc(ID_COMMAND_PUTID, &CommandPutID);
  bCap_SetCallFunc(ID_COMMAND_RELEASE, &CommandRelease);
  bCap_SetCallFunc(ID_MESSAGE_REPLY, &MessageReply);
  bCap_SetCallFunc(ID_MESSAGE_CLEAR, &MessageClear);
  bCap_SetCallFunc(ID_MESSAGE_GETDATETIME, &MessageGetDateTime);
  bCap_SetCallFunc(ID_MESSAGE_GETDESCRIPTION, &MessageGetDescription);
  bCap_SetCallFunc(ID_MESSAGE_GETDESTINATION, &MessageGetDestination);
  bCap_SetCallFunc(ID_MESSAGE_GETNUMBER, &MessageGetNumber);
  bCap_SetCallFunc(ID_MESSAGE_GETSERIALNUMBER, &MessageGetSerialNumber);
  bCap_SetCallFunc(ID_MESSAGE_GETSOURCE, &MessageGetSource);
  bCap_SetCallFunc(ID_MESSAGE_GETVALUE, &MessageGetValue);
  bCap_SetCallFunc(ID_MESSAGE_RELEASE, &MessageRelease);
}

/*****/
int fd = 0;
int fd1 = 0;

void sig_handler(int signum) {
  fprintf(stderr, "==== Catch Signal Ctrl-C\n");
  bCap_Close_Server(&fd);
  bCap_Close_Server(&fd1);
  return;
}

/**
 *
 *
 */
int
main(void)
{
  HRESULT hr;
  start_time = time(NULL);

  if (signal(SIGINT, sig_handler) == SIG_ERR) {
     std::cerr << "===== Signal Error =====" << std::endl;
     exit(1);
  }

  std::cerr << "--- start " << std::endl;
  char *dir_ = std::getenv("RC8SERVER_DIR");
  std::string cwd;
  if (dir_){
    cwd = std::string(dir_);
  }else{
    cwd = std::string("/usr/local/rc8server/");
  }

  SetCallFunctions();
  load_int_value(cwd+"config/int_val.csv");
  load_float_value(cwd+"config/float_val.csv");

  LoadTaskList();

  hr = bCap_Open_Server("tcp", 1000, &fd);
  hr = bCap_Open_Server("udp", 1000, &fd1);
  if (SUCCEEDED(hr)) {
    while(fd && fd1){
      usleep(300000);
    }
  }
  save_int_value(cwd+"config/int_val.csv");
  save_float_value(cwd+"config/float_val.csv");
  return 0;
}
