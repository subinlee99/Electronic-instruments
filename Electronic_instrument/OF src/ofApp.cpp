#include "ofApp.h"
int drum1_flag;
int drum2_flag;
int fall;
int sx, sy, sz;
int t_time, d_time;
//--------------------------------------------------------------
void ofApp::setup(){
    int fall =0;
    //ofBackground(255,255,255);
    /*
    //arduino setup
    //serial communication
    serial.listDevices();
    vector <ofSerialDeviceInfo>
    deviceList = serial.getDeviceList();
    int baud = 9600;
    serial.setup(0, baud);
     */
    //instrument setup
    drum1_flag = 0;
    drum2_flag = 0;
    //
    osc.setup(PORT);
    
    //set colors
    colorX = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
    colorY =ofMap(mouseY, 0, ofGetHeight(), 0, 255);
    int t_time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    /*
    //read arduino input
    while(serial.available() > 0){
        state = serial.readByte();
        printf("%d\n", state);
    }
     */
    while (osc.hasWaitingMessages()) {
       ofxOscMessage m;
       osc.getNextMessage(&m);
       if (m.getAddress() == "/drum") {
         dis = m.getArgAsFloat(0);
           //printf("dis: %d\n", dis);
           drum1_flag =1;
           //else drum1_flag =0;
       }
        if (m.getAddress() == "/no") {
          dis = m.getArgAsFloat(0);
            //printf("dis: %d\n", dis);
            drum1_flag =0;
            //else drum1_flag =0;
        }
       
       else if (m.getAddress() == "/x") {
         sx = m.getArgAsFloat(0);
           //printf("sx: %d\n", sx);
       }
        
        else if (m.getAddress() == "/y") {
          sy = m.getArgAsFloat(0);
        }
        
        else if (m.getAddress() == "/z") {
          sz = m.getArgAsFloat(0);
        }
     }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    ofEnableAlphaBlending();
    float bez1X1 = 350 + 100 * cos(ofGetElapsedTimef());
    float bez1Y1 = 200 + 100 * sin(ofGetElapsedTimef());
    float bez1X2 = 400 + 100 * cos(ofGetElapsedTimef());
    float bez1Y2 = 300 + 100 * sin(ofGetElapsedTimef());
    ofColor centerColor = ofColor(160,233,244,100);
    ofColor edgeColor(173, 201, 224,150);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);

    sun(ofGetWidth()/2, ofGetHeight()/2-200);
    for(int i=ofGetHeight(); i>ofGetHeight()/2;i-=50){
        wave(i,0,ofGetWidth(), 900-10);
    }
     
    
     
}
void ofApp::Drum(int dis){
   // fall=0;
    for (int i = 0; i < dis*10; i++){
        ofSetColor(colorX-i/2,colorY-i/2,colorX+colorY/2-i/2);
        ofDrawCircle(ofRandom(0,ofGetWidth()),fall,dis*i);
       
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
void ofApp::wave(int h, int start, int end, int wh){
    float time = ofGetElapsedTimef();
    ofEnableAlphaBlending();
    int c = ofRandom(0,255);
    
    ofFill();
    ofSetColor(0,119, 190,70);
    ofSetColor(0,ofGetMouseY()/5,150, 70);
    //printf("%d", colorY);
    float bez1X1 = sx + wh * cos(time);
    float bez1Y1 = h+wh * sin(time);
    float bez1X2 = sy + wh * cos(time);
    float bez1Y2 = h-sy * sin(time);
    float bez1X3 = 400 - wh * cos(time);
    float bez1Y3 = -sx * wh*sin(time);
    
    ofBeginShape();
    ofVertex(start, h);
    //파도
    ofBezierVertex(bez1X1, bez1Y1, bez1X2, bez1Y2, end, h);
    ofVertex(end, h);
    ofEndShape();
    //바다 표현(밑에 있을 수록 어둡게)
    ofDrawRectangle(0, h,end-start, h);
}

void ofApp::sun(int x, int y){
    int a;
    if(drum1_flag==1) a= 500;
    else a=0;
    for(int i=0; i<200; i+=20){
        ofSetColor(255, 243,128,255-i*1.3);
        ofDrawCircle(x,y,a/10+i);
    }
}
