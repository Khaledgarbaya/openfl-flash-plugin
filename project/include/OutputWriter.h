/*************************************************************************
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright [2013] Adobe Systems Incorporated
*  All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains
* the property of Adobe Systems Incorporated and its suppliers,
* if any.  The intellectual and technical concepts contained
* herein are proprietary to Adobe Systems Incorporated and its
* suppliers and are protected by all applicable intellectual 
* property laws, including trade secret and copyright laws.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/

/**
 * @file  OutputWriter.h
 *
 * @brief This file contains declarations for a output writer.
 */

#ifndef OUTPUT_WRITER_H_
#define OUTPUT_WRITER_H_

#include "IOutputWriter.h"
#include <string>

/* -------------------------------------------------- Forward Decl */

class JSONNode;

namespace OpenFL
{
    class ITimelineWriter;
}

/* -------------------------------------------------- Enums */

namespace OpenFL
{
    enum StrokeStyleType
    {
        INVALID_STROKE_STYLE_TYPE,
        SOLID_STROKE_STYLE_TYPE
    };
}


/* -------------------------------------------------- Macros / Constants */

#define IMAGE_FOLDER "images"

#define JSON_OUTPUT_FILE_NAME "sample.json"


/* -------------------------------------------------- Structs / Unions */

namespace OpenFL
{
    struct SOLID_STROKE_STYLE
    {
        FCM::Double thickness;
        DOM::StrokeStyle::JOIN_STYLE joinStyle;
        DOM::StrokeStyle::CAP_STYLE capStyle;
        DOM::Utils::ScaleType scaleType;
        FCM::Boolean strokeHinting;
    };

    struct STROKE_STYLE
    {
        StrokeStyleType type;

        union
        {
            SOLID_STROKE_STYLE solidStrokeStyle;
        };
    };
}


/* -------------------------------------------------- Class Decl */

namespace OpenFL
{
    class JSONOutputWriter : public IOutputWriter
    {
    public:

        // Marks the begining of the output
        virtual FCM::Result StartOutput(std::string& outputFileName);

        // Marks the end of the output
        virtual FCM::Result EndOutput();

        // Marks the begining of the Document
        virtual FCM::Result StartDocument(
            const DOM::Utils::COLOR& background,
            FCM::U_Int32 stageHeight, 
            FCM::U_Int32 stageWidth);

        // Marks the end of the Document
        virtual FCM::Result EndDocument();

        // Marks the start of a timeline
        virtual FCM::Result StartDefineTimeline();

        // Marks the end of a timeline
        virtual FCM::Result EndDefineTimeline(
            FCM::U_Int32 resId, 
            FCM::StringRep16 pName, 
            ITimelineWriter* pTimelineWriter);

        // Marks the start of a shape
        virtual FCM::Result StartDefineShape();

        // Start of fill region definition
        virtual FCM::Result StartDefineFill();

        // Solid fill style definition
        virtual FCM::Result DefineSolidFillStyle(const DOM::Utils::COLOR& color);

        // Bitmap fill style definition
        virtual FCM::Result DefineBitmapFillStyle(
            FCM::Boolean clipped,
            const DOM::Utils::MATRIX2D& matrix,
            FCM::S_Int32 height, 
            FCM::S_Int32 width,
            FCM::StringRep16 pName,
            DOM::LibraryItem::PIMediaItem pMediaItem);

        // Start Linear Gradient fill style definition
        virtual FCM::Result StartDefineLinearGradientFillStyle(
            DOM::FillStyle::GradientSpread spread,
            const DOM::Utils::MATRIX2D& matrix);

        // Sets a specific key point in a color ramp (for both radial and linear gradient)
        virtual FCM::Result SetKeyColorPoint(
            const DOM::Utils::GRADIENT_COLOR_POINT& colorPoint);

        // End Linear Gradient fill style definition
        virtual FCM::Result EndDefineLinearGradientFillStyle();

        // Start Radial Gradient fill style definition
        virtual FCM::Result StartDefineRadialGradientFillStyle(
            DOM::FillStyle::GradientSpread spread,
            const DOM::Utils::MATRIX2D& matrix,
            FCM::S_Int32 focalPoint);

        // End Radial Gradient fill style definition
        virtual FCM::Result EndDefineRadialGradientFillStyle();

        // Start of fill region boundary
        virtual FCM::Result StartDefineBoundary();

        // Sets a segment of a path (Used for boundary, holes)
        virtual FCM::Result SetSegment(const DOM::Utils::SEGMENT& segment);

