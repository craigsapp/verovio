/////////////////////////////////////////////////////////////////////////////
// Name:        aligner.h
// Author:      Laurent Pugin
// Created:     2013
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_ALIGNER_H__
#define __VRV_ALIGNER_H__

#include "object.h"

namespace vrv {

class GraceAligner;
class MeasureAligner;
class Note;
class StaffAlignment;
class SystemAligner;
class TimestampAttr;

/**
 * Alignment types for aligning types together.
 * For example, we align notes and rests (default) together, clefs separately, etc.
 * The container is a generic alignment for tuplet, chords, beams, etc.; we need
 * this to avoid notes aligning to it
 */
enum AlignmentType {
    // Non-justifiable
    ALIGNMENT_MEASURE_START = 0,
    ALIGNMENT_BARLINE,
    ALIGNMENT_CLEF_ATTR,
    ALIGNMENT_KEYSIG_ATTR,
    ALIGNMENT_MENSUR_ATTR,
    ALIGNMENT_METERSIG_ATTR,
    // Justifiable
    ALIGNMENT_CLEF,
    ALIGNMENT_KEYSIG,
    ALIGNMENT_MENSUR,
    ALIGNMENT_METERSIG,
    ALIGNMENT_DOT,
    ALIGNMENT_GRACENOTE,
    ALIGNMENT_CONTAINER,
    ALIGNMENT_FULLMEASURE,
    ALIGNMENT_FULLMEASURE2,
    ALIGNMENT_ACCID,
    ALIGNMENT_DEFAULT,
    ALIGNMENT_MEASURE_END
};

//----------------------------------------------------------------------------
// SystemAligner
//----------------------------------------------------------------------------

/**
 * This class aligns the content of a system
 * It contains a vector of StaffAlignment
 */
class SystemAligner : public Object {
public:
    // constructors and destructors
    SystemAligner();
    virtual ~SystemAligner();
    virtual ClassId Is() const { return SYSTEM_ALIGNER; }

    int GetStaffAlignmentCount() const { return (int)m_children.size(); };

    /**
     * Reset the aligner (clear the content) and creates the end (bottom) alignement
     */
    virtual void Reset();

    /**
     * Get bottom StaffAlignment for the system.
     * For each SystemAligner, we keep a StaffAlignment for the bottom position.
     */
    StaffAlignment *GetBottomAlignment() const { return m_bottomAlignment; };

    /**
     * Get the StaffAlignment at index idx.
     * Creates the StaffAlignment if not there yet.
     * Checks the they are created incrementally (without gap).
     * If a staff is passed, it will be used for initializing m_staffN and m_staffSize of the aligner.
     * (no const since the bottom alignment is temporarily removed)
     */
    StaffAlignment *GetStaffAlignment(int idx, Staff *staff, Doc *doc);

    /**
     * Get the StaffAlignment for the staffN.
     * Return NULL if not found.
     */
    StaffAlignment *GetStaffAlignmentForStaffN(int staffN) const;

private:
    //
public:
    //
private:
    /**
     * A pointer to the left StaffAlignment object kept for the system bottom position
     */
    StaffAlignment *m_bottomAlignment;
};

//----------------------------------------------------------------------------
// StaffAlignment
//----------------------------------------------------------------------------

/**
 * This class stores an alignement position staves will point to
 */
class StaffAlignment : public Object {
public:
    /**
     * @name Constructors, destructors, reset methods
     * Reset method reset all attribute classes
     */
    ///@{
    StaffAlignment();
    virtual ~StaffAlignment();
    virtual ClassId Is() const { return STAFF_ALIGNMENT; }
    ///@}

    /**
     * @name Setter and getter for y
     */
    void SetYRel(int yRel) { m_yRel = yRel; };
    int GetYRel() const { return m_yRel; };

    void SetYShift(int yShift);
    int GetYShift() const { return m_yShift; };

    /**
     * @name Set and get verse count.
     * When setting a value of 0, then 1 is assumed. This occurs
     * Typically with one single verse and no @n in <verse>
     */
    ///@{
    void SetVerseCount(int verse_count);
    int GetVerseCount() const { return m_verseCount; };

