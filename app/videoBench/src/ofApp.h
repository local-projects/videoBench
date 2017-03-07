#pragma once

// NOTE: ofxThrededVideo only works in 32-bit.
// You must remove it from the project if
// compiling in 64 bit.
#define USE_THREADED_VIDEO

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxSmartFont.h"
#include "ofxJsonSettings.h"

#ifdef USE_THREADED_VIDEO
#include "ofxThreadedVideo.h"
#endif

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
	bool useThreaded = false;
  vector<ofVideoPlayer *> videoPlayers;
  ofDirectory *videoDir;
  int videoCount;
	// Threaded (32 BIT ONLY?)
#ifdef USE_THREADED_VIDEO
	void drawThreadedVideos();
	vector<ofxThreadedVideo *> threadedVideoPlayers;
	void threadedVideoEvent(ofxThreadedVideoEvent & event);
#endif
	
	

  // GUI -------------------------------------------------
  ofxDatGui *gui;
	ofxDatGuiTheme *guiTheme;
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
