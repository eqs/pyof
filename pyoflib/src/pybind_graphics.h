#pragma once
#include "ofMain.h"
#include "ofImage.h"
#include "ofPixels.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

template<typename PixelType>
void declare_ofImage(py::module &m, std::string &pyclass_name) {
	typedef ofImage_<PixelType> ImageClass;
	// typedef ofPixels<PixelType> PixelClass;
	py::class_<ImageClass>(m, pyclass_name.c_str())
		.def(py::init<>())
		.def(py::init<ImageClass>())
		// .def(py::init<PixelClass>())
		.def("allocate", (void (ImageClass::*)(int, int, ofImageType)) &ImageClass::allocate)
		.def("bind", (void (ImageClass::*)(int)) &ImageClass::bind, py::arg("textureLocation") = 0)
		.def("clear", &ImageClass::clear)
		.def("crop", (void (ImageClass::*)(int, int, int, int)) &ImageClass::crop)
		.def("cropFrom", (void (ImageClass::*)(const ofImage_<PixelType> &, int, int, int, int)) &ImageClass::cropFrom)
		.def("draw", py::overload_cast<float, float>(&ImageClass::draw, py::const_))
		.def("draw", py::overload_cast<float, float, float>(&ImageClass::draw, py::const_))
		.def("draw", py::overload_cast<const glm::vec3 &>(&ImageClass::draw, py::const_))
		.def("draw", py::overload_cast<float, float, float, float>(&ImageClass::draw, py::const_))
		.def("draw", py::overload_cast<float, float, float, float, float>(&ImageClass::draw, py::const_))
		.def("draw", py::overload_cast<const glm::vec3 &, float, float>(&ImageClass::draw, py::const_))
		.def("drawSubsection", py::overload_cast<float, float, float, float, float, float>(&ImageClass::drawSubsection, py::const_))
		.def("drawSubsection", py::overload_cast<float, float, float, float, float, float, float>(&ImageClass::drawSubsection, py::const_))
		.def("drawSubsection", py::overload_cast<float, float, float, float, float, float, float, float>(&ImageClass::drawSubsection, py::const_))
		.def("getColor", py::overload_cast<int, int>(&ImageClass::getColor, py::const_))
		.def("getColor", py::overload_cast<int>(&ImageClass::getColor, py::const_))
		.def("getHeight", (float (ImageClass::*)()) &ImageClass::getHeight)
		.def("getImageType", (ofImageType (ImageClass::*)()) &ImageClass::getImageType)
		.def("getPixels", py::overload_cast<>(&ImageClass::getPixels))
		.def("getPixels", py::overload_cast<>(&ImageClass::getPixels, py::const_))
		.def("getTexture", py::overload_cast<>(&ImageClass::getTexture))
		.def("getTexture", py::overload_cast<>(&ImageClass::getTexture, py::const_))
		.def("getWidth", (float (ImageClass::*)()) &ImageClass::getWidth)
		.def("grabScreen", (void (ImageClass::*)(int, int, int, int)) &ImageClass::grabScreen)
		.def("isAllocated", &ImageClass::isAllocated)
		.def("isUsingTexture", (bool (ImageClass::*)()) &ImageClass::isUsingTexture)
		.def(
			"load",
			(bool (ImageClass::*)(const std::filesystem::path &, const ofImageLoadSettings &)) &ImageClass::load,
			py::arg("path"), py::arg("settings") = ofImageLoadSettings()
		)
		.def(
			"load",
			(bool (ImageClass::*)(const ofBuffer &, const ofImageLoadSettings &)) &ImageClass::load,
			py::arg("buffer"), py::arg("settings") = ofImageLoadSettings()
		)
		.def("mirror", (void (ImageClass::*)(bool, bool)) &ImageClass::mirror)
		.def("resetAnchor", &ImageClass::resetAnchor)
		.def("resize", (void (ImageClass::*)(int, int)) &ImageClass::resize)
		.def("rotate90", (void (ImageClass::*)(int)) &ImageClass::rotate90)
		.def(
			"save",
			py::overload_cast<const std::filesystem::path &, ofImageQualityType>(&ImageClass::save, py::const_),
			py::arg("fileName"), py::arg("compressionLevel") = OF_IMAGE_QUALITY_BEST
		)
		.def(
			"save",
			py::overload_cast<ofBuffer &, ofImageFormat, ofImageQualityType>(&ImageClass::save, py::const_),
			py::arg("buffer"), py::arg("imageFormat") = OF_IMAGE_FORMAT_PNG, py::arg("compressionLevel") = OF_IMAGE_QUALITY_BEST
		)
		.def("setAnchorPercent", (void (ImageClass::*)(float, float)) &ImageClass::setAnchorPercent)
		.def("setAnchorPoint", (void (ImageClass::*)(float, float)) &ImageClass::setAnchorPoint)
		.def("setColor", py::overload_cast<int, int, const ofColor_<PixelType> &>(&ImageClass::setColor))
		.def("setColor", py::overload_cast<int, const ofColor_<PixelType> &>(&ImageClass::setColor))
		.def("setColor", py::overload_cast<const ofColor_<PixelType> &>(&ImageClass::setColor))
		.def("setCompression", (void (ImageClass::*)(ofTexCompression)) &ImageClass::setCompression)
		.def(
			"setFromPixels",
			py::overload_cast<const PixelType *, int, int, ofImageType, bool>(&ImageClass::setFromPixels),
			py::arg("pixels"), py::arg("w"), py::arg("h"), py::arg("type"), py::arg("bOderIsRGB") = true)
		.def("setFromPixels", py::overload_cast<const ofPixels_<PixelType> &>(&ImageClass::setFromPixels))
		.def("setImageType", (void (ImageClass::*)(ofImageType)) &ImageClass::setImageType)
		.def("setUseTexture", (void (ImageClass::*)(bool)) &ImageClass::setUseTexture)
		.def("unbind", (void (ImageClass::*)(int)) &ImageClass::unbind, py::arg("textureLocation") = 0)
		.def("update", &ImageClass::update);
}

