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

#include <Axes3D.h>
#include <DataNode.h>

//
// Enum conversion methods for Axes3D::Axes
//

static const char *Axes_strings[] = {
"ClosestTriad", "FurthestTriad", "OutsideEdges", 
"StaticTriad", "StaticEdges"};

std::string
Axes3D::Axes_ToString(Axes3D::Axes t)
{
    int index = int(t);
    if(index < 0 || index >= 5) index = 0;
    return Axes_strings[index];
}

std::string
Axes3D::Axes_ToString(int t)
{
    int index = (t < 0 || t >= 5) ? 0 : t;
    return Axes_strings[index];
}

bool
Axes3D::Axes_FromString(const std::string &s, Axes3D::Axes &val)
{
    val = Axes3D::ClosestTriad;
    for(int i = 0; i < 5; ++i)
    {
        if(s == Axes_strings[i])
        {
            val = (Axes)i;
            return true;
        }
    }
    return false;
}

//
// Enum conversion methods for Axes3D::Location
//

static const char *Location_strings[] = {
"Inside", "Outside", "Both"
};

std::string
Axes3D::Location_ToString(Axes3D::Location t)
{
    int index = int(t);
    if(index < 0 || index >= 3) index = 0;
    return Location_strings[index];
}

std::string
Axes3D::Location_ToString(int t)
{
    int index = (t < 0 || t >= 3) ? 0 : t;
    return Location_strings[index];
}

bool
Axes3D::Location_FromString(const std::string &s, Axes3D::Location &val)
{
    val = Axes3D::Inside;
    for(int i = 0; i < 3; ++i)
    {
        if(s == Location_strings[i])
        {
            val = (Location)i;
            return true;
        }
    }
    return false;
}

// ****************************************************************************
// Method: Axes3D::Axes3D
//
// Purpose: 
//   Init utility for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void Axes3D::Init()
{
    visible = true;
    autoSetTicks = true;
    autoSetScaling = true;
    lineWidth = 0;
    tickLocation = Inside;
    axesType = ClosestTriad;
    triadFlag = true;
    bboxFlag = true;
    xAxis.GetTitle().SetTitle("X-Axis");
    yAxis.GetTitle().SetTitle("Y-Axis");
    zAxis.GetTitle().SetTitle("Z-Axis");
    setBBoxLocation = false;
    bboxLocation[0] = 0;
    bboxLocation[1] = 1;
    bboxLocation[2] = 0;
    bboxLocation[3] = 1;
    bboxLocation[4] = 0;
    bboxLocation[5] = 1;

    Axes3D::SelectAll();
}

// ****************************************************************************
// Method: Axes3D::Axes3D
//
// Purpose: 
//   Copy utility for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void Axes3D::Copy(const Axes3D &obj)
{

    visible = obj.visible;
    autoSetTicks = obj.autoSetTicks;
    autoSetScaling = obj.autoSetScaling;
    lineWidth = obj.lineWidth;
    tickLocation = obj.tickLocation;
    axesType = obj.axesType;
    triadFlag = obj.triadFlag;
    bboxFlag = obj.bboxFlag;
    xAxis = obj.xAxis;
    yAxis = obj.yAxis;
    zAxis = obj.zAxis;
    setBBoxLocation = obj.setBBoxLocation;
    for(int i = 0; i < 6; ++i)
        bboxLocation[i] = obj.bboxLocation[i];


    Axes3D::SelectAll();
}

// Type map format string
const char *Axes3D::TypeMapFormatString = AXES3D_TMFS;
const AttributeGroup::private_tmfs_t Axes3D::TmfsStruct = {AXES3D_TMFS};


// ****************************************************************************
// Method: Axes3D::Axes3D
//
// Purpose: 
//   Default constructor for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

Axes3D::Axes3D() : 
    AttributeSubject(Axes3D::TypeMapFormatString)
{
    Axes3D::Init();
}

// ****************************************************************************
// Method: Axes3D::Axes3D
//
// Purpose: 
//   Constructor for the derived classes of Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

Axes3D::Axes3D(private_tmfs_t tmfs) : 
    AttributeSubject(tmfs.tmfs)
{
    Axes3D::Init();
}

// ****************************************************************************
// Method: Axes3D::Axes3D
//
// Purpose: 
//   Copy constructor for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

