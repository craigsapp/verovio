/////////////////////////////////////////////////////////////////////////////
// Name:        tempo.h
// Author:      Laurent Pugin
// Created:     2015
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_TEMPO_H__
#define __VRV_TEMPO_H__

#include "floatingelement.h"
#include "textdirinterface.h"
#include "timeinterface.h"

namespace vrv {

class TextElement;

//----------------------------------------------------------------------------
// Tempo
//----------------------------------------------------------------------------

/**
 * This class is an interface for <tempo> elements at the measure level
 */
class Tempo : public FloatingElement, public TextDirInterface, public TimePointInterface {
public:
    /**
     * @name Constructors, destructors, reset methods
     * Reset method resets all attribute classes
     */
    ///@{
    Tempo();
    virtual ~Tempo();
    virtual void Reset();
    virtual std::string GetClassName() const { return "Tempo"; };
    virtual ClassId Is() const { return TEMPO; };
    ///@}

    virtual TextDirInterface *GetTextDirInterface() { return dynamic_cast<TextDirInterface *>(this); }
    virtual TimePointInterface *GetTimePointInterface() { return dynamic_cast<TimePointInterface *>(this); }

    /**
     * Add an element (text, rend. etc.) to a tempo.
     * Only supported elements will be actually added to the child list.
     */
    void AddTextElement(TextElement *element);

private:
    //
public:
    //
private:
};

} // namespace vrv

#endif
