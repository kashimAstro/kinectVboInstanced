#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"


class ofApp : public ofBaseApp {
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	void changeAngle(int & value);
	
	void keyPressed(int key);

	ofxPanel gui;
	ofParameter<bool> drawBox;
	ofParameter<bool> drawCone;
	ofParameter<bool> drawModel;


	ofParameter<bool> debugimage;

        ofParameter<int> contatore;
	ofParameter<int> angle;
	ofParameter<int> distance;
	ofParameter<float> sizeBox;

        ofParameter<ofVec3f> dist;
        ofParameter<ofVec3f> xPos,offset;
	ofParameter<ofVec3f> translateFbo;
	ofParameter<ofVec4f> globalColor;
      
        ofParameter<string> label;

	ofxAssimpModelLoader model;

	ofxKinect kinect;
        ofShader shader;
	ofEasyCam cam;
	ofFbo contorno;
	ofMesh line;

};
