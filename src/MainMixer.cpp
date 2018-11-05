#include "MainMixer.h"

int MainMixer::globalMainMixCont = 0;

MainMixer::MainMixer() 
{
	this->l1 = nullptr;
	this->l2 = nullptr;




	all.setName("Mixer" + ofToString(globalMainMixCont));

	all.add(fader.set("fader", 0.5, 0, 1));
	all.add(mode.set("mode", 1, 0, 5));
	all.add(submodeA.set("submodeA", 1, 1, 10));
	all.add(submodeB.set("submodeB", 1, 1, 10));
	all.add(invertA.set("invertA", 0,0,1));
	all.add(invertB.set("invertB", 0,0,1));
	all.add(efxA.set("efxA", 0, 0, 1));
	all.add(efxB.set("efxB", 0, 0, 1));
	all.add(flipA.set("flipA", 0, 0, 1));
	all.add(flipB.set("flipB", 0, 0, 1));
	all.add(black.set("black", 0, 0, 1));




	globalMainMixCont++;
}


MainMixer::~MainMixer()
{


}

void MainMixer::setup(ofxLayer::Layer * l1, ofxLayer::Layer * l2,int w,int h)
{
	this->l1 = l1;
	this->l2 = l2;

	width = w;
	height = h;

	fbo_layer1.allocate(width, height);
	fbo_layer2.allocate(width, height);
	fbo_layer1_efx.allocate(width, height);
	fbo_layer2_efx.allocate(width, height);

	shader.load("shader.vert", "blend.frag");
	blurXShader.load("shader.vert", "blurX.frag");
	blurYShader.load("shader.vert", "blurY.frag");


	fullQuad.set(width, height);
	fullQuad.setPosition(width /2, height /2, 0);
	fullQuad.setResolution(2, 2);



}

void MainMixer::update()
{

		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			fbo_layer2.begin();

			ofPushStyle();
			glPushMatrix();



			ofClear(0,0,0);
			ofSetColor(255, 255);

			l2->draw();

			glPopMatrix();
			ofPopStyle();

			fbo_layer2.end();
		}
		glPopAttrib();



		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			fbo_layer1.begin();

			ofPushStyle();
			glPushMatrix();


			ofClear(0, 0, 0);
			ofSetColor(255, 255);

			

			l1->draw();

			glPopMatrix();
			ofPopStyle();

			fbo_layer1.end();
		}
		glPopAttrib();


		if (efxA == 1) {
			for (size_t i = 7; i > 0; i--)
			{



				fbo_layer1_efx.begin();
				blurXShader.begin();

				ofPushStyle();
				glPushMatrix();

				ofClear(0, 0, 0);
				ofSetColor(255, 255);

				blurXShader.setUniform1f("blurAmnt", i);
				blurXShader.setUniform1f("glowAmnt", 2);
				blurXShader.setUniformTexture("tex0", fbo_layer1.getTexture(), 1);
				blurXShader.setUniform2f("format", fbo_layer1.getWidth(), fbo_layer1.getHeight());

				fullQuad.draw();


				glPopMatrix();
				ofPopStyle();

				blurXShader.end();
				fbo_layer1_efx.end();


				fbo_layer1.begin();
				blurYShader.begin();

				ofPushStyle();
				glPushMatrix();

				ofClear(0, 0, 0);
				ofSetColor(255, 255);

				blurYShader.setUniform1f("blurAmnt", i);
				blurYShader.setUniform1f("glowAmnt", 2);
				blurYShader.setUniformTexture("tex0", fbo_layer1_efx.getTexture(), 1);
				blurYShader.setUniform2f("format", fbo_layer1_efx.getWidth(), fbo_layer1_efx.getHeight());

				fullQuad.draw();
		


				glPopMatrix();
				ofPopStyle();

				blurYShader.end();
				fbo_layer1.end();

			}
		}

		if (efxB == 1) {
			for (size_t i = 7; i > 0; i--)
			{



				fbo_layer2_efx.begin();
				blurXShader.begin();

				ofPushStyle();
				glPushMatrix();

				ofClear(0, 0, 0);
				ofSetColor(255, 255);

				blurXShader.setUniform1f("blurAmnt", i);
				blurXShader.setUniform1f("glowAmnt", 2);
				blurXShader.setUniformTexture("tex0", fbo_layer2.getTexture(), 1);

				blurXShader.setUniform2f("format", fbo_layer2.getWidth(), fbo_layer2.getHeight());

				fullQuad.draw();


				glPopMatrix();
				ofPopStyle();

				blurXShader.end();
				fbo_layer2_efx.end();


				fbo_layer2.begin();
				blurYShader.begin();

				ofPushStyle();
				glPushMatrix();

				ofClear(0, 0, 0);
				ofSetColor(255, 255);

				blurYShader.setUniform1f("blurAmnt", i);
				blurYShader.setUniform1f("glowAmnt", 2);
				blurYShader.setUniformTexture("tex0", fbo_layer2_efx.getTexture(), 1);
				blurYShader.setUniform2f("format", fbo_layer2_efx.getWidth(), fbo_layer2_efx.getHeight());

				fullQuad.draw();

				//ofDrawRectangle(0, 0, width, height);


				glPopMatrix();
				ofPopStyle();

				blurYShader.end();
				fbo_layer2.end();

			}
		}

		if (flipA == 1) {
			fbo_layer1_efx.begin();
			ofPushStyle();
			glPushMatrix();

			ofClear(0, 0, 0);
			ofSetColor(255, 255);

			fbo_layer1.draw(0,0);

			glPopMatrix();
			ofPopStyle();
			fbo_layer1_efx.end();


			fbo_layer1.begin();
			ofPushStyle();
			glPushMatrix();

			ofClear(0, 0, 0);
			ofSetColor(255, 255);

			ofTranslate(width , height);
			ofRotate(180);
			//ofTranslate(width / 2, height / 2);

			fbo_layer1_efx.draw(0, 0);

			glPopMatrix();
			ofPopStyle();
			fbo_layer1.end();

		}

		if (flipB == 1) {
			fbo_layer2_efx.begin();
			ofPushStyle();
			glPushMatrix();

			ofClear(0, 0, 0);
			ofSetColor(255, 255);

			fbo_layer2.draw(0, 0);

			glPopMatrix();
			ofPopStyle();
			fbo_layer2_efx.end();


			fbo_layer2.begin();
			ofPushStyle();
			glPushMatrix();

			ofClear(0, 0, 0);
			ofSetColor(255, 255);

			ofTranslate(width, height);
			ofRotate(180);
			//ofTranslate(width / 2, height / 2);

			fbo_layer2_efx.draw(0, 0);

			glPopMatrix();
			ofPopStyle();
			fbo_layer2.end();

		}

}

void MainMixer::draw()
{

	shader.begin();
	shader.setUniformTexture("mtex0", fbo_layer1.getTexture(), 1);
	shader.setUniformTexture("mtex1", fbo_layer2.getTexture(), 2);
	shader.setUniform1i("mode", mode);
	shader.setUniform1f("faderA", CLAMP(fader*2, 0.0,1.0));	
	shader.setUniform1f("faderB", CLAMP(((1 - fader) * 2), 0.0, 1.0));
	shader.setUniform1i("invertA", invertA);
	shader.setUniform1i("invertB", invertB);
	shader.setUniform1i("width", width);
	shader.setUniform1i("height", height);
	shader.setUniform1i("submodeA", submodeA);
	shader.setUniform1i("submodeB", submodeB);
	shader.setUniform1i("black", black);

	shader.setUniform1i("tcd", 1);
	fullQuad.draw();

	shader.end();

}
