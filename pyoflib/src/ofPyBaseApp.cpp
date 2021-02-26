#include "ofMain.h"
#include "ofUtils.h"
#include "ofPyBaseApp.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void ofPyBaseApp::setup() {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, setup);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::update() {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, update);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::draw() {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, draw);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::exit() {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, exit);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::keyPressed(int key) {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, keyPressed, key);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::keyReleased(int key) {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, keyReleased, key);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::mouseMoved(int x, int y) {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, mouseMoved, x, y);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::mouseDragged(int x, int y, int button) {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, mouseDragged, x, y, button);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::mousePressed(int x, int y, int button) {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, mousePressed, x, y, button);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::mouseReleased(int x, int y, int button) {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, mouseReleased, x, y, button);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::mouseEntered(int x, int y) {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, mouseEntered, x, y);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::mouseExited(int x, int y) {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, mouseExited, x, y);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::windowResized(int w, int h) {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, windowResized, w, h);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::dragEvent(ofDragInfo dragInfo) {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, dragEvent, dragInfo);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}
void ofPyBaseApp::gotMessage(ofMessage msg) {
	try{
		PYBIND11_OVERLOAD(void, ofBaseApp, gotMessage, msg);
	} catch (py::error_already_set &e) {
		std::cerr << e.what() << std::endl;
	}
}


void ofPyBaseApp::run(int w, int h, ofWindowMode mode) {

	// Change default working dir
	auto os_module = py::module::import("os");
	auto result = os_module.attr("getcwd")();
	std::filesystem::path path = result.cast<std::string>();
	path += "/data";
	ofSetDataPathRoot(path);

	py::object self = py::cast(this);
	self.inc_ref();
	ofSetupOpenGL(w, h, mode);
	ofRunApp(self.cast<ofBaseApp*>());
}
