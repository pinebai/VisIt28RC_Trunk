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
//  File: avtRectilinearProject2DFilter.C
// ************************************************************************* //

#include <avtRectilinearProject2DFilter.h>

#include <list>

#include <float.h>

#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkDoubleArray.h>
#include <vtkFieldData.h>
#include <vtkIntArray.h>
#include <vtkPointData.h>
#include <vtkRectilinearGrid.h>
#include <vtkStructuredData.h>
#include <vtkStructuredGrid.h>


// ****************************************************************************
//  Method: avtRectilinearProject2DFilter constructor
//
//  Programmer: ghweber -- generated by xml2avt
//  Creation:   Thu Jun 6 15:24:16 PST 2013
//
// ****************************************************************************

avtRectilinearProject2DFilter::avtRectilinearProject2DFilter()
{
}


// ****************************************************************************
//  Method: avtRectilinearProject2DFilter destructor
//
//  Programmer: ghweber -- generated by xml2avt
//  Creation:   Thu Jun 6 15:24:16 PST 2013
//
//  Modifications:
//
// ****************************************************************************

avtRectilinearProject2DFilter::~avtRectilinearProject2DFilter()
{
}


// ****************************************************************************
//  Method:  avtRectilinearProject2DFilter::Create
//
//  Programmer: ghweber -- generated by xml2avt
//  Creation:   Thu Jun 6 15:24:16 PST 2013
//
// ****************************************************************************

avtFilter *
avtRectilinearProject2DFilter::Create()
{
    return new avtRectilinearProject2DFilter();
}


// ****************************************************************************
//  Method:      avtRectilinearProject2DFilter::SetAtts
//
//  Purpose:
//      Sets the state of the filter based on the attribute object.
//
//  Arguments:
//      a        The attributes to use.
//
//  Programmer: ghweber -- generated by xml2avt
//  Creation:   Thu Jun 6 15:24:16 PST 2013
//
// ****************************************************************************

void
avtRectilinearProject2DFilter::SetAtts(const AttributeGroup *a)
{
    atts = *(const RectilinearProject2DAttributes*)a;
}


// ****************************************************************************
//  Method: avtRectilinearProject2DFilter::Equivalent
//
//  Purpose:
//      Returns true if creating a new avtRectilinearProject2DFilter with the given
//      parameters would result in an equivalent avtRectilinearProject2DFilter.
//
//  Programmer: ghweber -- generated by xml2avt
//  Creation:   Thu Jun 6 15:24:16 PST 2013
//
// ****************************************************************************

bool
avtRectilinearProject2DFilter::Equivalent(const AttributeGroup *a)
{
    return (atts == *(RectilinearProject2DAttributes*)a);
}


// ****************************************************************************
//  Method: avtRectilinearProject2DFilter::PreExecute
//
//  Purpose:
//      Called before "Execute". Initialize variable we use to keep track of
//      value range.
//
//  Programmer: Gunther H. Weber 
//  Creation:   June 6, 2013
//
//  Modifications:
//
// ****************************************************************************

void
avtRectilinearProject2DFilter::PreExecute(void)
{
    avtPluginDataTreeIterator::PreExecute();
    range[0] =  FLT_MAX;
    range[1] = -FLT_MAX;
}


// ****************************************************************************
//  Method: avtRectilinearProject2DFilter::Execute
//
//  Purpose:
//      Execute filter on data tree
//
//  Programmer: ghweber -- generated by xml2avt
//  Creation:   Thu Jun 6 15:24:16 PST 2013
//
// ****************************************************************************

struct box2d
{
    int iMin, iMax;
    int jMin, jMax;

    box2d(int _iMin, int _iMax, int _jMin, int _jMax) : iMin(_iMin), iMax(_iMax), jMin(_jMin), jMax(_jMax) {}
    bool operator==(box2d& o) { return iMin == o.iMin && iMax == o.iMax && jMin == o.jMin && jMax == o.jMax; }
};