    /**
     * @name Setter and getter for above or below dir/dynam/hairpin
     * Currently unused
     */
    ///@{
    void SetDirAbove() { m_dirAbove = true; };
    bool GetDirAbove() const { return m_dirAbove; };
    void SetDirBelow() { m_dirBelow = true; };
    bool GetDirBelow() const { return m_dirBelow; };
    void SetDynamAbove() { m_dynamAbove = true; };
    bool GetDynamAbove() const { return m_dynamAbove; };
    void SetDynamBelow() { m_dynamBelow = true; };
    bool GetDynamBelow() const { return m_dynamBelow; };
    void SetHairpinAbove() { m_hairpinAbove = true; };
    bool GetHairpinAbove() const { return m_hairpinAbove; };
    void SetHairpinBelow() { m_hairpinBelow = true; };
    bool GetHairpinBelow() const { return m_hairpinBelow; };
    ///@}

    /**
     * Retrieves or creates the FloatingPositioner for the FloatingElement on this staff.
     */
    void SetCurrentFloatingPositioner(FloatingElement *element, int x, int y);

    /**
     * @name Setter and getter of the staff from which the alignment is created alignment.
     * Used for accessing the staff @n, the size, etc.
     */
    ///@{
    Staff *GetStaff() const { return m_staff; };
    void SetStaff(Staff *staff, Doc *doc);
    ///@}

    /**
     * Returns the staff size (100 if no staff object is refered to)
     */
    int GetStaffSize() const;

    /**
     * @name Calculates the overlow (above or below for the bounding box.
     * Looks if the bounding box is a FloatingPositioner or not, in which case it we take into account its m_drawingYRel
     * value.
     */
    ///@{
    int CalcOverflowAbove(BoundingBox *box);
    int CalcOverflowBelow(BoundingBox *box);
    ///@}

    /**
     * @name Setter and getter for overflow and overlap values
     */
    ///@{
    void SetOverflowAbove(int overflowAbove);
    int GetOverflowAbove() const { return m_overflowAbove; };
    void SetOverflowBelow(int overflowBottom);
    int GetOverflowBelow() const { return m_overflowBelow; };
    void SetOverlap(int overlap);
    int GetOverlap() const { return m_overlap; };
    int GetStaffHeight() const { return m_staffHeight; };
    ///@}

    /**
     * @name Adds a bounding box to the array of overflowing objects above or below
     */
    ///@{
    void AddBBoxAbove(BoundingBox *box) { m_overflowAboveBBoxes.push_back(box); };
    void AddBBoxBelow(BoundingBox *box) { m_overflowBelowBBoxes.push_back(box); };
    ///@}

    /**
     * Deletes all the FloatingPositioner objects.
     */
    void ClearPositioners();

    //----------//
    // Functors //
    //----------//

    /**
     * Set the position of the StaffAlignment.
     * Functor redirected from System.
     */
    virtual int SetAligmentYPos(ArrayPtrVoid *params);

    /**
     * See Object::CalcStaffOverlap
     */
    virtual int CalcStaffOverlap(ArrayPtrVoid *params);

    /**
     * Correct the Y alignment once the the content of a system has been aligned and laid out.
     * Special case of functor redirected from System.
     */
    virtual int IntegrateBoundingBoxYShift(ArrayPtrVoid *params);

    /**
     * Adjust the position of the positoners looking at previously overlowing bounding boxes.
     * Also add them to the list of overflowing elements.
     */
    virtual int AdjustFloatingPostioners(ArrayPtrVoid *params);

private:
    //
public:
    //
private:
    /**
     * The list of FloatingPositioner for the staff.
     */
    ArrayOfFloatingPositioners m_floatingPositioners;
    /**
     * Stores a pointer to the staff from which the aligner was created.
     * This is necessary since we don't always have all the staves.
     */
    Staff *m_staff;
    /**
     * Stores the position relative to the system.
     */
    int m_yRel;
    int m_yShift;
    /**
     * Stores the number of verse of the staves attached to the aligner
     */
    int m_verseCount;
    /**
     * @name indicator for the presence of above and below dynam/hairpin
     */
    ///@{
    bool m_dirAbove;
    bool m_dirBelow;
    bool m_dynamAbove;
    bool m_dynamBelow;
    bool m_hairpinAbove;
    bool m_hairpinBelow;
    ///@}

    /**
     * @name values for storing the overlow and overlap
     */
    ///@{
    int m_overflowAbove;
    int m_overflowBelow;
    int m_overlap;
    int m_staffHeight;
    ///@}

