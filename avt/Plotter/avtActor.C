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
//                                  avtActor.C                               //
// ************************************************************************* //

#include <avtActor.h>
#include <vtkRenderer.h>
#include <avtTransparencyActor.h>
#include <ColorAttribute.h>


// ****************************************************************************
//  Method: avtActor constructor
//
//  Programmer: Hank Childs
//  Creation:   December 21, 2000
//
//  Modifications:
//
//    Hank Childs, Sun Jul  7 12:55:05 PDT 2002
//    Initialized new data member 'transparencyActor'.
//
//    Kathleen Bonnell, Fri Jul 12 16:10:49 PDT 2002 
//    Add support for a decorations drawable.
//
//    Mark C. Miller, Thu Dec 19 16:19:23 PST 2002
//    Added new data members, extRenderedImagesActor and extRenderedImageId
//    Added initialization for transparencyIndex;
//
//    Mark C. Miller, Tue May 11 20:21:24 PDT 2004
//    Elminated extRenderedImagesActor and extRenderedImageId
//
//    Chris Wojtan, Fri Jul 23 14:13:44 PDT 2004
//    Initialize isVisible to true.
//
//    Mark Blair, Wed Aug 30 14:09:00 PDT 2006
//    Initialize typeName to indicate unknown.
//
//    Brad Whitlock, Mon Mar 19 17:39:01 PST 2007
//    Added actorName.
//
// ****************************************************************************

avtActor::avtActor()
{
    behavior               = NULL;
    drawable               = NULL;
    decorations            = NULL;
    renderer               = NULL;
    transparencyActor      = NULL;
    transparencyIndex      = -1;
    isVisible              = true;
    typeName               = "<unknown>";
    actorName              = new char[1];
    actorName[0] = '\0';
}


// ****************************************************************************
//  Method: avtActor destructor
//
//  Programmer: Hank Childs
//  Creation:   June 25, 2003
//
// ****************************************************************************

avtActor::~avtActor()
{
    if (transparencyActor != NULL && transparencyIndex >= 0)
    {
        transparencyActor->RemoveInput(transparencyIndex);
    }

    if(actorName != NULL)
    {
        delete [] actorName;
        actorName = NULL;
    }
}


// ****************************************************************************
//  Method: avtActor::SetBehavior
//
//  Purpose:
//      Sets the behavior of the actor.
//
//  Arguments:
//      b      The behavior for this actor.
//
//  Programmer: Hank Childs
//  Creation:   December 28, 2000
//
// ****************************************************************************

void
avtActor::SetBehavior(avtBehavior_p b)
{
    behavior = b;
}


// ****************************************************************************
//  Method: avtActor::SetDrawable
//
//  Purpose:
//      Sets the drawable of the actor.
//
//  Arguments:
//      d      The drawable for this actor.
//
//  Programmer: Hank Childs
//  Creation:   December 28, 2000
//
//  Modifications:
//
//    Hank Childs, Wed Apr  7 08:03:14 PDT 2004
//    Check to make sure the drawable input is not NULL as well.
//
// ****************************************************************************

void
avtActor::SetDrawable(avtDrawable_p d)
{
    drawable = d;
    if ((renderer != NULL) && (*drawable != NULL))
    {
        drawable->Add(renderer);
    }
}


// ****************************************************************************
//  Method: avtActor::SetDecorations
//
//  Purpose:
//      Sets the deocorations of the actor.
//
//  Arguments:
//      d      The decorations for this actor.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   July 12, 2002 
//
// ****************************************************************************

void
avtActor::SetDecorations(avtDrawable_p d)
{
    decorations = d;
    if (*(decorations) != NULL && renderer != NULL)
    {
        decorations->Add(renderer);
    }
}


// ****************************************************************************
//  Method: avtActor::SetTypeName
//
//  Purpose: Sets the actor's type name.  This can be set, for instance, to the
//           type name of the actor's associated plot.
//
//  Arguments:
//      typeName : The type name to be associated with the actor.
//
//  Programmer: Mark Blair
//  Creation:   Wed Aug 30 14:09:00 PDT 2006
//
// ****************************************************************************

