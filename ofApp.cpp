#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 28, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	vector<glm::vec3> bases{ glm::vec3(-300, 300, 0), glm::vec3(300, 300, 0), glm::vec3(-300, -300, 0), glm::vec3(300, -300, 0) };
	int size = 40;
	int count = 0;
	for (auto base : bases) {

		for (int x = -200; x <= 200; x += size) {

			for (int y = -200; y <= 200; y += size) {

				for (int z = -200; z <= 200; z += size) {

					auto location = glm::vec3(x, y, z);
					auto noise_value = ofNoise(glm::vec4(location * 0.003, ofGetFrameNum() * 0.005));

					if (count * 0.25 <= noise_value && noise_value < (count + 1) * 0.25) {

						ofFill();
						ofSetColor(239);
						ofDrawBox(base + location, size * 0.99);

						ofNoFill();
						ofSetColor(39);
						ofDrawBox(base + location, size);
					}
				}
			}
		}

		auto font_location = base + glm::vec3(0, -300, 200);
		ostringstream oss;
		oss << fixed << setprecision(2) << count * 0.25 << " - " << (count + 1) * 0.25;

		ofPushMatrix();
		ofTranslate(font_location);
		this->font.drawString(oss.str(), this->font.stringWidth(oss.str()) * -0.5, 0);
		ofPopMatrix();

		count++;
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}