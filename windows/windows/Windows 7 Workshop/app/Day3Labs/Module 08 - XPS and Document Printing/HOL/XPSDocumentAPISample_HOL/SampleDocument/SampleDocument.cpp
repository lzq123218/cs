// SampleDocument.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "macros.h"


HRESULT 
GetXpsFactory(
    __out IXpsOMObjectFactory **ppXpsFactory
    )
{
    return CoCreateInstance(__uuidof(XpsOMObjectFactory), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IXpsOMObjectFactory), reinterpret_cast<LPVOID*>(ppXpsFactory));
}

HRESULT 
GetOpcFactory(
    __out IOpcFactory **ppOpcFactory
    )
{
    return CoCreateInstance(__uuidof(OpcFactory), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IOpcFactory), reinterpret_cast<LPVOID*>(ppOpcFactory));
}


HRESULT 
GenerateNewFontPartUri(
    __in  IOpcFactory   *pOpcFactory,
    __out IOpcPartUri  **ppPartUri
    )
{
    HRESULT hr = S_OK;
    GUID guid;
    WCHAR guidString[128] = {0};
    WCHAR uriString[256] = {0};

    IFC(CoCreateGuid(&guid));
    IFC(StringFromGUID2( 
            guid, 
            guidString, 
            ARRAYSIZE(guidString)));

    wcscpy_s(uriString, ARRAYSIZE(uriString), L"/Resources/Fonts/");
    wcsncat_s(uriString, ARRAYSIZE(uriString), guidString + 1, wcslen(guidString) - 2); // guid string start and ends with curly braces so they are removed
    wcscat_s(uriString, ARRAYSIZE(uriString), L".odttf");

    IFC(pOpcFactory->CreatePartUri(
            uriString,
            ppPartUri));

Cleanup:
	// No cleanup needed.
    return hr;
}

HRESULT
AppendSimpleText(
    __in    IXpsOMObjectFactory *xpsFactory, 
    __in    IXpsOMFontResource  *xpsFont, 
    __in    float                fontEmSize, 
    __in    XPS_COLOR           &xpsColor, 
    __in    float                originX, 
    __in    float                originY, 
    __in    LPCWSTR              unicodeString, 
    __inout IXpsOMCanvas        *xpsCanvas
    )
{
	HRESULT                  hr             = S_OK;
	XPS_POINT                glyphsOrigin   = {originX, originY};
	IXpsOMGlyphsEditor      *glyphsEditor   = NULL;
	IXpsOMGlyphs            *xpsGlyphs      = NULL;
	IXpsOMVisualCollection  *canvasVisuals  = NULL;
	IXpsOMSolidColorBrush   *xpsBrush       = NULL;

    // Create a brush from the solid color provided
    IFC( xpsFactory->CreateSolidColorBrush(&xpsColor, NULL, &xpsBrush) );

    // Create a new Glyphs object and set its properties
	IFC( xpsFactory->CreateGlyphs(xpsFont, &xpsGlyphs) );
	IFC( xpsGlyphs->SetOrigin(&glyphsOrigin) );
	IFC( xpsGlyphs->SetFontRenderingEmSize(fontEmSize) );
	IFC( xpsGlyphs->SetFillBrushLocal(xpsBrush) );

    // Some properties are inter-dependent so must be changed through a GlyphsEditor
	IFC( xpsGlyphs->GetGlyphsEditor(&glyphsEditor) );
	IFC( glyphsEditor->SetUnicodeString(unicodeString) );
	IFC( glyphsEditor->ApplyEdits() );

	// Add the new Glyphs object to the provided canvas
	IFC( xpsCanvas->GetVisuals(&canvasVisuals) );
	IFC( canvasVisuals->Append(xpsGlyphs) );

	// Clean up unneeded interfaces
	xpsBrush->Release();
	glyphsEditor->Release();
	xpsGlyphs->Release();
	canvasVisuals->Release();
	
	return hr;
	
Cleanup:
	// Error was encountered, so systematically clean up working objects.
    if(xpsBrush)       xpsBrush->Release();
    if(glyphsEditor)   glyphsEditor->Release();
    if(xpsGlyphs)      xpsGlyphs->Release();
    if(canvasVisuals)  canvasVisuals->Release();

	return hr;
}

HRESULT 
AppendSidebar(
    __in    IXpsOMObjectFactory    *xpsFactory,
    __inout IXpsOMCanvas           *xpsCanvas
	)
{
	HRESULT                         hr                         = S_OK;
	IXpsOMVisualCollection          *canvasVisuals             = NULL;
	IXpsOMPath                      *pathSidebar               = NULL;
	IXpsOMGeometry                  *xpsGeometry               = NULL;
	IXpsOMGeometryFigure            *xpsFigure                 = NULL;
	IXpsOMGeometryFigureCollection  *xpsFigureCollection       = NULL;
	IXpsOMSolidColorBrush           *sidebarBrush              = NULL;

	XPS_COLOR                        xpsColorSidebar;
	XPS_POINT                        startPoint;

    // First we need to get the top-level Canvas visual collection
	IFC( xpsCanvas->GetVisuals(&canvasVisuals) );

	// Create the brush needed for the sidebar
	xpsColorSidebar.colorType        = XPS_COLOR_TYPE_SRGB;
    xpsColorSidebar.value.sRGB.alpha = 0xFF;
    xpsColorSidebar.value.sRGB.red   = 0x2E;
    xpsColorSidebar.value.sRGB.green = 0x36;
    xpsColorSidebar.value.sRGB.blue  = 0x40;
	IFC( xpsFactory->CreateSolidColorBrush(&xpsColorSidebar, NULL, &sidebarBrush) );

	// Create the geometry needed for the sidebar
    startPoint.x = 18.0f;
	startPoint.y = 18.0f;
    XPS_SEGMENT_TYPE sidebarSegmentTypes[3] = {
        XPS_SEGMENT_TYPE_LINE, 
        XPS_SEGMENT_TYPE_LINE, 
        XPS_SEGMENT_TYPE_LINE
    };
    FLOAT sidebarSegmentData[6] = {
        18.0f, 774.0f,
        157.5f, 774.0f,
		157.5f, 18.0f
    };
    BOOL sidebarSegmentStrokes[3] = {
        FALSE, FALSE, FALSE
    };
    IFC( xpsFactory->CreateGeometryFigure( &startPoint, &xpsFigure ) );
    IFC( xpsFigure->SetIsClosed( TRUE ));
    IFC( xpsFigure->SetIsFilled( TRUE ));
    IFC( xpsFigure->SetSegments(3, 6, sidebarSegmentTypes, sidebarSegmentData, sidebarSegmentStrokes) );
	IFC( xpsFactory->CreateGeometry(&xpsGeometry) );
    IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->Append(xpsFigure) );

    // Create our sidebar
	IFC( xpsFactory->CreatePath(&pathSidebar) );
	IFC( pathSidebar->SetFillBrushLocal(sidebarBrush) );
	IFC( pathSidebar->SetGeometryLocal(xpsGeometry) );

	// Add the sidebar to the top-level canvas
	IFC( canvasVisuals->Append(pathSidebar) );

    // Clean up interfaces
	xpsGeometry->Release();
	xpsFigureCollection->Release();
	xpsFigure->Release();
	pathSidebar->Release();
	sidebarBrush->Release();
	canvasVisuals->Release();

	return hr;

Cleanup:
	// Error was encountered, so systematically clean up working objects.
    if (xpsGeometry)          xpsGeometry->Release();
	if (xpsFigureCollection)  xpsFigureCollection->Release();
	if (xpsFigure)            xpsFigure->Release();
	if (pathSidebar)          pathSidebar->Release();
	if (sidebarBrush)         sidebarBrush->Release();
	if (canvasVisuals)        canvasVisuals->Release();

	return hr;
}

