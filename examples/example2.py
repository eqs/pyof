# -*- coding: utf-8 -*-
import sys
import numpy as np
from scipy.spatial import distance_matrix
import pyof as of


class ofApp(of.ofPyBaseApp):
    def setup(self):
        of.ofSetWindowTitle('Particles')

        self.N = 500
        self.dist_thresh = 64

        x_list = np.random.randint(0, of.ofGetWidth(), self.N)
        y_list = np.random.randint(0, of.ofGetHeight(), self.N)
        self.p_list = np.vstack([x_list, y_list]).T
        self.d_matrix = distance_matrix(self.p_list, self.p_list)

        vx_list = np.random.randn(self.N) * 0.25
        vy_list = np.random.randn(self.N) * 0.25
        self.v_list = np.vstack([vx_list, vy_list]).T


    def update(self):
        self.p_list = self.p_list + self.v_list
        self.d_matrix = distance_matrix(self.p_list, self.p_list)

    def draw(self):
        of.ofBackground(0, 255);

        # Draw lines
        of.ofSetColor(255, 255, 255, 128)
        of.ofSetLineWidth(4.0)

        ii, jj = np.where(self.d_matrix < self.dist_thresh)
        for i, j in zip(ii, jj):
            if i != j:
                of.ofDrawLine(self.p_list[i, 0], self.p_list[i, 1],
                              self.p_list[j, 0], self.p_list[j, 1])

        # Draw Circles
        of.ofSetColor(230, 0, 0, 255)
        of.ofSetLineWidth(1.0)
        for x, y in self.p_list:
            of.ofDrawCircle(x, y, 8)


if __name__ == '__main__':
    app = ofApp()
    app.run(800, 800, of.OF_WINDOW)
