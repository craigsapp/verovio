/////////////////////////////////////////////////////////////////////////////
// Name:        iomei.h
// Author:      Laurent Pugin
// Created:     2011
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_IOMEI_H__
#define __VRV_IOMEI_H__

#include <sstream>

//----------------------------------------------------------------------------

#include "doc.h"
#include "io.h"

//----------------------------------------------------------------------------

#include "pugixml.hpp"

namespace vrv {

class Abbr;
class Accid;
class Add;
class AnchoredText;
class Annot;
class App;
class BarLine;
class Beam;
class BeatRpt;
class BTrem;
class Chord;
class Clef;
class Corr;
class Custos;
class Damage;
class Del;
class Dot;
class Dir;
class DurationInterface;
class Dynam;
class Expan;
class FloatingElement;
class FTrem;
class Hairpin;
class Layer;
class LayerElement;
class Lem;
class Measure;
class Mensur;
class MeterSig;
class MRest;
class MRpt;
class MRpt2;
class MultiRest;
class MultiRpt;
class Note;
class Orig;
class PitchInterface;
class PositionInterface;
class Proport;
class Rdg;
class Reg;
class Rend;
class Rest;
class Restore;
class ScoreDef;
class ScoreDefInterface;
class Sic;
class Slur;
class Space;
class Staff;
class Supplied;
class Syl;
class System;
class Tempo;
class Text;
class TextDirInterface;
class TextElement;
class Tie;
class TimePointInterface;
class TimeSpanningInterface;
class Tuplet;
class Unclear;
class Verse;

//----------------------------------------------------------------------------
// MeiOutput
//----------------------------------------------------------------------------

/**
 * This class is a file output stream for writing MEI files.
 * It uses the libmei C++ library.
 * Not implemented.
*/
class MeiOutput : public FileOutputStream {
public:
    /** @name Constructors and destructor */
    ///@{
    MeiOutput(Doc *doc, std::string filename);
    virtual ~MeiOutput();
    ///@}

    /**
     * The main method for exporting the file to MEI.
     */
    virtual bool ExportFile();

    /**
     * The main method for write objects.
     */
    virtual bool WriteObject(Object *object);

    /**
     * Writing object method that must be overridden in the child class.
     */
    virtual bool WriteObjectEnd(Object *object);

    /**
     * Return the output as a string by writing it to the stringstream member.
     */
    std::string GetOutput(int page = -1);

    /**
     * Setter for score-based MEI output (not implemented)
     */
    void SetScoreBasedMEI(bool scoreBasedMEI) { m_scoreBasedMEI = scoreBasedMEI; };

private:
    bool WriteMeiDoc(Doc *doc);

    /**
     * Write the @xml:id to the currentNode
     */
    void WriteXmlId(pugi::xml_node currentNode, Object *object);

    /**
     * @name Methods for writing MEI containers (measures, staff, etc) scoreDef and related.
     */
    ///@{
    void WriteMeiPage(pugi::xml_node currentNode, Page *page);
    void WriteMeiSystem(pugi::xml_node currentNode, System *system);
    void WriteMeiScoreDef(pugi::xml_node currentNode, ScoreDef *scoreDef);
    void WriteMeiStaffGrp(pugi::xml_node currentNode, StaffGrp *staffGrp);
    void WriteMeiStaffDef(pugi::xml_node currentNode, StaffDef *staffDef);
    void WriteMeiMeasure(pugi::xml_node currentNode, Measure *measure);
    void WriteMeiStaff(pugi::xml_node currentNode, Staff *staff);
    void WriteMeiLayer(pugi::xml_node currentNode, Layer *layer);
    ///@}

