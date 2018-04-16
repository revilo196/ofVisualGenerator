#include "ParticleGrowTexture.h"

GrowParticle::GrowParticle()
{
}

void GrowParticle::setup(ofVec2f* m_base, ofVec2f m_direction, ofVec2f offset,
	float* directionRotateSpeed, float* offset_rotateSpeed, float* m_radius, float m_timeout, float time, float size )
{
	this->base = m_base;
	this->direction = m_direction;
	this->offset = offset;
	this->directionStart = m_direction;
	this->rotate_direction = directionRotateSpeed;
	this->rotate_offset = offset_rotateSpeed;
	this->radius = m_radius;
	this->time = time;
	this->size = size;
	this->timeout = m_timeout;
	this->position = ofVec2f(0, 0);
	this->positioninv = ofVec2f(0, 0);
	updateInvBase();
}

void GrowParticle::update(float deltatime)
{
	position = position + (direction * deltatime * (*radius));
	positioninv = positioninv + (direction* deltatime * -1 * (*radius));
	offset.rotate((*rotate_offset) * fabs(deltatime));
	direction.rotate((*rotate_direction) * fabs(deltatime));
	time += deltatime;

	//resetTime
	if (time > timeout ) {
		time = 0;

		directionStart = direction;
		updateInvBase();
		position = ofVec2f(0,0);

	}
	else if (time < -timeout) {
		time = 0;
		position = ofVec2f(0, 0);
		directionStart = direction;
		updateInvBase();
		position = baseinv - (*base);
	}

	
}

void GrowParticle::draw() const
{
	float val = (1 - ((time / timeout)));
	if (val >= 0.99) {
		val -= 1;
	}

	val *= 512;
	
	val = CLAMP(val, 0, 255);
	ofSetColor(val);
	ofDrawRectangle((*base) + position +offset , size, size);

	//ofDrawRectangle(baseinv + positioninv + offset , size, size);

	//DebugLine
	//ofVec2f copy = directionStart;
	//copy.rotate((*rotate_direction) * timeout/2);
	//copy.normalize();
	//float d = calcD();
	//ofDrawLine(base, base + copy * d);

/* debug Paths
	for (int j = 30; j < 31; j+=5)
	{


		ofVec2f c2 = offsetstart;
		ofVec2f p1(0, 0);
		for (int i = 0; i < 1800 + 1; i++) {

			ofVec2f p2 = p1 + c2 * (1.0 / 60.0);
			c2.rotate((j) * (1.0 / 60.0));


			ofDrawLine(p1, p2);
			p1 = p2;
		}
		//cout << p1 << endl;
		double rlen = (offsetstart.length()) / (DEG_TO_RAD*j);
		double d = 2 * rlen * sin((DEG_TO_RAD*j) * 3);
		ofVec2f r = offsetstart;
		r = r.rotate(90).normalize() * rlen;

		ofDrawLine(base, r);

	}*/
	
	
	

}

void GrowParticle::updateInvBase()
{
	ofVec2f copy = directionStart;
	copy.rotate((*rotate_direction) * timeout / 2);
	copy.normalize();
	double d = calcD();
	this->baseinv = (*base) + copy * d;
	this->positioninv = ofVec2f(0,0);
}

float GrowParticle::calcD() const
{
	double rlen = (directionStart.length()* (*radius)) / (DEG_TO_RAD*(*rotate_direction));
	double d = 2 * rlen * sin(((DEG_TO_RAD*(*rotate_direction)) / 2) * timeout);
	return d;
}


ParticleGrowTexture::ParticleGrowTexture(string name) : TextureGen(name)
{
	addParameter(speed.set("speed", 1.0, -3, 3));
	addParameter(speedRot.set("speedRotation", 0.05, -0.3, 0.3));
	addParameter(speedX.set("speedX", 0.05, -0.3, 0.3));
	addParameter(speedY.set("speedY", 0.05, -0.3, 0.3));
	addParameter(ampX.set("ampX", .125, 0, 2));
	addParameter(ampY.set("ampY", .252, 0, 2));
	addParameter(radius.set("radius", 1, 0.2, 3));
	addParameter(color);


}


ParticleGrowTexture::~ParticleGrowTexture()
{
}

void ParticleGrowTexture::setup(float width, float height)
{
	TextureGen::setup(width, height);
	
	ofVec2f offset(0.02, 0.02);
	ofVec2f direction(0.1, 0.1);
	float timeout = 4.0f;
	
	for (size_t b = 0; b < 5; b++) {
		base[b] = ofVec2f(0.5, 0.5);
		base[b].rotate((360.0 / 5.0) * b);
		for (size_t i = 0; i < 4; i++) {
			float t = (i / 4.0) * timeout;
			for (size_t j = 0; j < 60; j++) {

				p[b][i][j].setup(&base[b], direction, offset, &rotate_direction, &rotate_offset,&radius_part ,timeout, t, 0.01);
				direction.rotateRad(TWO_PI / 60.0);
				offset.rotateRad(TWO_PI / 4.2456789);

			}
			direction.rotateRad(TWO_PI / 60.0);
			offset.rotateRad(TWO_PI / 4.2456789);
		}
		direction.rotateRad(TWO_PI / 60.0);
		offset.rotateRad(TWO_PI / 4.2456789);
	}

	fbo.allocate(width, height);
}

ofTexture & ParticleGrowTexture::getTextureRef()
{
	return fbo.getTexture();
}

void ParticleGrowTexture::update()
{
	float deltatime = ofGetElapsedTimef() - lasttime;
	lasttime = ofGetElapsedTimef();
	time += (deltatime + speedRot)*0.1;
	timeX += (deltatime + speedX)*0.1;
	timeY += (deltatime + speedY)*0.1;

	this->radius_part = radius;

	
	float xoff = sin(timeX);
	float yoff = sin(timeY);

	ofSetColor(color);
	for (size_t b = 0; b < 5; b++) {


		base[b] = ofVec2f(sin(((TWO_PI / 5.0) * b) + time)*ampX + xoff, cos(((TWO_PI / 5.0) * b) + time)*ampY + yoff);

		for (size_t i = 0; i < 4; i++) {

			for (size_t j = 0; j < 60; j++) {

				p[b][i][j].update(deltatime*speed);

			}

		}
	}

	render();
}


void ParticleGrowTexture::render()
{
	fbo.begin();
	translateMidFlipScale();
	ofClear(0,0,0,255);

	for (size_t b = 0; b < 5; b++) {
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 60; j++) {

				p[b][i][j].draw();

			}

		}
	}

	fbo.end();
}

void ParticleGrowTexture::draw(float x, float y, float w, float h) const
{
	fbo.draw(x, y, w, h);

}

void ParticleGrowTexture::draw(float x, float y) const
{
	fbo.draw(x, y);
}

