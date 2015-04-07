#include "ofApp.h"

void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	kinect.setRegistration(true);
	kinect.init();
	kinect.open();
	
        shader.load( "shaders/instanced.vert", "shaders/instanced.frag" );

	gui.setup();
        gui.add(xPos.set("grid",ofVec3f(104.,0.,48.),ofVec3f(-155.,-155.,-155.),ofVec3f(155.,155.,155.)));
        gui.add(offset.set("offset",ofVec3f(-0.5,-0.5,0.),ofVec3f(-2.,-2.,-2.),ofVec3f(2.,2.,2.)));
        gui.add(contatore.set("counter",80,0,500));
        gui.add(sizeBox.set("size box",1.f,0.f,150.f));

        gui.add(label.set("num model",""));
        gui.add(dist.set("axis vbo",ofVec3f(0,0,0),ofVec3f(-2.999,-2.999,-2.999),ofVec3f(2.999,2.999,2.999)));
	gui.add(distance.set("distance",1000,0,3000));

	gui.add(angle.set("angle",0,-30,30));

        gui.add(translateFbo.set("translate fbo",ofVec3f(-180,210,-580),ofVec3f(-1500,-1500,-1500),ofVec3f(1500,1500,1500)));
        gui.add(globalColor.set("global color",ofVec4f(0.f,0.f,0.f,0.f),ofVec4f(-1.f,-1.f,-1.f,-1.f),ofVec4f(1.f,1.f,1.f,1.f)));
        gui.add(debugimage.set("debug image",true));

        gui.add(drawModel.set("draw Model",false));
        gui.add(drawCone.set("draw Cone",true));
        gui.add(drawBox.set("draw Box",false));
	
	ofSetFrameRate(60);
	ofDisableArbTex();
	kinect.setCameraTiltAngle(angle);
	cam.setFarClip(100000);
        cam.setNearClip(1.);
	contorno.allocate(kinect.width,kinect.height);
	line.setMode(OF_PRIMITIVE_POINTS);
	angle.addListener(this, &ofApp::changeAngle);
	model.loadModel("model/dado/dado.obj",true);
}

void ofApp::changeAngle(int & value){
	kinect.setCameraTiltAngle(value);
}

void ofApp::update() {
	kinect.update();
	contorno.begin();
	ofClear(0,0,0,0);
	line.clear();
        int kw = 640;
        int kh = 480;
        int step = 2;
        for(int y = 0; y < kh; y += step) {
                for(int x = 0; x < kw; x += step) {
                        if(kinect.getDistanceAt(x, y) > 0 && kinect.getDistanceAt(x,y) < distance ) {
                                line.addColor(kinect.getColorAt(x,y));
                                line.addVertex(kinect.getWorldCoordinateAt(x, y));
                        }
                }
        }
        glPointSize(2);
        ofPushMatrix();
	ofRotateX(-160);
	ofRotateY(-160);

	ofScale(1,-1,-1);
        ofTranslate( translateFbo );
        line.drawVertices();
        ofPopMatrix();
	contorno.end();
}

void ofApp::draw() {
	ofBackgroundGradient(ofColor(140), ofColor(0));
	if(debugimage)
		contorno.draw(0,0);

	cam.begin();
                        ofEnableDepthTest();

			//ofMatrix4x4 mat;
			//mat.makeRotationMatrix( ofGetFrameNum(),  ofVec3f(0, 1, 0));

                        shader.begin();
                        shader.setUniformTexture("tex0",             contorno.getTextureReference(),0);
                        shader.setUniform4f("globalColor",           globalColor->x,globalColor->y,globalColor->z,globalColor->w);
                        shader.setUniform2f("offset",                offset->x,offset->y);
                        shader.setUniform3f("xPos",                  xPos->x,xPos->y,xPos->z);
                        shader.setUniform1f("counter",      	     contatore);
                        shader.setUniform3f("dist",         	     dist->x,dist->y,dist->z);
			//shader.setUniformMatrix4f("transformMatrix", mat.getPtr());

			ofVboMesh mesh;
			if(drawBox){
	                        ofBoxPrimitive box;
                        	box.set(sizeBox);
	                        mesh=box.getMesh();
			}
			if(drawCone){
				ofConePrimitive s;
                        	s.set(1,-sizeBox);
	                        mesh=s.getMesh();
			}
			if(drawModel){
				//for(int i = 0; i < mesh.getNumMeshes(); i++){
				mesh=model.getMesh(0);
				//}
			}
                        mesh.drawInstanced(OF_MESH_FILL, contatore*contatore);
                        shader.end();
                        ofDisableDepthTest();
        cam.end();

	gui.draw();
}

void ofApp::exit() {
	kinect.setCameraTiltAngle(0);
	kinect.close();
}

void ofApp::keyPressed (int key) {

}