    /**
     * @name Methods for writing LayerElement children.
     * Called from WriteLayerElement.
     */
    ///@{
    void WriteMeiAccid(pugi::xml_node currentNode, Accid *accid);
    void WriteMeiBarLine(pugi::xml_node currentNode, BarLine *barLine);
    void WriteMeiBeam(pugi::xml_node currentNode, Beam *beam);
    void WriteMeiBeatRpt(pugi::xml_node currentNode, BeatRpt *beatRpt);
    void WriteMeiBTrem(pugi::xml_node currentNode, BTrem *bTrem);
    void WriteMeiChord(pugi::xml_node currentNode, Chord *chord);
    void WriteMeiClef(pugi::xml_node currentNode, Clef *clef);
    void WriteMeiCustos(pugi::xml_node currentNode, Custos *custos);
    void WriteMeiDot(pugi::xml_node currentNode, Dot *dot);
    void WriteMeiFTrem(pugi::xml_node currentNode, FTrem *fTrem);
    void WriteMeiKeySig(pugi::xml_node currentNode, KeySig *keySig);
    void WriteMeiMensur(pugi::xml_node currentNode, Mensur *mensur);
    void WriteMeiMeterSig(pugi::xml_node currentNode, MeterSig *meterSig);
    void WriteMeiMRest(pugi::xml_node currentNode, MRest *mRest);
    void WriteMeiMRpt(pugi::xml_node currentNode, MRpt *mRpt);
    void WriteMeiMRpt2(pugi::xml_node currentNode, MRpt2 *mRpt2);
    void WriteMeiMultiRest(pugi::xml_node currentNode, MultiRest *multiRest);
    void WriteMeiMultiRpt(pugi::xml_node currentNode, MultiRpt *multiRpt);
    void WriteMeiNote(pugi::xml_node currentNode, Note *note);
    void WriteMeiProport(pugi::xml_node currentNode, Proport *proport);
    void WriteMeiRest(pugi::xml_node currentNode, Rest *rest);
    void WriteMeiSpace(pugi::xml_node currentNode, Space *space);
    void WriteMeiTuplet(pugi::xml_node currentNode, Tuplet *tuplet);
    ///@}

    /**
     * @name Methods for writing FloatingElement
     */
    ///@{
    void WriteMeiAnchoredText(pugi::xml_node currentNode, AnchoredText *anchoredText);
    void WriteMeiDir(pugi::xml_node currentNode, Dir *dir);
    void WriteMeiDynam(pugi::xml_node currentNode, Dynam *dynam);
    void WriteMeiHairpin(pugi::xml_node currentNode, Hairpin *hairpin);
    void WriteMeiSlur(pugi::xml_node currentNode, Slur *slur);
    void WriteMeiTempo(pugi::xml_node currentNode, Tempo *tempo);
    void WriteMeiTie(pugi::xml_node currentNode, Tie *tie);
    ///@}

    /**
     * @name Methods for writing TextElement
     */
    ///@{
    void WriteMeiRend(pugi::xml_node currentNode, Rend *rend);
    void WriteMeiText(pugi::xml_node currentNode, Text *text);
    ///@}

    /**
     * @name Methods for writing editorial markup
     */
    ///@{
    void WriteMeiAbbr(pugi::xml_node currentNode, Abbr *abbr);
    void WriteMeiAdd(pugi::xml_node currentNode, Add *add);
    void WriteMeiAnnot(pugi::xml_node currentNode, Annot *annot);
    void WriteMeiApp(pugi::xml_node currentNode, App *app);
    void WriteMeiCorr(pugi::xml_node currentNode, Corr *corr);
    void WriteMeiDamage(pugi::xml_node currentNode, Damage *damage);
    void WriteMeiDel(pugi::xml_node currentNode, Del *del);
    void WriteMeiExpan(pugi::xml_node currentNode, Expan *expan);
    void WriteMeiLem(pugi::xml_node currentNode, Lem *lem);
    void WriteMeiOrig(pugi::xml_node currentNode, Orig *orig);
    void WriteMeiRdg(pugi::xml_node currentNode, Rdg *rdg);
    void WriteMeiReg(pugi::xml_node currentNode, Reg *Reg);
    void WriteMeiRestore(pugi::xml_node currentNode, Restore *restore);
    void WriteMeiSic(pugi::xml_node currentNode, Sic *sic);
    void WriteMeiSupplied(pugi::xml_node currentNode, Supplied *supplied);
    void WriteMeiUnclear(pugi::xml_node currentNode, Unclear *unclear);
    ///@}

    /**
     * @name Methods for writing other mei elements
     */
    ///@{
    void WriteMeiVerse(pugi::xml_node currentNode, Verse *verse);
    void WriteMeiSyl(pugi::xml_node currentNode, Syl *syl);
    ///@}

