/*
 *
 */
#include "rc8server.h"


HRESULT
ControllerGetExtension(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ControllerGetExtension", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 2L;

  return S_OK;
}

HRESULT
ControllerGetFile(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ControllerGetFile", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 3L;

  return S_OK;
}


HRESULT
ControllerGetCommand(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ControllerGetCommand", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 7L;

  return S_OK;
}

HRESULT
ControllerGetExtensionNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  BSTR* pData;
  print_args("ControllerGetExtensionNames", vntArgs, Argc);

  vntRet->vt = VT_BSTR | VT_ARRAY;
  vntRet->parray = SafeArrayCreateVector(VT_BSTR, 0L, 2L);
  SafeArrayAccessData(vntRet->parray, (void **) &pData);
  pData[0] = SysAllocString(L"Controller Extension1");
  pData[1] = SysAllocString(L"Controller Extension2");
  SafeArrayUnaccessData(vntRet->parray);

  return S_OK;
}

HRESULT
ControllerGetFileNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  BSTR* pData;
  print_args("ControllerGetFileNames", vntArgs, Argc);

  vntRet->vt = VT_BSTR | VT_ARRAY;
  vntRet->parray = SafeArrayCreateVector(VT_BSTR, 0L, 2L);
  SafeArrayAccessData(vntRet->parray, (void **) &pData);
  pData[0] = SysAllocString(L"Controller File1");
  pData[1] = SysAllocString(L"Controller File2");
  SafeArrayUnaccessData(vntRet->parray);

  return S_OK;
}

HRESULT
ControllerGetRobotNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  BSTR* pData;
  print_args("ControllerGetRobotNames", vntArgs, Argc);

  vntRet->vt = VT_BSTR | VT_ARRAY;
  vntRet->parray = SafeArrayCreateVector(VT_BSTR, 0L, 2L);
  SafeArrayAccessData(vntRet->parray, (void **) &pData);
  pData[0] = SysAllocString(L"Controller Robot1");
  pData[1] = SysAllocString(L"Controller Robot2");
  SafeArrayUnaccessData(vntRet->parray);

  return S_OK;
}


HRESULT
ControllerGetVariableNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  BSTR* pData;
  print_args("ControllerGetVariableNames", vntArgs, Argc);

  vntRet->vt = VT_BSTR | VT_ARRAY;
  vntRet->parray = SafeArrayCreateVector(VT_BSTR, 0L, 2L);
  SafeArrayAccessData(vntRet->parray, (void **) &pData);
  pData[0] = SysAllocString(L"Controller Variable1");
  pData[1] = SysAllocString(L"Controller Variable2");
  SafeArrayUnaccessData(vntRet->parray);

  return S_OK;
}

HRESULT
ControllerGetCommandNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  BSTR* pData;
  print_args("ControllerGetCommandNames", vntArgs, Argc);

  vntRet->vt = VT_BSTR | VT_ARRAY;
  vntRet->parray = SafeArrayCreateVector(VT_BSTR, 0L, 2L);
  SafeArrayAccessData(vntRet->parray, (void **) &pData);
  pData[0] = SysAllocString(L"Controller Command1");
  pData[1] = SysAllocString(L"Controller Command2");
  SafeArrayUnaccessData(vntRet->parray);

  return S_OK;
}

HRESULT
ControllerGetMessage(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ControllerGetMessage", vntArgs, Argc);

  if ((rand() % 100) == 1) {
    vntRet->vt = VT_I4;
    vntRet->lVal = 8L;
    return S_OK;
  } else {
    return S_FALSE;
  }
}

HRESULT
ControllerGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ControllerGetAttribute", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
ControllerGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ControllerGetHelp", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Controller Help");

  return S_OK;
}

HRESULT
ControllerGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ControllerGetName", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Controller Name");

  return S_OK;
}

HRESULT
ControllerGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ControllerGetTag", vntArgs, Argc);

  vntRet->vt = VT_EMPTY;

  return S_OK;
}

HRESULT
ControllerPutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ControllerPutTag", vntArgs, Argc);

  return S_OK;
}

