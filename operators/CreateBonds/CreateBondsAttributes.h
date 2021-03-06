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

#ifndef CREATEBONDSATTRIBUTES_H
#define CREATEBONDSATTRIBUTES_H
#include <string>
#include <AttributeSubject.h>


// ****************************************************************************
// Class: CreateBondsAttributes
//
// Purpose:
//    Attributes for the CreateBondsOperator
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class CreateBondsAttributes : public AttributeSubject
{
public:
    // These constructors are for objects of this class
    CreateBondsAttributes();
    CreateBondsAttributes(const CreateBondsAttributes &obj);
protected:
    // These constructors are for objects derived from this class
    CreateBondsAttributes(private_tmfs_t tmfs);
    CreateBondsAttributes(const CreateBondsAttributes &obj, private_tmfs_t tmfs);
public:
    virtual ~CreateBondsAttributes();

    virtual CreateBondsAttributes& operator = (const CreateBondsAttributes &obj);
    virtual bool operator == (const CreateBondsAttributes &obj) const;
    virtual bool operator != (const CreateBondsAttributes &obj) const;
private:
    void Init();
    void Copy(const CreateBondsAttributes &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectElementVariable();
    void SelectAtomicNumber1();
    void SelectAtomicNumber2();
    void SelectMinDist();
    void SelectMaxDist();
    void SelectXVector();
    void SelectYVector();
    void SelectZVector();

    // Property setting methods
    void SetElementVariable(const std::string &elementVariable_);
    void SetAtomicNumber1(const intVector &atomicNumber1_);
    void SetAtomicNumber2(const intVector &atomicNumber2_);
    void SetMinDist(const doubleVector &minDist_);
    void SetMaxDist(const doubleVector &maxDist_);
    void SetMaxBondsClamp(int maxBondsClamp_);
    void SetAddPeriodicBonds(bool addPeriodicBonds_);
    void SetUseUnitCellVectors(bool useUnitCellVectors_);
    void SetPeriodicInX(bool periodicInX_);
    void SetPeriodicInY(bool periodicInY_);
    void SetPeriodicInZ(bool periodicInZ_);
    void SetXVector(const double *xVector_);
    void SetYVector(const double *yVector_);
    void SetZVector(const double *zVector_);

    // Property getting methods
    const std::string  &GetElementVariable() const;
          std::string  &GetElementVariable();
    const intVector    &GetAtomicNumber1() const;
          intVector    &GetAtomicNumber1();
    const intVector    &GetAtomicNumber2() const;
          intVector    &GetAtomicNumber2();
    const doubleVector &GetMinDist() const;
          doubleVector &GetMinDist();
    const doubleVector &GetMaxDist() const;
          doubleVector &GetMaxDist();
    int                GetMaxBondsClamp() const;
    bool               GetAddPeriodicBonds() const;
    bool               GetUseUnitCellVectors() const;
    bool               GetPeriodicInX() const;
    bool               GetPeriodicInY() const;
    bool               GetPeriodicInZ() const;
    const double       *GetXVector() const;
          double       *GetXVector();
    const double       *GetYVector() const;
          double       *GetYVector();
    const double       *GetZVector() const;
          double       *GetZVector();

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;


    // IDs that can be used to identify fields in case statements
    enum {
        ID_elementVariable = 0,
        ID_atomicNumber1,
        ID_atomicNumber2,
        ID_minDist,
        ID_maxDist,
        ID_maxBondsClamp,
        ID_addPeriodicBonds,
        ID_useUnitCellVectors,
        ID_periodicInX,
        ID_periodicInY,
        ID_periodicInZ,
        ID_xVector,
        ID_yVector,
        ID_zVector,
        ID__LAST
    };

private:
    std::string  elementVariable;
    intVector    atomicNumber1;
    intVector    atomicNumber2;
    doubleVector minDist;
    doubleVector maxDist;
    int          maxBondsClamp;
    bool         addPeriodicBonds;
    bool         useUnitCellVectors;
    bool         periodicInX;
    bool         periodicInY;
    bool         periodicInZ;
    double       xVector[3];
    double       yVector[3];
    double       zVector[3];

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define CREATEBONDSATTRIBUTES_TMFS "si*i*d*d*ibbbbbDDD"

#endif
