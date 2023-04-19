#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(0);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int span = 30;
	for (int x = -300; x <= 300; x += span) {

		for (int y = -300; y <= 300; y += span) {

			auto noise_y = ofMap(ofNoise(x * 0.0025 + ofGetFrameNum() * 0.035), 0, 1, -400, 400);
			auto next_noise_y = ofMap(ofNoise(x * 0.0025 + (ofGetFrameNum() + 1) * 0.035), 0, 1, -400, 400);

			auto noise_param = abs(y - noise_y) < 125 ? ofMap(abs(y - noise_y), 0, 125, 1, 0) : 0;
			auto next_noise_param = abs(y - next_noise_y) < 125 ? ofMap(abs(y - next_noise_y), 0, 125, 1, 0) : 0;

			auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

			auto param_x = ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.05), 0, 1, span * -1.25, span * 1.25) * noise_param;
			auto param_y = ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.05), 0, 1, span * -1.25, span * 1.25) * noise_param;

			auto next_param_x = ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + 1) * 0.05), 0, 1, span * -1.25, span * 1.25) * next_noise_param;
			auto next_param_y = ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + 1) * 0.05), 0, 1, span * -1.25, span * 1.25) * next_noise_param;

			if (noise_param > 0) {

				this->draw_arrow(glm::vec2(x + param_x, y + param_y), glm::vec2(x + next_param_x, y + next_param_y), span * 0.5, ofColor(0), ofColor(255));
			}
			else {

				ofSetColor(0);
				ofFill();
				ofDrawCircle(x + param_x, y + param_y, span * 0.2);

				ofSetColor(255);
				ofNoFill();
				ofDrawCircle(x + param_x, y + param_y, span * 0.2);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 next_location, float size, ofColor fill_color, ofColor no_fill_color) {

	auto angle = std::atan2(next_location.y - location.y, next_location.x - location.x);

	ofSetColor(fill_color);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * 0.8 * cos(angle), size * 0.8 * sin(angle)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) + location);
	ofEndShape(true);

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape(true);

	ofSetColor(no_fill_color);
	ofNoFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.8 * cos(angle), size * 0.8 * sin(angle)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}