HRESULT 
AppendTopbar(
    __in    IXpsOMObjectFactory    *xpsFactory,
    __inout IXpsOMCanvas           *xpsCanvas
	)
{
	HRESULT                         hr                         = S_OK;
	IXpsOMVisualCollection          *canvasVisuals             = NULL;
	IXpsOMPath                      *pathTopbar                = NULL;
	IXpsOMGeometry                  *xpsGeometry               = NULL;
	IXpsOMGeometryFigure            *xpsFigure                 = NULL;
	IXpsOMGeometryFigureCollection  *xpsFigureCollection       = NULL;
	IXpsOMLinearGradientBrush       *topbarBrush               = NULL;
	IXpsOMGradientStop              *xpsGradientStop1          = NULL,
	                                *xpsGradientStop2          = NULL;

	XPS_COLOR                        xpsColorTopbar;
	XPS_POINT                        startPoint, 
		                             endPoint;

    // First we need to get the top-level Canvas visual collection
	IFC( xpsCanvas->GetVisuals(&canvasVisuals) );

	// Create the brush needed for the topbar
	xpsColorTopbar.colorType        = XPS_COLOR_TYPE_SRGB;
    xpsColorTopbar.value.sRGB.alpha = 0xFF;
    xpsColorTopbar.value.sRGB.red   = 0xE4;
    xpsColorTopbar.value.sRGB.green = 0x3B;
    xpsColorTopbar.value.sRGB.blue  = 0x2F;
	IFC( xpsFactory->CreateGradientStop(&xpsColorTopbar, NULL, 0.0f, &xpsGradientStop1) );

	xpsColorTopbar.colorType        = XPS_COLOR_TYPE_SRGB;
    xpsColorTopbar.value.sRGB.alpha = 0xFF;
    xpsColorTopbar.value.sRGB.red   = 0xEF;
    xpsColorTopbar.value.sRGB.green = 0x79;
    xpsColorTopbar.value.sRGB.blue  = 0x2F;
	IFC( xpsFactory->CreateGradientStop(&xpsColorTopbar, NULL, 1.0f, &xpsGradientStop2) );

	startPoint.x = 375.75f;
	startPoint.y = 18.0f;
	endPoint.x   = 375.75f;
	endPoint.y   = 134.6f;

	IFC( xpsFactory->CreateLinearGradientBrush(xpsGradientStop1, xpsGradientStop2, &startPoint, &endPoint, &topbarBrush) );

	// Create the geometry needed for the topbar
    startPoint.x = 157.5f;
	startPoint.y = 18.0f;
    XPS_SEGMENT_TYPE topbarSegmentTypes[3] = {
        XPS_SEGMENT_TYPE_LINE, 
        XPS_SEGMENT_TYPE_BEZIER,  
		XPS_SEGMENT_TYPE_LINE
    };
    FLOAT topbarSegmentData[10] = {
        157.5f,   134.6f,
        322.76f, 102.91f, 476.79f, 105.27f, 594.0f, 116.63f,
		594.0f,    18.0f
    };
    BOOL topbarSegmentStrokes[3] = {
        FALSE, FALSE, FALSE
    };
    IFC( xpsFactory->CreateGeometryFigure( &startPoint, &xpsFigure ) );
    IFC( xpsFigure->SetIsClosed( TRUE ));
    IFC( xpsFigure->SetIsFilled( TRUE ));
    IFC( xpsFigure->SetSegments(3, 10, topbarSegmentTypes, topbarSegmentData, topbarSegmentStrokes) );
	IFC( xpsFactory->CreateGeometry(&xpsGeometry) );
    IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->Append(xpsFigure) );

    // Create our topbar
	IFC( xpsFactory->CreatePath(&pathTopbar) );
	IFC( pathTopbar->SetFillBrushLocal(topbarBrush) );
	IFC( pathTopbar->SetGeometryLocal(xpsGeometry) );

	// Add the topbar to the page
	IFC( canvasVisuals->Append(pathTopbar) );

	// Clean up interfaces
	xpsGeometry->Release();
	xpsFigureCollection->Release();
	xpsFigure->Release();
	topbarBrush->Release();
    xpsGradientStop1->Release();
	xpsGradientStop2->Release();
	pathTopbar->Release();
    canvasVisuals->Release();

	return hr;

Cleanup:
	// Error was encountered, so systematically clean up working objects.
    if (xpsGeometry)          xpsGeometry->Release();
	if (xpsFigureCollection)  xpsFigureCollection->Release();
	if (xpsFigure)            xpsFigure->Release();
	if (topbarBrush)          topbarBrush->Release();
	if (xpsGradientStop1)     xpsGradientStop1->Release();
	if (xpsGradientStop2)     xpsGradientStop2->Release();
	if (pathTopbar)           pathTopbar->Release();
	if (canvasVisuals)        canvasVisuals->Release();

	return hr;
}


