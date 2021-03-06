/*****************************************************************************
* Copyright (c) 2014 Intelligent Light. All rights reserved.
* Work partially supported by DOE Grant SC0007548.
* FieldView XDB Export is provided expressly for use within VisIt.
* All other uses are strictly forbidden.
*****************************************************************************/
#include <FieldViewXDBPluginInfo.h>
#include <avtFieldViewXDBWriter.h>

// ****************************************************************************
//  Function:  GetEngineInfo
//
//  Purpose:
//    Return a new EnginePluginInfo for the FieldViewXDB database.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************
extern "C" DBP_EXPORT EngineDatabasePluginInfo* FieldViewXDB_GetEngineInfo()
{
    return new FieldViewXDBEnginePluginInfo;
}

// ****************************************************************************
//  Method: FieldViewXDBEnginePluginInfo::GetWriter
//
//  Purpose:
//      Sets up a FieldViewXDB writer.
//
//  Returns:    A FieldViewXDB writer.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************
avtDatabaseWriter *
FieldViewXDBEnginePluginInfo::GetWriter(void)
{
    return new avtFieldViewXDBWriter;
}