void avtActor::SetTypeName(const char *typeName_)
{
    typeName = typeName_;
}


// ****************************************************************************
//  Method: avtActor::GetTypeName
//
//  Purpose: Gets the actor's type name (such as type name of associated plot).
//
//  Arguments:
//      typeName : The type name associated with the actor.
//
//  Programmer: Mark Blair
//  Creation:   Wed Aug 30 14:09:00 PDT 2006
//
// ****************************************************************************

const char *avtActor::GetTypeName()
{
    return typeName;
}

// ****************************************************************************
// Method: avtActor::GetActorName
//
// Purpose: 
//   Get the actor's name.
//
// Programmer: Brad Whitlock
// Creation:   Mon Mar 19 17:43:14 PST 2007
//
// Modifications:
//   
// ****************************************************************************

const char *
avtActor::GetActorName() const
{
    return actorName;
}

// ****************************************************************************
// Method: avtActor::SetActorName
//
// Purpose: 
//   Set the actor's name.
//
// Arguments:
//   newName : The new name for the actor.
//
// Programmer: Brad Whitlock
// Creation:   Mon Mar 19 17:43:03 PST 2007
//
// Modifications:
//   
// ****************************************************************************

void
avtActor::SetActorName(const char *newName)
{
    if(newName != NULL)
    {
        delete [] actorName;
        actorName = new char[strlen(newName) + 1];
        strcpy(actorName, newName);
    }
}

// ****************************************************************************
//  Method: avtActor::Add
//
//  Purpose:
//      Adds the actor to a renderer.
//
//  Arguments:
//      renderingCanvas   The canvas that the rendering takes place on.  This
//                        is for the drawable.
//      decorationCanvas  The canvas that decorations should be placed on.
//                        This is for the behavior.
//
//  Programmer: Hank Childs
//  Creation:   December 21, 2000
//
//  Modifications:
//
//    Hank Childs, Thu Mar  8 10:58:27 PST 2001
//    Added second renderer so 2D plots could work well.
//
//    Hank Childs, Sun Jul  7 12:55:05 PDT 2002
//    Add support for transparency.
//
//    Kathleen Bonnell, Fri Jul 12 16:10:49 PDT 2002 
//    Add support for a decorations drawable.
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

void
avtActor::Add(vtkRenderer *renderingCanvas, vtkRenderer *decorationCanvas)
{
    if (*behavior != NULL)
        behavior->Add(decorationCanvas);
    if (*drawable != NULL)
        drawable->Add(renderingCanvas);
    if (*decorations != NULL)
        decorations->Add(renderingCanvas);

    renderer = renderingCanvas;

    if (transparencyActor != NULL && transparencyIndex >=0)
    {
        transparencyActor->TurnOnInput(transparencyIndex);
    }
}


// ****************************************************************************
//  Method: avtActor::Remove
//
//  Purpose:
//      Removes the actor from a renderer.
//
//  Arguments:
//      renderingCanvas   The canvas that the rendering takes place on.  This
//                        is for the drawable.
//      decorationCanvas  The canvas that decorations should be placed on.
//                        This is for the behavior.
//
//  Programmer: Hank Childs
//  Creation:   December 21, 2000
//
//  Modifications:
//
//    Hank Childs, Thu Mar  8 10:58:27 PST 2001
//    Added second renderer so 2D plots could work well.
//
//    Hank Childs, Sun Jul  7 12:55:05 PDT 2002
//    Add support for transparency.
//
//    Kathleen Bonnell, Fri Jul 12 16:10:49 PDT 2002 
//    Add support for a decorations drawable.
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

void
avtActor::Remove(vtkRenderer *renderingCanvas, vtkRenderer *decorationCanvas)
{
    if (*behavior != NULL)
        behavior->Remove(decorationCanvas);
    if (*drawable != NULL)
        drawable->Remove(renderingCanvas);
    if (*decorations != NULL)
        decorations->Remove(renderingCanvas);

    renderer = NULL;

    if (transparencyActor != NULL && transparencyIndex >= 0)
    {
        transparencyActor->TurnOffInput(transparencyIndex);
    }
}