Axes3D::Axes3D(const Axes3D &obj) : 
    AttributeSubject(Axes3D::TypeMapFormatString)
{
    Axes3D::Copy(obj);
}

// ****************************************************************************
// Method: Axes3D::Axes3D
//
// Purpose: 
//   Copy constructor for derived classes of the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

Axes3D::Axes3D(const Axes3D &obj, private_tmfs_t tmfs) : 
    AttributeSubject(tmfs.tmfs)
{
    Axes3D::Copy(obj);
}

// ****************************************************************************
// Method: Axes3D::~Axes3D
//
// Purpose: 
//   Destructor for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

Axes3D::~Axes3D()
{
    // nothing here
}

// ****************************************************************************
// Method: Axes3D::operator = 
//
// Purpose: 
//   Assignment operator for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

Axes3D& 
Axes3D::operator = (const Axes3D &obj)
{
    if (this == &obj) return *this;

    Axes3D::Copy(obj);

    return *this;
}

// ****************************************************************************
// Method: Axes3D::operator == 
//
// Purpose: 
//   Comparison operator == for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

bool
Axes3D::operator == (const Axes3D &obj) const
{
    // Compare the bboxLocation arrays.
    bool bboxLocation_equal = true;
    for(int i = 0; i < 6 && bboxLocation_equal; ++i)
        bboxLocation_equal = (bboxLocation[i] == obj.bboxLocation[i]);

    // Create the return value
    return ((visible == obj.visible) &&
            (autoSetTicks == obj.autoSetTicks) &&
            (autoSetScaling == obj.autoSetScaling) &&
            (lineWidth == obj.lineWidth) &&
            (tickLocation == obj.tickLocation) &&
            (axesType == obj.axesType) &&
            (triadFlag == obj.triadFlag) &&
            (bboxFlag == obj.bboxFlag) &&
            (xAxis == obj.xAxis) &&
            (yAxis == obj.yAxis) &&
            (zAxis == obj.zAxis) &&
            (setBBoxLocation == obj.setBBoxLocation) &&
            bboxLocation_equal);
}

// ****************************************************************************
// Method: Axes3D::operator != 
//
// Purpose: 
//   Comparison operator != for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

bool
Axes3D::operator != (const Axes3D &obj) const
{
    return !(this->operator == (obj));
}

// ****************************************************************************
// Method: Axes3D::TypeName
//
// Purpose: 
//   Type name method for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

const std::string
Axes3D::TypeName() const
{
    return "Axes3D";
}

// ****************************************************************************
// Method: Axes3D::CopyAttributes
//
// Purpose: 
//   CopyAttributes method for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

bool
Axes3D::CopyAttributes(const AttributeGroup *atts)
{
    if(TypeName() != atts->TypeName())
        return false;

    // Call assignment operator.
    const Axes3D *tmp = (const Axes3D *)atts;
    *this = *tmp;

    return true;
}

// ****************************************************************************
// Method: Axes3D::CreateCompatible
//
// Purpose: 
//   CreateCompatible method for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

AttributeSubject *
Axes3D::CreateCompatible(const std::string &tname) const
{
    AttributeSubject *retval = 0;
    if(TypeName() == tname)
        retval = new Axes3D(*this);
    // Other cases could go here too. 

    return retval;
}

// ****************************************************************************
// Method: Axes3D::NewInstance
//
// Purpose: 
//   NewInstance method for the Axes3D class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

AttributeSubject *
Axes3D::NewInstance(bool copy) const
{
    AttributeSubject *retval = 0;
    if(copy)
        retval = new Axes3D(*this);
    else
        retval = new Axes3D;

    return retval;
}

// ****************************************************************************
// Method: Axes3D::SelectAll
//
// Purpose: 
//   Selects all attributes.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void
Axes3D::SelectAll()
{
    Select(ID_visible,         (void *)&visible);
    Select(ID_autoSetTicks,    (void *)&autoSetTicks);
    Select(ID_autoSetScaling,  (void *)&autoSetScaling);
    Select(ID_lineWidth,       (void *)&lineWidth);
    Select(ID_tickLocation,    (void *)&tickLocation);
    Select(ID_axesType,        (void *)&axesType);
    Select(ID_triadFlag,       (void *)&triadFlag);
    Select(ID_bboxFlag,        (void *)&bboxFlag);
    Select(ID_xAxis,           (void *)&xAxis);
    Select(ID_yAxis,           (void *)&yAxis);
    Select(ID_zAxis,           (void *)&zAxis);
    Select(ID_setBBoxLocation, (void *)&setBBoxLocation);
    Select(ID_bboxLocation,    (void *)bboxLocation, 6);
}