HRESULT 
AppendSwooshes(
    __in    IXpsOMObjectFactory *xpsFactory,
    __inout IXpsOMCanvas        *xpsCanvas
	)
{
	HRESULT                         hr                         = S_OK;
	IXpsOMVisualCollection          *canvasVisuals             = NULL;
	IXpsOMPath                      *pathSwoosh1               = NULL;
	IXpsOMPath                      *pathSwoosh2               = NULL;
	IXpsOMGeometry                  *xpsGeometry               = NULL;
	IXpsOMGeometryFigure            *xpsFigure                 = NULL;
	IXpsOMGeometryFigureCollection  *xpsFigureCollection       = NULL;
	IXpsOMSolidColorBrush           *swooshBrush               = NULL;

	XPS_COLOR                        xpsColorSwoosh;
	XPS_POINT                        startPoint;

	// First we need to get the top-level Canvas visual collection
	IFC( xpsCanvas->GetVisuals(&canvasVisuals) );

	// Create the brush needed for the first three swooshes
	xpsColorSwoosh.colorType        = XPS_COLOR_TYPE_SRGB;
    xpsColorSwoosh.value.sRGB.alpha = 0xFF;
    xpsColorSwoosh.value.sRGB.red   = 0xFF;
    xpsColorSwoosh.value.sRGB.green = 0xFF;
    xpsColorSwoosh.value.sRGB.blue  = 0xFE;
	IFC( xpsFactory->CreateSolidColorBrush(&xpsColorSwoosh, NULL, &swooshBrush) );

	// Create the geometry needed for the 1st swoosh
    startPoint.x = 18.0f;
	startPoint.y = 157.85f;
    XPS_SEGMENT_TYPE swooshSegmentTypes[1] = {
        XPS_SEGMENT_TYPE_BEZIER
    };
    FLOAT swooshSegmentData[6] = {
        238.2f, 104.65f, 447.83f, 110.32f, 593.3f, 126.64f
    };
    BOOL swooshSegmentStrokes[1] = {
        TRUE
    };
    IFC( xpsFactory->CreateGeometryFigure( &startPoint, &xpsFigure ) );
    IFC( xpsFigure->SetIsClosed( FALSE ));
    IFC( xpsFigure->SetIsFilled( FALSE ));
    IFC( xpsFigure->SetSegments(1, 6, swooshSegmentTypes, swooshSegmentData, swooshSegmentStrokes) );
	IFC( xpsFactory->CreateGeometry(&xpsGeometry) );
    IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->Append(xpsFigure) );

    // Create our swoosh
	IFC( xpsFactory->CreatePath(&pathSwoosh1) );
	IFC( pathSwoosh1->SetStrokeBrushLocal(swooshBrush) );
	IFC( pathSwoosh1->SetStrokeThickness(0.5f) );
	IFC( pathSwoosh1->SetGeometryLocal(xpsGeometry) );

	// Add the swoosh to the top-level canvas
	IFC( canvasVisuals->Append(pathSwoosh1) );

    // Clean up interfaces for reuse
	xpsGeometry->Release();
	xpsGeometry = NULL;
	xpsFigure->Release();
	xpsFigure = NULL;
	xpsFigureCollection->Release();
	xpsFigureCollection = NULL;
    swooshBrush->Release();
	swooshBrush = NULL;

	// Create our second swoosh by cloning the first ----------------
	IFC( pathSwoosh1->Clone(&pathSwoosh2) );

	// Modify the geometry of our cloned swoosh
	IFC( pathSwoosh2->GetGeometryLocal(&xpsGeometry) );
	IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->GetAt(0, &xpsFigure) );

    startPoint.x = 18.0f;
	startPoint.y = 163.75f;
    swooshSegmentData[0] = 235.85f;
    swooshSegmentData[1] = 102.28f;
	swooshSegmentData[2] = 445.95f;
	swooshSegmentData[3] = 100.15f;
	swooshSegmentData[4] = 593.3f;
	swooshSegmentData[5] = 111.26f;

	IFC( xpsFigure->SetStartPoint(&startPoint) );
    IFC( xpsFigure->SetSegments(1, 6, swooshSegmentTypes, swooshSegmentData, swooshSegmentStrokes) );

	// Add the swoosh to the top-level canvas
	IFC( canvasVisuals->Append(pathSwoosh2) );

	// Clean up interfaces for reuse
	xpsGeometry->Release();
	xpsGeometry = NULL;
	xpsFigureCollection->Release();
	xpsFigureCollection = NULL;
	xpsFigure->Release();
	xpsFigure = NULL;
    pathSwoosh2->Release();
	pathSwoosh2 = NULL;

	// Create our third swoosh by cloning the first  ----------------
	IFC( pathSwoosh1->Clone(&pathSwoosh2) );

	// Modify the geometry of our cloned swoosh
	IFC( pathSwoosh2->GetGeometryLocal(&xpsGeometry) );
	IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->GetAt(0, &xpsFigure) );

    startPoint.x = 18.0f;
	startPoint.y = 158.3f;
    swooshSegmentData[0] = 236.56f;
    swooshSegmentData[1] = 100.15f;
	swooshSegmentData[2] = 446.18f;
	swooshSegmentData[3] = 100.86f;
	swooshSegmentData[4] = 593.3f;
	swooshSegmentData[5] = 114.1f;

	IFC( xpsFigure->SetStartPoint(&startPoint) );
    IFC( xpsFigure->SetSegments(1, 6, swooshSegmentTypes, swooshSegmentData, swooshSegmentStrokes) );

	// Add the swoosh to the top-level canvas
	IFC( canvasVisuals->Append(pathSwoosh2) );

	// Clean up interfaces for reuse
	xpsGeometry->Release();
	xpsGeometry = NULL;
	xpsFigureCollection->Release();
	xpsFigureCollection = NULL;
	xpsFigure->Release();
	xpsFigure = NULL;
    pathSwoosh2->Release();
	pathSwoosh2 = NULL;

	// Create our fourth swoosh by cloning the first ----------------
	IFC( pathSwoosh1->Clone(&pathSwoosh2) );

	// Modify the geometry of our cloned swoosh
	IFC( pathSwoosh2->GetGeometryLocal(&xpsGeometry) );
	IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->GetAt(0, &xpsFigure) );

    startPoint.x = 593.3f;
	startPoint.y = 104.64f;
    swooshSegmentData[0] = 446.18f;
    swooshSegmentData[1] = 91.636f;
	swooshSegmentData[2] = 236.32f;
	swooshSegmentData[3] = 91.4f;
	swooshSegmentData[4] = 18.0f;
	swooshSegmentData[5] = 150.05f;

	IFC( xpsFigure->SetStartPoint(&startPoint) );
    IFC( xpsFigure->SetSegments(1, 6, swooshSegmentTypes, swooshSegmentData, swooshSegmentStrokes) );

	// Change the color for this swoosh
    xpsColorSwoosh.value.sRGB.alpha = 0xFF;
    xpsColorSwoosh.value.sRGB.red   = 0xEF;
    xpsColorSwoosh.value.sRGB.green = 0xB3;
    xpsColorSwoosh.value.sRGB.blue  = 0x2F;
	IFC( xpsFactory->CreateSolidColorBrush(&xpsColorSwoosh, NULL, &swooshBrush) );
	IFC( pathSwoosh2->SetStrokeBrushLocal(swooshBrush) );

	// Add the swoosh to the top-level canvas
	IFC( canvasVisuals->Append(pathSwoosh2) );

	// Clean up interfaces for reuse
	xpsGeometry->Release();
	xpsGeometry = NULL;
	xpsFigureCollection->Release();
	xpsFigureCollection = NULL;
	xpsFigure->Release();
	xpsFigure = NULL;
    pathSwoosh2->Release();
	pathSwoosh2 = NULL;
    swooshBrush->Release();
    swooshBrush = NULL;

	// Create our fifth and final swoosh by cloning the first ---------------
	IFC( pathSwoosh1->Clone(&pathSwoosh2) );

	// Modify the geometry of our cloned swoosh
	IFC( pathSwoosh2->GetGeometryLocal(&xpsGeometry) );
	IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->GetAt(0, &xpsFigure) );

    startPoint.x = 18.0f;
	startPoint.y = 168.0f;
    swooshSegmentData[0] = 236.32f;
    swooshSegmentData[1] = 109.35f;
	swooshSegmentData[2] = 445.95f;
	swooshSegmentData[3] = 109.59f;
	swooshSegmentData[4] = 593.3f;
	swooshSegmentData[5] = 122.36f;

	IFC( xpsFigure->SetStartPoint(&startPoint) );
    IFC( xpsFigure->SetSegments(1, 6, swooshSegmentTypes, swooshSegmentData, swooshSegmentStrokes) );

	// Change the color for this swoosh
	IFC( xpsFactory->CreateSolidColorBrush(&xpsColorSwoosh, NULL, &swooshBrush) );
	IFC( pathSwoosh2->SetStrokeBrushLocal(swooshBrush) );

	// Add the swoosh to the top-level canvas
	IFC( canvasVisuals->Append(pathSwoosh2) );

	// Clean up interfaces
	xpsGeometry->Release();
	xpsFigureCollection->Release();
	xpsFigure->Release();
    swooshBrush->Release();
	pathSwoosh2->Release();
    pathSwoosh1->Release();
	canvasVisuals->Release();

	return hr;

Cleanup:
	// Error was encountered, so systematically clean up working objects.
    if (xpsGeometry)          xpsGeometry->Release();
	if (xpsFigureCollection)  xpsFigureCollection->Release();
	if (xpsFigure)            xpsFigure->Release();
	if (swooshBrush)          swooshBrush->Release();
	if (pathSwoosh1)          pathSwoosh1->Release();
	if (pathSwoosh2)          pathSwoosh2->Release();
	if (canvasVisuals)        canvasVisuals->Release();

	return hr;
}

