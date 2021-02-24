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
		.def("activateAllDrawBuffers")
		.def("allocate")
		.def("attachTexture")
		.def("begin")
		.def("bind")
		.def("checkGLSupport")
		.def("checkStatus")
		.def("clear")
		.def("clearColorBuffer")
		.def("clearDepthBuffer")
		.def("clearDepthStencilBuffer")
		.def("clearStencilBuffer")
		.def("copyTo")
		.def("createAndAttachDepthStencilTexture")
		.def("createAndAttachRenderbuffer")
		.def("createAndAttachTexture")
		.def("draw")
		.def("end")
		.def("flagDirty")
		.def("getDefaultTextureIndex")
		.def("getDepthBuffer")
		.def("getDepthTexture")
		.def("getHeight")
		.def("getId")
		.def("getIdDrawBuffer")
		.def("getNumTextures")
		.def("getStencilBuffer")
		.def("getTexture")
		.def("getWidth")
		.def("isAllocated")
		.def("isUsingTexture")
		.def("maxColorAttachments")
		.def("maxDrawBuffers")
		.def("maxSamples")
		.def("readToPixels")
		.def("resetAnchor")
		.def("setActiveDrawBuffer")
		.def("setActiveDrawBuffers")
		.def("setAnchorPercent")
		.def("setAnchorPoint")
		.def("setDefaultTextureIndex")
		.def("setUseTexture")
		.def("unbind")
		.def("updateTexture");
}