///////////////////////////////////////////////////////////////////////////////
// Persistence methods
///////////////////////////////////////////////////////////////////////////////

// ****************************************************************************
// Method: Axes3D::CreateNode
//
// Purpose: 
//   This method creates a DataNode representation of the object so it can be saved to a config file.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

bool
Axes3D::CreateNode(DataNode *parentNode, bool completeSave, bool forceAdd)
{
    if(parentNode == 0)
        return false;

    Axes3D defaultObject;
    bool addToParent = false;
    // Create a node for Axes3D.
    DataNode *node = new DataNode("Axes3D");

    if(completeSave || !FieldsEqual(ID_visible, &defaultObject))
    {
        addToParent = true;
        node->AddNode(new DataNode("visible", visible));
    }

    if(completeSave || !FieldsEqual(ID_autoSetTicks, &defaultObject))
    {
        addToParent = true;
        node->AddNode(new DataNode("autoSetTicks", autoSetTicks));
    }

    if(completeSave || !FieldsEqual(ID_autoSetScaling, &defaultObject))
    {
        addToParent = true;
        node->AddNode(new DataNode("autoSetScaling", autoSetScaling));
    }

    if(completeSave || !FieldsEqual(ID_lineWidth, &defaultObject))
    {
        addToParent = true;
        node->AddNode(new DataNode("lineWidth", lineWidth));
    }

    if(completeSave || !FieldsEqual(ID_tickLocation, &defaultObject))
    {
        addToParent = true;
        node->AddNode(new DataNode("tickLocation", Location_ToString(tickLocation)));
    }

    if(completeSave || !FieldsEqual(ID_axesType, &defaultObject))
    {
        addToParent = true;
        node->AddNode(new DataNode("axesType", Axes_ToString(axesType)));
    }

    if(completeSave || !FieldsEqual(ID_triadFlag, &defaultObject))
    {
        addToParent = true;
        node->AddNode(new DataNode("triadFlag", triadFlag));
    }

    if(completeSave || !FieldsEqual(ID_bboxFlag, &defaultObject))
    {
        addToParent = true;
        node->AddNode(new DataNode("bboxFlag", bboxFlag));
    }

    if(completeSave || !FieldsEqual(ID_xAxis, &defaultObject))
    {
        DataNode *xAxisNode = new DataNode("xAxis");
        if(xAxis.CreateNode(xAxisNode, completeSave, false))
        {
            addToParent = true;
            node->AddNode(xAxisNode);
        }
        else
            delete xAxisNode;
    }

    if(completeSave || !FieldsEqual(ID_yAxis, &defaultObject))
    {
        DataNode *yAxisNode = new DataNode("yAxis");
        if(yAxis.CreateNode(yAxisNode, completeSave, false))
        {
            addToParent = true;
            node->AddNode(yAxisNode);
        }
        else
            delete yAxisNode;
    }

    if(completeSave || !FieldsEqual(ID_zAxis, &defaultObject))
    {
        DataNode *zAxisNode = new DataNode("zAxis");
        if(zAxis.CreateNode(zAxisNode, completeSave, false))
        {
            addToParent = true;
            node->AddNode(zAxisNode);
        }
        else
            delete zAxisNode;
    }

    if(completeSave || !FieldsEqual(ID_setBBoxLocation, &defaultObject))
    {
        addToParent = true;
        node->AddNode(new DataNode("setBBoxLocation", setBBoxLocation));
    }

    if(completeSave || !FieldsEqual(ID_bboxLocation, &defaultObject))
    {
        addToParent = true;
        node->AddNode(new DataNode("bboxLocation", bboxLocation, 6));
    }


    // Add the node to the parent node.
    if(addToParent || forceAdd)
        parentNode->AddNode(node);
    else
        delete node;

    return (addToParent || forceAdd);
}

