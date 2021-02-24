#pragma once
#include "ofMain.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void pybind_math(py::module m) {
	m.def("ofRandom", (float(*)(float, float)) &ofRandom);
	m.def("ofRandomf", (float(*)()) &ofRandomf);
	m.def("ofRandomuf", (float(*)()) &ofRandomuf);
	m.def("ofRandomWidth", (float(*)()) &ofRandomWidth);
	m.def("ofRandomHeight", (float(*)()) &ofRandomHeight);
	m.def("ofSeedRandom", py::overload_cast<>(&ofSeedRandom));
	m.def("ofSeedRandom", py::overload_cast<int>(&ofSeedRandom));
	m.def("ofNormalize", (float(*)(float, float, float)) &ofNormalize);
	m.def("ofMap", (float(*)(float, float, float, float, float, bool)) &ofMap);
	m.def("ofClamp", (float(*)(float, float, float)) &ofClamp);
	m.def("ofInRange", (bool(*)(float, float, float)) &ofInRange);
	m.def("ofLerp", (float(*)(float, float, float)) &ofLerp);
	m.def("ofDist", py::overload_cast<float, float, float, float>(&ofDist));
	m.def("ofDist", py::overload_cast<float, float, float, float, float, float>(&ofDist));
	m.def("ofDistSquared", py::overload_cast<float, float, float, float>(&ofDistSquared));
	m.def("ofDistSquared", py::overload_cast<float, float, float, float, float, float>(&ofDistSquared));
	m.def("ofRadToDeg", (float(*)(float)) &ofRadToDeg);
	m.def("ofDegToRad", (float(*)(float)) &ofDegToRad);
	m.def("ofLerpDegrees", (float(*)(float, float, float)) &ofLerpDegrees);
	m.def("ofLerpRadians", (float(*)(float, float, float)) &ofLerpRadians);
	m.def("ofAngleDifferenceDegrees", (float(*)(float, float)) &ofAngleDifferenceDegrees);
	m.def("ofAngleDifferenceRadians", (float(*)(float, float)) &ofAngleDifferenceRadians);
	m.def("ofWrap", (float(*)(float, float, float)) &ofWrap);
	m.def("ofWrapRadians", (float(*)(float, float, float)) &ofWrapRadians);
	m.def("ofWrapDegrees", (float(*)(float, float, float)) &ofWrapDegrees);
	m.def("ofNoise", py::overload_cast<float>(&ofNoise));
	m.def("ofNoise", py::overload_cast<float, float>(&ofNoise));
	// m.def("ofNoise", (float(*)(const int &)) &ofNoise);
	m.def("ofNoise", py::overload_cast<float, float, float>(&ofNoise));
	// m.def("ofNoise", (float(*)(const int &)) &ofNoise);
	m.def("ofNoise", py::overload_cast<float, float, float, float>(&ofNoise));
	// m.def("ofNoise", (float(*)(const int &)) &ofNoise);
	m.def("ofSignedNoise", py::overload_cast<float>(&ofSignedNoise));
	m.def("ofSignedNoise", py::overload_cast<float, float>(&ofSignedNoise));
	// m.def("ofSignedNoise", (float(*)(const int &)) &ofSignedNoise);
	m.def("ofSignedNoise", py::overload_cast<float, float, float>(&ofSignedNoise));
	// m.def("ofSignedNoise", (float(*)(const int &)) &ofSignedNoise);
	m.def("ofSignedNoise", py::overload_cast<float, float, float, float>(&ofSignedNoise));
	// m.def("ofSignedNoise", (float(*)(const int &)) &ofSignedNoise);

	m.def("ofNextPow2", (int(*)(int)) &ofNextPow2);
	m.def("ofSign", (int(*)(float)) &ofSign);
}
