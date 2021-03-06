/*****************************************************************************
*
* Copyright (c) 2000 - 2014, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                         avtActualExtentsFilter.h                          // 
// ************************************************************************* // 


#include <avtActualExtentsFilter.h>

#include <avtDataAttributes.h>
#include <avtDatasetExaminer.h>
#include <avtExtents.h>

#include <TimingsManager.h>


// ****************************************************************************
//  Method: avtActualExtentsFilter::Execute
//
//  Purpose:
//      This filter simply calculates extents.  Do that here.
//
//  Programmer: Kathleen Bonnell
//  Creation:   October 2, 2001 
//
//  Modifications:
// 
//    Hank Childs, Thu Aug 26 16:36:30 PDT 2010
//    Call UpdateExtents.
//
// ****************************************************************************

void
avtActualExtentsFilter::Execute(void)
{
    UpdateExtents();
    SetOutputDataTree(GetInputDataTree());
}


// ****************************************************************************
//  Method: avtActualExtentsFilter::UpdateExtents
//
//  Purpose:  Retrieves the actual data/spatial extents from the
//            input and stores them in output's info.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   October 3, 2001 
//
//  Modifications:
//
//    Hank Childs, Fri Mar 15 18:11:12 PST 2002
//    Account for avtDatasetExaminer.
//
//    Hank Childs, Thu Jul 17 17:40:24 PDT 2003
//    Treat 2D vectors as 3D since VTK will assume that vectors are 3D.
//
//    Hank Childs, Tue Feb 24 14:23:03 PST 2004
//    Account for multiple variables.
//
//    Kathleen Bonnell, Thu Mar 11 11:16:17 PST 2004 
//    DataExtents now always have only 2 components. 
//
//    Hank Childs, Thu Aug 26 13:47:30 PDT 2010
//    Change extents names.  Only calculate the requested variables.
//
// ****************************************************************************

void
avtActualExtentsFilter::UpdateExtents(void)
{
    int t1 = visitTimer->StartTimer();
    avtDataAttributes &atts = GetInput()->GetInfo().GetAttributes();
    avtDataAttributes &outAtts = GetOutput()->GetInfo().GetAttributes();
    avtDataset_p ds = GetTypedInput();

    int nVars = atts.GetNumberOfVariables();
    double de[2];
    for (int i = 0 ; i < nVars ; i++)
    {
        const char *vname = atts.GetVariableName(i).c_str();
        if (! lastContract->ShouldCalculateVariableExtents(vname))
            continue;
    
        bool foundDE = avtDatasetExaminer::GetDataExtents(ds, de, vname);
        if (foundDE)
        {
            outAtts.GetThisProcsActualDataExtents(vname)->Merge(de);
        }
    }

    if (lastContract->ShouldCalculateMeshExtents())
    {
        double se[6];
        bool foundSE = avtDatasetExaminer::GetSpatialExtents(ds, se);
        if (foundSE)
        {
            outAtts.GetThisProcsActualSpatialExtents()->Merge(se);
        }
    }
    visitTimer->StopTimer(t1, "Calculating the actual extents");
}


// ****************************************************************************
//  Method:  avtActualExtentsFilter::FilterUnderstandsTransformedRectMesh
//
//  Purpose:
//    If this filter returns true, this means that it correctly deals
//    with rectilinear grids having an implied transform set in the
//    data attributes.  It can do this conditionally if desired.
//
//  Arguments:
//    none
//
//  Programmer:  Jeremy Meredith
//  Creation:    February 15, 2007
//
// ****************************************************************************

bool
avtActualExtentsFilter::FilterUnderstandsTransformedRectMesh()
{
    // there were some changes made at lower levels which make
    // this filter safe
    return true;
}


// ****************************************************************************
//  Method: avtActualExtentsFilter::ModifyContract
//
//  Purpose:
//      The base class declares that this filter can only work on floats.
//      Reimplement this method to do nothing, just to prevent the base class
//      from doing the wrong thing.  The way the base class is working should
//      be overhauled, but I'm not going to address that now.
//
//  Programmer: Hank Childs
//  Creation:   August 26, 2008
//
//  Modifications:
//
//    Hank Childs, Thu Aug 26 16:36:30 PDT 2010
//    Cache the last contract.
//
// ****************************************************************************

avtContract_p
avtActualExtentsFilter::ModifyContract(avtContract_p c)
{
    lastContract = c;
    return c;
}