// ****************************************************************************
// Method: Axes3D::SetFromNode
//
// Purpose: 
//   This method sets attributes in this object from values in a DataNode representation of the object.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void
Axes3D::SetFromNode(DataNode *parentNode)
{
    if(parentNode == 0)
        return;

    DataNode *searchNode = parentNode->GetNode("Axes3D");
    if(searchNode == 0)
        return;

    DataNode *node;
    if((node = searchNode->GetNode("visible")) != 0)
        SetVisible(node->AsBool());
    if((node = searchNode->GetNode("autoSetTicks")) != 0)
        SetAutoSetTicks(node->AsBool());
    if((node = searchNode->GetNode("autoSetScaling")) != 0)
        SetAutoSetScaling(node->AsBool());
    if((node = searchNode->GetNode("lineWidth")) != 0)
        SetLineWidth(node->AsInt());
    if((node = searchNode->GetNode("tickLocation")) != 0)
    {
        // Allow enums to be int or string in the config file
        if(node->GetNodeType() == INT_NODE)
        {
            int ival = node->AsInt();
            if(ival >= 0 && ival < 3)
                SetTickLocation(Location(ival));
        }
        else if(node->GetNodeType() == STRING_NODE)
        {
            Location value;
            if(Location_FromString(node->AsString(), value))
                SetTickLocation(value);
        }
    }
    if((node = searchNode->GetNode("axesType")) != 0)
    {
        // Allow enums to be int or string in the config file
        if(node->GetNodeType() == INT_NODE)
        {
            int ival = node->AsInt();
            if(ival >= 0 && ival < 5)
                SetAxesType(Axes(ival));
        }
        else if(node->GetNodeType() == STRING_NODE)
        {
            Axes value;
            if(Axes_FromString(node->AsString(), value))
                SetAxesType(value);
        }
    }
    if((node = searchNode->GetNode("triadFlag")) != 0)
        SetTriadFlag(node->AsBool());
    if((node = searchNode->GetNode("bboxFlag")) != 0)
        SetBboxFlag(node->AsBool());
    if((node = searchNode->GetNode("xAxis")) != 0)
        xAxis.SetFromNode(node);
    if((node = searchNode->GetNode("yAxis")) != 0)
        yAxis.SetFromNode(node);
    if((node = searchNode->GetNode("zAxis")) != 0)
        zAxis.SetFromNode(node);
    if((node = searchNode->GetNode("setBBoxLocation")) != 0)
        SetSetBBoxLocation(node->AsBool());
    if((node = searchNode->GetNode("bboxLocation")) != 0)
        SetBboxLocation(node->AsDoubleArray());
}

///////////////////////////////////////////////////////////////////////////////
// Set property methods
///////////////////////////////////////////////////////////////////////////////

void
Axes3D::SetVisible(bool visible_)
{
    visible = visible_;
    Select(ID_visible, (void *)&visible);
}

void
Axes3D::SetAutoSetTicks(bool autoSetTicks_)
{
    autoSetTicks = autoSetTicks_;
    Select(ID_autoSetTicks, (void *)&autoSetTicks);
}

void
Axes3D::SetAutoSetScaling(bool autoSetScaling_)
{
    autoSetScaling = autoSetScaling_;
    Select(ID_autoSetScaling, (void *)&autoSetScaling);
}

void
Axes3D::SetLineWidth(int lineWidth_)
{
    lineWidth = lineWidth_;
    Select(ID_lineWidth, (void *)&lineWidth);
}

void
Axes3D::SetTickLocation(Axes3D::Location tickLocation_)
{
    tickLocation = tickLocation_;
    Select(ID_tickLocation, (void *)&tickLocation);
}

void
Axes3D::SetAxesType(Axes3D::Axes axesType_)
{
    axesType = axesType_;
    Select(ID_axesType, (void *)&axesType);
}

void
Axes3D::SetTriadFlag(bool triadFlag_)
{
    triadFlag = triadFlag_;
    Select(ID_triadFlag, (void *)&triadFlag);
}

void
Axes3D::SetBboxFlag(bool bboxFlag_)
{
    bboxFlag = bboxFlag_;
    Select(ID_bboxFlag, (void *)&bboxFlag);
}

