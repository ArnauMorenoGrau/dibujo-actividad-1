#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(255);
    ofSetFrameRate(60);
    generatePattern();
    ofImage img;
}

void ofApp::generatePattern() {
    lines1.clear();
    lines2.clear();
    lines3.clear();
    lines4.clear();
    lines5.clear();

    for (int i = 0; i < numLines; i++) {
        PerpLine line;
        line.t = ofRandom(0.0f, 3.0f);              // Posición aleatoria en la trayectoria
        line.lengthPos = ofRandom(10.0f, 90.0f);   // Longitud aleatoria lado A
        line.lengthNeg = ofRandom(10.0f, 90.0f);   // Longitud aleatoria lado B
        line.thickness = ofRandom(0.5f, 7.0f);      // Grosor aleatorio
        line.color = ofColor(0); 
        lines1.push_back(line);
    }

    for (int i = 0; i < numLines; i++) {
        PerpLine line2;
        line2.t = ofRandom(0.0f, 3.0f);              // Posición aleatoria en la trayectoria
        line2.lengthPos = ofRandom(10.0f, 40.0f);   // Longitud aleatoria lado A
        line2.lengthNeg = ofRandom(10.0f, 50.0f);   // Longitud aleatoria lado B
        line2.thickness = ofRandom(0.5f, 7.0f);      // Grosor aleatorio
        line2.color = ofColor(0); 

        lines2.push_back(line2);
    }

    for (int i = 0; i < numLines; i++) {
        PerpLine line3;
        line3.t = ofRandom(0.0f, 3.0f);              // Posición aleatoria en la trayectoria
        line3.lengthPos = ofRandom(1.0f, 20.0f);   // Longitud aleatoria lado A
        line3.lengthNeg = ofRandom(10.0f, 30.0f);   // Longitud aleatoria lado B
        line3.thickness = ofRandom(1.5f, 7.0f);      // Grosor aleatorio
        line3.color = ofColor(0); 

        lines3.push_back(line3);
    }

    for (int i = 0; i < numLines; i++) {
        PerpLine line4;
        line4.t = ofRandom(0.5f, 3.0f);              // Del 50% al 90% del camino
        line4.lengthPos = ofRandom(60.0f, 100.0f);
        line4.lengthNeg = ofRandom(60.0f, 100.0f);
        line4.thickness = ofRandom(2.5f, 7.0f);
        line4.color = ofColor(0);
        lines4.push_back(line4);
    }
    for (int i = 0; i < numLines; i++) {
        PerpLine line5;
        line5.t = ofRandom(0.0f, 3.0f);              // Posición aleatoria en la trayectoria
        line5.lengthPos = ofRandom(1.0f, 20.0f);   // Longitud aleatoria lado A
        line5.lengthNeg = ofRandom(10.0f, 30.0f);   // Longitud aleatoria lado B
        line5.thickness = ofRandom(1.5f, 7.0f);      // Grosor aleatorio
        line5.color = ofColor(0); // Variación ligera de brillo

        lines5.push_back(line5);
    }
}



