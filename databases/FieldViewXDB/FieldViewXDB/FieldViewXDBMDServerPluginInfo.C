/*****************************************************************************
* Copyright (c) 2014 Intelligent Light. All rights reserved.
* Work partially supported by DOE Grant SC0007548.
* FieldView XDB Export is provided expressly for use within VisIt.
* All other uses are strictly forbidden.
*****************************************************************************/

#include <FieldViewXDBPluginInfo.h>

// ****************************************************************************
//  Function:  GetMDServerInfo
//
//  Purpose:
//    Return a new MDServerPluginInfo for the XDB database.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************
extern "C" DBP_EXPORT MDServerDatabasePluginInfo* FieldViewXDB_GetMDServerInfo()
{
    return new FieldViewXDBMDServerPluginInfo;
}

// this makes compilers happy... remove if we ever have functions here
void FieldViewXDBMDServerPluginInfo::dummy()
{
}

