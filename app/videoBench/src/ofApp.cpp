#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  // GUI + SETTINGS---------------------------------------

  Settings::get().load("settings/settings.json");

  gui->setAssetPath("");
  gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
  gui->addHeader(":: Menu ::");

  ofxDatGuiFolder *systemGuiFolder, *videoPropertiesFolder;

  // System folder

  systemGuiFolder = gui->addFolder("System", ofColor::lime);

  systemGuiFolder->addFRM();
  fpsPlotter = systemGuiFolder->addValuePlotter("FPS", 0, 60);
  fpsPlotter->setSpeed(0.25);

  framerateSlider = systemGuiFolder->addSlider("App FPS", 1, 120, 60);
  framerateSlider->setPrecision(0);
  framerateSlider->onSliderEvent(this, &ofApp::onSliderEvent);

  vsyncToggle = systemGuiFolder->addToggle("Enable VSYNC", false);
  vsyncToggle->onButtonEvent(this, &ofApp::onButtonEvent);

  fullscreenToggle = systemGuiFolder->addToggle("Enable Fullscreen");
  fullscreenToggle->onButtonEvent(this, &ofApp::onButtonEvent);

  gui->addBreak();

  // Video properties folder

  videoPropertiesFolder = gui->addFolder("Video Properties", ofColor::fuchsia);

  videoRepeatSlider =
      videoPropertiesFolder->addSlider("Number of Videos", 1, 50, 1);
  videoRepeatSlider->bind(Settings::getInt("video-repeats"));
  videoRepeatSlider->setPrecision(0);
  videoRepeatSlider->onSliderEvent(this, &ofApp::onSliderEvent);

  repeatHorizToggle = videoPropertiesFolder->addToggle("Repeat Horizontally");
  repeatHorizToggle->onButtonEvent(this, &ofApp::onButtonEvent);

  videoStretchToggle =
      videoPropertiesFolder->addToggle("Stretch video to slice size");
  videoStretchToggle->onButtonEvent(this, &ofApp::onButtonEvent);

  videoRotateToggle = videoPropertiesFolder->addToggle("Rotate 90 degs");
  videoRotateToggle->onButtonEvent(this, &ofApp::onButtonEvent);

  saveSettingsButton = videoPropertiesFolder->addButton("Save Settings");
  saveSettingsButton->onButtonEvent(this, &ofApp::onButtonEvent);

  // LOAD VIDEOS -----------------------------------------
  videoDir = new ofDirectory("videos");
  for (int i = 0; i < videoDir->listDir(); i++) {
    ofVideoPlayer *tempVideo = new ofVideoPlayer();
    tempVideo->load(videoDir->getPath(i));
    tempVideo->play();
    videoPlayers.push_back(tempVideo);
  }

  // SYSTEM ----------------------------------------------
  ofSetFrameRate(framerateSlider->getValue());
  ofSetVerticalSync(vsyncToggle->getEnabled());
}

//--------------------------------------------------------------
void ofApp::update() {

  // Update FPS graph /////
  fpsPlotter->setValue(ofGetFrameRate());

  // Update video players /////
  for (auto player : videoPlayers) {
    player->update();
  }
}

//--------------------------------------------------------------
void ofApp::draw() {

  ofBackground(ofColor::black);
  drawVideos();
}

//--------------------------------------------------------------
void ofApp::drawVideos() {

  ofVec2f winSize(ofGetWindowWidth(), ofGetWindowHeight());
  ofVec2f offsetForSlice(0, winSize.y / Settings::getInt("video-repeats"));

  if (repeatHorizToggle->getEnabled()) {
    offsetForSlice.set(winSize.x / Settings::getInt("video-repeats"), 0);
  }

  // Translate and draw video players /////
  for (int i = 0; i < Settings::getInt("video-repeats"); i++) {

    ofPushMatrix();

    ofTranslate(i * offsetForSlice);

    ofPushMatrix();

    int playerNum = i % videoPlayers.size();
    ofVideoPlayer *playerToDraw = videoPlayers[playerNum];

    // Size of video /////
    ofVec2f vidSize(playerToDraw->getWidth(), playerToDraw->getHeight());
    if (shouldStretchVideo) {
      if (!repeatHorizToggle->getEnabled()) {
        vidSize.set(winSize.x, offsetForSlice.y);
      } else {
        vidSize.set(offsetForSlice.x, winSize.y);
      }

      if (videoRotateToggle->getEnabled()) {
        swap(vidSize.x, vidSize.y);
      }
    }

    // Translations for positioning video /////
    if (videoRotateToggle->getEnabled()) {
      ofTranslate(vidSize.y, 0);
      ofRotateZ(90);
    }

    // Draw video players /////
    if (!shouldStretchVideo) {
      playerToDraw->draw(0, 0);
    } else {
      playerToDraw->draw(0, 0, vidSize.x, vidSize.y);
    }

    ofPopMatrix();
    ofPopMatrix();

    // Draw debug info //
    if (shouldDrawDebugInfo) {
      ofPushMatrix();
      if (repeatHorizToggle->getEnabled()) {
        ofTranslate((offsetForSlice.x * i) + 10, 15);
      } else {
        ofTranslate(10, (offsetForSlice.y * i) + 15);
      }
      ofDrawBitmapString(ofToString(i) + ": " + playerToDraw->getMoviePath(), 0,
                         0);
      ofDrawBitmapString(ofToString(playerToDraw->getCurrentFrame()) + " / " +
                             ofToString(playerToDraw->getTotalNumFrames()),
                         0, 12);
      ofPopMatrix();
    }
  }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 'g') {
    gui->setAutoDraw(shouldDrawGui);
		shouldDrawGui = !shouldDrawGui;
  }
  if (key == 'd') {
    shouldDrawDebugInfo = !shouldDrawDebugInfo;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}

// --------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
  if (e.target == fullscreenToggle) { // Fullscreen
    ofSetFullscreen(e.target->getEnabled());
  } else if (e.target == videoStretchToggle) { // Video stretch
    shouldStretchVideo = e.target->getEnabled();
  } else if (e.target == saveSettingsButton) { // Save settings
    Settings::get().save("settings/settings.json");
  } else if (e.target == vsyncToggle) { // VSYNC
    ofSetVerticalSync(e.target->getEnabled());
  }
}

// --------------------
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {

  if (e.target == framerateSlider) { // Framerate
    ofSetFrameRate(e.target->getValue());
  }
}