void
avtRectilinearProject2DFilter::Execute()
{
    avtDataTree_p in_tree = GetInputDataTree();

    if (in_tree->IsEmpty())
    {
        SetOutputDataTree(in_tree);
        return;
    }

    int nLeaves = 0;
    vtkDataSet **leaves = in_tree->GetAllLeaves(nLeaves);

    // Get all data sets
    vtkRectilinearGrid **rgrids = new vtkRectilinearGrid*[nLeaves];
    for (int i = 0; i < nLeaves; ++i)
        if (!(rgrids[i] = dynamic_cast<vtkRectilinearGrid*>(leaves[i])))
            EXCEPTION1(ImproperUseException, "Can only project rectilinear grids.");

    // Compute extents in i,j index space as list of boxes
    std::vector<box2d> boxes;
    boxes.reserve(nLeaves);

    for (int i = 0; i < nLeaves; ++i)
    {
        int dims[3] = { 0, 0, 0 };
        rgrids[i]->GetDimensions(dims);

        vtkIntArray *arr = dynamic_cast<vtkIntArray*>(rgrids[i]->GetFieldData()->GetArray("base_index"));
        int base_index[3] = { 0, 0, 0 };
        if (arr)
            for (int d = 0; d < 3; ++d)
                base_index[d] = arr->GetValue(d);

        boxes.push_back(box2d(
                    base_index[0], base_index[0] + dims[0] - 2,
                    base_index[1], base_index[1] + dims[1] - 2
                    ));
    }

    // Group boxes by same i, j extents
    // ... for each group of boxes with same i, j exntents identify one representing box
    // ... this is the box with the lowest index that has the same i, j extents
    std::vector<int> representingBox(boxes.size());
    for (size_t i = 0; i < boxes.size(); ++i)
        for (size_t j = 0; j<=i; ++j)
            if (boxes[i] == boxes[j])
            {
                representingBox[i] = (int)j;
                break;
            }

    // ... group all boxes that have the same representing box
    // ... since a representing box always has the smallest id, a box represetning itself
    // ... starts a new group
    std::vector<int> ijGroupNo(boxes.size());
    int currNewIJGroup = 0;
    for (size_t i = 0; i < representingBox.size(); ++i)
    {
        if ((size_t)representingBox[i] == i)
            ijGroupNo[i] = currNewIJGroup++;
        else
            ijGroupNo[i] = ijGroupNo[representingBox[i]];
    }

    std::vector< std::vector<int> > ijGroup(currNewIJGroup);
    for (size_t i = 0; i < ijGroupNo.size(); ++i)
        ijGroup[ijGroupNo[i]].push_back((int)i);

    // Project grids per group to 2D generating one 2D mesh per group
    vtkDataSet** ogrids = new vtkDataSet*[ijGroup.size()];
    int currGrid = 0;
    std::vector<int> domain_ids;
    for (std::vector< std::vector<int> >::const_iterator currGroupIt = ijGroup.begin();
            currGroupIt != ijGroup.end(); ++currGroupIt)
    {
        const std::vector<int>& currGroup = *currGroupIt;
        domain_ids.push_back(currGroup[0]);

        // Dimensions of data set
        int dims[3];
        rgrids[currGroup[0]]->GetDimensions(dims);

        vtkDataSet *ods;
        int odims[3] = { dims[0], dims[1], 1 };

        if (atts.GetMapGrid())
        {
            vtkStructuredGrid *sgrid = vtkStructuredGrid::New();
            sgrid->SetDimensions(odims);

            vtkPointData *ipdata = rgrids[currGroup[0]]->GetPointData();
            if (!ipdata)
                EXCEPTION1(ImproperUseException, "Mapping turned on, but no coordinates available!");
            vtkDataArray *xCoordData = ipdata->GetArray("_mapping_xcoord");
            vtkDataArray *yCoordData = ipdata->GetArray("_mapping_ycoord");
            if (!(xCoordData && yCoordData))
                EXCEPTION1(ImproperUseException, "Mapping turned on, but no coordinates available!");

            vtkPoints *mappedPoints = vtkPoints::New();
            mappedPoints->SetNumberOfPoints(dims[0]*dims[1]);
            for (int j=0; j<dims[1]; ++j)
                for (int i=0; i<dims[0]; ++i)
                {
                    int ijk[3] = { i, j, 0 };
                    vtkIdType from_point_id = rgrids[currGroup[0]]->ComputePointId(ijk);
                    vtkIdType to_point_id = vtkStructuredData::ComputePointId(odims, ijk);
                    mappedPoints->SetPoint(to_point_id, xCoordData->GetTuple1(from_point_id), yCoordData->GetTuple1(from_point_id), 0);
                }

            sgrid->SetPoints(mappedPoints);
            mappedPoints->Delete();
            ods = sgrid;
        }
        else
        {
            vtkRectilinearGrid *rgrid = vtkRectilinearGrid::New();
            rgrid->SetDimensions(dims[0], dims[1], 1);
            rgrid->SetXCoordinates(rgrids[currGroup[0]]->GetXCoordinates());
            rgrid->SetYCoordinates(rgrids[currGroup[0]]->GetYCoordinates());
            vtkDataArray *zCoords = rgrids[currGroup[0]]->GetZCoordinates()->NewInstance();
            zCoords->SetNumberOfTuples(1);
            zCoords->SetTuple1(0, 0.0);
            rgrid->SetZCoordinates(zCoords);
            zCoords->Delete();
            ods = rgrid;
        }

        int base_index[3] = { 0, 0, 0 };
        if (vtkIntArray *arr = dynamic_cast<vtkIntArray*>(rgrids[currGroup[0]]->GetFieldData()->GetArray("base_index")))
            for (int d = 0; d < 3; ++d)
                base_index[d] = arr->GetValue(d);

        vtkIntArray *arr = vtkIntArray::New();
        arr->SetNumberOfTuples(3);
        arr->SetValue(0, base_index[0]);
        arr->SetValue(1, base_index[1]);
        arr->SetValue(2, 0);
        arr->SetName("base_index");
        ods->GetFieldData()->AddArray(arr);
        arr->Delete();

#if 0
        if (vtkPointData *ipdata = rgrids[currGroup[0]]->GetPointData())
        {
            for (int varNo = 0; varNo < ipdata->GetNumberOfArrays(); ++varNo)
            {
                vtkDataArray *ipvals = ipdata->GetArray(varNo);

                // Create array for output data
                vtkDataArray *opvals = ipvals->NewInstance();
                opvals->SetName(ipvals->GetName());
                opvals->SetNumberOfComponents(ipvals->GetNumberOfComponents());
                opvals->SetNumberOfTuples((dims[0])*(dims[1]));

                // Copy first slice
                for (int j=0; j<dims[1]; ++j)
                    for (int i=0; i<dims[0]; ++i)
                    {
                        int ijk[3] = { i, j, 0 };
                        vtkIdType from_point_id = rgrids[currGroup[0]]->ComputePointId(ijk);
                        vtkIdType to_point_id = vtkStructuredData::ComputePointId(odims, ijk);
                        opvals->SetTuple(to_point_id, ipvals->GetTuple(from_point_id));
                    }
                opvals->SetName(ipvals->GetName());
                ods->GetPointData()->AddArray(opvals);
                opvals->Delete();
            }

            // If active scalar exists, set it in output array
            if (vtkDataArray *ascalars = ipdata->GetScalars())
                ods->GetPointData()->SetActiveScalars(ascalars->GetName());
        }
#endif
        if (vtkCellData *icdata = rgrids[currGroup[0]]->GetCellData())
        {
            for (int varNo = 0; varNo<icdata->GetNumberOfArrays(); ++varNo)
            {
                vtkDataArray *icvals = icdata->GetArray(varNo);
                vtkDataArray *ocvals = icvals->NewInstance();
                ocvals->SetName(icvals->GetName());
                ocvals->SetNumberOfComponents(icvals->GetNumberOfComponents());
                ocvals->SetNumberOfTuples((dims[0]-1)*(dims[1]-1));
                const char *varname = icvals->GetName();
                bool isPipelineVariable = (strcmp(varname, pipelineVariable) == 0);

                if (strcmp(varname, "avtOriginalCellNumbers") == 0)
                {
                    for (int i=0; i<dims[0]-1; ++i)
                        for (int j=0; j<dims[1]-1; ++j)
                        {
                            int ijk[3] = { i, j, 0 };
                            vtkIdType in_cell_id = rgrids[currGroup[0]]->ComputeCellId(ijk);
                            vtkIdType out_cell_id = vtkStructuredData::ComputeCellId(odims, ijk);
                            ocvals->SetTuple(out_cell_id, icvals->GetTuple(in_cell_id));
                        }
                }
                else
                {
                    for (int i=0; i<dims[0]-1; ++i)
                        for (int j=0; j<dims[1]-1; ++j)
                        {
                            double val = 0.0;
                            int nKTotal = 0;
                            for (std::vector<int>::const_iterator boxNoIt = currGroup.begin();
                                    boxNoIt != currGroup.end(); ++boxNoIt)
                            {
                                vtkIdType nK = rgrids[*boxNoIt]->GetDimensions()[2] - 1;
                                nKTotal += nK;
                                vtkDataArray *curr_icvals = rgrids[*boxNoIt]->GetCellData()->GetArray(varname);
                                if (!curr_icvals)
                                    EXCEPTION1(ImproperUseException, "Error: All domains must have the same set of variables.");

                                for (int k=0; k<nK; ++k)
                                {
                                    int ijk[3] = { i, j, k };
                                    vtkIdType cell_id = rgrids[*boxNoIt]->ComputeCellId(ijk);
                                    val += curr_icvals->GetTuple1(cell_id);
                                }
                            }

                            if (atts.GetReductionOperator() == RectilinearProject2DAttributes::Average)
                                val /= nKTotal;

                            int out_ijk[3] = { i, j, 0 };
                            vtkIdType out_cell_id = vtkStructuredData::ComputeCellId(odims, out_ijk);
                            ocvals->SetTuple1(out_cell_id, val);
                            if (isPipelineVariable)
                            {
                                if (val < range[0]) range[0] = val;
                                if (val > range[1]) range[1] = val;
                            }
                        }
                }
                ods->GetCellData()->AddArray(ocvals);
                ocvals->Delete();
            }
            if (vtkDataArray *ascalars = icdata->GetScalars())
            {
                ods->GetCellData()->SetActiveScalars(ascalars->GetName());
            }
        }
        ogrids[currGrid++] = ods;
    }
    delete[] rgrids;
    avtDataTree_p out_tree = new avtDataTree((int)ijGroup.size(), ogrids, domain_ids);
    delete[] ogrids;
    SetOutputDataTree(out_tree);
}