// ****************************************************************************
//  Method: avtActor::GetOriginalBounds
//
//  Purpose:
//      Gets the original bounds of an actor.
//
//  Arguments:
//      bounds    A place to put the bounds.
//
//  Programmer:   Hank Childs
//  Creation:     December 21, 2000
//
//  Modifications:
//
//    Hank Childs, Mon Jul 15 09:07:25 PDT 2002
//    Renamed to GetOriginalBounds (from GetBounds).
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

void
avtActor::GetOriginalBounds(double bounds[6])
{
    if (*behavior != NULL)
        behavior->GetOriginalBounds(bounds);
}


// ****************************************************************************
//  Method: avtActor::GetActualBounds
//
//  Purpose:
//      Gets the actual bounds of an actor.
//
//  Arguments:
//      bounds    A place to put the bounds.
//
//  Programmer:   Hank Childs
//  Creation:     July 15, 2002
//
//  Modifications:
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

void
avtActor::GetActualBounds(double bounds[6])
{
    if (*behavior != NULL)
        behavior->GetActualBounds(bounds);
}


// ****************************************************************************
//  Method: avtActor::GetDimension
//
//  Purpose:
//      Gets the dimension of the plot.
//
//  Returns:    the spatial dimension of the plot
//
//  Programmer: Hank Childs
//  Creation:   December 28, 2000
//
//  Modifications:
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

int
avtActor::GetDimension(void)
{
    if (*behavior != NULL)
        return behavior->GetDimension();
    return -1;
}


// ****************************************************************************
//  Method: avtActor::GetWindowMode
//
//  Purpose:
//      Gets the window mode of the plot.
//
//  Returns:    the window mode of the plot
//
//  Programmer: Eric Brugger
//  Creation:   August 20, 2003
//
//  Modifications:
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

WINDOW_MODE
avtActor::GetWindowMode(void)
{
    if (*behavior != NULL)
        return behavior->GetWindowMode();
    return WINMODE_NONE;
}


// ****************************************************************************
//  Method: avtActor::AdaptsToAnyWindowMode
//
//  Purpose:
//      Tells whether the actor can adapt to any window mode.
//
//  Returns:    true if the actor can adapt to any window mode, false otherwise
//
//  Programmer: Hank Childs
//  Creation:   August 30, 2007
//
//  Modifications:
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

bool
avtActor::AdaptsToAnyWindowMode(void)
{
    if (*behavior != NULL)
        return behavior->AdaptsToAnyWindowMode();
    return true;
}


// ****************************************************************************
//  Method: avtActor::GetRenderOrder
//
//  Purpose:
//      Gets the render order of the plot.
//
//  Arguments:
//    aa  Indicates antialiasing mode.
//
//  Returns:    the render order of the plot
//
//  Programmer: Kathleen Bonnell 
//  Creation:   April 3, 2001 
//
//  Modifications:
//    Kathleen Bonnell, Mon Sep 29 13:44:01 PDT 2003
//    Added bool argument.
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

int
avtActor::GetRenderOrder(bool aa)
{
    if (*behavior != NULL)
        return behavior->GetRenderOrder(aa);
    return -1;
}


// ****************************************************************************
//  Method: avtActor::GetLegend
//
//  Purpose:
//      Gets the legend from the behavior.
//
//  Returns:     A legend, NULL is possible if there is no legend.
//
//  Programmer:  Hank Childs
//  Creation:    December 28, 2000
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

avtLegend_p
avtActor::GetLegend(void)
{
    if (*behavior != NULL)
        return behavior->GetLegend();
    return 0;
}


// ****************************************************************************
//  Method: avtActor::VisibilityOff
//
//  Purpose:
//      Has a drawable remove itself from the scene for something along the
//      lines of bounding box mode.
//
//  Programmer: Hank Childs
//  Creation:   December 28, 2000
//
//  Modifications:
//
//    Hank Childs, Sun Jul  7 12:55:05 PDT 2002
//    Add support for transparency.
//
//    Hank Childs, Thu Jul 11 16:07:53 PDT 2002
//    Use the concept of 'visibility' for the transparency actor, rather
//    than turning it on and off.
//
//    Chris Wojtan, Fri Jul 23 14:13:44 PDT 2004
//    set isVisible to false
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

