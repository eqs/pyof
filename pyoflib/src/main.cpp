#include "ofMain.h"

#include <pybind11/pybind11.h>

#include "ofPyBaseApp.h"
#include "pybind_app.h"
#include "pybind_graphics.h"
#include "pybind_math.h"

namespace py = pybind11;

PYBIND11_MODULE(pyoflib, m) {
	using namespace py::literals;

	m.doc() = "openFrameworks for Python";

	pybind_app(m);
	pybind_graphics(m);
	pybind_math(m);

	py::class_<ofBaseApp, ofPyBaseApp>(m, "ofPyBaseApp")
		.def(py::init<>())
		.def("__init__", [](const ofBaseApp & a) {})
		.def("setup", (void (ofBaseApp::*)()) &ofBaseApp::setup)
		.def("update", (void (ofBaseApp::*)()) &ofBaseApp::update)
		.def("draw", (void (ofBaseApp::*)()) &ofBaseApp::draw)
		.def("exit", (void (ofBaseApp::*)()) &ofBaseApp::exit)
		.def("keyPressed", (void (ofBaseApp::*)(int)) &ofBaseApp::keyPressed)
		.def("keyReleased", (void (ofBaseApp::*)(int)) &ofBaseApp::keyReleased)
		.def("mouseMoved", (void (ofBaseApp::*)(int, int)) &ofBaseApp::mouseMoved)
		.def("mouseDragged", (void (ofBaseApp::*)(int, int, int)) &ofBaseApp::mouseDragged)
		.def("mousePressed", (void (ofBaseApp::*)(int, int, int)) &ofBaseApp::mousePressed)
		.def("mouseReleased", (void (ofBaseApp::*)(int, int, int)) &ofBaseApp::mouseReleased)
		.def("mouseEntered", (void (ofBaseApp::*)(int, int)) &ofBaseApp::mouseEntered)
		.def("mouseExited", (void (ofBaseApp::*)(int, int)) &ofBaseApp::mouseExited)
		.def("windowResized", (void (ofBaseApp::*)(int, int)) &ofBaseApp::windowResized)
		.def("dragEvent", (void (ofBaseApp::*)(ofDragInfo)) &ofBaseApp::dragEvent)
		.def("gotMessage", (void (ofBaseApp::*)(ofMessage)) &ofBaseApp::gotMessage)
		.def("run", (void (ofBaseApp::*)(int, int, ofWindowMode)) &ofPyBaseApp::run);

	m.def("ofSetWindowTitle", (void(*)(std::string)) &ofSetWindowTitle);
	m.def("ofGetFrameNum", (int(*)()) &ofGetFrameNum);

	// Misc

	// https://stackoverflow.com/questions/56009999/python-bindings-using-pybind11-with-stdfilesystem-as-function-argument-giving
	py::class_<std::filesystem::path>(m, "Path")
		.def(py::init<std::string>());
	py::implicitly_convertible<std::string, std::filesystem::path>();

	m.attr("__version__") = py::str("0.0.1");
	m.attr("__author__") = py::str("eqs");
}
