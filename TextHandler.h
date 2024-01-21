#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <SFML/Graphics.hpp>
using namespace sf;

enum PositionAlignment {
	CENTERED,
	U_LEFT,
	U_RIGHT,
	D_LEFT,
	D_RIGHT
};

class TextHandler {
private:
	Text text;
	Font font;
	Vector2f initialPosition = Vector2f(0.0, 0.0);
	unsigned int initialCharacterSize = 0;

public:
	TextHandler(const char* fontPath, Vector2f textPosition = Vector2f(0.0, 0.0), unsigned int characterSizePixels = 24, Color fillColor = Color::White, Text::Style textStyle = Text::Regular);
	TextHandler(const char* fontPath, String string, Vector2f textPosition = Vector2f(0.0, 0.0), unsigned int characterSizePixels = 24, Color fillColor = Color::White, Text::Style textStyle = Text::Regular);
	TextHandler(const char* fontPath, String string, PositionAlignment alignment, Vector2f window_size, unsigned int characterSizePixels = 24, Color fillColor = Color::White, Text::Style textStyle = Text::Regular);

	void setVisible(bool visible);
	void setFillColor(Color color);
	void setStyle(Text::Style style);
	void setSize(unsigned int characterSizePixels);
	void setString(String string);
	void setPosition(Vector2f position);
	Vector2f getPosition() { return text.getPosition(); }
	Vector2f getSizeInPixels() { return Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height); }
	Text& getTextRender() { return text; }
};

#endif