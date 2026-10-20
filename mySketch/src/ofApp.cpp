#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(255);
    ofSetFrameRate(60);
    generatePattern();
}

void ofApp::generatePattern() {
    lines.clear();

    for (int i = 0; i < numLines; i++) {
        PerpLine line;
        line.t = ofRandom(0.0f, 1.0f);              // Posición aleatoria en la trayectoria
        line.lengthPos = ofRandom(10.0f, 140.0f);   // Longitud aleatoria lado A
        line.lengthNeg = ofRandom(10.0f, 140.0f);   // Longitud aleatoria lado B
        line.thickness = ofRandom(0.5f, 4.5f);      // Grosor aleatorio
        line.color = ofColor(0, ofRandom(150, 255)); // Variación ligera de brillo

        lines.push_back(line);
    }
}
//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float w = ofGetWidth();
    float h = ofGetHeight();

    // Puntos de control de la curva Bézier cúbica (centrada en el canvas)
    glm::vec2 p0(w * 0.10f, h * 0.50f); // Inicio
    glm::vec2 p1(w * 0.35f, h * 0.15f); // Control 1
    glm::vec2 p2(w * 0.65f, h * 0.85f); // Control 2
    glm::vec2 p3(w * 0.90f, h * 0.50f); // Fin

    for (const auto& line : lines) {
        float t = line.t;
        float u = 1.0f - t;

        // 1. Posición sobre la curva Bézier: B(t)
        glm::vec2 pos = u * u * u * p0 +
            3.0f * u * u * t * p1 +
            3.0f * u * t * t * p2 +
            t * t * t * p3;

        // 2. Vector tangente (derivada de la curva): B'(t)
        glm::vec2 tangent = 3.0f * u * u * (p1 - p0) +
            6.0f * u * t * (p2 - p1) +
            3.0f * t * t * (p3 - p2);

        // 3. Normalizar la tangente y calcular el vector normal (perpendicular)
        glm::vec2 dir = glm::normalize(tangent);
        glm::vec2 normal(-dir.y, dir.x);

        // 4. Calcular los extremos de la línea perpendicular
        glm::vec2 startPoint = pos + normal * line.lengthPos;
        glm::vec2 endPoint = pos - normal * line.lengthNeg;

        // 5. Renderizar la línea
        ofSetLineWidth(line.thickness);
        ofSetColor(line.color);
        ofDrawLine(startPoint, endPoint);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Pulsa Espacio o 'r' para regenerar el dibujo aleatorio
    if (key == ' ' || key == 'r' || key == 'R') {
        generatePattern();
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