HRESULT
ControllerGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ControllerGetID", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
ControllerPutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ControllerPutID", vntArgs, Argc);

  return S_OK;
}

HRESULT
ExtensionGetVariable(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ExtensionGetVariable", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 9L;

  return S_OK;
}

HRESULT
ExtensionGetVariableNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  BSTR* pData;
  print_args("ExtensionGetVariableNames", vntArgs, Argc);

  vntRet->vt = VT_BSTR | VT_ARRAY;
  vntRet->parray = SafeArrayCreateVector(VT_BSTR, 0L, 2L);
  SafeArrayAccessData(vntRet->parray, (void **) &pData);
  pData[0] = SysAllocString(L"Extension Variable1");
  pData[1] = SysAllocString(L"Extension Variable2");
  SafeArrayUnaccessData(vntRet->parray);

  return S_OK;
}

HRESULT
ExtensionExecute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ExtensionExecute", vntArgs, Argc);

  return S_OK;
}

HRESULT
ExtensionGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ExtensionGetAttribute", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
ExtensionGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ExtensionGetHelp", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Extension Help");

  return S_OK;
}

HRESULT
ExtensionGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ExtensionGetName", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Extension Name");

  return S_OK;
}

HRESULT
ExtensionGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ExtensionGetTag", vntArgs, Argc);

  vntRet->vt = VT_EMPTY;

  return S_OK;
}

HRESULT
ExtensionPutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ExtensionPutTag", vntArgs, Argc);

  return S_OK;
}

HRESULT
ExtensionGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ExtensionGetID", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0;

  return S_OK;
}

HRESULT
ExtensionPutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ExtensionPutID", vntArgs, Argc);

  return S_OK;
}

HRESULT
ExtensionRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("ExtensionRelease", vntArgs, Argc);

  return S_OK;
}

HRESULT
FileGetFile(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetFile", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 10L;

  return S_OK;
}

HRESULT
FileGetVariable(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetVariable", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 11L;

  return S_OK;
}

HRESULT
FileGetFileNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  BSTR* pData;
  print_args("FileGetFileNames", vntArgs, Argc);

  vntRet->vt = VT_BSTR | VT_ARRAY;
  vntRet->parray = SafeArrayCreateVector(VT_BSTR, 0L, 2L);
  SafeArrayAccessData(vntRet->parray, (void **) &pData);
  pData[0] = SysAllocString(L"File File1");
  pData[1] = SysAllocString(L"File File2");
  SafeArrayUnaccessData(vntRet->parray);

  return S_OK;
}

HRESULT
FileGetVariableNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  BSTR* pData;
  print_args("FileGetVariableNames", vntArgs, Argc);

  vntRet->vt = VT_BSTR | VT_ARRAY;
  vntRet->parray = SafeArrayCreateVector(VT_BSTR, 0L, 2L);
  SafeArrayAccessData(vntRet->parray, (void **) &pData);
  pData[0] = SysAllocString(L"File Variable1");
  pData[1] = SysAllocString(L"File Variable2");
  SafeArrayUnaccessData(vntRet->parray);

  return S_OK;
}

HRESULT
FileExecute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileExecute", vntArgs, Argc);

  return S_OK;
}

HRESULT
FileCopy(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileCopy", vntArgs, Argc);

  return S_OK;
}

HRESULT
FileDelete(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileDelete", vntArgs, Argc);

  return S_OK;
}

HRESULT
FileMove(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileMove", vntArgs, Argc);

  return S_OK;
}

HRESULT
FileRun(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileRun", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"FileRun");

  return S_OK;
}

HRESULT
FileGetDateCreated(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetDateCreated", vntArgs, Argc);

  vntRet->vt = VT_DATE;
  vntRet->date = 0;

  return S_OK;
}

HRESULT
FileGetDateLastAccessed(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetDateLastAccessed", vntArgs, Argc);

  vntRet->vt = VT_DATE;
#ifdef _MSC_VER
  vntRet->date = COleDateTime::GetCurrentTime();
#else
  time(&vntRet->date);
#endif

  return S_OK;
}