//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float w = ofGetWidth();
    float h = ofGetHeight();

    /* 1. Crear el camino usando la sintaxis estándar de openFrameworks*/
    ofPolyline path;
    path.addVertex(w * -0.5f, h * -0.30f); // Punto inicial (p0)
    path.bezierTo(
        w * 0.35f, h * 0.85f, // p1 (Control 1)
        w * 0.05f, h * 0.85f, // p2 (Control 2)
        w * 0.90f, h * 0.99f  // p3 (Fin)
    );
    

    /*2. Dibujar las líneas perpendiculares sobre el camino*/ 
    for (const auto& line : lines1) {
        float t = line.t; // Valor entre 0.0 y 1.0

        // openFrameworks calcula la posición por ti:
        glm::vec2 pos = path.getPointAtPercent(t);

       //  Calculamos la dirección tomando una muestra milimétrica adelante:
        glm::vec2 posNext = path.getPointAtPercent(std::min(t + 0.001f, 1.0f));
        glm::vec2 dir = glm::normalize(posNext - pos);

        // Vector perpendicular (-y, x)
        glm::vec2 normal(-dir.y, dir.x);

        // Puntos final e inicial de la línea perpendicular
        glm::vec2 startPoint = pos + normal * line.lengthPos;
        glm::vec2 endPoint = pos - normal * line.lengthNeg;

        ofSetLineWidth(line.thickness);
        ofSetColor(line.color);
        ofDrawLine(startPoint, endPoint);
    }
    ofPolyline path2;
    path2.addVertex(100, 100);
    path2.bezierTo(1050, -50, 47, 768, 0, 1024);
    
    for (const auto& line2 : lines2) {
        float t = line2.t; // Valor entre 0.0 y 1.0

       //  openFrameworks calcula la posición por ti:
        glm::vec2 pos = path2.getPointAtPercent(t);

     //    Calculamos la dirección tomando una muestra milimétrica adelante:
        glm::vec2 posNext = path2.getPointAtPercent(std::min(t + 0.001f, 1.0f));
        glm::vec2 dir = glm::normalize(posNext - pos);

       //  Vector perpendicular (-y, x)
        glm::vec2 normal(-dir.y, dir.x);

         //Puntos final e inicial de la línea perpendicular
        glm::vec2 startPoint = pos + normal * line2.lengthPos;
        glm::vec2 endPoint = pos - normal * line2.lengthNeg;

        ofSetLineWidth(line2.thickness);
        ofSetColor(line2.color);
        ofDrawLine(startPoint, endPoint);
    }

    ofPolyline path3;
    path3.addVertex(1000, 200);
    path3.bezierTo(500, 100, 600, 400, 200, 1000);

    for (const auto& line3 : lines3) {
        float t = line3.t; // Valor entre 0.0 y 1.0

         //openFrameworks calcula la posición por ti:
        glm::vec2 pos = path3.getPointAtPercent(t);

        // Calculamos la dirección tomando una muestra milimétrica adelante:
        glm::vec2 posNext = path3.getPointAtPercent(std::min(t + 0.001f, 1.0f));
        glm::vec2 dir = glm::normalize(posNext - pos);

        // Vector perpendicular (-y, x)
        glm::vec2 normal(-dir.y, dir.x);

        // Puntos final e inicial de la línea perpendicular
        glm::vec2 startPoint = pos + normal * line3.lengthPos;
        glm::vec2 endPoint = pos - normal * line3.lengthNeg;

        ofSetLineWidth(line3.thickness);
        ofSetColor(line3.color);
        ofDrawLine(startPoint, endPoint);
    }
    ofPolyline path4;
    path4.addVertex(1200, -1000);
    path4.bezierTo(1200, 100, 600, 400, 1200, 500);

    for (const auto& line4 : lines4) { // Corregido: recorre lines4
        float t = line4.t;

        glm::vec2 pos = path4.getPointAtPercent(t);
        glm::vec2 posNext = path4.getPointAtPercent(std::min(t + 0.001f, 1.0f));
        glm::vec2 dir = glm::normalize(posNext - pos);

        glm::vec2 normal(-dir.y, dir.x);

        glm::vec2 startPoint = pos + normal * line4.lengthPos;
        glm::vec2 endPoint = pos - normal * line4.lengthNeg;

        ofSetLineWidth(line4.thickness);
        ofSetColor(line4.color);
        ofDrawLine(startPoint, endPoint);
    }

    ofPolyline path5;
    path5.addVertex(0, 50);
    path5.bezierTo(300, 500, 600, 700, 1200, 700);

    for (const auto& line5 : lines5) { // Corregido: recorre lines4
        float t = line5.t;

        glm::vec2 pos = path5.getPointAtPercent(t);
        glm::vec2 posNext = path5.getPointAtPercent(std::min(t + 0.001f, 1.0f));
        glm::vec2 dir = glm::normalize(posNext - pos);

        glm::vec2 normal(-dir.y, dir.x);

        glm::vec2 startPoint = pos + normal * line5.lengthPos;
        glm::vec2 endPoint = pos - normal * line5.lengthNeg;

        ofSetLineWidth(line5.thickness);
        ofSetColor(line5.color);
        ofDrawLine(startPoint, endPoint);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofImage img;
    // Pulsa Espacio o 'r' para regenerar el dibujo aleatorio
    if (key == ' ' || key == 'r' || key == 'R') {
        generatePattern();
    }
    if (key == 'p' || key == 'P') {
        img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        img.save("screenshot_" + ofGetTimestampString() + ".jpg");

    }
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
