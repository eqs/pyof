#pragma once
#include "ofMain.h"
#include "ofUtils.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void pybind_utils(py::module m) {
	m.def(
		"ofToDataPath", (std::string(*)(const std::filesystem::path &, bool)) &ofToDataPath,
		py::arg("path"), py::arg("absolute") = false
	);
	m.def("ofSetDataPathRoot", (void(*)(const std::filesystem::path &)) &ofSetDataPathRoot);
}