HRESULT 
AppendLogo(
    __in    IXpsOMObjectFactory *xpsFactory,
    __inout IXpsOMCanvas        *xpsCanvas
	)
{
	HRESULT                         hr                         = S_OK;
	IXpsOMVisualCollection          *canvasVisuals             = NULL;
	IXpsOMPath                      *pathLogo1                 = NULL,
	                                *pathLogo2                 = NULL,
									*pathLogo3                 = NULL,
									*pathLogo4                 = NULL,
									*pathLogo5                 = NULL,
									*pathLogo6                 = NULL;
	IXpsOMGeometry                  *xpsGeometry               = NULL;
	IXpsOMGeometryFigure            *xpsFigure                 = NULL;
	IXpsOMGeometryFigureCollection  *xpsFigureCollection       = NULL;
	IXpsOMBrush                     *xpsBrush                  = NULL;
	IXpsOMLinearGradientBrush       *logoBrush                 = NULL;
	IXpsOMGradientStopCollection    *xpsGradientStopCollection = NULL;
	IXpsOMGradientStop              *xpsGradientStop1          = NULL;
	IXpsOMGradientStop				*xpsGradientStop2          = NULL;
	IXpsOMGradientStop              *xpsGradientStop3          = NULL;

	XPS_COLOR                        xpsColorLogo;
	XPS_POINT                        startPoint, endPoint;

    // First we need to get the top-level Canvas visual collection
	IFC( xpsCanvas->GetVisuals(&canvasVisuals) );

	// Create the brush needed for the first path of the logo--------------
	xpsColorLogo.colorType        = XPS_COLOR_TYPE_SRGB;
    xpsColorLogo.value.sRGB.alpha = 0xFF;
    xpsColorLogo.value.sRGB.red   = 0xE3;
    xpsColorLogo.value.sRGB.green = 0x38;
    xpsColorLogo.value.sRGB.blue  = 0x30;
	IFC( xpsFactory->CreateGradientStop(&xpsColorLogo, NULL, 0.0f, &xpsGradientStop1) );
	IFC( xpsFactory->CreateGradientStop(&xpsColorLogo, NULL, 1.0f, &xpsGradientStop3) );

	xpsColorLogo.colorType        = XPS_COLOR_TYPE_SRGB;
    xpsColorLogo.value.sRGB.alpha = 0xFF;
    xpsColorLogo.value.sRGB.red   = 0xEF;
    xpsColorLogo.value.sRGB.green = 0xB3;
    xpsColorLogo.value.sRGB.blue  = 0x2F;
	IFC( xpsFactory->CreateGradientStop(&xpsColorLogo, NULL, 0.4f, &xpsGradientStop2) );

	startPoint.x = 471.44f;
	startPoint.y = 722.1f;
	endPoint.x   = 508.28f;
	endPoint.y   = 773.88f;

	IFC( xpsFactory->CreateLinearGradientBrush(xpsGradientStop1, xpsGradientStop3, &startPoint, &endPoint, &logoBrush) );
	IFC( logoBrush->GetGradientStops(&xpsGradientStopCollection) );
	IFC( xpsGradientStopCollection->InsertAt(1, xpsGradientStop2) );

	// Create the geometry needed for the first logo path
    startPoint.x = 491.01f;
	startPoint.y = 734.1f;
    XPS_SEGMENT_TYPE logoSegmentTypes[6] = {
        XPS_SEGMENT_TYPE_BEZIER, 
        XPS_SEGMENT_TYPE_BEZIER,  
        XPS_SEGMENT_TYPE_BEZIER, 
        XPS_SEGMENT_TYPE_BEZIER,  
        XPS_SEGMENT_TYPE_BEZIER, 
        XPS_SEGMENT_TYPE_BEZIER  
    };
    FLOAT logoSegmentData1[36] = {
		486.96f, 740.52f,  478.62f, 742.18f,  472.43f, 738.14f, 
        469.81f, 736.48f,  467.90f, 733.86f,  466.95f, 731.01f, 
        467.43f, 734.81f,  469.57f, 738.62f,  473.14f, 740.76f, 
        479.34f, 744.80f,  487.68f, 743.14f,  491.49f, 736.71f, 
        493.87f, 733.39f,  494.35f, 729.10f,  493.16f, 725.30f, 
        493.40f, 728.39f,  492.68f, 731.48f,  491.01f, 734.1f
    };
    BOOL logoSegmentStrokes[6] = {
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE
    };
    IFC( xpsFactory->CreateGeometryFigure( &startPoint, &xpsFigure ) );
    IFC( xpsFigure->SetIsClosed( TRUE ));
    IFC( xpsFigure->SetIsFilled( TRUE ));
    IFC( xpsFigure->SetSegments(6, 36, logoSegmentTypes, logoSegmentData1, logoSegmentStrokes) );
	IFC( xpsFactory->CreateGeometry(&xpsGeometry) );
    IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->Append(xpsFigure) );

    // Create our logo
	IFC( xpsFactory->CreatePath(&pathLogo1) );
	IFC( pathLogo1->SetFillBrushLocal(logoBrush) );
	IFC( pathLogo1->SetGeometryLocal(xpsGeometry) );

	// Add the path to the page
	IFC( canvasVisuals->Append(pathLogo1) );

	// Clean up interfaces for reuse
	xpsGeometry->Release();
	xpsGeometry = NULL;
	xpsFigureCollection->Release();
	xpsFigureCollection = NULL;
	xpsFigure->Release();
	xpsFigure = NULL;
	logoBrush->Release();
	logoBrush = NULL;
	xpsGradientStop1->Release();
	xpsGradientStop1 = NULL;
	xpsGradientStop2->Release();
	xpsGradientStop2 = NULL;
	xpsGradientStop3->Release();
	xpsGradientStop3 = NULL;
	xpsGradientStopCollection->Release();
	xpsGradientStopCollection = NULL;


	// Create the second path of the logo by cloning the first.--------------
	IFC( pathLogo1->Clone(&pathLogo2) );

	// Modify the geometry for the path
	IFC( pathLogo2->GetGeometry(&xpsGeometry) );
	IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->GetAt(0, &xpsFigure) );

	startPoint.x = 484.12f;
	startPoint.y = 737.9f;
    FLOAT logoSegmentData2[36] = {
        476.72f, 739.56f,  469.57f, 734.81f,  468.14f, 727.68f, 
        467.42f, 724.59f,  467.90f, 721.50f,  469.33f, 718.65f, 
        466.94f, 721.74f,  465.75f, 725.78f,  466.70f, 729.82f, 
        468.14f, 737.19f,  475.29f, 741.70f,  482.69f, 740.27f, 
        486.74f, 739.32f,  490.08f, 736.71f,  491.75f, 733.15f, 
        489.84f, 735.52f,  487.22f, 737.19f,  484.12f, 737.9f
    };
    IFC( xpsFigure->SetSegments(6, 36, logoSegmentTypes, logoSegmentData2, logoSegmentStrokes) );
	IFC( xpsFigure->SetStartPoint(&startPoint) );

	// Modify the gradient range
	startPoint.x = 467.31f;
	startPoint.y = 717.27f;
	endPoint.x   = 513.07f;
	endPoint.y   = 768.89f;
	IFC( pathLogo2->GetFillBrushLocal(&xpsBrush) );
	IFC( xpsBrush->QueryInterface(&logoBrush) );
	IFC( logoBrush->SetStartPoint(&startPoint) );
	IFC( logoBrush->SetEndPoint(&endPoint) );

	// Add the path to the page
	IFC( canvasVisuals->Append(pathLogo2) );

	// Clean up interfaces for reuse
	xpsGeometry->Release();
	xpsGeometry = NULL;
	xpsFigureCollection->Release();
	xpsFigureCollection = NULL;
	xpsFigure->Release();
	xpsFigure = NULL;
	pathLogo2->Release();
	pathLogo2 = NULL;
	xpsBrush->Release();
	xpsBrush = NULL;
	logoBrush->Release();
	logoBrush = NULL;


	// Create the third path of the logo by cloning the first.--------------
	IFC( pathLogo1->Clone(&pathLogo3) );

	// Modify the geometry for the path
	IFC( pathLogo3->GetGeometry(&xpsGeometry) );
	IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->GetAt(0, &xpsFigure) );

	startPoint.x = 477.43f;
	startPoint.y = 728.16f;
    FLOAT logoSegmentData3[36] = {
        476.24f, 724.36f,  478.38f, 720.32f,  482.19f, 719.14f, 
        483.86f, 718.66f,  485.52f, 718.90f,  486.95f, 719.37f, 
        485.28f, 718.19f,  483.14f, 717.95f,  481.00f, 718.66f, 
        477.19f, 719.85f,  475.05f, 723.89f,  476.24f, 727.69f, 
        476.95f, 729.83f,  478.38f, 731.25f,  480.29f, 732.20f, 
        479.10f, 731.25f,  477.91f, 729.83f,  477.43f, 728.16f
    };
    IFC( xpsFigure->SetSegments(6, 36, logoSegmentTypes, logoSegmentData3, logoSegmentStrokes) );
	IFC( xpsFigure->SetStartPoint(&startPoint) );

	// Modify the gradient range
	startPoint.x = 459.97f;
	startPoint.y = 742.64f;
	endPoint.x   = 488.01f;
	endPoint.y   = 719.22f;
	IFC( pathLogo3->GetFillBrushLocal(&xpsBrush) );
	IFC( xpsBrush->QueryInterface(&logoBrush) );
	IFC( logoBrush->SetStartPoint(&startPoint) );
	IFC( logoBrush->SetEndPoint(&endPoint) );

	// Modify the gradient offset
	IFC( logoBrush->GetGradientStops(&xpsGradientStopCollection) );
	IFC( xpsGradientStopCollection->GetAt(1, &xpsGradientStop2) );
	IFC( xpsGradientStop2->SetOffset(0.6f) );

	// Add the path to the page
	IFC( canvasVisuals->Append(pathLogo3) );

	// Clean up interfaces for reuse
	xpsGeometry->Release();
	xpsGeometry = NULL;
	xpsFigureCollection->Release();
	xpsFigureCollection = NULL;
	xpsFigure->Release();
	xpsFigure = NULL;
	pathLogo1->Release();
	pathLogo1 = NULL;
	xpsBrush->Release();
	xpsBrush = NULL;
	logoBrush->Release();
	logoBrush = NULL;
	xpsGradientStopCollection->Release();
	xpsGradientStopCollection = NULL;
	xpsGradientStop2->Release();
	xpsGradientStop2 = NULL;

	
	// Create the fourth path of the logo by cloning the third.--------------
	IFC( pathLogo3->Clone(&pathLogo4) );

	// Modify the geometry for the path
	IFC( pathLogo4->GetGeometry(&xpsGeometry) );
	IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->GetAt(0, &xpsFigure) );

	startPoint.x = 478.37f;
	startPoint.y = 724.11f;
    FLOAT logoSegmentData4[36] = {
        480.04f, 720.56f,  484.57f, 719.13f,  488.15f, 721.03f, 
        489.58f, 721.98f,  490.77f, 723.16f,  491.25f, 724.58f,
		491.01f, 722.69f,  489.58f, 720.79f,  487.67f, 719.61f, 
		484.09f, 717.95f,  479.80f, 719.13f,  477.89f, 722.69f,
		476.70f, 724.82f,  476.70f, 726.95f,  477.65f, 728.85f,
		477.18f, 727.43f,  477.42f, 725.53f,  478.37f, 724.11f
    };
    IFC( xpsFigure->SetSegments(6, 36, logoSegmentTypes, logoSegmentData4, logoSegmentStrokes) );
	IFC( xpsFigure->SetStartPoint(&startPoint) );

	// Modify the gradient range
	startPoint.x = 468.28f;
	startPoint.y = 744.34f;
	endPoint.x   = 489.2f;
	endPoint.y   = 716.41f;
	IFC( pathLogo4->GetFillBrushLocal(&xpsBrush) );
	IFC( xpsBrush->QueryInterface(&logoBrush) );
	IFC( logoBrush->SetStartPoint(&startPoint) );
	IFC( logoBrush->SetEndPoint(&endPoint) );

	// Add the path to the page
	IFC( canvasVisuals->Append(pathLogo4) );

	// Clean up interfaces for reuse
	xpsGeometry->Release();
	xpsGeometry = NULL;
	xpsFigureCollection->Release();
	xpsFigureCollection = NULL;
	xpsFigure->Release();
	xpsFigure = NULL;
	pathLogo3->Release();
	pathLogo3 = NULL;
	xpsBrush->Release();
	xpsBrush = NULL;
	logoBrush->Release();
	logoBrush = NULL;


	// Create the fifth path of the logo by cloning the fourth.--------------
	IFC( pathLogo4->Clone(&pathLogo5) );

	// Modify the geometry for the path
	IFC( pathLogo5->GetGeometry(&xpsGeometry) );
	IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->GetAt(0, &xpsFigure) );

	startPoint.x = 476.47f;
	startPoint.y = 733.39f;
    FLOAT logoSegmentData5[36] = {
		471.69f, 730.3f,   470.26f, 723.88f,  473.37f, 719.13f,
		474.80f, 716.99f,  476.71f, 715.56f,  479.10f, 714.85f, 
		475.99f, 715.09f,  473.13f, 716.75f,  471.46f, 719.6f, 
		468.35f, 724.36f,  469.54f, 730.77f,  474.56f, 733.86f, 
		477.19f, 735.76f,  480.53f, 736.00f,  483.40f, 735.05f,
		481.01f, 735.29f,  478.62f, 734.81f,  476.47f, 733.39f
    };
    IFC( xpsFigure->SetSegments(6, 36, logoSegmentTypes, logoSegmentData5, logoSegmentStrokes) );
	IFC( xpsFigure->SetStartPoint(&startPoint) );

	// Modify the gradient range
	startPoint.x = 445.9f;
	startPoint.y = 746.75f;
	endPoint.x   = 485.86f;
	endPoint.y   = 718.31f;
	IFC( pathLogo5->GetFillBrushLocal(&xpsBrush) );
	IFC( xpsBrush->QueryInterface(&logoBrush) );
	IFC( logoBrush->SetStartPoint(&startPoint) );
	IFC( logoBrush->SetEndPoint(&endPoint) );

	// Modify the central gradient offset and color
    xpsColorLogo.value.sRGB.green = 0x79;
	IFC( xpsFactory->CreateGradientStop(&xpsColorLogo, NULL, 0.5f, &xpsGradientStop2) );
	IFC( logoBrush->GetGradientStops(&xpsGradientStopCollection) );
	IFC( xpsGradientStopCollection->SetAt(1, xpsGradientStop2) );

	// Add the path to the page
	IFC( canvasVisuals->Append(pathLogo5) );

	// Clean up interfaces for reuse
	xpsGeometry->Release();
	xpsGeometry = NULL;
	xpsFigureCollection->Release();
	xpsFigureCollection = NULL;
	xpsFigure->Release();
	xpsFigure = NULL;
	pathLogo4->Release();
	pathLogo4 = NULL;
	xpsBrush->Release();
	xpsBrush = NULL;
	logoBrush->Release();
	logoBrush = NULL;
	xpsGradientStopCollection->Release();
	xpsGradientStopCollection = NULL;
	xpsGradientStop2->Release();
	xpsGradientStop2 = NULL;


	// Create the sixth path of the logo by cloning the fifth.--------------
	IFC( pathLogo5->Clone(&pathLogo6) );

	// Modify the geometry for the path
	IFC( pathLogo6->GetGeometry(&xpsGeometry) );
	IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->GetAt(0, &xpsFigure) );

	startPoint.x = 473.61f;
	startPoint.y = 728.16f;
    FLOAT logoSegmentData6[36] = {
		472.42f, 722.46f,  476.00f, 716.99f, 481.73f, 715.56f, 
		484.12f, 715.09f,  486.50f, 715.56f, 488.65f, 716.51f, 
		486.26f, 714.61f,  483.16f, 713.9f,  479.82f, 714.61f, 
		474.33f, 715.80f,  470.75f, 721.27f, 471.94f, 726.97f, 
		472.66f, 730.06f,  474.57f, 732.67f, 477.43f, 734.1f,
		475.52f, 732.67f,  474.09f, 730.54f, 473.61f, 728.16f
    };
    IFC( xpsFigure->SetSegments(6, 36, logoSegmentTypes, logoSegmentData6, logoSegmentStrokes) );
	IFC( xpsFigure->SetStartPoint(&startPoint) );

	// Modify the gradient range
	startPoint.x = 449.62f;
	startPoint.y = 750.65f;
	endPoint.x   = 489.72f;
	endPoint.y   = 715.11f;
	IFC( pathLogo6->GetFillBrushLocal(&xpsBrush) );
	IFC( xpsBrush->QueryInterface(&logoBrush) );
	IFC( logoBrush->SetStartPoint(&startPoint) );
	IFC( logoBrush->SetEndPoint(&endPoint) );

	// Add the path to the page
	IFC( canvasVisuals->Append(pathLogo6) );

	// Clean up remaining interfaces
	xpsGeometry->Release();
	xpsFigureCollection->Release();
	xpsFigure->Release();
	pathLogo5->Release();
	pathLogo6->Release();
	xpsBrush->Release();
	logoBrush->Release();
	canvasVisuals->Release();

	return hr;