void
Axes3D::SetXAxis(const AxisAttributes &xAxis_)
{
    xAxis = xAxis_;
    Select(ID_xAxis, (void *)&xAxis);
}

void
Axes3D::SetYAxis(const AxisAttributes &yAxis_)
{
    yAxis = yAxis_;
    Select(ID_yAxis, (void *)&yAxis);
}

void
Axes3D::SetZAxis(const AxisAttributes &zAxis_)
{
    zAxis = zAxis_;
    Select(ID_zAxis, (void *)&zAxis);
}

void
Axes3D::SetSetBBoxLocation(bool setBBoxLocation_)
{
    setBBoxLocation = setBBoxLocation_;
    Select(ID_setBBoxLocation, (void *)&setBBoxLocation);
}

void
Axes3D::SetBboxLocation(const double *bboxLocation_)
{
    for(int i = 0; i < 6; ++i)
        bboxLocation[i] = bboxLocation_[i];
    Select(ID_bboxLocation, (void *)bboxLocation, 6);
}

///////////////////////////////////////////////////////////////////////////////
// Get property methods
///////////////////////////////////////////////////////////////////////////////

bool
Axes3D::GetVisible() const
{
    return visible;
}

bool
Axes3D::GetAutoSetTicks() const
{
    return autoSetTicks;
}

bool
Axes3D::GetAutoSetScaling() const
{
    return autoSetScaling;
}

int
Axes3D::GetLineWidth() const
{
    return lineWidth;
}

Axes3D::Location
Axes3D::GetTickLocation() const
{
    return Location(tickLocation);
}

Axes3D::Axes
Axes3D::GetAxesType() const
{
    return Axes(axesType);
}

bool
Axes3D::GetTriadFlag() const
{
    return triadFlag;
}

bool
Axes3D::GetBboxFlag() const
{
    return bboxFlag;
}

const AxisAttributes &
Axes3D::GetXAxis() const
{
    return xAxis;
}

AxisAttributes &
Axes3D::GetXAxis()
{
    return xAxis;
}

const AxisAttributes &
Axes3D::GetYAxis() const
{
    return yAxis;
}

AxisAttributes &
Axes3D::GetYAxis()
{
    return yAxis;
}

const AxisAttributes &
Axes3D::GetZAxis() const
{
    return zAxis;
}

AxisAttributes &
Axes3D::GetZAxis()
{
    return zAxis;
}

bool
Axes3D::GetSetBBoxLocation() const
{
    return setBBoxLocation;
}

const double *
Axes3D::GetBboxLocation() const
{
    return bboxLocation;
}

double *
Axes3D::GetBboxLocation()
{
    return bboxLocation;
}

///////////////////////////////////////////////////////////////////////////////
// Select property methods
///////////////////////////////////////////////////////////////////////////////

void
Axes3D::SelectXAxis()
{
    Select(ID_xAxis, (void *)&xAxis);
}

void
Axes3D::SelectYAxis()
{
    Select(ID_yAxis, (void *)&yAxis);
}

void
Axes3D::SelectZAxis()
{
    Select(ID_zAxis, (void *)&zAxis);
}

void
Axes3D::SelectBboxLocation()
{
    Select(ID_bboxLocation, (void *)bboxLocation, 6);
}

///////////////////////////////////////////////////////////////////////////////
// Keyframing methods
///////////////////////////////////////////////////////////////////////////////

// ****************************************************************************
// Method: Axes3D::GetFieldName
//
// Purpose: 
//   This method returns the name of a field given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

std::string
Axes3D::GetFieldName(int index) const
{
    switch (index)
    {
    case ID_visible:         return "visible";
    case ID_autoSetTicks:    return "autoSetTicks";
    case ID_autoSetScaling:  return "autoSetScaling";
    case ID_lineWidth:       return "lineWidth";
    case ID_tickLocation:    return "tickLocation";
    case ID_axesType:        return "axesType";
    case ID_triadFlag:       return "triadFlag";
    case ID_bboxFlag:        return "bboxFlag";
    case ID_xAxis:           return "xAxis";
    case ID_yAxis:           return "yAxis";
    case ID_zAxis:           return "zAxis";
    case ID_setBBoxLocation: return "setBBoxLocation";
    case ID_bboxLocation:    return "bboxLocation";
    default:  return "invalid index";
    }
}