    /**
     * Write unsupported attributes stored in Object::m_unsupported (not tested)
     */
    void WriteUnsupportedAttr(pugi::xml_node currentNode, Object *object);

    /**
     * @name Methods for writing LayerElement, EditorialElement and interfaces.
     * Call WriteDurationInferface from WriteNote, for example.
     */
    ///@{
    void WriteLayerElement(pugi::xml_node currentNode, LayerElement *element);
    void WriteEditorialElement(pugi::xml_node currentNode, EditorialElement *element);
    void WriteDurationInterface(pugi::xml_node currentNode, DurationInterface *interface);
    void WritePitchInterface(pugi::xml_node currentNode, PitchInterface *interface);
    void WritePositionInterface(pugi::xml_node currentNode, PositionInterface *interface);
    void WriteScoreDefInterface(pugi::xml_node currentNode, ScoreDefInterface *interface);
    void WriteTextDirInterface(pugi::xml_node currentNode, TextDirInterface *interface);
    void WriteTimePointInterface(pugi::xml_node currentNode, TimePointInterface *interface);
    void WriteTimeSpanningInterface(pugi::xml_node currentNode, TimeSpanningInterface *interface);
    ///@}

    /**
     * Escapes SMuFL characters to entities (e.g., &#xe1e7;).
     * Must be used in conjunction with (pugi::format_default | pugi::format_no_escapes).
     * Unused for now (see WriteMeiText) because of un-escaped entities in the header.
     */
    std::wstring EscapeSMuFL(std::wstring data);

    /** @name Methods for converting members into MEI attributes. */
    ///@{
    std::string UuidToMeiStr(Object *element);
    std::string DocTypeToStr(DocType type);
    ///@}

public:
    //
private:
    std::string m_filename;
    std::ostringstream m_streamStringOutput;
    bool m_writeToStreamString;
    int m_page;
    bool m_scoreBasedMEI;
    pugi::xml_node m_mei;
    /** @name Current element */
    pugi::xml_node m_currentNode;
    std::list<pugi::xml_node> m_nodeStack;
};

//----------------------------------------------------------------------------
// MeiInput
//----------------------------------------------------------------------------

/**
 * This class is a file input stream for reading MEI files.
 * It uses the libmei C++ library.
 * Under development.
*/
class MeiInput : public FileInputStream {
public:
    // constructors and destructors
    MeiInput(Doc *doc, std::string filename);
    virtual ~MeiInput();

    virtual bool ImportFile();
    virtual bool ImportString(std::string mei);

    /**
     * Set an xPath query for selecting specific <rdg>.
     * By default, the first <lem> or <rdg> is loaded.
     * If a query is provided, the element retrieved by the specified xPath
     * query will be selected (if any, otherwise the first one will be used).
     */
    virtual void SetAppXPathQuery(std::string appXPathQuery) { m_appXPathQuery = appXPathQuery; };

private:
    bool ReadMei(pugi::xml_node root);
    bool ReadMeiHeader(pugi::xml_node meihead);

    /**
     * @name Methods for reading  MEI containers (measures, staff, etc) scoreDef and related.
     * For each container (page, system, measure, staff and layer) there is one method for
     * reading the element and one method for reading its children. The method for reading
     * the children can also be called when reading EditorialElement objects (<lem> or <rdg>
     * for example. The filter object is optional and can be set for filtering the allowed
     * children (see MeiInput::IsAllowed)
     */
    ///@{
    bool ReadMeiPage(pugi::xml_node page);
    bool ReadMeiPageChildren(Object *parent, pugi::xml_node parentNode);
    bool ReadMeiSystem(Object *parent, pugi::xml_node system);
    bool ReadMeiSystemChildren(Object *parent, pugi::xml_node parentNode);
    bool ReadMeiScoreDef(Object *parent, pugi::xml_node scoreDef);
    bool ReadMeiScoreDefChildren(Object *parent, pugi::xml_node parentNode);
    bool ReadMeiStaffGrp(Object *parent, pugi::xml_node staffGrp);
    bool ReadMeiStaffGrpChildren(Object *parent, pugi::xml_node parentNode);
    bool ReadMeiStaffDef(Object *parent, pugi::xml_node staffDef);
    bool ReadMeiMeasure(Object *parent, pugi::xml_node measure);
    bool ReadMeiMeasureChildren(Object *parent, pugi::xml_node parentNode);
    bool ReadMeiStaff(Object *parent, pugi::xml_node staff);
    bool ReadMeiStaffChildren(Object *parent, pugi::xml_node parentNode);
    bool ReadMeiLayer(Object *parent, pugi::xml_node layer);
    bool ReadMeiLayerChildren(Object *parent, pugi::xml_node parentNode, Object *filter = NULL);
    bool ReadMeiTextChildren(Object *parent, pugi::xml_node parentNode, Object *filter = NULL);
    ///@}

