#include "ParticleSystem.h"


ParticleSystem::ParticleSystem(size_t count, string name) : VjObject(name)
{
	this->count = count;

	//Create arrays for the VBO
	vertex = new ofVec3f[count];
	color = new ofFloatColor[count];
	indices = new ofIndexType[count*3];

	//init indices not uses we only draw points but needed for the shader
	for (int i = 0; i < count*3; i++)
	{
		indices[i] = i % count;
	}

	//add Parameter to the VjObject
	addParameter(speed.set("speed", 0.002, -0.05, 0.05));
	addParameter(forceAmplitude.set("force", 1,-3,3));
	addParameter(scale.set("scale", 1.0, 0.1, 5));
	addParameter(partVel.set("Particle Velocity", 0.20, 0.05, 0.7));
	addParameter(add.set("add particle",false));
	addParameter(remove.set("remove Particle",false));
}


ParticleSystem::~ParticleSystem()
{
	delete[] vertex;
	delete[] color;
	delete[] indices;
}

void ParticleSystem::update()
{
	
	//go foreward in time
	time += speed;
	m_partVel = partVel;
	//update every particle
	for (int i = 0; i < system.size(); i++) {
		//applyForce to this particle acording to PerlinNoiseVectorfield
		system[i].applyForceNoise(forceAmplitude, scale);
		//update this particle
		system[i].update();
	}

	//update the vertexBufferObject
	vbo.updateVertexData(&vertex[0], count);
	vbo.updateColorData(&color[0], count);
}

void ParticleSystem::draw(float x, float y, float w, float h) const
{
	draw(0, 0);
}

void ParticleSystem::draw(float x, float y) const
{
	ofCamera cam;
	cam.begin();

	//draw every single particle
	//for (int i = 0; i < system.size(); i++) {
	//	system[i].draw();
	//}


	//draw all particles with one VertexBufferObject and Geometry shader
	glPointSize(10.f);
	shader.begin();
	vbo.drawElements(GL_POINTS, count);
	shader.end();
	cam.end();

}

void ParticleSystem::setup(float width, float height)
{
		this->height = height;
		this->width = width;

		//load shader
		shader.load("particle.vert", "particle.frag", "particle.geom");

		//init vertex buffer object
		vbo.setVertexData(&vertex[0], count, GL_DYNAMIC_DRAW);
		vbo.setColorData(&color[0], count, GL_DYNAMIC_DRAW);
		vbo.setIndexData(&indices[0], count, GL_DYNAMIC_DRAW);

		//init the particles and conenct them to the vertex array
		system.resize(count);
		for (int i = 0; i < count; i++) {
			system[i] = Particle();
			vertex[i] = ofVec3f(ofRandomf() * 40, ofRandomf() * 40, -10 - ofRandomuf() * 80);
			system[i].setup(&vertex[i],&color[i],ofVec3f(40,40,-20), ofVec3f(-40,-40,-95), &time,&m_partVel);
		}

}

void Particle::update()
{

	if (vel.lengthSquared() > 0.1) {
		this->vel += (acc) - (vel.normalize()*(vel.lengthSquared())*(0.4));
	} else {
		this->vel += acc;
	}
	 
	if(vel.length() > 3) 
	{
		vel = vel.normalize() * 3;
	}

	(*this->pos) += vel*(*velfac);
	this->acc = acc * 0;

	this->vrt += art; // TODO max / damping
	this->rot += vrt;
	this->art = art * 0;

	//--- position is Out of Bounds
	// --->Reset to random position on opposite plane
	if (pos->x < posMin.x) {
		pos->x = posMax.x;
		pos->y = ofMap(ofRandomf(), -1, 1, posMin.y, posMax.y);
		pos->z = ofMap(ofRandomf(), -1, 1, posMin.z, posMax.z);

	}
	if (pos->y < posMin.y) {
		pos->y = posMax.y;
		pos->x = ofMap(ofRandomf(), -1, 1, posMin.x, posMax.x);
		pos->z = ofMap(ofRandomf(), -1, 1, posMin.z, posMax.z);
	}
	if (pos->z < posMin.z) {
		pos->z = posMax.z;
		pos->x = ofMap(ofRandomf(), -1, 1, posMin.x, posMax.x);
		pos->y = ofMap(ofRandomf(), -1, 1, posMin.y, posMax.y);
	}
	if (pos->x > posMax.x) {
		pos->x = posMin.x;
		pos->y = ofMap(ofRandomf(), -1, 1, posMin.y, posMax.y);
		pos->z = ofMap(ofRandomf(), -1, 1, posMin.z, posMax.z);
	}
	if (pos->y > posMax.y) {
		pos->y = posMin.y;
		pos->x = ofMap(ofRandomf(), -1, 1, posMin.x, posMax.x);
		pos->z = ofMap(ofRandomf(), -1, 1, posMin.z, posMax.z);
	}
	if (pos->z > posMax.z) {
		pos->z = posMin.z;
		pos->x = ofMap(ofRandomf(), -1, 1, posMin.x, posMax.x);
		pos->y = ofMap(ofRandomf(), -1, 1, posMin.y, posMax.y);
	}

	//calculate color from distance from the mid
	ofVec3f r = (*pos) - midVec;
	float dist = (1 - (r.lengthSquared() / (midVec.lengthSquared()*0.3)));
	color->a = MAX(MIN(dist, 1),0);
}