void
avtActor::VisibilityOff(void)
{
    if (*drawable != NULL)
        drawable->VisibilityOff();
    isVisible = false;

    if (transparencyActor != NULL && transparencyIndex >= 0)
    {
        transparencyActor->SetVisibility(transparencyIndex, false);
    }
}


// ****************************************************************************
//  Method: avtActor::VisibilityOn
//
//  Purpose:
//      Has a drawable add itself back to the scene after something along the
//      lines of bounding box mode.
//
//  Programmer: Hank Childs
//  Creation:   December 28, 2000
//
//  Modifications:
//
//    Hank Childs, Sun Jul  7 12:55:05 PDT 2002
//    Add support for transparency.
//
//    Hank Childs, Thu Jul 11 16:07:53 PDT 2002
//    Use the concept of 'visibility' for the transparency actor, rather
//    than turning it on and off.
//
//    Chris Wojtan, Fri Jul 23 14:14:08 PDT 2004
//    set isVisible to true
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

void
avtActor::VisibilityOn(void)
{
    if (*drawable != NULL)
        drawable->VisibilityOn();
    isVisible = true;

    if (transparencyActor != NULL && transparencyIndex >= 0)
    {
        transparencyActor->SetVisibility(transparencyIndex, true);
    }
}


// ****************************************************************************
//  Method: avtActor::ShiftByVector
//
//  Purpose:
//      Shifts the actor by a vector.
//
//  Arguments:
//      vec     The vector to shift by.
//
//  Programmer: Hank Childs
//  Creation:   March 12, 2001
//
// ****************************************************************************

void
avtActor::ShiftByVector(const double vec[3])
{
    //
    // Not all plots should be shifted by the same amount.  The behavior has
    // a factor (presumably between 0 and 1) that will determine by what
    // amount to shift.
    //
    double f = behavior->GetShiftFactor();

    double v[3];
    v[0] = vec[0]*f;
    v[1] = vec[1]*f;
    v[2] = vec[2]*f;

    drawable->ShiftByVector(v);
}


// ****************************************************************************
//  Method: avtActor::ScaleByVector
//
//  Purpose:
//      Scale the actor component-wise by a vector.
//
//  Arguments:
//      vec     The vector to scale by.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   July 12, 2002 
//
//  Modifications:
//    Kathleen Bonnell, Wed Jul 16 16:40:47 PDT 2003
//    Scale the transparency actor.
//
// ****************************************************************************

void
avtActor::ScaleByVector(const double vec[3])
{
    drawable->ScaleByVector(vec);
    if (*decorations != NULL)
    {
        decorations->ScaleByVector(vec);
    }
    if (transparencyActor != NULL && transparencyIndex >= 0)
    {
        transparencyActor->ScaleByVector(vec);
    }
}



// ****************************************************************************
//  Method: avtActor::GetDataExtents
//
//  Purpose:
//      Gets the data extents of an actor.
//
//  Arguments:
//      dmin    A place to put minimum value. 
//      dmax    A place to put maximum value. 
//
//  Programmer:   Kathleen Bonnell 
//  Creation:     May 7, 2002 
//
//  Modifications:
//
//    Mark C. Miller, Tue Apr 13 13:11:03 PDT 2010
//    Replaced EXCEPTION with test(s) for non-NULL and doing what we can.
//    In cases where a value is returned where we would have otherwise
//    thrown an exception, the resultant returned value was chosen as
//    best as possible.
// ****************************************************************************

void
avtActor::GetDataExtents(double &dmin, double &dmax) 
{
    if (*behavior != NULL)
        behavior->GetDataExtents(dmin, dmax);
}


// ****************************************************************************
//  Method: avtActor::GetDataObject
//
//  Purpose:
//      Gets the data objects added to this actor.
//
//  Programmer: Hank Childs
//  Creation:   May 24, 2002
//
//  Modifications:
//
//    Hank Childs, Sun May 26 18:37:23 PDT 2002
//    Changed interface to return an avtDataObject directly.  This is a more
//    general interface and allows us to not modify the tree structure for an
//    avtDataset.
//
// ****************************************************************************