Cleanup:
	// Error was encountered, so systematically clean up working objects.
    if (xpsGeometry)                xpsGeometry->Release();
	if (xpsFigureCollection)        xpsFigureCollection->Release();
	if (xpsFigure)                  xpsFigure->Release();
	if (pathLogo1)                  pathLogo1->Release();
	if (pathLogo2)                  pathLogo2->Release();
	if (pathLogo3)                  pathLogo3->Release();
	if (pathLogo4)                  pathLogo4->Release();
	if (pathLogo5)                  pathLogo5->Release();
	if (pathLogo6)                  pathLogo6->Release();
	if (xpsBrush)                   xpsBrush->Release();
	if (logoBrush)                  logoBrush->Release();
	if (xpsGradientStopCollection)  xpsGradientStopCollection->Release();
	if (xpsGradientStop1)           xpsGradientStop1->Release();
	if (xpsGradientStop2)           xpsGradientStop2->Release();
	if (xpsGradientStop3)           xpsGradientStop3->Release();
	if (canvasVisuals)              canvasVisuals->Release();

	return hr;
}

HRESULT 
BuildXpsPageTextContent(
    __in    IOpcFactory         *pOpcFactory,
    __in    IXpsOMObjectFactory *pXpsObjectFactory, 
    __inout IXpsOMPage          *pXpsFixedPage
    )
{

	HRESULT                hr = S_OK;

	IStream                *fontStream      = NULL;
    IOpcPartUri            *fontUri         = NULL;
	IXpsOMFontResource     *fontResource    = NULL;
	IXpsOMVisualCollection *pageVisuals     = NULL;
	IXpsOMCanvas           *canvas          = NULL;
	IXpsOMVisual           *canvasVisual    = NULL;
	XPS_COLOR              xpsColorSidebarTitle, xpsColorSidebarText, xpsColorBodyText, xpsColorLogoText, xpsColorBullet;

	// Create font stream
	IFC( SHCreateStreamOnFileEx(L"C:\\Windows\\Fonts\\arial.ttf\0\0", STGM_READ, FILE_ATTRIBUTE_NORMAL, FALSE, NULL, &fontStream) );
	
	// Create new obfuscated part URI for this resource
    IFC( GenerateNewFontPartUri(pOpcFactory, &fontUri) );

    // Create new XPS font resource
    IFC( pXpsObjectFactory->CreateFontResource(
            fontStream,
            XPS_FONT_EMBEDDING_OBFUSCATED,
            fontUri,
            FALSE, //isObfSourceStream
            &fontResource) );


	// Create the colors to fill our text with
	xpsColorSidebarTitle.colorType = XPS_COLOR_TYPE_SRGB;
    xpsColorSidebarTitle.value.sRGB.alpha = 0xFF;
    xpsColorSidebarTitle.value.sRGB.red = 0xEF;
    xpsColorSidebarTitle.value.sRGB.green = 0x79;
    xpsColorSidebarTitle.value.sRGB.blue = 0x2F;

	xpsColorSidebarText.colorType = XPS_COLOR_TYPE_SRGB;
    xpsColorSidebarText.value.sRGB.alpha = 0xFF;
    xpsColorSidebarText.value.sRGB.red = 0xFF;
    xpsColorSidebarText.value.sRGB.green = 0xFF;
    xpsColorSidebarText.value.sRGB.blue = 0xFF;

	xpsColorBodyText.colorType = XPS_COLOR_TYPE_SRGB;
    xpsColorBodyText.value.sRGB.alpha = 0xFF;
    xpsColorBodyText.value.sRGB.red = 0x00;
    xpsColorBodyText.value.sRGB.green = 0x00;
    xpsColorBodyText.value.sRGB.blue = 0x00;

	xpsColorLogoText.colorType = XPS_COLOR_TYPE_SRGB;
    xpsColorLogoText.value.sRGB.alpha = 0xFF;
    xpsColorLogoText.value.sRGB.red = 0x2E;
    xpsColorLogoText.value.sRGB.green = 0x36;
    xpsColorLogoText.value.sRGB.blue = 0x40;

	xpsColorBullet.colorType = XPS_COLOR_TYPE_SRGB;
    xpsColorBullet.value.sRGB.alpha = 0xFF;
    xpsColorBullet.value.sRGB.red = 0xE3;
    xpsColorBullet.value.sRGB.green = 0x38;
    xpsColorBullet.value.sRGB.blue = 0x30;

	// Find the root-level canvas for this page that will contain all our content.
	IFC( pXpsFixedPage->GetVisuals(&pageVisuals) );
	IFC( pageVisuals->GetAt(0, &canvasVisual) );
	IFC( canvasVisual->QueryInterface(&canvas) );

	// Build the sidebar text
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 8.04f, xpsColorSidebarTitle, 33.6f, 249.74f, L"INTERNET SECURITY", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 265.73f, L"Sit amet, consec tetuer ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 281.81f, L"adipiscing elit, sed diam ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 297.77f, L"nonummy nibh euismod tincidunt ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 313.73f, L"ut laoreet dolore magna aliquam.", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 8.04f, xpsColorSidebarTitle, 33.6f, 345.77f, L"NETWORK PROTECTION", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 361.73f, L"Ut wisi enim ad minim veniam, ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 377.81f, L"quis nostrud exerci tation ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 393.77f, L"ullamcorper.Et iusto odio ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 409.73f, L"dignissim qui blandit ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 425.81f, L"praeseptatum zzril delenit ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 441.79f, L"augue duis dolore te feugait ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 457.75f, L"nulla adipiscing elit, sed diam ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 473.83f, L"nonummy nibh.", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 8.04f, xpsColorSidebarTitle, 33.6f, 505.75f, L"PERSONAL FIREWALLS", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 521.83f, L"Tincidunt ut laoreet dolore ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 537.79f, L"magna aliquam erat volut pat. Ut ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 553.75f, L"wisi enim ad minim veniam, quis ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 569.83f, L"exerci tation ullamcorper cipit ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorSidebarText,  33.6f, 585.79f, L"lobortis nisl ut aliquip ex.", canvas) );

	// Build the topbar text
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 24.0f, xpsColorSidebarText, 187.46f, 56.4f, L"Information Technology Solutions", canvas) );

	// Build doc title and bulleted list
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 21.96f, xpsColorBodyText, 187.46f, 185.18f, L"Network Systems Diagnostic Testing", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 8.04f, xpsColorBullet,    400.4f,  252.62f, L"●", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText,  416.11f, 252.62f, L"Justo odio dignissim qui blandit praesent ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText,  416.11f, 266.57f, L"luptatum zzril delenit augue duis dolore te ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText,  416.11f, 280.61f, L"feugait lorem ipsum dolo.", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 8.04f, xpsColorBullet,    400.4f,  308.57f, L"●", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText,  416.11f, 308.57f, L"Lorem ipsum dolorsit amet, conse ctetuer ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText,  416.11f, 322.61f, L"adipiscing elit, sed diam nonummy nibh ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText,  416.11f, 336.65f, L"euismod elit adispe.", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 8.04f, xpsColorBullet,    400.4f,  364.61f, L"●", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText,  416.11f, 364.61f, L"Feugait nulla facilisi. Lorem ipsum dolorsit ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText,  416.11f, 378.65f, L"amet, conse ctetuer laoreet dolore magna ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText,  416.11f, 392.57f, L"aliquam erat volutpat.", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 8.04f, xpsColorBullet,    400.4f,  420.65f, L"●", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText,  416.11f, 420.65f, L"Magna aliquam erat volu isi enim ad minim ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText,  416.11f, 434.71f, L"veniam melo eratta dolore magnus.", canvas) );

	// Build bottom block of text, column 1
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 501.55f, L"Lorem ipsum dolor sit amet, consec tetuer adipiscing ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 517.63f, L"elit, sed diam nonummy nibh euismod tincidunt ut ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 533.59f, L"laoreet dolore magna aliquam erat volutpat. Ut wisi enim ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 549.55f, L"ad minim veniam, quis nostrud exerci tation ullamcorper. ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 565.63f, L"Et iusto odio dignissim qui blandit praesent luptatum", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 581.59f, L"zzril delenit augue duis dolore te feugait nulla facilisi. ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 597.55f, L"Lorem ipsum dolor sit amet, conse ctetuer adipiscing ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 613.66f, L"elit, sed diam nonummy nibh euismod tincidunt ut ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 629.62f, L"laoreet dolore magna aliquam erat volutpat. Ut wisi ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 645.58f, L"enim ad minim veniam, quis exerci tation ullamcorper ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 661.66f, L"suscipit lobortis nisl ut aliquip ex ea commodo. Lorem ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 677.62f, L"ipsum dolor sit amet, consectetuer adipiscing elit elum ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 183.74f, 693.46f, L"corpes ipso mogno.", canvas) );

	// Build bottom block of text, column 2
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 501.79f, L"Nonummy nibh euismod tincidunt ut laoreet dolore ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 517.75f, L"magna aliquam erat volutpat. Ut wisi enim ad minim", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 533.83f, L"veniam, quis nostrud exerci tation ullamcorper. Et ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 549.79f, L"iusto odio dignissim qui blandit praesent luptatum zzril ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 565.75f, L"delenit augue duis dolore te feugait nisl ut aliquip ex ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 581.83f, L"ea commodo. Et iusto odio dignissim qui blandit ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 597.79f, L"praesent luptatum zzril delenit augue duis dolore te ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 613.78f, L"feugait nulla facilisi. Lorem ipsum dolor sit amet, ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 629.86f, L"conse ctetuer adipiscing. Feugait nulla facilisi. Lorem ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 645.82f, L"ipsum dolor sit amet, conse ctetuer laoreet dolore ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 661.78f, L"magna aliquam erat volutpat. Ut wisi enim ad minim ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 677.86f, L"veniam, quis exerci tation ullamcorper suscipit lobortis ", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 7.56f, xpsColorBodyText, 398.95f, 693.82f, L"nisl ut aliquip dolore te feugait nulla facilisi ex ea.", canvas) );

	// Build logo text
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 14.04f, xpsColorLogoText, 500.5f, 734.98f, L"technology", canvas) );
	IFC( AppendSimpleText(pXpsObjectFactory, fontResource, 8.04f, xpsColorSidebarTitle, 520.06f, 747.94f, L"consulting", canvas) );

	// Release unneeded interfaces
	fontUri->Release(); 
	fontUri = NULL;
	fontStream->Release();
	fontStream = NULL;
	pageVisuals->Release();
	pageVisuals = NULL;
	canvasVisual->Release();
	canvasVisual = NULL;
	fontResource->Release();
	fontResource = NULL;
	canvas->Release();
	canvas = NULL;

	return hr;

