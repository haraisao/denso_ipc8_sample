#include "bCAPServerSample.h"


/***************/
BSTR convToBstr(const std::string& input)
{
  size_t i;
  wchar_t* buffer = new wchar_t[input.size()+1];
  mbstowcs(buffer, input.c_str(), input.size());
  return buffer;
}

char *convToStr(BSTR bstr)
{
  size_t i;
  std::wstring ws(bstr);
  char *buffer=new char[ws.length() +1];
  wcstombs(buffer, ws.c_str(), ws.size());
  return buffer;
}

/**************/
static HRESULT
ServiceStart(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ServiceStart", vntArgs, Argc);
  return S_OK;
}

static HRESULT
ServiceStop(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ServiceStop", vntArgs, Argc);
  return S_OK;
}

static HRESULT
ControllerConnect(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ControllerConnect", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 1L;

  return S_OK;
}

static HRESULT
ControllerDisconnect(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ControllerDisconnect", vntArgs, Argc);
  return S_OK;
}

static HRESULT
ControllerGetRobot(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ControllerGetRobot", vntArgs, Argc);
  ////
  vntRet->vt = VT_I4;
  vntRet->lVal = 4L;

  return S_OK;
}

static HRESULT
ControllerGetTask(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ControllerGetTask", vntArgs, Argc);
  std::string name(convToStr(vntArgs[1].bstrVal));
  std::vector<std::string> f_list=GetTaskNames("config/scripts");

  ///
  vntRet->vt = VT_I4;
  vntRet->lVal = 5L;
  /// T.B.D.
 

  return S_OK;
}

static HRESULT
ControllerGetVariable(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("ControllerGetVariable", vntArgs, Argc);
  if(Argc < 3){ return (HRESULT)(-1); }

  vntRet->vt = VT_I4;
  vntRet->lVal = 6L;

  return get_controller_variable_handle(&vntRet->lVal, vntArgs[1].bstrVal);
}



static HRESULT
ControllerGetTaskNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // T.B.D
  BSTR* pData;
  print_args("ControllerGetTaskNames", vntArgs, Argc);

  std::vector<std::string> f_list=GetTaskNames("config/scripts");

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

static HRESULT
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

  }else{
    std::cerr << cmd << std::endl;
  }
  
  return S_OK;
}


static HRESULT
RobotGetVariable(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("RobotGetVariable", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 12L;

  return get_robot_variable_handle(&vntRet->lVal, vntArgs[1].bstrVal);

}

static HRESULT
RobotExecute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("RobotExecute", vntArgs, Argc);
  // TakeArm, GiveArm, Motor, ExtSpeed, OutRange, CurPos, CurJnt, CurFig
  std::string cmd(convToStr(vntArgs[1].bstrVal));
  std::cerr << cmd << std::endl;
    
  if (cmd == "ExtSpeed"){
    vntRet->vt = VT_R4;
    vntRet->fltVal = 10.0;
    get_variable_value( (16 & ROBOT_VAL), vntRet);

  }else{
    std::cerr << cmd << std::endl;
  }
  return S_OK;
}

static HRESULT
RobotMove(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("RobotMove", vntArgs, Argc);
  // T.B.D

  return S_OK;
}

static HRESULT
RobotRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("RobotRelease", vntArgs, Argc);

  return S_OK;
}

static HRESULT
TaskGetVariable(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("TaskGetVariable", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 13L;

  return get_task_variable_handle(&vntRet->lVal, vntArgs[1].bstrVal);

}

static HRESULT
TaskExecute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("TaskExecute", vntArgs, Argc);
  // GetStatus
  std::string cmd(convToStr(vntArgs[1].bstrVal));
  std::cerr << cmd << std::endl;
  if(cmd == "GetStatus"){
    vntRet->vt = VT_I4;
    vntRet->lVal = 2L;  // 0: Not exists, 1: Suspend, 2: Ready, 3: Running, 4: StepStop
  }
  return S_OK;
}

static HRESULT
TaskStart(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // T.B.D
  print_args("TaskStart", vntArgs, Argc);

  return S_OK;
}

static HRESULT
TaskStop(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // T.B.D
  print_args("TaskStop", vntArgs, Argc);

  return S_OK;
}

static HRESULT
TaskRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // T.B.D
  print_args("TaskRelease", vntArgs, Argc);

  return S_OK;
}


static HRESULT
VariableGetValue(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("VariableGetValue", vntArgs, Argc);
  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;
  get_variable_value( vntArgs[0].lVal, vntRet);
  return S_OK;
}

static HRESULT
VariablePutValue(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("VariablePutValue", vntArgs, Argc);
  put_variable_value(vntArgs[0].lVal, vntArgs[1]);
  return S_OK;
}


static HRESULT
VariableRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  print_args("VariableRelease", vntArgs, Argc);
  return S_OK;
}

static void
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

int
main(void)
{
  int fd = 0;
  HRESULT hr;

  SetCallFunctions();
  load_int_value("config/int_val.csv");
  load_float_value("config/float_val.csv");

  hr = bCap_Open_Server("tcp", 1000, &fd);
  if (SUCCEEDED(hr)) {
    getchar();
    bCap_Close_Server(&fd);
  }
  save_int_value("config/int_val.csv");
  save_float_value("config/float_val.csv");
  return 0;
}