avtDataObject_p
avtActor::GetDataObject(void)
{
    return drawable->GetDataObject();
}


// ****************************************************************************
//  Method: avtActor::SetTransparencyActor
//
//  Purpose:
//      Sets the transparency actor that this actor must notify of changes in
//      status.
//
//  Programmer: Hank Childs
//  Creation:   July 7, 2002
//
//  Modifications:
//
//    Hank Childs, Thu Mar  8 11:08:53 PST 2007
//    Initialize the transparency actor with a good default.  If there should
//    be a scale factor, that will be determined later.
//
// ****************************************************************************

void
avtActor::SetTransparencyActor(avtTransparencyActor *actor)
{
    transparencyActor = actor;
    transparencyIndex = drawable->SetTransparencyActor(transparencyActor);

    double vec[3] = { 1, 1, 1 };
    transparencyActor->ScaleByVector(vec);
}


// ****************************************************************************
//  Method: avtActor::UpdateScaleFactor
//
//  Purpose:
//      Tells the decorations to update the scale factor. 
//
//  Programmer: Kathleen Bonenll 
//  Creation:   July 19, 2002
//
// ****************************************************************************

void
avtActor::UpdateScaleFactor()
{
    if (*(decorations) != NULL)
    {
        decorations->UpdateScaleFactor();
    }
}


// ****************************************************************************
//  Method: avtActor::TurnLightingOn
//
//  Purpose:
//      Tells the drawable to update the lighting coefficients. 
//
//  Programmer: Kathleen Bonenll 
//  Creation:   August 13, 2002
//
// ****************************************************************************

void
avtActor::TurnLightingOn()
{
    if (*(drawable) != NULL)
    {
        drawable->TurnLightingOn();
    }
}


// ****************************************************************************
//  Method: avtActor::TurnLightingOff
//
//  Purpose:
//      Tells the drawable to update the lighting coefficients. 
//
//  Programmer: Kathleen Bonenll 
//  Creation:   August 13, 2002
//
// ****************************************************************************

void
avtActor::TurnLightingOff()
{
    if (*(drawable) != NULL)
    {
        drawable->TurnLightingOff();
    }
}


// ****************************************************************************
//  Method: avtActor::SetAmbientCoefficient
//
//  Purpose:
//      Tells the drawable to update the ambient lighting coefficient. 
//
//  Programmer: Kathleen Bonenll 
//  Creation:   August 13, 2002
//
// ****************************************************************************

void
avtActor::SetAmbientCoefficient(const double amb)
{
    if (*(drawable) != NULL)
    {
        drawable->SetAmbientCoefficient(amb);
    }
}

// ****************************************************************************
//  Method: avtActor::SetSurfaceRepresentation
//
//  Purpose:
//      Tells the drawable to set its surface representation. 
//
//  Programmer: Brad Whitlock
//  Creation:   Mon Sep 23 15:54:15 PST 2002
//
// ****************************************************************************

void
avtActor::SetSurfaceRepresentation(int rep)
{
    if (*(drawable) != NULL)
    {
        drawable->SetSurfaceRepresentation(rep);
    }
}

// ****************************************************************************
//  Method: avtActor::SetImmediateModeRendering
//
//  Purpose:
//      Tells the drawable adn the decorations to set their immediate mode
//      rendering flags. 
//
//  Programmer: Brad Whitlock
//  Creation:   Mon Sep 23 15:54:15 PST 2002
//
// ****************************************************************************

void
avtActor::SetImmediateModeRendering(bool val)
{
    if (*(drawable) != NULL)
    {
        drawable->SetImmediateModeRendering(val);
    }

    if (*(decorations) != NULL)
    {
        decorations->SetImmediateModeRendering(val);
    }
}

// ****************************************************************************
//  Method: avtActor::SetSpecularProperties
//
//  Purpose:
//      Tells the drawable to set its specular properties. 
//
//  Arguments:
//      coeff :  the new specular coefficient
//      power :  the new specular power
//      color :  the new specular color
//
//  Programmer: Jeremy Meredith
//  Creation:   November 14, 2003
//
// ****************************************************************************