Cleanup:
	// Error was encountered, so systematically clean up working objects.
    if(fontUri)          fontUri->Release();
	if(fontStream)       fontStream->Release();
    if(fontResource)     fontResource->Release();
    if(pageVisuals)      pageVisuals->Release();
    if(canvas)           canvas->Release();
    if(canvasVisual)     canvasVisual->Release();

	return hr;
}

HRESULT 
BuildXpsPageImageContent(
    __in    IOpcFactory         *pOpcFactory, 
    __in    IXpsOMObjectFactory *pXpsObjectFactory, 
    __inout IXpsOMPage          *pXpsFixedPage
    )
{
	HRESULT                          hr                   = S_OK;
	IStream                         *imageStream          = NULL;
    IXpsOMCanvas                    *canvas               = NULL;
	IXpsOMVisual                    *canvasVisual         = NULL;
	IXpsOMVisualCollection          *pageVisuals          = NULL, 
		                            *canvasVisuals        = NULL;
	IXpsOMPath                      *imagePath            = NULL;
	IXpsOMGeometry                  *xpsGeometry          = NULL;
	IXpsOMGeometryFigure            *xpsFigure            = NULL;
	IXpsOMGeometryFigureCollection  *xpsFigureCollection  = NULL;
	IXpsOMImageBrush                *imageBrush           = NULL;
	IOpcPartUri                     *imageUri             = NULL;
	IXpsOMImageResource             *imageResource        = NULL;

	XPS_RECT                        xpsViewbox  = {0.0f,      0.0f, 453.76f, 464.0f};
	XPS_RECT                        xpsViewport = {147.2f, 215.15f,  238.4f, 243.6f};
	XPS_POINT                       startPoint;

    // Image font stream - Update path to where boxshot.jpg is located.
	IFC( SHCreateStreamOnFileEx(L"boxshot.jpg\0\0", STGM_READ, FILE_ATTRIBUTE_NORMAL, FALSE, NULL, &imageStream) );

	// create the image resource
    IFC( pOpcFactory->CreatePartUri(L"/Resources/Images/boxshot.jpg", &imageUri) );
	IFC( pXpsObjectFactory->CreateImageResource(imageStream, XPS_IMAGE_TYPE_JPEG, imageUri, &imageResource) );

	// Create the image brush
	IFC( pXpsObjectFactory->CreateImageBrush(imageResource, &xpsViewbox, &xpsViewport, &imageBrush) );

	// Create the geometry needed for the image
    startPoint.x = 147.2f;
	startPoint.y = 485.75f;
    XPS_SEGMENT_TYPE segmentTypes[3] = {
        XPS_SEGMENT_TYPE_LINE, 
        XPS_SEGMENT_TYPE_LINE, 
        XPS_SEGMENT_TYPE_LINE
    };
    FLOAT segmentData[6] = {
        147.2f, 215.15f,
        385.6f, 215.15f,
		385.6f, 458.75f
    };
    BOOL segmentStrokes[3] = {
        FALSE, FALSE, FALSE
    };
    IFC( pXpsObjectFactory->CreateGeometryFigure( &startPoint, &xpsFigure ) );
    IFC( xpsFigure->SetIsClosed( TRUE ));
    IFC( xpsFigure->SetIsFilled( TRUE ));
    IFC( xpsFigure->SetSegments(3, 6, segmentTypes, segmentData, segmentStrokes) );
	IFC( pXpsObjectFactory->CreateGeometry(&xpsGeometry) );
    IFC( xpsGeometry->GetFigures(&xpsFigureCollection) );
	IFC( xpsFigureCollection->Append(xpsFigure) );

    // Create our image
	IFC( pXpsObjectFactory->CreatePath(&imagePath) );
	IFC( imagePath->SetFillBrushLocal(imageBrush) );
	IFC( imagePath->SetGeometryLocal(xpsGeometry) );

	// Find the root-level canvas for this page that will contain all our content and insert our image.
	IFC( pXpsFixedPage->GetVisuals(&pageVisuals) );
	IFC( pageVisuals->GetAt(0, &canvasVisual) );
	IFC( canvasVisual->QueryInterface(&canvas) );
	IFC( canvas->GetVisuals(&canvasVisuals) );
	IFC( canvasVisuals->InsertAt(0, imagePath) ); // We insert at the start so the extra part of the image falls behind the sidebar.

	// Clean up interfaces
	imageStream->Release();
	imageUri->Release();
	imageResource->Release();
	imageBrush->Release();
	xpsFigure->Release();
	xpsFigureCollection->Release();
	xpsGeometry->Release();
	imagePath->Release();
	pageVisuals->Release();
	canvasVisual->Release();
	canvasVisuals->Release();
	canvas->Release();

	return hr;
	
Cleanup:
	// Error was encountered, so systematically clean up working objects.
    if (imageStream)        imageStream->Release();
    if (canvas)             canvas->Release();
    if (canvasVisual)       canvasVisual->Release();
    if (pageVisuals)        pageVisuals->Release();
    if (canvasVisuals)      canvasVisuals->Release();
    if (imagePath)          imagePath->Release();
    if (xpsGeometry)        xpsGeometry->Release();
    if (xpsFigure)          xpsFigure->Release();
    if (xpsFigureCollection)xpsFigureCollection->Release();
    if (imageBrush)         imageBrush->Release();
    if (imageUri)           imageUri->Release();
    if (imageResource)      imageResource->Release();

	return hr;
}

