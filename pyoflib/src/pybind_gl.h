#pragma once
#include "ofMain.h"
#include "ofFbo.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void pybind_utils(py::module m) {
	m.def(
		"ofToDataPath", (std::string(*)(const std::filesystem::path &, bool)) &ofToDataPath,
		py::arg("path"), py::arg("absolute") = false
	);
	m.def("ofSetDataPathRoot", (void(*)(const std::filesystem::path &)) &ofSetDataPathRoot);

	// ofFbo.h
	py::enum_<ofFboMode>(m, "ofFboMode")
		.value("OF_FBOMODE_NODEFAULTS", ofFboMode::OF_FBOMODE_NODEFAULTS) ///< base GL fbo, no OF defaults
		.value("OF_FBOMODE_PERSPECTIVE", ofFboMode::OF_FBOMODE_PERSPECTIVE) ///< set OF perspective and viewport
		.value("OF_FBOMODE_MATRIXFLIP", ofFboMode::OF_FBOMODE_MATRIXFLIP) ///< flip vertically
		.export_values();

	py::class_<ofFboSettings>(m, "ofFboSettings")
		.def(py::init<>())
		.def_readwrite("width", &ofFboSettings::width)  ///< width of images attached to fbo
		.def_readwrite("height", &ofFboSettings::height)  ///< height of images attached to fbo
		.def_readwrite("numColorbuffers", &ofFboSettings::numColorbuffers)  ///< how many color buffers to create
		.def_readwrite("colorFormats", &ofFboSettings::colorFormats)  ///< format of the color attachments for MRT.
		.def_readwrite("useDepth", &ofFboSettings::useDepth)  ///< whether to use depth buffer or not
		.def_readwrite("useStencil", &ofFboSettings::useStencil)  ///< whether to use stencil buffer or not
		.def_readwrite("depthStencilAsTexture", &ofFboSettings::depthStencilAsTexture)  ///< use a texture instead of a renderbuffer for depth (useful to draw it or use it in a shader later)
		.def_readwrite("textureTarget", &ofFboSettings::textureTarget)  ///< GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE_ARB
		.def_readwrite("internalformat", &ofFboSettings::internalformat)  ///< GL_RGBA, GL_RGBA16F_ARB, GL_RGBA32F_ARB, GL_LUMINANCE32F_ARB etc.
		.def_readwrite("depthStencilInternalFormat", &ofFboSettings::depthStencilInternalFormat)  ///< GL_DEPTH_COMPONENT(16/24/32)
		.def_readwrite("wrapModeHorizontal", &ofFboSettings::wrapModeHorizontal)  ///< GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER etc.
		.def_readwrite("wrapModeVertical", &ofFboSettings::wrapModeVertical)  ///< GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER etc.
		.def_readwrite("minFilter", &ofFboSettings::minFilter)  ///< GL_NEAREST, GL_LINEAR etc.
		.def_readwrite("maxFilter", &ofFboSettings::maxFilter)  ///< GL_NEAREST, GL_LINEAR etc.
		.def_readwrite("numSamples", &ofFboSettings::numSamples);  ///< number of samples for multisampling (set 0 to disable)
		// ofFboSettings(std::shared_ptr<ofBaseGLRenderer> renderer=nullptr);
		// bool operator!=(const ofFboSettings & other);

	py::class_<ofFbo>(m, "ofFbo")
		.def(py::init<>())
		.def(py::init<const ofFbo &>())
		.def("activateAllDrawBuffers", (void (ofFbo::*)()) &ofFbo::activateAllDrawBuffers)
		.def("allocate", py::overload_cast<int, int, int, int>(&ofFbo::allocate)
			py::arg("width"), py::arg("height"), py::arg("internalformat") = GL_RGBA, py::arg("numSamples") = 0)
		.def("allocate", py::overload_cast<ofFboSettings>(&ofFbo::allocate),
			py::arg("settings") = ofFboSettings(nullptr))
		.def("attachTexture", (void (ofFbo::*)(ofTexture &, GLenum, GLenum)) &ofFbo::attachTexture)
		.def("begin", (void (ofFbo::*)(ofFboMode)) &ofFbo::begin,
			py::arg("mode") = OF_FBOMODE_PERSPECTIVE | OF_FBOMODE_MATRIXFLIP)
		.def("bind", (void (ofFbo::*)()) &ofFbo::bind)
		.def_static("checkGLSupport", (bool (ofFbo::*)()) &ofFbo::checkGLSupport)
		.def("checkStatus", (bool (ofFbo::*)()) &ofFbo::checkStatus)
		.def("clear", (void (ofFbo::*)()) &ofFbo::clear)
		.def("clearColorBuffer", (void (ofFbo::*)(size_t, const ofFloatColor &)) &ofFbo::clearColorBuffer)
		.def("clearDepthBuffer", (void (ofFbo::*)(float)) &ofFbo::clearDepthBuffer)
		.def("clearDepthStencilBuffer", (void (ofFbo::*)(float, int)) &ofFbo::clearDepthStencilBuffer)
		.def("clearStencilBuffer", (void (ofFbo::*)(int)) &ofFbo::clearStencilBuffer)
		.def("copyTo", (void (ofFbo::*)(ofBufferObject &)) &ofFbo::copyTo)
		.def("createAndAttachDepthStencilTexture", py::overload_cast<GLenum, GLint, GLenum>(&ofFbo::createAndAttachDepthStencilTexture))
		.def("createAndAttachDepthStencilTexture", py::overload_cast<GLenum, GLint, GLenum, GLenum, GLenum>(&ofFbo::createAndAttachDepthStencilTexture))
		.def("createAndAttachRenderbuffer", (GLuint (ofFbo::*)(GLenum, GLenum)) &ofFbo::createAndAttachRenderbuffer)
		.def("createAndAttachTexture", (void (ofFbo::*)(GLenum, GLenum)) &ofFbo::createAndAttachTexture)
		.def("draw", py::overload_cast<float, float>(&ofFbo::draw, py::const_))
		.def("draw", py::overload_cast<float, float, float, float>(&ofFbo::draw, py::const_))
		.def("end", (void (ofFbo::*)()) &ofFbo::end)
		.def("flagDirty", (void (ofFbo::*)()) &ofFbo::flagDirty)
		.def("getDefaultTextureIndex", (int (ofFbo::*)()) &ofFbo::getDefaultTextureIndex)
		.def("getDepthBuffer", (GLuint (ofFbo::*)()) &ofFbo::getDepthBuffer)
		.def("getDepthTexture", (ofTexture (ofFbo::*)()) &ofFbo::getDepthTexture)
		.def("getHeight", (float (ofFbo::*)()) &ofFbo::getHeight)
		.def("getId", (GLuint (ofFbo::*)()) &ofFbo::getId)
		.def("getIdDrawBuffer", (GLuint (ofFbo::*)()) &ofFbo::getIdDrawBuffer)
		.def("getNumTextures", (int (ofFbo::*)()) &ofFbo::getNumTextures)
		.def("getStencilBuffer", (GLuint (ofFbo::*)()) &ofFbo::getStencilBuffer)
		.def("getTexture", py::overload_cast<>(&ofFbo::getTexture))
		.def("getTexture", py::overload_cast<>(&ofFbo::getTexture, py::const_))
		.def("getTexture", py::overload_cast<int>(&ofFbo::getTexture))
		.def("getTexture", py::overload_cast<int>(&ofFbo::getTexture, py::const_))
		.def("getWidth", (float (ofFbo::*)()) &ofFbo::getWidth)
		.def("isAllocated", (bool (ofFbo::*)()) &ofFbo::isAllocated)
		.def("isUsingTexture", (bool (ofFbo::*)()) &ofFbo::isUsingTexture)
		.def_static("maxColorAttachments", (int (ofFbo::*)()) &ofFbo::maxColorAttachments)
		.def_static("maxDrawBuffers", (int (ofFbo::*)()) &ofFbo::maxDrawBuffers)
		.def_static("maxSamples", (int (ofFbo::*)()) &ofFbo::maxSamples)
		.def("readToPixels", py::overload_cast<ofPixels, int>(&ofFbo::readToPixels, py::const_),
				py::arg("pixels"), py::("attachmentPoint") = 0)
		.def("readToPixels", py::overload_cast<ofShortPixels, int>(&ofFbo::readToPixels, py::const_),
				py::arg("pixels"), py::("attachmentPoint") = 0)
		.def("readToPixels", py::overload_cast<ofFloatPixels, int>(&ofFbo::readToPixels, py::const_),
				py::arg("pixels"), py::("attachmentPoint") = 0)
		.def("resetAnchor", (void (ofFbo::*)()) &ofFbo::resetAnchor)
		.def("setActiveDrawBuffer", (void (ofFbo::*)(int)) &ofFbo::setActiveDrawBuffer)
		.def("setActiveDrawBuffers", (void (ofFbo::*)(const std::vector<int> &)) &ofFbo::setActiveDrawBuffers)
		.def("setAnchorPercent", (void (ofFbo::*)(float, float)) &ofFbo::setAnchorPercent)
		.def("setAnchorPoint", (void (ofFbo::*)(float, float)) &ofFbo::setAnchorPoint)
		.def("setDefaultTextureIndex", (void (ofFbo::*)(int)) &ofFbo::setDefaultTextureIndex)
		.def("setUseTexture", (void (ofFbo::*)(bool)) &ofFbo::setUseTexture)
		.def("unbind", (void (ofFbo::*)()) &ofFbo::unbind)
		.def("updateTexture"), (void (ofFbo::*)(int)) &ofFbo::updateTexture;
}
