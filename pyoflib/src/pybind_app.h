#pragma once
#include "ofMain.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void pybind_app(py::module m) {

	py::enum_<ofWindowMode>(m, "ofWindowMode")
		.value("OF_WINDOW", OF_WINDOW)
		.value("OF_FULLSCREEN", OF_FULLSCREEN)
		.value("OF_GAME_MODE", OF_GAME_MODE)
		.export_values();

	// void noopDeleter(Window *)
	// m.def("ofCreateWindow", (shared_ptr(*) (const ofWindowSettings &)) &ofCreateWindow);
	m.def("ofDoesHWOrientation", (bool(*) ()) &ofDoesHWOrientation);
	m.def("ofEvents", (ofCoreEvents &(*) ()) &ofEvents);
	m.def("ofExit", (void(*) (int)) &ofExit);
	m.def("ofGetAppPtr", (ofBaseApp *(*) ()) &ofGetAppPtr);
	m.def("ofGetClipboardString", (string(*) ()) &ofGetClipboardString);
	// m.def("ofGetCurrentRenderer", (shared_ptr &(*) ()) &ofGetCurrentRenderer);
	// m.def("ofGetCurrentWindow", (shared_ptr(*) ()) &ofGetCurrentWindow);
	m.def("ofGetFixedStepForFps", (uint64_t(*) (double)) &ofGetFixedStepForFps);
	m.def("ofGetFrameNum", (uint64_t(*) ()) &ofGetFrameNum);
	m.def("ofGetFrameRate", (float(*) ()) &ofGetFrameRate);
	// m.def("ofGetGLXContext", (GLXContext(*) ()) &ofGetGLXContext);
	m.def("ofGetHeight", (int(*) ()) &ofGetHeight);
	m.def("ofGetLastFrameTime", (double(*) ()) &ofGetLastFrameTime);
	// m.def("ofGetMainLoop", (shared_ptr(*) ()) &ofGetMainLoop);
	m.def("ofGetOrientation", (ofOrientation(*) ()) &ofGetOrientation);
	m.def("ofGetScreenHeight", (int(*) ()) &ofGetScreenHeight);
	m.def("ofGetScreenWidth", (int(*) ()) &ofGetScreenWidth);
	m.def("ofGetTargetFrameRate", (float(*) ()) &ofGetTargetFrameRate);
	m.def("ofGetWidth", (int(*) ()) &ofGetWidth);
	m.def("ofGetWindowHeight", (int(*) ()) &ofGetWindowHeight);
	m.def("ofGetWindowMode", (int(*) ()) &ofGetWindowMode);
	m.def("ofGetWindowPositionX", (int(*) ()) &ofGetWindowPositionX);
	m.def("ofGetWindowPositionY", (int(*) ()) &ofGetWindowPositionY);
	m.def("ofGetWindowPtr", (ofAppBaseWindow *(*) ()) &ofGetWindowPtr);
	m.def("ofGetWindowRect", (ofRectangle(*) ()) &ofGetWindowRect);
	m.def("ofGetWindowSize", (glm::vec2(*) ()) &ofGetWindowSize);
	m.def("ofGetWindowWidth", (int(*) ()) &ofGetWindowWidth);
	// m.def("ofGetX11Display", (Display *(*) ()) &ofGetX11Display);
	// m.def("ofGetX11Window", (Window(*) ()) &ofGetX11Window);
	m.def("ofHideCursor", (void(*) ()) &ofHideCursor);
	m.def("ofInit", (void(*) ()) &ofInit);
	m.def("ofRandomHeight", (float(*) ()) &ofRandomHeight);
	m.def("ofRandomWidth", (float(*) ()) &ofRandomWidth);
	m.def("ofRunApp", (int(*) (ofBaseApp *)) &ofRunApp);
	// int ofRunApp(shared_ptr &&OFSA)
	// void ofRunApp(shared_ptr window, shared_ptr &&app)
	m.def("ofRunMainLoop", (int(*) ()) &ofRunMainLoop);
	m.def("ofSetClipboardString", (void(*) (const string &)) &ofSetClipboardString);
	// m.def("ofSetCurrentRenderer", (void(*) (shared_ptr, bool)) &ofSetCurrentRenderer);
	m.def("ofSetEscapeQuitsApp", (void(*) (bool)) &ofSetEscapeQuitsApp);
	m.def("ofSetFrameRate", (void(*) (int)) &ofSetFrameRate);
	m.def("ofSetFullscreen", (void(*) (bool)) &ofSetFullscreen);
	// m.def("ofSetMainLoop", (void(*) (shared_ptr)) &ofSetMainLoop);
	m.def("ofSetOrientation", (void(*) (ofOrientation, bool)) &ofSetOrientation);
	m.def("ofSetTimeModeFiltered", (void(*) (float)) &ofSetTimeModeFiltered);
	m.def("ofSetTimeModeFixedRate", (void(*) (uint64_t)) &ofSetTimeModeFixedRate);
	m.def("ofSetTimeModeSystem", (void(*) ()) &ofSetTimeModeSystem);
	m.def("ofSetVerticalSync", (void(*) (bool)) &ofSetVerticalSync);
	m.def("ofSetWindowPosition", (void(*) (int, int)) &ofSetWindowPosition);
	m.def("ofSetWindowShape", (void(*) (int, int)) &ofSetWindowShape);
	m.def("ofSetWindowTitle", (void(*) (std::string)) &ofSetWindowTitle);
	m.def("ofSetupOpenGL", (void(*) (int, int, ofWindowMode)) &ofSetupOpenGL);
	// m.def("ofSetupOpenGL", (void(*) (shared_ptr, int, int, ofWindowMode)) &ofSetupOpenGL);
	// m.def("ofSetupOpenGL", (void(*) (shared_ptr, int, int, ofWindowMode)) &ofSetupOpenGL);
	m.def("ofShowCursor", (void(*) ()) &ofShowCursor);
	m.def("ofToggleFullscreen", (void(*) ()) &ofToggleFullscreen);
}