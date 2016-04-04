#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxJsonSettings.h"

class ofApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  // VIDEO -----------------------------------------------
	void drawVideos();
  vector<ofVideoPlayer *> videoPlayers;
  ofDirectory *videoDir;
  int videoCount;

  // GUI -------------------------------------------------
  ofxDatGui *gui;
  ofxDatGuiValuePlotter *fpsPlotter;
	ofxDatGuiToggle *fullscreenToggle, *videoStretchToggle, *videoRotateToggle, *repeatHorizToggle, *vsyncToggle;
	ofxDatGuiSlider *videoRepeatSlider, *videoRotationSlider, *framerateSlider;
	ofxDatGuiButton *saveSettingsButton;
  void onButtonEvent(ofxDatGuiButtonEvent e);
  void onSliderEvent(ofxDatGuiSliderEvent e);

  bool shouldStretchVideo = false;
	bool shouldDrawGui, shouldDrawDebugInfo = true;
	bool firstSetup = true;
};
