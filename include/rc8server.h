
#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#ifdef _MSC_VER
#include <Windows.h>
#include <ATLComTime.h>
#else
#include <unistd.h>
#endif

#ifdef _MSC_VER
#include "bcap_server.h"
#else
#include "bCAPServer/bcap_server.h"
#endif

#define GET_HANDLE(h)    (h & 0x0ff)
#define MAX_N_VALS      100
#define N_AXIS          6
#define N_V_TYPE        3
#define N_P_TYPE        7
#define N_J_TYPE        8
#define N_T_TYPE        10

enum{
  I_VAL=0x100,
  F_VAL=0x200,
  CTRL_VAL=0x400,
  ROBOT_VAL=0x800,
  TASK_VAL=0xf00,
};


/** Variables ***/
HRESULT get_controller_variable_handle(int32_t *handle, BSTR bstr);
HRESULT get_robot_variable_handle(int32_t *handle, BSTR bstr);
HRESULT get_task_variable_handle(int32_t *handle, BSTR bstr);
void get_variable_value(int32_t h, VARIANT *v);
void put_variable_value(int32_t h, VARIANT v);
void load_int_value(std::string fname);
void save_int_value(std::string fname);
void load_float_value(std::string fname);
void save_float_value(std::string fname);
int32_t get_error_value();
void put_error_value(int32_t val);
void put_joint_values(double *joints);

/** PrintVariant***/
void print_args(const char *chName, VARIANT *vntArgs, int16_t Argc);

/** file System*/
std::vector<std::string> GetTaskNames(std::string path);
//int ReadTaskTime(std::string name);
int ReadTaskTime(std::vector<std::string>f_list, std::string name);

int GetTaskTime(std::string name);
void LoadTaskList();


/** NotUseFunc */
HRESULT ControllerGetExtension(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetFile(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetCommand(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetExtensionNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetFileNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetRobotNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetVariableNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetCommandNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetMessage(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerPutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ControllerPutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ExtensionGetVariable(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ExtensionGetVariableNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ExtensionExecute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ExtensionGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ExtensionGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ExtensionGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ExtensionGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ExtensionPutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ExtensionGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet) ;
HRESULT ExtensionPutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT ExtensionRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetFile(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetVariable(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetFileNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetVariableNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileExecute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileCopy(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileDelete(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileMove(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileRun(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetDateCreated(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetDateLastAccessed(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetDateLastModified(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetPath(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetSize(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetType(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetValue(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FilePutValue(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FilePutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FilePutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT FileRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotGetVariableNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotAccelerate(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotChange(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotChuck(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotDrive(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotGoHome(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotHalt(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotHold(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotRotate(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotSpeed(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotUnchuck(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotUnhold(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotPutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT RobotPutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT TaskGetVariableNames(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT TaskDelete(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT TaskGetFileName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT TaskGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);;
HRESULT TaskGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT TaskGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT TaskGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet) ;
HRESULT TaskPutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT TaskGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT TaskPutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT VariableGetDateTime(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT VariableGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT VariableGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT VariableGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT VariableGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT VariablePutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT VariableGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT VariablePutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT VariableGetMicrosecond(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandExecute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandCancel(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandGetTimeout(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandPutTimeout(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandGetState(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandGetParameters(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandPutParameters(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandGetResult(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandGetAttribute(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandGetHelp(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandGetName(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandGetTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandPutTag(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandGetID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandPutID(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT CommandRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT MessageReply(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT MessageClear(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT MessageGetDateTime(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT MessageGetDescription(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT MessageGetDestination(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT MessageGetNumber(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT MessageGetSerialNumber(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT MessageGetSource(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT MessageGetValue(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
HRESULT MessageRelease(VARIANT *vntArgs, int16_t Argc, VARIANT *vntRet);