HRESULT 
BuildXpsPageGraphicsContent(
	__in    IXpsOMObjectFactory* pXpsObjectFactory, 
	__inout IXpsOMPage* pXpsFixedPage)
{
	HRESULT                          hr               = S_OK;
	IXpsOMCanvas                    *xpsCanvas        = NULL;
	IXpsOMVisualCollection          *pageVisuals      = NULL;
	IXpsOMMatrixTransform           *transform        = NULL;

	XPS_MATRIX                       xpsMatrix = { 1.333333333f, 0, 0, 1.333333333f, 0, 0 };

	// Create a page-level canvas to contain all of our page content
	IFC( pXpsObjectFactory->CreateCanvas(&xpsCanvas) );
	IFC( pXpsFixedPage->GetVisuals(&pageVisuals) );
	IFC( pageVisuals->Append(xpsCanvas) );

	// Set a transform on our canvas. Makes it easy to scale our content to the desired rendering size
    IFC( pXpsObjectFactory->CreateMatrixTransform(&xpsMatrix, &transform) );
    IFC( xpsCanvas->SetTransformLocal(transform) );

	IFC( AppendSidebar(pXpsObjectFactory, xpsCanvas) );
	IFC( AppendTopbar(pXpsObjectFactory, xpsCanvas) );
	IFC( AppendSwooshes(pXpsObjectFactory, xpsCanvas) );
	IFC( AppendLogo(pXpsObjectFactory, xpsCanvas) );

	// Clean up interfaces
	pageVisuals->Release();
	transform->Release();
	xpsCanvas->Release();

	return hr;
	
Cleanup:
	// Error was encountered, so systematically clean up working objects.
	if (pageVisuals)   pageVisuals->Release();
	if (transform)     transform->Release();
	if (xpsCanvas)     xpsCanvas->Release();

	return hr;
}

