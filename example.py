# -*- coding: utf-8 -*-
import sys
import numpy as np

sys.path.append('./pyoflib/bin')
import pyoflib as of


class ofApp(of.ofPyBaseApp):
    def setup(self):
        of.ofSetWindowTitle('Hello, openFrameworks!')
        self.x = 0.0
        self.y = 0.0

    def update(self):
        t = of.ofGetFrameNum()
        self.x = 200 + 100 * np.cos(t * 0.1)
        self.y = 200 + 100 * np.sin(t * 0.1)

    def draw(self):
        of.ofDrawCircle(self.x, self.y, 40)


if __name__ == '__main__':
    app = ofApp()
    app.run(400, 400, of.OF_WINDOW)
