#include <API/TextHandler.h>

TextHandler::TextHandler(const char* fontPath, Vector2f textPosition, unsigned int characterSizePixels, Color fillColor, Text::Style textStyle) {
	this->font.loadFromFile(fontPath);
	this->text.setFont(this->font);
	this->text.setCharacterSize(characterSizePixels);
	this->text.setFillColor(fillColor);
	this->text.setStyle(textStyle);
	this->text.setPosition(textPosition);
	this->initialPosition = textPosition;
	this->initialCharacterSize = characterSizePixels;
}

TextHandler::TextHandler(const char* fontPath, String string, Vector2f textPosition,  unsigned int characterSizePixels, Color fillColor, Text::Style textStyle) {
	this->font.loadFromFile(fontPath);
	this->text.setFont(this->font);
	this->text.setCharacterSize(characterSizePixels);
	this->text.setFillColor(fillColor);
	this->text.setStyle(textStyle);
	this->text.setString(string);
	this->text.setPosition(textPosition);
	this->initialPosition = textPosition;
	this->initialCharacterSize = characterSizePixels;
}

TextHandler::TextHandler(const char* fontPath, String string, PositionAlignment alignment, Vector2f window_size, unsigned int characterSizePixels, Color fillColor, Text::Style textStyle) {
	this->font.loadFromFile(fontPath);
	this->text.setFont(this->font);
	this->text.setCharacterSize(characterSizePixels);
	this->text.setFillColor(fillColor);
	this->text.setStyle(textStyle);
	this->text.setString(string);
	//text alignmment
	switch (alignment) {
	case PositionAlignment::CENTERED : {
		this->initialPosition = Vector2f((window_size.x / 2) - (this->text.getGlobalBounds().width / 2), (window_size.y / 2) - (this->text.getGlobalBounds().height / 2));
		break;
	}
	case PositionAlignment::D_LEFT: {
		this->initialPosition = Vector2f(0.0, (window_size.y - this->text.getGlobalBounds().height));
		break;
	}
	case PositionAlignment::D_RIGHT: {
		this->initialPosition = Vector2f((window_size.x - this->text.getGlobalBounds().width), (window_size.y - this->text.getGlobalBounds().height));
		break;
	}
	case PositionAlignment::U_LEFT: {
		this->initialPosition = Vector2f(0.0, 0.0);
		break;
	}
	case PositionAlignment::U_RIGHT: {
		this->initialPosition = Vector2f((window_size.x - this->text.getGlobalBounds().width), 0.0);
		break;
	}
	default: {
		this->initialPosition = Vector2f(0.0, 0.0);
	}
	}
	this->text.setPosition(this->initialPosition);
	this->initialCharacterSize = characterSizePixels;
}

void TextHandler::setVisible(bool visible) {
	if (visible) {
		this->text.setPosition(this->initialPosition);
		this->text.setCharacterSize(this->initialCharacterSize);
	}
	else {
		this->text.setPosition(Vector2f(-1000.0, -1000.0));
		this->text.setCharacterSize(0);
	}
}

void TextHandler::setFillColor(Color color) {
	this->text.setFillColor(color);
}

void TextHandler::setStyle(Text::Style style) {
	this->text.setStyle(style);
}

void TextHandler::setSize(unsigned int characterSizePixels) {
	this->text.setCharacterSize(characterSizePixels);
}

void TextHandler::setString(String string) {
	this->text.setString(string);
}

void TextHandler::setPosition(Vector2f position) {
	this->text.setPosition(position);
}