    /**
     * The list of overflowing bounding boxes (e.g, LayerElement or FloatingPositioner)
     */
    std::vector<BoundingBox *> m_overflowAboveBBoxes;
    std::vector<BoundingBox *> m_overflowBelowBBoxes;
};

//----------------------------------------------------------------------------
// Alignment
//----------------------------------------------------------------------------

/**
 * This class stores an alignement position elements will point to
 */
class Alignment : public Object {
public:
    // constructors and destructors
    Alignment();
    Alignment(double time, AlignmentType type = ALIGNMENT_DEFAULT);
    virtual ~Alignment();
    virtual ClassId Is() const { return ALIGNMENT; }

    void SetXRel(int x_rel);
    int GetXRel() const { return m_xRel; };

    void SetXShift(int xShift);
    int GetXShift() const { return m_xShift; };

    void SetMaxWidth(int maxWidth);
    int GetMaxWidth() const { return m_maxWidth; };

    /**
     * @name Set and get the time value of the alignment
     */
    ///@{
    void SetTime(double time) { m_time = time; };
    double GetTime() const { return m_time; };
    ///@}

    /**
     * @name Set and get the type of the alignment
     */
    ///@{
    void SetType(AlignmentType type) { m_type = type; };
    AlignmentType GetType() const { return m_type; };
    ///@}

    /**
     * Returns the GraceAligner for the Alignment.
     * Create it if necessary.
     */
    GraceAligner *GetGraceAligner();

    /**
     * Returns true if the aligner has a GraceAligner
     */
    bool HasGraceAligner() const { return (m_graceAligner != NULL); };

    /**
     * Correct the X alignment of grace notes once the content of a system has been aligned and laid out.
     * Special case that redirects the functor to the GraceAligner.
     */
    virtual int IntegrateBoundingBoxGraceXShift(ArrayPtrVoid *params);

    /**
     * Correct the X alignment once the content of a system has been aligned and laid out.
     * Special case of functor redirected from Measure.
     */
    virtual int IntegrateBoundingBoxXShift(ArrayPtrVoid *params);

    virtual int HorizontalSpaceForDuration(
        double intervalTime, int maxActualDur, double spacingLinear, double spacingNonLinear);

    /**
     * Set the position of the Alignment.
     * Looks at the time different with the previous Alignment.
     */
    virtual int SetAlignmentXPos(ArrayPtrVoid *params);

    /**
     * Justify the X positions
     * Special case of functor redirected from Measure.
     */
    virtual int JustifyX(ArrayPtrVoid *params);

private:
    //
public:
    //
private:
    /**
     * Stores the position relative to the measure.
     * This is instanciated by the Object::SetAlignmentXPos functor.
     * It takes into account a non-linear according to the time interval with
     * the previous Alignement
     */
    int m_xRel;
    /**
     * Stores temporally the maximum amount we need to shift the element pointing to it for
     * avoiding collisions. This is set in Object::SetBoundingBoxXShift and then
     * integrated for all alignment in Alignment::IntegrateBoundingBoxXShift.
     */
    int m_xShift;
    /**
     * Stores temporally the maximum width of the of the element pointing to it.
     * It is set and integrated as m_xShift and it is used only for shifting the
     * alignment of the end of the measure (ALIGNMENT_MEASURE_END).
     */
    int m_maxWidth;
    /**
     * Stores the time at which the alignment occur.
     * It is set by Object::AlignHorizontally.
     */
    double m_time;
    /**
     * Defines the type of alignment (see the AlignmentType enum).
     * We have different types because we want some events occuring at the same
     * time to be aligned separately. Examples: the clefs needs to be aligned
     * together, key signatures together, and then the notes, even if all of them
     * occur at time 0.
     */
    AlignmentType m_type;
    /**
     * A pointer to a GraceAligner if any.
     * The Alignment owns it.
     */
    GraceAligner *m_graceAligner;
};

//----------------------------------------------------------------------------
// MeasureAligner
//----------------------------------------------------------------------------

/**
 * This class aligns the content of a measure
 * It contains a vector of Alignment
 */
class MeasureAligner : public Object {
public:
    // constructors and destructors
    MeasureAligner();
    virtual ~MeasureAligner();
    virtual ClassId Is() const { return MEASURE_ALIGNER; }

    int GetAlignmentCount() const { return (int)m_children.size(); };

    /**
     * Reset the aligner (clear the content) and creates the start (left) and end (right) alignement
     */
    virtual void Reset();