// ****************************************************************************
// Method: Axes3D::GetFieldType
//
// Purpose: 
//   This method returns the type of a field given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

AttributeGroup::FieldType
Axes3D::GetFieldType(int index) const
{
    switch (index)
    {
    case ID_visible:         return FieldType_bool;
    case ID_autoSetTicks:    return FieldType_bool;
    case ID_autoSetScaling:  return FieldType_bool;
    case ID_lineWidth:       return FieldType_linewidth;
    case ID_tickLocation:    return FieldType_enum;
    case ID_axesType:        return FieldType_enum;
    case ID_triadFlag:       return FieldType_bool;
    case ID_bboxFlag:        return FieldType_bool;
    case ID_xAxis:           return FieldType_att;
    case ID_yAxis:           return FieldType_att;
    case ID_zAxis:           return FieldType_att;
    case ID_setBBoxLocation: return FieldType_bool;
    case ID_bboxLocation:    return FieldType_doubleArray;
    default:  return FieldType_unknown;
    }
}

// ****************************************************************************
// Method: Axes3D::GetFieldTypeName
//
// Purpose: 
//   This method returns the name of a field type given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

std::string
Axes3D::GetFieldTypeName(int index) const
{
    switch (index)
    {
    case ID_visible:         return "bool";
    case ID_autoSetTicks:    return "bool";
    case ID_autoSetScaling:  return "bool";
    case ID_lineWidth:       return "linewidth";
    case ID_tickLocation:    return "enum";
    case ID_axesType:        return "enum";
    case ID_triadFlag:       return "bool";
    case ID_bboxFlag:        return "bool";
    case ID_xAxis:           return "att";
    case ID_yAxis:           return "att";
    case ID_zAxis:           return "att";
    case ID_setBBoxLocation: return "bool";
    case ID_bboxLocation:    return "doubleArray";
    default:  return "invalid index";
    }
}

// ****************************************************************************
// Method: Axes3D::FieldsEqual
//
// Purpose: 
//   This method compares two fields and return true if they are equal.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

bool
Axes3D::FieldsEqual(int index_, const AttributeGroup *rhs) const
{
    const Axes3D &obj = *((const Axes3D*)rhs);
    bool retval = false;
    switch (index_)
    {
    case ID_visible:
        {  // new scope
        retval = (visible == obj.visible);
        }
        break;
    case ID_autoSetTicks:
        {  // new scope
        retval = (autoSetTicks == obj.autoSetTicks);
        }
        break;
    case ID_autoSetScaling:
        {  // new scope
        retval = (autoSetScaling == obj.autoSetScaling);
        }
        break;
    case ID_lineWidth:
        {  // new scope
        retval = (lineWidth == obj.lineWidth);
        }
        break;
    case ID_tickLocation:
        {  // new scope
        retval = (tickLocation == obj.tickLocation);
        }
        break;
    case ID_axesType:
        {  // new scope
        retval = (axesType == obj.axesType);
        }
        break;
    case ID_triadFlag:
        {  // new scope
        retval = (triadFlag == obj.triadFlag);
        }
        break;
    case ID_bboxFlag:
        {  // new scope
        retval = (bboxFlag == obj.bboxFlag);
        }
        break;
    case ID_xAxis:
        {  // new scope
        retval = (xAxis == obj.xAxis);
        }
        break;
    case ID_yAxis:
        {  // new scope
        retval = (yAxis == obj.yAxis);
        }
        break;
    case ID_zAxis:
        {  // new scope
        retval = (zAxis == obj.zAxis);
        }
        break;
    case ID_setBBoxLocation:
        {  // new scope
        retval = (setBBoxLocation == obj.setBBoxLocation);
        }
        break;
    case ID_bboxLocation:
        {  // new scope
        // Compare the bboxLocation arrays.
        bool bboxLocation_equal = true;
        for(int i = 0; i < 6 && bboxLocation_equal; ++i)
            bboxLocation_equal = (bboxLocation[i] == obj.bboxLocation[i]);

        retval = bboxLocation_equal;
        }
        break;
    default: retval = false;
    }

    return retval;
}

///////////////////////////////////////////////////////////////////////////////
// User-defined methods.
///////////////////////////////////////////////////////////////////////////////

