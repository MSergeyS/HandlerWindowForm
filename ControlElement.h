#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define COLOR_DEFAULT {200, 200, 200}

#define BUTTON_NAME_DEFAULT "Button"
#define EDIT_NAME_DEFAULT "Edit"
#define IMAGE_NAME_DEFAULT "Image"

using namespace sf;

struct Point {
	int x = 0;
	int y = 0;
};


class ControlElement {
public:
	// конструктор класса Control
	ControlElement();
	~ControlElement();

	void SetName(const std::string name);
	void SetPosition(const Point position);
	void SetSize(const Point size);
	void SetPivotPoint(const Point pivot_point);
	void SetRotation(const float rotation);
	void SetVisible(const bool visible);
	void SetText(const std::string text);
	void SetFont(const Font font);
	void SetColor(const Color color = COLOR_DEFAULT);
	void SetSelected(const bool sel);
	
	std::string GetName() const;
	Point GetPosition() const;
	Point GetSize() const;
	Point GetPivotPoint() const;
	float GetRotation() const;
	bool GetVisible() const;
	Text GetText() const;
	RectangleShape GetShape() const;
	const Font* GetFont() const;
	bool GetSelected() const;

	virtual void ReDraw();

	bool isMouseOver(Point mouse_position);

protected:
	std::string name_;
	Point position_ = {0, 0};
	Point size_= {0, 0};
	Point pivot_point_ = {0, 0};
	float rotation_ = 0.0f;
	Color color_shape_ = COLOR_DEFAULT;
	bool visible_ = true;
	bool is_selected_ = false;
	Font font_;
	Text text_;
	RectangleShape shape_;

	// графика
	void DrawShape();
    void DrawText();


	virtual void IsSelect();
};

class Button : public ControlElement
{
public:
	Button(Point position = { 0, 0 },
		   Point size = {10, 10},
		   Point pivot_point = { 0, 0 },
		   float rotation = 0.0f,
		   std::string text = "button",
		   bool visible = true);
    
	bool PushButton();
	bool GetState();

	void ReDraw() override;

private:
	bool state_ = false;
};

class ImageN : public ControlElement
{
public:
	ImageN(Point position = { 0, 0 },
		   Point size = { 10, 10 },
		   Point pivot_point = { 0, 0 },
		   float rotation = 0.0f,
		   std::string text = "image",
		   bool visible = true);

	void SetTexture(Texture texture);
	Sprite GetImage() const;

	void ReDraw() override;

private:
	Texture texture_;
	Sprite image_;

	// графика
	void DrawImage();
};

class Edit : public ControlElement
{

public:
	Edit(Point position = { 0, 0 },
		 Point size = { 10, 10 },
		 Point pivot_point = { 0, 0 },
		 float rotation = 0.0f,
		 std::string text = "Edit",
		 bool visible = true);

	void typedOn(Event input);

	void ReDraw() override;

private:
	std::ostringstream ostream_;

	void deleteLastChar();
	void inputLogic(int charTyped);

	void IsSelect();
};