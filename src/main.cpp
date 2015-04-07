#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"

int main() {
       ofPtr<ofBaseRenderer> renderer(new ofGLProgrammableRenderer(false));
       ofSetCurrentRenderer(renderer, false);

    ofSetupOpenGL(1024, 768, OF_WINDOW);
    ofRunApp(new ofApp());
}