    /**
     * @name Methods for reading MEI layer elements
     */
    ///@{
    bool ReadMeiAccid(Object *parent, pugi::xml_node accid);
    bool ReadMeiBarLine(Object *parent, pugi::xml_node barLine);
    bool ReadMeiBeam(Object *parent, pugi::xml_node beam);
    bool ReadMeiBeatRpt(Object *parent, pugi::xml_node beatRpt);
    bool ReadMeiBTrem(Object *parent, pugi::xml_node bTrem);
    bool ReadMeiChord(Object *parent, pugi::xml_node chord);
    bool ReadMeiClef(Object *parent, pugi::xml_node clef);
    bool ReadMeiCustos(Object *parent, pugi::xml_node custos);
    bool ReadMeiDot(Object *parent, pugi::xml_node dot);
    bool ReadMeiFTrem(Object *parent, pugi::xml_node fTrem);
    bool ReadMeiKeySig(Object *parent, pugi::xml_node keySig);
    bool ReadMeiMensur(Object *parent, pugi::xml_node mensur);
    bool ReadMeiMeterSig(Object *parent, pugi::xml_node meterSig);
    bool ReadMeiMRest(Object *parent, pugi::xml_node mRest);
    bool ReadMeiMRpt(Object *parent, pugi::xml_node mRpt);
    bool ReadMeiMRpt2(Object *parent, pugi::xml_node mRpt2);
    bool ReadMeiMultiRest(Object *parent, pugi::xml_node multiRest);
    bool ReadMeiMultiRpt(Object *parent, pugi::xml_node multiRpt);
    bool ReadMeiNote(Object *parent, pugi::xml_node note);
    bool ReadMeiProport(Object *parent, pugi::xml_node proport);
    bool ReadMeiRest(Object *parent, pugi::xml_node rest);
    bool ReadMeiSpace(Object *parent, pugi::xml_node space);
    bool ReadMeiSyl(Object *parent, pugi::xml_node syl);
    bool ReadMeiTuplet(Object *parent, pugi::xml_node tuplet);
    bool ReadMeiVerse(Object *parent, pugi::xml_node verse);
    ///@}

    /**
     * @name Methods for reading MEI floating elements
     */
    ///@{
    bool ReadMeiAnchoredText(Object *parent, pugi::xml_node anchoredText);
    bool ReadMeiDir(Object *parent, pugi::xml_node dir);
    bool ReadMeiDynam(Object *parent, pugi::xml_node dynam);
    bool ReadMeiHairpin(Object *parent, pugi::xml_node hairpin);
    bool ReadMeiSlur(Object *parent, pugi::xml_node slur);
    bool ReadMeiTempo(Object *parent, pugi::xml_node tempo);
    bool ReadMeiTie(Object *parent, pugi::xml_node tie);
    ///@}

    /**
     * @name Methods for reading MEI text elements
     */
    ///@{
    bool ReadMeiRend(Object *parent, pugi::xml_node rend);
    bool ReadMeiText(Object *parent, pugi::xml_node text, bool trimLeft, bool trimRight);
    ///@}

