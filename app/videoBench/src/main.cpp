#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {

  ofGLFWWindowSettings settings;

  settings.width = 1280;
  settings.height = 720;
  settings.setPosition(ofVec2f(100, 100));
  settings.multiMonitorFullScreen = true;

  shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
  shared_ptr<ofApp> mainApp(new ofApp);

  ofRunApp(mainWindow, mainApp);
  ofRunMainLoop();
}