// ****************************************************************************
//  Method: avtRectilinearProject2DFilter::PostExecute
//
//  Purpose:
//      Called after "Execute". Remove mapping variables from data attributes
//      that we "consume." Update value range.
//
//  Programmer: Gunther H. Weber 
//  Creation:   June 6, 2013
//
//  Modifications:
//
// ****************************************************************************

void
avtRectilinearProject2DFilter::PostExecute(void)
{
    avtPluginDataTreeIterator::PostExecute();
    avtDataAttributes &dataAtts = GetOutput()->GetInfo().GetAttributes();
    if (atts.GetMapGrid())
    {
        dataAtts.SetActiveVariable(pipelineVariable);
        dataAtts.RemoveVariable("_mapping_xcoord");
        dataAtts.RemoveVariable("_mapping_ycoord");
    }
    if (dataAtts.GetVariableType(pipelineVariable) == AVT_SCALAR_VAR &&
        dataAtts.GetCentering(pipelineVariable) == AVT_ZONECENT)
    {
        dataAtts.GetThisProcsOriginalDataExtents(pipelineVariable)->Set(range);
        dataAtts.GetThisProcsActualDataExtents(pipelineVariable)->Set(range);
    }
}


// ****************************************************************************
//  Method: avtRectilinearProject2DFilter::ModifyContract
//
//  Purpose:
//      Creates a contract that adds requests for secondary variables with
//      mapping information.
//
//  Programmer: ghweber -- generated by xml2avt
//  Creation:   Thu Jun 6 15:24:16 PST 2013
//
// ****************************************************************************

