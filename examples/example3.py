# -*- coding: utf-8 -*-
import sys
import numpy as np
import pyof as of


TWO_PI = np.pi * 2
N_POINTS = 200

class ofApp(of.ofPyBaseApp):
    def setup(self):
        of.ofSetFrameRate(60)
        of.ofSetWindowTitle('openFrameworks')

        of.ofBackground(239, 239, 239, 255)
        of.ofEnableSmoothing()

        w = of.ofGetWidth()
        h = of.ofGetHeight()
        self.fbo = of.ofFbo()
        self.fbo.allocate(w, h, 6408, 8);

        self.points = np.zeros((N_POINTS, 2))
        self.clicked_frame = 0

    def update(self):
        frameCount = of.ofGetFrameNum() - self.clicked_frame

        t = np.linspace(0, TWO_PI, N_POINTS)
        self.points[:, 0] = 16 * np.sin(t) ** 3
        self.points[:, 1] = -(13*np.cos(t) - 5*np.cos(2*t)
                              - 2*np.cos(3*t) - np.cos(4*t))

        c = self.points[:, 0].max() - self.points[:, 0].min()
        self.points = self.points / c * (of.ofGetWidth() / 2)

        tau = frameCount / 60.0 / TWO_PI * 125.0
        rx = 1.0 + 0.2 * np.exp(-0.1 * tau) * np.cos(tau)
        ry = 1.0 + 0.2 * np.exp(-0.1 * tau) * np.sin(tau)
        self.points[:, 0] = self.points[:, 0] * rx
        self.points[:, 1] = self.points[:, 1] * ry

    def draw(self):
        w = of.ofGetWidth()
        h = of.ofGetHeight()

        self.fbo.begin()
        of.ofClear(239, 255)
        of.ofTranslate(w / 2.0, h / 2.0, 0.0)

        of.ofFill()
        of.ofSetColor(248, 24, 24, 255)
        self.drawShape(self.points)

        of.ofNoFill()
        of.ofSetLineWidth(1)
        of.ofSetColor(0, 0, 0, 255)
        self.drawShape(self.points)

        self.fbo.end()

        self.fbo.draw(0, 0, w, h)

    def drawShape(self, points):
        of.ofBeginShape()
        for point in points:
            x, y = point
            of.ofVertex(x, y)
        of.ofEndShape(True)

    def mousePressed(self, x, y, button):
        self.clicked_frame = of.ofGetFrameNum()


if __name__ == '__main__':
    app = ofApp()
    app.run(800, 800, of.OF_WINDOW)