        // End of fill region boundary
        virtual FCM::Result EndDefineBoundary();

        // Start of fill region hole
        virtual FCM::Result StartDefineHole();

        // End of fill region hole
        virtual FCM::Result EndDefineHole();

        // Start of stroke group
        virtual FCM::Result StartDefineStrokeGroup();

        // Start solid stroke style definition
        virtual FCM::Result StartDefineSolidStrokeStyle(
            FCM::Double thickness,
            const DOM::StrokeStyle::JOIN_STYLE& joinStyle,
            const DOM::StrokeStyle::CAP_STYLE& capStyle,
            DOM::Utils::ScaleType scaleType,
            FCM::Boolean strokeHinting);

        // End of solid stroke style
        virtual FCM::Result EndDefineSolidStrokeStyle();

        // Start of stroke 
        virtual FCM::Result StartDefineStroke();

        // End of a stroke 
        virtual FCM::Result EndDefineStroke();

        // End of stroke group
        virtual FCM::Result EndDefineStrokeGroup();

        // End of fill style definition
        virtual FCM::Result EndDefineFill();

        // Marks the end of a shape
        virtual FCM::Result EndDefineShape(FCM::U_Int32 resId);

        // Define a bitmap
        virtual FCM::Result DefineBitmap(
            FCM::U_Int32 resId,
            FCM::S_Int32 height, 
            FCM::S_Int32 width,
            FCM::StringRep16 pName,
            DOM::LibraryItem::PIMediaItem pMediaItem);

        JSONOutputWriter(FCM::PIFCMCallback pCallback);

        virtual ~JSONOutputWriter();

        // Start of a path
        virtual FCM::Result StartDefinePath();

        // End of a path 
        virtual FCM::Result EndDefinePath();

    private:

        JSONNode* m_pRootNode;

        JSONNode* m_pShapeArray;

        JSONNode* m_pTimelineArray;

        JSONNode* m_pBitmapArray;

        JSONNode*   m_shapeElem;

        JSONNode*   m_pathArray;

        JSONNode*   m_pathElem;

        JSONNode*   m_gradientColor;

        JSONNode*   m_stopPointArray;

        std::string m_pathCmdStr;

        bool        m_firstSegment;

        STROKE_STYLE m_strokeStyle;

        std::string m_outputHTMLFile;

        std::string m_outputJSONFile;

        std::string m_outputImageFolder;

        char* m_HTMLOutput;

        FCM::PIFCMCallback m_pCallback;
    };


    class JSONTimelineWriter : public ITimelineWriter
    {
    public:

        virtual FCM::Result PlaceObject(
            FCM::U_Int32 resId,
            FCM::U_Int32 objectId,
            FCM::U_Int32 placeAfterObjectId,
            const DOM::Utils::MATRIX2D* pMatrix,
            FCM::PIFCMUnknown pUnknown = NULL);

        virtual FCM::Result RemoveObject(
            FCM::U_Int32 objectId);

        virtual FCM::Result UpdateZOrder(
            FCM::U_Int32 objectId,
            FCM::U_Int32 placeAfterObjectId);

        virtual FCM::Result UpdateBlendMode(
            FCM::U_Int32 objectId,
            DOM::FrameElement::BlendMode blendMode);

        virtual FCM::Result UpdateVisibility(
            FCM::U_Int32 objectId,
            FCM::Boolean visible);

        virtual FCM::Result AddGraphicFilter(
            FCM::U_Int32 objectId,
            FCM::PIFCMUnknown pFilter);

        virtual FCM::Result UpdateDisplayTransform(
            FCM::U_Int32 objectId,
            const DOM::Utils::MATRIX2D& matrix);

        virtual FCM::Result UpdateColorTransform(
            FCM::U_Int32 objectId,
            const DOM::Utils::COLOR_MATRIX& colorMatrix);

        virtual FCM::Result ShowFrame(FCM::U_Int32 frameNum);

        virtual FCM::Result AddFrameScript(FCM::StringRep16 pFrameScript);

        JSONTimelineWriter();

        virtual ~JSONTimelineWriter();

        const JSONNode* GetRoot();

        void Finish(FCM::U_Int32 resId, FCM::StringRep16 pName);

    private:

        JSONNode* m_pCommandArray;

        JSONNode* m_pFrameArray;

        JSONNode* m_pTimelineElement;
    };
};

#endif // OUTPUT_WRITER_H_