avtContract_p
avtRectilinearProject2DFilter::ModifyContract(avtContract_p in_contract)
{
    avtContract_p out_contract = new avtContract(in_contract);
    if (atts.GetMapGrid())
    {
        avtDataRequest_p dataRequest = out_contract->GetDataRequest();
        dataRequest->AddSecondaryVariable("_mapping_xcoord");
        dataRequest->AddSecondaryVariable("_mapping_ycoord");
    }

    return out_contract;
}


// ****************************************************************************
//  Method: avtRectilinearProject2DFilter::UpdateDataObjectInfo
//
//  Purpose:
//      Update topolgocial dimension and invalidate metadata.
//
//  Programmer: ghweber -- generated by xml2avt
//  Creation:   Thu Jun 6 15:24:16 PST 2013
//
//  Modifications:
//    Brad Whitlock, Mon Apr  7 15:55:02 PDT 2014
//    Add filter metadata used in export.
//    Work partially supported by DOE Grant SC0007548.
//
// ****************************************************************************

void
avtRectilinearProject2DFilter::UpdateDataObjectInfo(void)
{
    avtDataAttributes &datts = GetOutput()->GetInfo().GetAttributes();
    datts.SetSpatialDimension(2);
    datts.SetTopologicalDimension(2);
    datts.AddFilterMetaData("RectilinearProject2D");
    GetOutput()->GetInfo().GetValidity().InvalidateSpatialMetaData();
    GetOutput()->GetInfo().GetValidity().InvalidateDataMetaData();
}