void
avtActor::SetSpecularProperties(bool flag, double coeff, double power,
                                const ColorAttribute &color)
{
    if (*(drawable) != NULL)
    {
        if (GetWindowMode() == WINMODE_3D)
            drawable->SetSpecularProperties(flag,coeff,power,color);
        else
            drawable->SetSpecularProperties(false,0,0,ColorAttribute(0,0,0));
    }
}

// ****************************************************************************
// Method: avtActor::SetColorTexuringFlag
//
// Purpose: 
//   Sets the actor's color texturing flag.
//
// Arguments:
//   val : The new color texturing flag value.
//
// Programmer: Brad Whitlock
// Creation:   Mon Sep 18 11:20:20 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
avtActor::SetColorTexturingFlag(bool val)
{
    if (*(drawable) != NULL)
    {
        drawable->SetColorTexturingFlag(val);
    } 
}

// *******************************************************************************
//   Method: avtActor::IsVisible
//
//   Purpose:
//       returns true if this actor is supposed to be drawn to the screen,
//       false otherwise.
//
//   Programmer: Chris Wojtan
//   Creation:   Fri Jul 23 14:00:09 PDT 2004
//
// *******************************************************************************

bool
avtActor::IsVisible()
{
    return isVisible;
}


// ******************************************************************************
//   Method: avtActor::OpaqueVisibilityOn
//
//   Purpose:
//       make the actor visible if it is opaque
//
//   Programmer: Chris Wojtan
//   Creation:   Mon Jul 26 17:22:57 PDT 2004
//
// ******************************************************************************

void
avtActor::OpaqueVisibilityOn()
{
    drawable->VisibilityOn();
}


// ******************************************************************************
//   Method: avtActor::OpaqueVisibilityOff
//
//   Purpose:
//       make the actor invisible if it is opaque
//
//   Programmer: Chris Wojtan
//   Creation:   Mon Jul 26 17:22:57 PDT 2004
//
// ******************************************************************************

void
avtActor::OpaqueVisibilityOff()
{
    drawable->VisibilityOff();
}

// ****************************************************************************
//  Method: avtActor::MakePickable
//
//  Purpose:
//    Tells the drawable to make its vtkActors pickable. 
//
//  Programmer: Kathleen Bonnell 
//  Creation:   September 27, 2004 
//
// ****************************************************************************

void
avtActor::MakePickable()
{
    if (*(drawable) != NULL)
    {
        drawable->MakePickable();
    }
}


// ****************************************************************************
//  Method: avtActor::MakeUnPickable
//
//  Purpose:
//    Tells the drawable to make its vtkActors unpickable. 
//
//  Programmer: Kathleen Bonnell 
//  Creation:   September 27, 2004 
//
// ****************************************************************************

void
avtActor::MakeUnPickable()
{
    if (*(drawable) != NULL)
    {
        drawable->MakeUnPickable();
    }
}


// ****************************************************************************
//  Method: avtActor::GetZPosition
//
//  Purpose:
//    Retrieves the z-position of the underlying vtk actor. 
//
//  Programmer: Kathleen Bonnell 
//  Creation:   June 27, 2005 
//
// ****************************************************************************

double
avtActor::GetZPosition()
{
    return drawable->GetZPosition();
}

// ****************************************************************************
// Method: avtActor::ReducedDetailModeOn
//
// Purpose: 
//   Set whether the actor should use reduced detail when rendering.
//
// Programmer: Brad Whitlock
// Creation:   Wed Aug 22 11:00:22 PDT 2007
//
// Modifications:
//   
// ****************************************************************************

void
avtActor::ReducedDetailModeOn()
{
    drawable->ReducedDetailModeOn();
}

// ****************************************************************************
// Method: avtActor::ReducedDetailModeOff
//
// Purpose: 
//   Turn off reduced detail mode.
//
// Returns:
//   True if the actor needs a re-render to return to regular appearance;
//   false otherwise.
//
// Programmer: Brad Whitlock
// Creation:   Wed Aug 22 11:00:22 PDT 2007
//
// Modifications:
//   
// ****************************************************************************

bool
avtActor::ReducedDetailModeOff()
{
    return drawable->ReducedDetailModeOff();
}