void Particle::setup(ofVec3f * pos, ofFloatColor * color, ofVec3f posMax, ofVec3f posMin, float *time, float *sair)
{
	this->pos = pos;
	this->color = color;
	this->posMax = posMax;
	this->posMin = posMin;

	 midVec = (posMin + posMax) / 2;
	 this->time = time;
	 this->velfac = sair; 
}

void Particle::draw() const
{
	ofVec3f r = (*pos) - midVec;
	float dist = (1-(r.lengthSquared()/(midVec.lengthSquared()*0.3)))*255;

	//ofSetColor(fabs(vel.x)*255, fabs(vel.y)*255,fabs(vel.z)*255,MAX(MIN(dist,255),0));
	//float red = MIN(fabs(vel.x) * 255, 255);
	//float green = MIN(fabs(vel.y) * 255, 255);
	//float blue = MIN(fabs(vel.z) * 255, 255);
	//ofSetColor(red, green, blue, MAX(MIN(dist, 255), 0));
	ofSetColor(255, 255, 255, MAX(MIN(dist, 255),0));

	ofDrawBox((*pos), 1);;
}

void Particle::applyForce(ofVec3f force)
{
	acc += force;
}

void Particle::applyForceRot(ofVec3f force)
{
	art += force;
}

void Particle::applyForceNoise(float amp, float mscale)
{
	float scale = 30 *mscale;
	float x = 1-(ofNoise(pos->x / scale, pos->y / scale, pos->z / scale, 1.0 + (*time))*2);
	float y = 1-(ofNoise(pos->x / scale, pos->y / scale, pos->z / scale, 1000.0 + (*time))*2);
	float z = 1-(ofNoise(pos->x / scale, pos->y / scale, pos->z / scale, -1000.0 + (*time))*2);

	ofVec3f force = ofVec3f(x, y, z)*amp;
	applyForce(force*2);

}

void Particle::setVelocity(ofVec3f vel)
{
	this->vel = vel;
}

void Particle::setVelocityRot(ofVec3f velRot)
{
	this->vrt = velRot;
}

ofVec3f Particle::getPos()
{
	return rot;
}

ofVec3f Particle::getRot()
{
	return rot;
}


//----------------WIP----------------------------


QubeTree::QubeTree(BoxContainer bound, int cap)
{
	this->boundary = bound;
	this->cap = cap;
}

QubeTree::~QubeTree()
{
	if (subdivided) {
		delete nwf;
		delete nef;
		delete sef;
		delete swf;
		delete nwb;
		delete neb;
		delete seb;
		delete swb;
	}
}

void QubeTree::insert(ofVec3f point)
{
	if (this->points.size() < this->cap) {
		this->points.push_back(point);
	}
	else {
		this->subdivide();
	}
}

void QubeTree::subdivide()
{
	ofVec3f min = boundary.cubemin;
	ofVec3f max = boundary.cubemax;
	ofVec3f mid = (boundary.cubemin + boundary.cubemax) / 2;
	/*
	nwf = new QubeTree(BoxContainer(mid, max),4);
	nef = new QubeTree(BoxContainer(ofVec3f(min.x, mid.y, mid.z),ofVec3f(mid.x,max.y,max.z)),4);
	sef = new QubeTree(BoxContainer(ofVec3f(min.x, min.y, mid.z), ofVec3f(mid.x, mid.y, max.z)), 4);
	swf = new QubeTree();
	nwb = new QubeTree();
	neb = new QubeTree();
	seb = new QubeTree(BoxContainer(min, mid, 4);
	swb = new QubeTree();*/
}

BoxContainer::BoxContainer(ofVec3f cubemin, ofVec3f cubemax)
{
	this->cubemin = cubemin;
	this->cubemax = cubemax;
}

bool BoxContainer::contains(ofVec3f point)
{
	if (point.x < cubemin.x || point.y < cubemin.y || point.z < cubemin.z
		|| point.x > cubemax.x || point.y > cubemax.y || point.z > cubemax.z)
		return false; //is not within cube
	return true; //is within cube
}
