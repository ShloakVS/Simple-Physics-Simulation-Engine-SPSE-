#include <physics/physics.h>




//platform class
Platform::Platform(Color platformColor, Vector2f platformSize, Vector2f platformPosition) {
	this->platform.setFillColor(platformColor);
	this->platform.setPosition(platformPosition);
	this->platform.setSize(platformSize);
}

Platform::~Platform() {
	//cleanup
}




//body class
Body::Body(float mass, Vector2f init_velocity, Vector2f position, Vector2f window_size) : mass(mass), velocity(init_velocity), position(position), window_size(window_size) {
	object.setPosition(position);
	object.setSize(Vector2f(20.0f, 20.0f));
	dir = Vector2f(1.0, 1.0);
}

void Body::accelerate(Vector2f acceleration) {
	this->acceleration.x += acceleration.x;
	this->acceleration.y += acceleration.y * -1;
}

void Body::setTrail(bool visible) {
	if (visible) {
		trails = true;
	}
	else trails = false;
}

void Body::deaccelerate(float dt) {
	if (acceleration.x > 0) {
		acceleration.x -= (0.9 * dt);
	}
	else if (acceleration.x < 0) {
		acceleration.x += (0.9 * dt);
	}
	//rounding off velocity to zero
	if ((acceleration.x < 0.001 && acceleration.x > -0.001)) {
		acceleration.x = 0;
		velocity.x = acceleration.x;
	}
}

void Body::gravity(float dt) {
	if (((object.getPosition().y + object.getSize().y) < window_size.y)) {
		acceleration.y += 9.8 * dt;
	}
	if ((object.getPosition().y + object.getSize().y) >= window_size.y) {
		acceleration.y = (acceleration.y - acceleration.y);
		velocity.y = acceleration.y;
		object.setPosition(Vector2f(object.getPosition().x, window_size.y - object.getSize().y));
	}
}

RectangleShape Body::drawTrailRect() {
	RectangleShape trail;
	trail.setSize(Vector2f(2.0, 2.0));
	trail.setPosition(Vector2f(object.getPosition().x + object.getSize().x / 2, object.getPosition().y + object.getSize().y / 2));
	trail.setFillColor(Color::Red);
	return trail;
}

RectangleShape Body::deleteRectangle(RectangleShape rect)
{
	rect.setPosition(Vector2f(0.0, 0.0));
	rect.setSize(Vector2f(0.0, 0.0));
	rect.setFillColor(Color::Black);
}

void Body::update(float deltaTime) {
	if (!pauseB) {
		velocity = acceleration;
		velocity = Vector2f(velocity.x * dir.x, velocity.y * dir.y);

		if ((object.getPosition().x) >= (window_size.x - object.getSize().x)) {
			dir.x = -1;
		}
		else if (object.getPosition().x <= 0) {
			if (velocity.x < 0) {
				dir.x = 1;
				velocity.x = abs(velocity.x);
			}
			else dir.x = 1;
		}
		if (velocity.x == 0) {
			dir.x = 1;
		}
		position += velocity;
		object.setPosition(position);
		deaccelerate(deltaTime);
		gravity(deltaTime);
		//trails
		if (trails) {
			trailRects.push_back(drawTrailRect());
		}
		else if (!trails) {
			trailRects.clear();
		}
	}
	else {
		normalizeVector(velocity);
		normalizeVector(acceleration);
		dir = Vector2f(1.0, 1.0);
	}
}

void Body::pause(bool pause) {
	if (pause) {
		this->pauseB = true;
	}
	else this->pauseB = false;
}

void Body::drawRenderTargets(RenderWindow& window) { 
	if (!trails) {
		window.draw(object);
	}
	else {
		for (RectangleShape i : trailRects)
			window.draw(i);
		window.draw(object);
	}
}

void Body::respectPlatform(Platform platform) {
	if ((this->object.getPosition().x + this->object.getSize().x) >= platform.get().getPosition().x && (this->object.getPosition().y) >= platform.get().getPosition().y && this->object.getPosition().y <= (platform.get().getPosition().y + platform.get().getSize().y)) {
		//object touched the left side of the platform
		this->dir.x *= -1;
	}
}

String Body::getVelocity(VelocityDirection velocityDirection) {
	if (velocityDirection == VelocityDirection::X) {
		return ("Velocity X:" + std::to_string(velocity.x));
	}
	else if (velocityDirection == VelocityDirection::Y) {
		if (velocity.y < 0) {
			return ("Velocity Y:" + std::to_string(std::abs(velocity.y)));
		}
		else if (velocity.y > -1 && velocity.y != 0) {
			return ("Velocity Y:" + std::to_string((velocity.y * -1)));
		}
		else if (velocity.y == 0) {
			std::string velocityY = std::to_string(velocity.y);
			velocityY.erase(remove(velocityY.begin(), velocityY.end(), '-'), velocityY.end());
			return ("Velocity Y:" + velocityY);
		}
	}
}

Body::~Body() {
	this->object.setPosition(Vector2f(0.0, 0.0));
	this->object.setSize(Vector2f(0.0, 0.0));
	this->velocity = Vector2f(0.0, 0.0);
	this->position = Vector2f(0.0, 0.0);
	this->mass = 0.0f;
	this->collisions = 0;
	this->dir = Vector2f(0.0, 0.0);
	//this->trailRects.clear();
	this->window_size = Vector2f(0.0, 0.0);
	this->momentum = Vector2f(0.0, 0.0);
}