HRESULT
FileGetDateLastModified(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetDateLastModified", vntArgs, Argc);

  vntRet->vt = VT_DATE;
  vntRet->date = 0;

  return S_OK;
}

HRESULT
FileGetPath(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetPath", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Path");

  return S_OK;
}

HRESULT
FileGetSize(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetSize", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
FileGetType(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetType", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Type");

  return S_OK;
}

HRESULT
FileGetValue(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetValue", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"FileValue");

  return S_OK;
}

HRESULT
FilePutValue(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FilePutValue", vntArgs, Argc);

  return S_OK;
}

HRESULT
FileGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetAttribute", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
FileGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetHelp", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"File Help");

  return S_OK;
}

HRESULT
FileGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetName", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"File Name");

  return S_OK;
}

HRESULT
FileGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetTag", vntArgs, Argc);

  vntRet->vt = VT_EMPTY;

  return S_OK;
}

HRESULT
FilePutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FilePutTag", vntArgs, Argc);

  return S_OK;
}

HRESULT
FileGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileGetID", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
FilePutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FilePutID", vntArgs, Argc);

  return S_OK;
}

HRESULT
FileRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("FileRelease", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotGetVariableNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  BSTR* pData;
  print_args("RobotGetVariableNames", vntArgs, Argc);

  vntRet->vt = VT_BSTR | VT_ARRAY;
  vntRet->parray = SafeArrayCreateVector(VT_BSTR, 0L, 2L);
  SafeArrayAccessData(vntRet->parray, (void **) &pData);
  pData[0] = SysAllocString(L"Robot Variable1");
  pData[1] = SysAllocString(L"Robot Variable2");
  SafeArrayUnaccessData(vntRet->parray);

  return S_OK;
}

HRESULT
RobotAccelerate(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotAccelerate", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotChange(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotChange", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotChuck(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotChuck", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotDrive(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotDrive", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotGoHome(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotGoHome", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotHalt(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotHalt", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotHold(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotHold", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotRotate(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotRotate", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotSpeed(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotSpeed", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotUnchuck(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotUnchuck", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotUnhold(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotUnhold", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotGetAttribute", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
RobotGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotGetHelp", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Robot Help");

  return S_OK;
}

HRESULT
RobotGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotGetName", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Robot Name");

  return S_OK;
}

HRESULT
RobotGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // NOt use
  print_args("RobotGetTag", vntArgs, Argc);

  vntRet->vt = VT_EMPTY;

  return S_OK;
}

HRESULT
RobotPutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotPutTag", vntArgs, Argc);

  return S_OK;
}

HRESULT
RobotGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotGetID", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
RobotPutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("RobotPutID", vntArgs, Argc);

  return S_OK;
}

HRESULT
TaskGetVariableNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  BSTR* pData;
  print_args("TaskGetVariableNames", vntArgs, Argc);

  vntRet->vt = VT_BSTR | VT_ARRAY;
  vntRet->parray = SafeArrayCreateVector(VT_BSTR, 0L, 2L);
  SafeArrayAccessData(vntRet->parray, (void **) &pData);
  pData[0] = SysAllocString(L"Task Variable1");
  pData[1] = SysAllocString(L"Task Variable2");
  SafeArrayUnaccessData(vntRet->parray);

  return S_OK;
}

HRESULT
TaskDelete(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("TaskDelete", vntArgs, Argc);

  return S_OK;
}

HRESULT
TaskGetFileName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("TaskGetFileName", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Task FileName");

  return S_OK;
}

HRESULT
TaskGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("TaskGetAttribute", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
TaskGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("TaskGetHelp", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Task Help");

  return S_OK;
}

HRESULT
TaskGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("TaskGetName", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Task Name");

  return S_OK;
}

HRESULT
TaskGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("TaskGetTag", vntArgs, Argc);

  vntRet->vt = VT_EMPTY;

  return S_OK;
}

HRESULT
TaskPutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("TaskPutTag", vntArgs, Argc);

  return S_OK;
}

HRESULT
TaskGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("TaskGetID", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
TaskPutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("TaskPutID", vntArgs, Argc);

  return S_OK;
}

