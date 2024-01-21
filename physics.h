#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

//global vector
enum VelocityDirection {
	X, Y
};

//Platform class
class Platform {
private:
	RectangleShape platform;

public:
	Platform(Color platformColor, Vector2f platformSize, Vector2f platformPosition);

	RectangleShape& get() { return this->platform; }

	~Platform();
};

//Rigid body class (Rectangle)
class Body {
protected:
	Vector2f window_size = Vector2f(0.0, 0.0);
	int collisions = 0;

private:
	Vector2f position = Vector2f(0.0f, 0.0f);
	Vector2f velocity = Vector2f(0.0f, 0.0f);
	Vector2f acceleration = Vector2f(0.0f, 0.0f);
	RectangleShape object;
	float mass = 0.0f;
	Vector2f dir = Vector2f(0.0, 0.0);
	Vector2f momentum = Vector2f(0.0, 0.0);
	bool trails = false;
	std::vector<RectangleShape> trailRects;
	bool pauseB = false;

	void deaccelerate(float dt = 1);
	void gravity(float dt);
	RectangleShape drawTrailRect();
	Vector2f normalizeVector(Vector2f vector) { vector = Vector2f(0.0, 0.0); return vector; }
	RectangleShape deleteRectangle(RectangleShape rect);

public:
	Body(float mass, Vector2f init_velocity, Vector2f position, Vector2f window_size = Vector2f(640, 480));

	//void functions
	void accelerate(Vector2f accleration);
	void setTrail(bool visible);
	void update(float deltaTime);
	void drawRenderTargets(RenderWindow& window);
	void respectPlatform(Platform platform);
	void setPosition(Vector2f position) { this->position = position; }
	void pause(bool pause = false);
	//returning functions
	Vector2f getSize() { return object.getSize(); }
	Vector2f getPosition() { return object.getPosition(); }
	String getVelocity(VelocityDirection velocitydir);

	~Body();
};

#endif