HRESULT 
BuildXpsDocument(
    VOID 
    )
{
	HRESULT                         hr                  = S_OK;
	IXpsOMObjectFactory            *pXpsObjectFactory   = NULL;
	IOpcFactory                    *pOpcFactory         = NULL;
    IXpsOMPackage                  *pXpsPackage         = NULL;
    IXpsOMDocumentSequence         *pFixedDocSeq        = NULL;
    IXpsOMDocument                 *pFixedDoc           = NULL;
    IXpsOMDocumentCollection       *pFixedDocColl       = NULL;
    IXpsOMPageReference            *pFixedPageRef       = NULL;
    IXpsOMPageReferenceCollection  *pFixedPageRefColl   = NULL;
    IXpsOMPage                     *pFixedPage1         = NULL;
    IOpcPartUri                    *page1Uri            = NULL, 
                                   *docUri              = NULL, 
                                   *docSeqUri           = NULL;

    XPS_SIZE                        pageSize            = {816.0, 1056.0};

    // Create our Factory object.
	IFC ( CoInitialize(NULL) );
    IFC ( GetXpsFactory(&pXpsObjectFactory));
    IFC ( GetOpcFactory(&pOpcFactory));

    // Create needed OpcPartUris
    IFC( pOpcFactory->CreatePartUri(L"/FixedDocumentSequence.fdseq", &docSeqUri) );
    IFC( pOpcFactory->CreatePartUri(L"/Documents/1/FixedDoc.fdoc", &docUri) );
    IFC( pOpcFactory->CreatePartUri(L"/Documents/1/Pages/1.fpage", &page1Uri) );

    // Call factory to create XPS package root, FDS, FD, FPR, and FP
    IFC( pXpsObjectFactory->CreatePackage(&pXpsPackage) );
    IFC( pXpsObjectFactory->CreateDocumentSequence(docSeqUri, &pFixedDocSeq) );
    IFC( pXpsObjectFactory->CreateDocument(docUri, &pFixedDoc) );
    IFC( pXpsObjectFactory->CreatePageReference(&pageSize, &pFixedPageRef) );
	IFC( pXpsObjectFactory->CreatePage(&pageSize, L"en-US", page1Uri, &pFixedPage1) );


    // Now connect trunk objects - SetParent happens internally !
	IFC( pXpsPackage->SetDocumentSequence(pFixedDocSeq));

    IFC( pFixedDocSeq->GetDocuments(&pFixedDocColl) );
    IFC( pFixedDocColl->Append(pFixedDoc) );

    IFC( pFixedDoc->GetPageReferences(&pFixedPageRefColl) );
    IFC( pFixedPageRefColl->Append(pFixedPageRef) );

    IFC( pFixedPageRef->SetPage(pFixedPage1) );

    // Now we need to start building our page.
	IFC( BuildXpsPageGraphicsContent(pXpsObjectFactory, pFixedPage1) );
	IFC( BuildXpsPageTextContent(pOpcFactory, pXpsObjectFactory, pFixedPage1) );
	IFC( BuildXpsPageImageContent(pOpcFactory, pXpsObjectFactory, pFixedPage1) );

	// Now we can save our work to a file    
	IFC(pXpsPackage->WriteToFile(
		L"SampleDocument.xps",
        NULL, // LPSECURITY_ATTRIBUTES
        FILE_ATTRIBUTE_NORMAL,
        FALSE // optimizeMarkupSize
        ));

    // Clean up our interfaces.
    pFixedDocSeq->Release();
    pFixedDocColl->Release();
    pFixedPageRefColl->Release();
    pFixedDoc->Release();
    pFixedPageRef->Release();
    pFixedPage1->Release();
    pXpsObjectFactory->Release();
    pOpcFactory->Release();
    pXpsPackage->Release();
    page1Uri->Release();
    docUri->Release();
    docSeqUri->Release();


	return SUCCEEDED(hr);

Cleanup:
	// Error was encountered, so systematically clean up working objects.
    if(pXpsObjectFactory)    pXpsObjectFactory->Release();
    if(pOpcFactory)          pOpcFactory->Release();  
    if(pXpsPackage)          pXpsPackage->Release();
    if(pFixedDocSeq)         pFixedDocSeq->Release();
    if(pFixedDoc)            pFixedDoc->Release();
    if(pFixedDocColl)        pFixedDocColl->Release();
    if(pFixedPageRef)        pFixedPageRef->Release();
    if(pFixedPageRefColl)    pFixedPageRefColl->Release();
    if(pFixedPage1)          pFixedPage1->Release();
    if(page1Uri)             page1Uri->Release();
    if(docUri)               docUri->Release();
    if(docSeqUri)            docSeqUri->Release(); 

	return hr;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HRESULT hr = S_OK;

	IFC(BuildXpsDocument());

	return SUCCEEDED(hr);

Cleanup:
	// Error was encountered, but nothing to clean up.
	return hr;
}