HRESULT
VariableGetDateTime(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("VariableGetDateTime", vntArgs, Argc);

  vntRet->vt = VT_DATE;
#ifdef _MSC_VER
  vntRet->date = COleDateTime::GetCurrentTime();
#else
  time(&vntRet->date);
#endif

  return S_OK;
}

HRESULT
VariableGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("VariableGetAttribute", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
VariableGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("VariableGetHelp", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Variable Help");

  return S_OK;
}

HRESULT
VariableGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("VariableGetName", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Variable Name");

  return S_OK;
}

HRESULT
VariableGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("VariableGetTag", vntArgs, Argc);

  vntRet->vt = VT_EMPTY;

  return S_OK;
}

HRESULT
VariablePutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("VariablePutTag", vntArgs, Argc);

  return S_OK;
}

HRESULT
VariableGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("VariableGetID", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
VariablePutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("VariablePutID", vntArgs, Argc);

  return S_OK;
}

HRESULT
VariableGetMicrosecond(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("VariableGetMicrosecond", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0;

  return S_OK;
}

HRESULT
CommandExecute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandExecute", vntArgs, Argc);

  return S_OK;
}

HRESULT
CommandCancel(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandCancel", vntArgs, Argc);

  return S_OK;
}

HRESULT
CommandGetTimeout(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandGetTimeout", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
CommandPutTimeout(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandPutTimeout", vntArgs, Argc);

  return S_OK;
}

HRESULT
CommandGetState(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandGetState", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
CommandGetParameters(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandGetParameters", vntArgs, Argc);

  vntRet->vt = VT_EMPTY;

  return S_OK;
}

HRESULT
CommandPutParameters(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandPutParameters", vntArgs, Argc);

  return S_OK;
}

HRESULT
CommandGetResult(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandGetResult", vntArgs, Argc);

  vntRet->vt = VT_BOOL;
  vntRet->boolVal = VARIANT_FALSE;

  return S_OK;
}

HRESULT
CommandGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandGetAttribute", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
CommandGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandGetHelp", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Command Help");

  return S_OK;
}

HRESULT
CommandGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandGetName", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Command Name");

  return S_OK;
}

HRESULT
CommandGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandGetTag", vntArgs, Argc);

  vntRet->vt = VT_EMPTY;

  return S_OK;
}

HRESULT
CommandPutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandPutTag", vntArgs, Argc);

  return S_OK;
}

HRESULT
CommandGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandGetID", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
CommandPutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandPutID", vntArgs, Argc);

  return S_OK;
}

HRESULT
CommandRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("CommandRelease", vntArgs, Argc);

  return S_OK;
}

HRESULT
MessageReply(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("MessageReply", vntArgs, Argc);

  return S_OK;
}

HRESULT
MessageClear(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("MessageClear", vntArgs, Argc);

  return S_OK;
}

HRESULT
MessageGetDateTime(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("MessageGetDateTime", vntArgs, Argc);

  vntRet->vt = VT_DATE;
#ifdef _MSC_VER
  vntRet->date = COleDateTime::GetCurrentTime();
#else
  time(&vntRet->date);
#endif

  return S_OK;
}

HRESULT
MessageGetDescription(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("MessageGetDescription", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Description");

  return S_OK;
}

HRESULT
MessageGetDestination(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("MessageGetDestination", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Destination");

  return S_OK;
}

HRESULT
MessageGetNumber(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("MessageGetNumber", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
MessageGetSerialNumber(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("MessageGetSerialNumber", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
MessageGetSource(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("MessageGetSource", vntArgs, Argc);

  vntRet->vt = VT_BSTR;
  vntRet->bstrVal = SysAllocString(L"Source");

  return S_OK;
}

HRESULT
MessageGetValue(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("MessageGetValue", vntArgs, Argc);

  vntRet->vt = VT_I4;
  vntRet->lVal = 0L;

  return S_OK;
}

HRESULT
MessageRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet)
{
  // Not use
  print_args("MessageRelease", vntArgs, Argc);

  return S_OK;
}