    /**
     * @name Methods for reading critical apparatus, other editorial markup and <annot>.
     * The filter is propagated (if any)
     */
    ///@{
    bool ReadMeiEditorialElement(Object *parent, pugi::xml_node app, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiAbbr(Object *parent, pugi::xml_node abbr, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiAdd(Object *parent, pugi::xml_node add, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiAnnot(Object *parent, pugi::xml_node annot);
    bool ReadMeiApp(Object *parent, pugi::xml_node app, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiAppChildren(Object *parent, pugi::xml_node parentNode, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiCorr(Object *parent, pugi::xml_node corr, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiDamage(Object *parent, pugi::xml_node damage, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiDel(Object *parent, pugi::xml_node del, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiExpan(Object *parent, pugi::xml_node expan, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiLem(Object *parent, pugi::xml_node lem, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiOrig(Object *parent, pugi::xml_node orig, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiRdg(Object *parent, pugi::xml_node rdg, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiReg(Object *parent, pugi::xml_node reg, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiRestore(Object *parent, pugi::xml_node restore, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiSic(Object *parent, pugi::xml_node sic, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiSupplied(Object *parent, pugi::xml_node supplied, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiUnclear(Object *parent, pugi::xml_node unclear, EditorialLevel level, Object *filter = NULL);
    bool ReadMeiEditorialChildren(Object *parent, pugi::xml_node supplied, EditorialLevel level, Object *filter = NULL);
    ///@}
    ///@}

    /**
     * @name Methods for reading MEI LayerElement, EidtorialElement and interfaces
     */
    ///@{
    bool ReadLayerElement(pugi::xml_node element, LayerElement *object);
    bool ReadEditorialElement(pugi::xml_node element, EditorialElement *object);
    bool ReadDurationInterface(pugi::xml_node element, DurationInterface *interface);
    bool ReadPitchInterface(pugi::xml_node element, PitchInterface *interface);
    bool ReadPositionInterface(pugi::xml_node element, PositionInterface *interface);
    bool ReadScoreDefInterface(pugi::xml_node element, ScoreDefInterface *interface);
    bool ReadTextDirInterface(pugi::xml_node element, TextDirInterface *interface);
    bool ReadTimePointInterface(pugi::xml_node element, TimePointInterface *interface);
    bool ReadTimeSpanningInterface(pugi::xml_node element, TimeSpanningInterface *interface);
    ///@}

    /**
     * @name Methods for reading other MEI elements.
     */
    ///@{
    bool ReadTupletSpanAsTuplet(Measure *measure, pugi::xml_node tupletSpan);
    ///@}

    /**
     * Write unsupported attributes and store them in Object::m_unsupported (not tested)
     */
    void ReadUnsupportedAttr(pugi::xml_node element, Object *object);

    /**
     * Method for adding the element to the appropriate parent (e.g., Layer, Beam).
     * This used for any element that supports different types of child.
     * For example, the StaffGrp can contain StaffGrp or StaffDef.
     * These methods dynamically case the parent to the appropriate class.
     */
    ///@{
    void AddLayerElement(Object *parent, LayerElement *element);
    void AddFloatingElement(Object *parent, FloatingElement *element);
    void AddTextElement(Object *parent, TextElement *element);
    void AddScoreDef(Object *parent, ScoreDef *element);
    void AddStaffGrp(Object *parent, StaffGrp *element);
    ///@}

    /**
     * Returns true if the element is name is an editorial element (e.g., "app", "supplied", etc.)
     */
    bool IsEditorialElementName(std::string elementName);

    /**
     * Read score-based MEI
     */
    bool ReadScoreBasedMei(pugi::xml_node element);

    /**
     * @name Various methods for reading / converting values.
     */
    ///@{
    void SetMeiUuid(pugi::xml_node element, Object *object);
    DocType StrToDocType(std::string type);
    /** Extract the uuid for references to uuids with ..#uuid values */
    std::string ExtractUuidFragment(std::string refUuid);
    std::wstring LeftTrim(std::wstring str);
    std::wstring RightTrim(std::wstring str);
    ///@}

public:
    //
private:
    std::string m_filename;

    /** The current page when reading score-based MEI */
    Page *m_page;
    /** The current system when reading score-based MEI */
    System *m_system;

    /**
     *
     */
    std::string m_appXPathQuery;

    /**
     * This is used when reading a standard MEI file to specify if a scoreDef has already been read or not.
     */
    bool m_hasScoreDef;

    /**
     * Check if an element is allowed within a given parent
     */
    bool IsAllowed(std::string element, Object *filterParent);

    /**
     * A static array for storing the implemented editorial elements
     */
    static std::string s_editorialElementNames[];
};

} // namespace vrv

#endif
