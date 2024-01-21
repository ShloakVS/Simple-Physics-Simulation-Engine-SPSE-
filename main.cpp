#include <SFML/Graphics.hpp>
using namespace sf;

//Custom libraries
#include <physics/physics.h>
#include <API/TextHandler.h>

//Window Data
const char* windowTitle = "Simple Physics Simulation Engine (S.P.S.E)";
const VideoMode windowSize = VideoMode(1000, 500);
const auto windowStyle = Style::Default;

int main() {
	//Window Icon
	Image icon;
	icon.loadFromFile("assets/images/icon.png");
	//Window
	RenderWindow window(windowSize, windowTitle, windowStyle);
	//Set window icon
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	//Body
	Body body(1.0f, Vector2f(0.0, 0.0), Vector2f(10.0f, 50.0f), Vector2f((float)windowSize.width, (float)windowSize.height));
	body.setTrail(true);

	//Platform 
	Platform platform(Color::White, Vector2f(50, 10), Vector2f(50, 200));

	//Text Handler for main screen
	TextHandler splashText("assets/fonts/arial_rounded.ttf", "Press F2 to start/pause\nPress F1 to hide/show trails\nPress F5 to position object", PositionAlignment::CENTERED, Vector2f(windowSize.width, windowSize.height));

	//Text for velocity
	TextHandler velocityX("assets/fonts/arial_rounded.ttf", Vector2f(0.0, 0.0));
	//set a starting text to make the alignments proper
	velocityX.setString("Velocity X: 999999.00000000");
	TextHandler velocityY("assets/fonts/arial_rounded.ttf", Vector2f(0.0, 5 + velocityX.getPosition().y + velocityX.getSizeInPixels().y));

	//Event
	Event event;
	//last iteration
	bool isOpen = true;
	//Delta time
	Clock deltaClock;
	Time deltaTime;
	//Start handle
	bool started = false;
	//Paused?
	bool paused = true;
	//Positioning mode
	bool positioningMode = false;
	//trails enable
	bool trailsEnabled = false;
	//main loop
	while (isOpen) {
		//delta time
		deltaTime = deltaClock.restart();
		//pollevents
		while (window.pollEvent(event)) {
			//quit event
			if (event.type == Event::Closed)
				isOpen = false;
			else if (Keyboard::isKeyPressed(Keyboard::F2)) {
				if (paused) {
					//pause is false
					paused = false;
					//start the handle
					started = true;
					//Hide splash text
					splashText.setVisible(false);
				}
				else {
					//paused is true
					paused = true;
					//stop the handle
					started = false;
					//Show splash text
					splashText.setVisible(true);
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::F1)) {
				if (trailsEnabled) {
					//disable trails if true
					trailsEnabled = false;
					//set trails enabled in body class
					body.setTrail(trailsEnabled);
				}
				else {
					//enable trials
					trailsEnabled = true;
					//set trails disabled in body class
					body.setTrail(trailsEnabled);
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::F5)) {
				if (positioningMode) {
					//pause is false
					positioningMode = false;
					//start physics
					body.pause(false);
				}
				else {
					//paused is true
					positioningMode = true;
					//stop physics
					body.pause(true);
					//set position
					body.setPosition(Vector2f(Mouse::getPosition(window).x - (body.getSize().x / 2), Mouse::getPosition(window).y - (body.getSize().y / 2)));
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				//accelerate x
				body.accelerate(Vector2f(0.0, 1.0));
			}
			else if (Keyboard::isKeyPressed(Keyboard::RShift)) {
				//acclerate y
				body.accelerate(Vector2f(1.0, 0.0));
			}
			else if (Keyboard::isKeyPressed(Keyboard::LShift)) {
				//acclerate y
				body.accelerate(Vector2f(-1.0, 0.0));
			}
		}
		//update physics
		if (started) {
			//physics
			body.update(deltaTime.asSeconds());
		}
		//update the position of the object in positioning mode
		if (positioningMode) {
			//set the object centre to the mouse cursor position relative to the window
			body.setPosition(Vector2f(Mouse::getPosition(window).x - (body.getSize().x / 2), Mouse::getPosition(window).y - (body.getSize().y / 2)));
		}
		//window clear
		window.clear();

		//window draw
		body.drawRenderTargets(window);
		window.draw(splashText.getTextRender());
		//platform draw
		window.draw(platform.get());
		body.respectPlatform(platform);
		//update velocity text
		velocityX.setString(body.getVelocity(X));
		velocityY.setString(body.getVelocity(Y));
		//draw velocity text
		window.draw(velocityX.getTextRender());
		window.draw(velocityY.getTextRender());

		//window display
		window.display();
	}

	//Clean up
	window.close();
	return 0;
}