void pybind_graphics(py::module m) {
	m.def("ofBackground", py::overload_cast<const ofColor &>(&ofBackground));
	m.def("ofBackground", py::overload_cast<int, int>(&ofBackground));
	m.def("ofBackground", py::overload_cast<int, int, int, int>(&ofBackground));
	m.def("ofBackgroundGradient", (void(*) (const ofColor &, const ofColor &, ofGradientMode)) &ofBackgroundGradient);
	m.def("ofBackgroundHex", (void(*) (int, int)) &ofBackgroundHex);
	m.def("ofBeginSaveScreenAsPDF", (void(*) (std::string, bool, bool, ofRectangle)) &ofBeginSaveScreenAsPDF);
	m.def("ofBeginSaveScreenAsSVG", (void(*) (std::string, bool, bool, ofRectangle)) &ofBeginSaveScreenAsSVG);
	m.def("ofBeginShape", (void(*) ()) &ofBeginShape);
	m.def("ofBezierVertex", py::overload_cast<const glm::vec3 &, const glm::vec3 &, const glm::vec3 &>(&ofBezierVertex));
	m.def("ofBezierVertex", py::overload_cast<const glm::vec2 &, const glm::vec2 &, const glm::vec2 &>(&ofBezierVertex));
	m.def("ofBezierVertex", py::overload_cast<float, float, float, float, float, float, float, float, float>(&ofBezierVertex));
	m.def("ofBezierVertex", py::overload_cast<float, float, float, float, float, float>(&ofBezierVertex));
	m.def("ofClear", py::overload_cast<const ofColor &>(&ofClear));
	m.def("ofClear", py::overload_cast<float, float>(&ofClear));
	m.def("ofClear", py::overload_cast<float, float, float, float>(&ofClear));
	m.def("ofClearAlpha", (void(*) ()) &ofClearAlpha);
	m.def("ofCurveVertex", py::overload_cast<const glm::vec3 &>(&ofCurveVertex));
	m.def("ofCurveVertex", py::overload_cast<const glm::vec2 &>(&ofCurveVertex));
	m.def("ofCurveVertex", py::overload_cast<float, float, float>(&ofCurveVertex));
	m.def("ofCurveVertex", py::overload_cast<float, float>(&ofCurveVertex));
	//m.def("ofCurveVertices", (void(*) (const vector &)) &ofCurveVertices);
	//m.def("ofCurveVertices", (void(*) (const vector &)) &ofCurveVertices);
	//m.def("ofCurveVertices", (void(*) (const vector &)) &ofCurveVertices);
	//m.def("ofCurveVertices", (void(*) (const vector &)) &ofCurveVertices);
	m.def("ofDisableAlphaBlending", (void(*) ()) &ofDisableAlphaBlending);
	m.def("ofDisableAntiAliasing", (void(*) ()) &ofDisableAntiAliasing);
	m.def("ofDisableBlendMode", (void(*) ()) &ofDisableBlendMode);
	m.def("ofDisableDepthTest", (void(*) ()) &ofDisableDepthTest);
	m.def("ofDisablePointSprites", (void(*) ()) &ofDisablePointSprites);
	m.def("ofDisableSmoothing", (void(*) ()) &ofDisableSmoothing);
	m.def("ofDrawBezier", py::overload_cast<float, float, float, float, float, float, float, float>(&ofDrawBezier));
	m.def("ofDrawBezier", py::overload_cast<float, float, float, float, float, float, float, float, float, float, float, float>(&ofDrawBezier));
	// m.def("ofDrawBitmapString", (void(*) (const T &, const glm::vec2 &)) &ofDrawBitmapString);
	// m.def("ofDrawBitmapString", (void(*) (const T &, const glm::vec3 &)) &ofDrawBitmapString);
	// m.def("ofDrawBitmapString", py::overload_cast<const string &, const glm::vec3 &>(&ofDrawBitmapString));
	// m.def("ofDrawBitmapString", py::overload_cast<const string &, const glm::vec2 &>(&ofDrawBitmapString));
	// m.def("ofDrawBitmapString", (void(*) (const T &, float, float)) &ofDrawBitmapString);
	// m.def("ofDrawBitmapString", (void(*) (const T &, float, float, float)) &ofDrawBitmapString);
	m.def("ofDrawBitmapString", (void(*) (const string &, float, float, float)) &ofDrawBitmapString);
	m.def("ofDrawBitmapStringHighlight", py::overload_cast<std::string, const glm::vec3 &, const ofColor &, const ofColor &>(&ofDrawBitmapStringHighlight));
	m.def("ofDrawBitmapStringHighlight", py::overload_cast<std::string, const glm::vec2 &, const ofColor &, const ofColor &>(&ofDrawBitmapStringHighlight));
	m.def("ofDrawBitmapStringHighlight", py::overload_cast<std::string, int, int, const ofColor &, const ofColor &>(&ofDrawBitmapStringHighlight));
	m.def("ofDrawCircle", py::overload_cast<const glm::vec3 &, float>(&ofDrawCircle));
	m.def("ofDrawCircle", py::overload_cast<const glm::vec2 &, float>(&ofDrawCircle));
	m.def("ofDrawCircle", py::overload_cast<float, float, float>(&ofDrawCircle));
	m.def("ofDrawCircle", py::overload_cast<float, float, float, float>(&ofDrawCircle));
	m.def("ofDrawCurve", py::overload_cast<float, float, float, float, float, float, float, float>(&ofDrawCurve));
	m.def("ofDrawCurve", py::overload_cast<float, float, float, float, float, float, float, float, float, float, float, float>(&ofDrawCurve));
	m.def("ofDrawEllipse", py::overload_cast<const glm::vec3 &, float, float>(&ofDrawEllipse));
	m.def("ofDrawEllipse", py::overload_cast<const glm::vec2 &, float, float>(&ofDrawEllipse));
	m.def("ofDrawEllipse", py::overload_cast<float, float, float, float>(&ofDrawEllipse));
	m.def("ofDrawEllipse", py::overload_cast<float, float, float, float, float>(&ofDrawEllipse));
	m.def("ofDrawLine", py::overload_cast<const glm::vec3 &, const glm::vec3 &>(&ofDrawLine));
	m.def("ofDrawLine", py::overload_cast<const glm::vec2 &, const glm::vec2 &>(&ofDrawLine));
	m.def("ofDrawLine", py::overload_cast<float, float, float, float>(&ofDrawLine));
	m.def("ofDrawLine", py::overload_cast<float, float, float, float, float, float>(&ofDrawLine));
	m.def("ofDrawRectRounded", py::overload_cast<const ofRectangle &, float>(&ofDrawRectRounded));
	m.def("ofDrawRectRounded", py::overload_cast<const ofRectangle &, float, float, float, float>(&ofDrawRectRounded));
	m.def("ofDrawRectRounded", py::overload_cast<const glm::vec2 &, float, float, float>(&ofDrawRectRounded));
	m.def("ofDrawRectRounded", py::overload_cast<const glm::vec3 &, float, float, float>(&ofDrawRectRounded));
	m.def("ofDrawRectRounded", py::overload_cast<const glm::vec3 &, float, float, float, float, float, float>(&ofDrawRectRounded));
	m.def("ofDrawRectRounded", py::overload_cast<const glm::vec2 &, float, float, float, float, float, float>(&ofDrawRectRounded));
	m.def("ofDrawRectRounded", py::overload_cast<float, float, float, float, float>(&ofDrawRectRounded));
	m.def("ofDrawRectRounded", py::overload_cast<float, float, float, float, float, float>(&ofDrawRectRounded));
	m.def("ofDrawRectRounded", py::overload_cast<float, float, float, float, float, float, float, float, float>(&ofDrawRectRounded));
	m.def("ofDrawRectangle", py::overload_cast<const glm::vec3 &, float, float>(&ofDrawRectangle));
	m.def("ofDrawRectangle", py::overload_cast<const glm::vec2 &, float, float>(&ofDrawRectangle));
	m.def("ofDrawRectangle", py::overload_cast<const ofRectangle &>(&ofDrawRectangle));
	m.def("ofDrawRectangle", py::overload_cast<float, float, float, float, float>(&ofDrawRectangle));
	m.def("ofDrawRectangle", py::overload_cast<float, float, float, float>(&ofDrawRectangle));
	m.def("ofDrawTriangle", py::overload_cast<const glm::vec3 &, const glm::vec3 &, const glm::vec3 &>(&ofDrawTriangle));
	m.def("ofDrawTriangle", py::overload_cast<const glm::vec2 &, const glm::vec2 &, const glm::vec2 &>(&ofDrawTriangle));
	m.def("ofDrawTriangle", py::overload_cast<float, float, float, float, float, float>(&ofDrawTriangle));
	m.def("ofDrawTriangle", py::overload_cast<float, float, float, float, float, float, float, float, float>(&ofDrawTriangle));
	m.def("ofEnableAlphaBlending", (void(*) ()) &ofEnableAlphaBlending);
	m.def("ofEnableAntiAliasing", (void(*) ()) &ofEnableAntiAliasing);
	m.def("ofEnableBlendMode", (void(*) (ofBlendMode)) &ofEnableBlendMode);
	m.def("ofEnableDepthTest", (void(*) ()) &ofEnableDepthTest);
	m.def("ofEnablePointSprites", (void(*) ()) &ofEnablePointSprites);
	m.def("ofEnableSmoothing", (void(*) ()) &ofEnableSmoothing);
	m.def("ofEndSaveScreenAsPDF", (void(*) ()) &ofEndSaveScreenAsPDF);
	m.def("ofEndSaveScreenAsSVG", (void(*) ()) &ofEndSaveScreenAsSVG);
	m.def("ofEndShape", (void(*) (bool)) &ofEndShape);
	m.def("ofFill", (void(*) ()) &ofFill);
	m.def("ofGetBackgroundAuto", (bool(*) ()) &ofGetBackgroundAuto);
	m.def("ofGetBackgroundColor", (ofColor(*) ()) &ofGetBackgroundColor);
	m.def("ofGetCoordHandedness", (ofHandednessType(*) ()) &ofGetCoordHandedness);
	m.def("ofGetCurrentMatrix", (glm::mat4(*) (ofMatrixMode)) &ofGetCurrentMatrix);
	m.def("ofGetCurrentNormalMatrix", (glm::mat4(*) ()) &ofGetCurrentNormalMatrix);
	m.def("ofGetCurrentOrientationMatrix", (glm::mat4(*) ()) &ofGetCurrentOrientationMatrix);
	m.def("ofGetCurrentViewMatrix", (glm::mat4(*) ()) &ofGetCurrentViewMatrix);
	m.def("ofGetCurrentViewport", (ofRectangle(*) ()) &ofGetCurrentViewport);
	m.def("ofGetFill", (ofFillFlag(*) ()) &ofGetFill);
	m.def("ofGetNativeViewport", (ofRectangle(*) ()) &ofGetNativeViewport);
	m.def("ofGetRectMode", (ofRectMode(*) ()) &ofGetRectMode);
	m.def("ofGetStyle", (ofStyle(*) ()) &ofGetStyle);
	m.def("ofGetViewportHeight", (int(*) ()) &ofGetViewportHeight);
	m.def("ofGetViewportWidth", (int(*) ()) &ofGetViewportWidth);
	m.def("ofIsVFlipped", (bool(*) ()) &ofIsVFlipped);
	m.def("ofLoadIdentityMatrix", (void(*) ()) &ofLoadIdentityMatrix);
	m.def("ofLoadMatrix", py::overload_cast<const glm::mat4 &>(&ofLoadMatrix));
	m.def("ofLoadMatrix", py::overload_cast<const float *>(&ofLoadMatrix));
	m.def("ofLoadViewMatrix", (void(*) (const glm::mat4 &)) &ofLoadViewMatrix);
	m.def("ofMultMatrix", py::overload_cast<const glm::mat4 &>(&ofMultMatrix));
	m.def("ofMultMatrix", py::overload_cast<const float *>(&ofMultMatrix));
	m.def("ofMultViewMatrix", (void(*) (const glm::mat4 &)) &ofMultViewMatrix);
	m.def("ofNextContour", (void(*) (bool)) &ofNextContour);
	m.def("ofNoFill", (void(*) ()) &ofNoFill);
	m.def("ofOrientationToDegrees", (int(*) (ofOrientation)) &ofOrientationToDegrees);
	m.def("ofPopMatrix", (void(*) ()) &ofPopMatrix);
	m.def("ofPopStyle", (void(*) ()) &ofPopStyle);
	m.def("ofPopView", (void(*) ()) &ofPopView);
	m.def("ofPushMatrix", (void(*) ()) &ofPushMatrix);
	m.def("ofPushStyle", (void(*) ()) &ofPushStyle);
	m.def("ofPushView", (void(*) ()) &ofPushView);
	m.def("ofRotateDeg", py::overload_cast<float>(&ofRotateDeg));
	m.def("ofRotateDeg", py::overload_cast<float, float, float, float>(&ofRotateDeg));
	m.def("ofRotateRad", py::overload_cast<float>(&ofRotateRad));
	m.def("ofRotateRad", py::overload_cast<float, float, float, float>(&ofRotateRad));
	m.def("ofRotateXDeg", (void(*) (float)) &ofRotateXDeg);
	m.def("ofRotateXRad", (void(*) (float)) &ofRotateXRad);
	m.def("ofRotateYDeg", (void(*) (float)) &ofRotateYDeg);
	m.def("ofRotateYRad", (void(*) (float)) &ofRotateYRad);
	m.def("ofRotateZDeg", (void(*) (float)) &ofRotateZDeg);
	m.def("ofRotateZRad", (void(*) (float)) &ofRotateZRad);
	m.def("ofScale", py::overload_cast<const glm::vec3 &>(&ofScale));
	m.def("ofScale", py::overload_cast<float>(&ofScale));
	m.def("ofScale", py::overload_cast<float, float, float>(&ofScale));
	m.def("ofSetBackgroundAuto", (void(*) (bool)) &ofSetBackgroundAuto);
	m.def("ofSetBackgroundColor", py::overload_cast<const ofColor &>(&ofSetBackgroundColor));
	m.def("ofSetBackgroundColor", py::overload_cast<int, int>(&ofSetBackgroundColor));
	m.def("ofSetBackgroundColor", py::overload_cast<int, int, int, int>(&ofSetBackgroundColor));
	m.def("ofSetBackgroundColorHex", (void(*) (int, int)) &ofSetBackgroundColorHex);
	m.def("ofSetCircleResolution", (void(*) (int)) &ofSetCircleResolution);
	m.def("ofSetColor", py::overload_cast<const ofColor &>(&ofSetColor));
	m.def("ofSetColor", py::overload_cast<const ofColor &, int>(&ofSetColor));
	m.def("ofSetColor", py::overload_cast<int>(&ofSetColor));
	m.def("ofSetColor", py::overload_cast<int, int, int>(&ofSetColor));
	m.def("ofSetColor", py::overload_cast<int, int, int, int>(&ofSetColor));
	m.def("ofSetCoordHandedness", (void(*) (ofHandednessType)) &ofSetCoordHandedness);
	m.def("ofSetCurveResolution", (void(*) (int)) &ofSetCurveResolution);
	m.def("ofSetDepthTest", (void(*) (bool)) &ofSetDepthTest);
	m.def("ofSetDrawBitmapMode", (void(*) (ofDrawBitmapMode)) &ofSetDrawBitmapMode);
	m.def("ofSetHexColor", (void(*) (int)) &ofSetHexColor);
	m.def("ofSetLineWidth", (void(*) (float)) &ofSetLineWidth);
	m.def("ofSetMatrixMode", (void(*) (ofMatrixMode)) &ofSetMatrixMode);
	m.def("ofSetPolyMode", (void(*) (ofPolyWindingMode)) &ofSetPolyMode);
	m.def("ofSetRectMode", (void(*) (ofRectMode)) &ofSetRectMode);
	m.def("ofSetStyle", (void(*) (ofStyle)) &ofSetStyle);
	m.def("ofSetupScreen", (void(*) ()) &ofSetupScreen);
	m.def("ofSetupScreenOrtho", (void(*) (float, float, float, float)) &ofSetupScreenOrtho);
	m.def("ofSetupScreenPerspective", (void(*) (float, float, float, float, float)) &ofSetupScreenPerspective);
	// string ofToString(const T &)
	m.def("ofTranslate", py::overload_cast<const glm::vec3 &>(&ofTranslate));
	m.def("ofTranslate", py::overload_cast<const glm::vec2 &>(&ofTranslate));
	m.def("ofTranslate", py::overload_cast<float, float, float>(&ofTranslate));
	m.def("ofVertex", py::overload_cast<const glm::vec3 &>(&ofVertex));
	m.def("ofVertex", py::overload_cast<const glm::vec2 &>(&ofVertex));
	m.def("ofVertex", py::overload_cast<float, float, float>(&ofVertex));
	m.def("ofVertex", py::overload_cast<float, float>(&ofVertex));
	//m.def("ofVertices", (void(*) (const vector &)) &ofVertices);
	//m.def("ofVertices", (void(*) (const vector &)) &ofVertices);
	//m.def("ofVertices", (void(*) (const vector &)) &ofVertices);
	//m.def("ofVertices", (void(*) (const vector &)) &ofVertices);
	m.def("ofViewport", py::overload_cast<ofRectangle>(&ofViewport));
	m.def("ofViewport", py::overload_cast<float, float, float, float, bool>(&ofViewport));

	// ofPixels.h ------------------------------------------------------------

	py::enum_<ofPixelFormat>(m, "ofPixelFormat")
		.value("OF_PIXELS_GRAY", ofPixelFormat::OF_PIXELS_GRAY)
		.value("OF_PIXELS_GRAY_ALPHA", ofPixelFormat::OF_PIXELS_GRAY_ALPHA)
		.value("OF_PIXELS_RGB", ofPixelFormat::OF_PIXELS_RGB)
		.value("OF_PIXELS_BGR", ofPixelFormat::OF_PIXELS_BGR)
		.value("OF_PIXELS_RGBA", ofPixelFormat::OF_PIXELS_RGBA)
		.value("OF_PIXELS_BGRA", ofPixelFormat::OF_PIXELS_BGRA)
		.value("OF_PIXELS_RGB565", ofPixelFormat::OF_PIXELS_RGB565)
		.value("OF_PIXELS_NV12", ofPixelFormat::OF_PIXELS_NV12)
		.value("OF_PIXELS_NV21", ofPixelFormat::OF_PIXELS_NV21)
		.value("OF_PIXELS_YV12", ofPixelFormat::OF_PIXELS_YV12)
		.value("OF_PIXELS_I420", ofPixelFormat::OF_PIXELS_I420)
		.value("OF_PIXELS_YUY2", ofPixelFormat::OF_PIXELS_YUY2)
		.value("OF_PIXELS_UYVY", ofPixelFormat::OF_PIXELS_UYVY)
		.value("OF_PIXELS_Y", ofPixelFormat::OF_PIXELS_Y)
		.value("OF_PIXELS_U", ofPixelFormat::OF_PIXELS_U)
		.value("OF_PIXELS_V", ofPixelFormat::OF_PIXELS_V)
		.value("OF_PIXELS_UV", ofPixelFormat::OF_PIXELS_UV)
		.value("OF_PIXELS_VU", ofPixelFormat::OF_PIXELS_VU)
		.value("OF_PIXELS_NUM_FORMATS", ofPixelFormat::OF_PIXELS_NUM_FORMATS)
		.value("OF_PIXELS_UNKNOWN", ofPixelFormat::OF_PIXELS_UNKNOWN)
		.value("OF_PIXELS_NATIVE", ofPixelFormat::OF_PIXELS_NATIVE)
		.export_values();

	// ofImage.h -------------------------------------------------------------
	py::enum_<ofImageQualityType>(m, "ofImageQualityType")
		/// \brief Equivalent to FreeImage's JPEG_QUALITYSUPERB (100:1 ratio)
		.value("OF_IMAGE_QUALITY_BEST", ofImageQualityType::OF_IMAGE_QUALITY_BEST)
		/// \brief Equivalent to FreeImage's JPEG_QUALITYGOOD (75:1 ratio)
		.value("OF_IMAGE_QUALITY_HIGH", ofImageQualityType::OF_IMAGE_QUALITY_HIGH)
		/// \brief Equivalent to FreeImage's JPEG_QUALITYNORMAL (50:1 ratio)
		.value("OF_IMAGE_QUALITY_MEDIUM", ofImageQualityType::OF_IMAGE_QUALITY_MEDIUM)
		/// \brief Equivalent to FreeImage's JPEG_QUALITYAVERAGE (25:1 ratio)
		.value("OF_IMAGE_QUALITY_LOW", ofImageQualityType::OF_IMAGE_QUALITY_LOW)
		/// \brief Equivalent to FreeImage's JPEG_QUALITYBAD (10:1 ratio)
		.value("OF_IMAGE_QUALITY_WORST", ofImageQualityType::OF_IMAGE_QUALITY_WORST)
		.export_values();

	py::enum_<ofImageFormat>(m, "ofImageFormat")
		.value("OF_IMAGE_FORMAT_BMP", ofImageFormat::OF_IMAGE_FORMAT_BMP)
		.value("OF_IMAGE_FORMAT_ICO", ofImageFormat::OF_IMAGE_FORMAT_ICO)
		.value("OF_IMAGE_FORMAT_JPEG", ofImageFormat::OF_IMAGE_FORMAT_JPEG)
		.value("OF_IMAGE_FORMAT_JNG", ofImageFormat::OF_IMAGE_FORMAT_JNG)
		.value("OF_IMAGE_FORMAT_KOALA", ofImageFormat::OF_IMAGE_FORMAT_KOALA)
		.value("OF_IMAGE_FORMAT_LBM", ofImageFormat::OF_IMAGE_FORMAT_LBM)
		.value("OF_IMAGE_FORMAT_IFF", ofImageFormat::OF_IMAGE_FORMAT_IFF)
		.value("OF_IMAGE_FORMAT_MNG", ofImageFormat::OF_IMAGE_FORMAT_MNG)
		.value("OF_IMAGE_FORMAT_PBM", ofImageFormat::OF_IMAGE_FORMAT_PBM)
		.value("OF_IMAGE_FORMAT_PBMRAW", ofImageFormat::OF_IMAGE_FORMAT_PBMRAW)
		.value("OF_IMAGE_FORMAT_PCD", ofImageFormat::OF_IMAGE_FORMAT_PCD)
		.value("OF_IMAGE_FORMAT_PCX", ofImageFormat::OF_IMAGE_FORMAT_PCX)
		.value("OF_IMAGE_FORMAT_PGM", ofImageFormat::OF_IMAGE_FORMAT_PGM)
		.value("OF_IMAGE_FORMAT_PGMRAW", ofImageFormat::OF_IMAGE_FORMAT_PGMRAW)
		.value("OF_IMAGE_FORMAT_PNG", ofImageFormat::OF_IMAGE_FORMAT_PNG)
		.value("OF_IMAGE_FORMAT_PPM", ofImageFormat::OF_IMAGE_FORMAT_PPM)
		.value("OF_IMAGE_FORMAT_PPMRAW", ofImageFormat::OF_IMAGE_FORMAT_PPMRAW)
		.value("OF_IMAGE_FORMAT_RAS", ofImageFormat::OF_IMAGE_FORMAT_RAS)
		.value("OF_IMAGE_FORMAT_TARGA", ofImageFormat::OF_IMAGE_FORMAT_TARGA)
		.value("OF_IMAGE_FORMAT_TIFF", ofImageFormat::OF_IMAGE_FORMAT_TIFF)
		.value("OF_IMAGE_FORMAT_WBMP", ofImageFormat::OF_IMAGE_FORMAT_WBMP)
		.value("OF_IMAGE_FORMAT_PSD", ofImageFormat::OF_IMAGE_FORMAT_PSD)
		.value("OF_IMAGE_FORMAT_CUT", ofImageFormat::OF_IMAGE_FORMAT_CUT)
		.value("OF_IMAGE_FORMAT_XBM", ofImageFormat::OF_IMAGE_FORMAT_XBM)
		.value("OF_IMAGE_FORMAT_XPM", ofImageFormat::OF_IMAGE_FORMAT_XPM)
		.value("OF_IMAGE_FORMAT_DDS", ofImageFormat::OF_IMAGE_FORMAT_DDS)
		.value("OF_IMAGE_FORMAT_GIF", ofImageFormat::OF_IMAGE_FORMAT_GIF)
		.value("OF_IMAGE_FORMAT_HDR", ofImageFormat::OF_IMAGE_FORMAT_HDR)
		.value("OF_IMAGE_FORMAT_FAXG3", ofImageFormat::OF_IMAGE_FORMAT_FAXG3)
		.value("OF_IMAGE_FORMAT_SGI", ofImageFormat::OF_IMAGE_FORMAT_SGI)
		.value("OF_IMAGE_FORMAT_EXR", ofImageFormat::OF_IMAGE_FORMAT_EXR)
		.value("OF_IMAGE_FORMAT_J2K", ofImageFormat::OF_IMAGE_FORMAT_J2K)
		.value("OF_IMAGE_FORMAT_JP2", ofImageFormat::OF_IMAGE_FORMAT_JP2)
		.value("OF_IMAGE_FORMAT_PFM", ofImageFormat::OF_IMAGE_FORMAT_PFM)
		.value("OF_IMAGE_FORMAT_PICT", ofImageFormat::OF_IMAGE_FORMAT_PICT)
		.value("OF_IMAGE_FORMAT_RAW", ofImageFormat::OF_IMAGE_FORMAT_RAW)
		.export_values();

	py::class_<ofImageLoadSettings>(m, "ofImageLoadSettings")
		.def(py::init<>())
		.def_readwrite("accurate", &ofImageLoadSettings::accurate)
		.def_readwrite("exifRotate", &ofImageLoadSettings::exifRotate)
		.def_readwrite("grayscale", &ofImageLoadSettings::grayscale)
		.def_readwrite("separateCMYK", &ofImageLoadSettings::separateCMYK);

	declare_ofImage<unsigned char>(m, std::string("ofImage"));
	declare_ofImage<float>(m, std::string("ofFloatImage"));
	declare_ofImage<unsigned short>(m, std::string("ofShortImage"));
}