    Alignment *GetAlignmentAtTime(double time, AlignmentType type, bool hasEndAlignment = true);

    /**
     * Keep the maximum time of the measure.
     * This corresponds to the whole duration of the measure and
     * should be the same for all staves/layers.
     */
    void SetMaxTime(double time);

    /**
     * @name Set and get the non-justifiable margin
     */
    ///@{
    void SetNonJustifiableMargin(int margin) { m_nonJustifiableLeftMargin = margin; };
    int GetNonJustifiableMargin() const { return m_nonJustifiableLeftMargin; };
    ///@}

    /**
     * Get left Alignment for the measure.
     * For each MeasureAligner, we keep and Alignment for the left position.
     * The Alignment time will be always 0.0 and will appear first in the list.
     */
    Alignment *GetLeftAlignment() const { return m_leftAlignment; };

    /**
     * Get right Alignment for the measure.
     * For each MeasureAligner, we keep and Alignment for the right position.
     * The Alignment time will be increased whenever necessary when values are added.
     */
    Alignment *GetRightAlignment() const { return m_rightAlignment; };

    /**
     * Correct the X alignment once the the content of a system has been aligned and laid out.
     * Special case of functor redirected from Measure.
     */
    virtual int IntegrateBoundingBoxXShift(ArrayPtrVoid *params);

    /**
     * Set the position of the Alignment.
     * Looks at the time different with the previous Alignment.
     * For each MeasureAlignment, we need to reset the previous time position.
     */
    virtual int SetAlignmentXPos(ArrayPtrVoid *params);

    /**
     * Justify the X positions
     * Special case of functor redirected from Measure.
     */
    virtual int JustifyX(ArrayPtrVoid *params);

private:
    void AddAlignment(Alignment *alignment, int idx = -1);

public:
    //
private:
    /**
     * A pointer to the left Alignment object kept for the measure start position
     */
    Alignment *m_leftAlignment;

    /**
     * A pointer to the left Alignment object kept for the measure end position
     */
    Alignment *m_rightAlignment;

    /**
     * Store measure's non-justifiable margin used by the scoreDef attributes.
     */
    int m_nonJustifiableLeftMargin;
};

//----------------------------------------------------------------------------
// GraceAligner
//----------------------------------------------------------------------------

/**
 * This class aligns the content of a grace note group
 * It contains a vector of Alignment
 */
class GraceAligner : public MeasureAligner {
public:
    // constructors and destructors
    GraceAligner();
    virtual ~GraceAligner();
    virtual ClassId Is() const { return GRACE_ALIGNER; }

    /**
     * Because the grace notes appear from left to right but need to be aligned
     * from right to left, we first need to stack them and align them eventually
     * when we have all of them. This is done by GraceAligner::AlignNote called
     * at the end of each Layer in
     */
    void StackNote(Note *note);

    /**
     * Align the notes in the reverse order
     */
    void AlignStack();

    /**
     * @name Setter and getter for the width of the group of grace notes
     */
    ///@{
    void SetWidth(int totalWidth) { m_totalWidth = totalWidth; };
    int GetWidth() const { return m_totalWidth; };
    ///@}

private:
    //
public:
    //
private:
    /**
     * The stack of notes where they are piled up before getting aligned
     */
    ArrayOfObjects m_noteStack;
    /**
     * The witdth of the group of grace notes instanciated after the bounding
     * boxes X are integrated in Alignment::IntegrateBoundingBoxGraceXShift
     */
    int m_totalWidth;
};

//----------------------------------------------------------------------------
// TimestampAligner
//----------------------------------------------------------------------------

/**
 * This class stores the timestamps (TimestampsAttr) in a measure.
 * It does not itself perform any alignment but only stores them and avoids duplicates
 * (i.e., having two objects at the same position.
 * It contains a vector of TimestampsAttr.
 */
class TimestampAligner : public Object {
public:
    // constructors and destructors
    TimestampAligner();
    virtual ~TimestampAligner();
    virtual ClassId Is() const { return TIMESTAMP_ALIGNER; }

    /**
     * Reset the aligner (clear the content)
     */
    virtual void Reset();

    /**
     * Look for an existing TimestampAttr at a certain time.
     * Creates it if not found
     */
    TimestampAttr *GetTimestampAtTime(double time);

private:
    //
public:
    //
private:
    //
};

} // namespace vrv

#endif
