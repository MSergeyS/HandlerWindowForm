#include "ControlElement.h"

#include <cassert>

using namespace sf;

ControlElement::ControlElement() = default;
ControlElement::~ControlElement() = default;

void ControlElement::SetName(const std::string name)
{
    name_ = name;
}

void ControlElement::SetPosition(const Point position)
{
    position_ = position;
    ReDraw();
}

void ControlElement::SetSize(const Point size)
{
    size_ = size;
    ReDraw();
}

void ControlElement::SetPivotPoint(const Point pivot_point)
{
    pivot_point_ = pivot_point;
    ReDraw();
}

void ControlElement::SetRotation(const float rotation)
{
    rotation_ = rotation;
    ReDraw();
}

void ControlElement::SetVisible(const bool visible)
{
    visible_ = visible;
    ReDraw();
}

void ControlElement::SetText(const std::string text)
{
    text_.setString(text);
    DrawText();
}

void ControlElement::SetFont(const Font font)
{
    font_ = font;
    DrawText();
}

void ControlElement::SetColor(const Color color)
{
    color_shape_ = color;
    DrawShape();
}

void ControlElement::SetSelected(const bool sel)
{
    is_selected_ = sel;
    IsSelect();
    DrawShape();
}

std::string  ControlElement::GetName() const
{
    return name_;
}

Point ControlElement::GetPosition() const
{
    return position_;
}


Point ControlElement::GetSize() const
{
    return size_;
}


Point ControlElement::GetPivotPoint() const
{
    return pivot_point_;
}

float ControlElement::GetRotation() const
{
    return rotation_;
}
bool ControlElement::GetVisible() const
{
    return visible_;
}

Text ControlElement::GetText() const
{
    return text_;
}


RectangleShape ControlElement::GetShape() const
{
    return shape_;
}

const Font* ControlElement::GetFont() const
{
    return text_.getFont();
}

bool ControlElement::GetSelected() const
{
    return is_selected_;
}

void ControlElement::DrawText()
{
    // https://eeprogrammer.wordpress.com/2015/03/27/sfml-draw-image-and-text/
    text_.setFillColor(Color::Black);
    text_.setCharacterSize(24);
    text_.setStyle(Text::Bold);
    text_.setPosition(position_.x, position_.y);
    text_.setFont(font_);
    float rotation = text_.getRotation();
    text_.rotate(-rotation);
    text_.rotate(rotation_);
}

void ControlElement::DrawShape()
{
    shape_.setSize({ float(size_.x), float(size_.y) });
    shape_.setFillColor(color_shape_);
    shape_.setPosition(position_.x, position_.y);
    float rotation = shape_.getRotation();
    shape_.rotate(-rotation);
    shape_.rotate(rotation_);
}

void ControlElement::ReDraw()
{
    DrawShape();
    DrawText();
}

// Проверяем находится ли курсор мышки в пределах управляющего элемента
bool ControlElement::isMouseOver(Point mouse_position)
{
    auto shape_region = shape_.getGlobalBounds();
    int position_x = shape_region.left + shape_region.width;
    int position_y = shape_region.top + shape_region.height;


    if (mouse_position.x < position_x &&
        mouse_position.x > shape_region.left &&
        mouse_position.y < position_y &&
        mouse_position.y > shape_region.top) {
        return true;
    }
    return false;
}

void ControlElement::IsSelect()
{

}

// Bottom --------------------------------------------------

Button::Button(Point position, Point size, Point pivot_point,
               float rotation, std::string text, bool visible)
{
    position_ = position;
    size_ = size;
    pivot_point_ = pivot_point;
    rotation_ = rotation;
    text_.setString(text);
    visible_ = visible;
    name_ = BUTTON_NAME_DEFAULT;

    ReDraw();
}

bool Button::PushButton()
{
    state_ = !state_;
    return state_;
}

bool Button::GetState()
{
    return state_;
}

void Button::ReDraw()
{
    DrawShape();
    DrawText();
}

// Image --------------------------------------------------

ImageN::ImageN(Point position, Point size, Point pivot_point,
               float rotation, std::string text, bool visible)
{
    position_ = position;
    size_ = size;
    pivot_point_ = pivot_point;
    rotation_ = rotation;
    text_.setString(text);
    visible_ = visible;
    name_ = IMAGE_NAME_DEFAULT;

    ReDraw();
}

void ImageN::SetTexture(Texture texture)
{
    texture_ = texture;
    image_.setTexture(texture_);
    Vector2u size = texture_.getSize();
    size_ = { int(size.x), int(size.y) };
}

Sprite ImageN::GetImage() const
{
    return image_;
}

void ImageN::DrawImage()
{
    image_.setPosition(GetPosition().x, GetPosition().y);
    image_.rotate(rotation_);
}

void ImageN::ReDraw()
{
    DrawShape();
    DrawImage();
    DrawText();
}

// Edit --------------------------------------------------------

Edit::Edit(Point position, Point size, Point pivot_point,
    float rotation, std::string text, bool visible)
{
    position_ = position;
    size_ = size;
    pivot_point_ = pivot_point;
    rotation_ = rotation;
    text_.setString(text);   
    text_.setCharacterSize(12);
    visible_ = visible;
    name_ = EDIT_NAME_DEFAULT;

    ReDraw();
}

void Edit::typedOn(Event input) {
    if (is_selected_) {
        int charTyped = input.text.unicode;

        if (charTyped < 128) {
            inputLogic(charTyped);
        }
    }
}

// удаляем последний символ:
void Edit::deleteLastChar() {
    std::string t = ostream_.str();
    std::string newT = "";
    for (int i = 0; i < t.length() - 1; i++) {
        newT += t[i];
    }
    ostream_.str("");
    ostream_ << newT;
    text_.setString(ostream_.str() + "_");
}

void Edit::inputLogic(int charTyped) {
    if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
        ostream_ << static_cast<char>(charTyped);
    }
    else if (charTyped == DELETE_KEY) {
        if (ostream_.str().length() > 0) {
            deleteLastChar();
        }
    }
    text_.setString(ostream_.str() + "_");
}

void Edit::ReDraw()
{
    DrawShape();
    DrawText();
}

void Edit::IsSelect()
{
    if (is_selected_) {
        text_.setString(ostream_.str() + "_");
    }
    else {
        std::string t = ostream_.str();
        std::string newT = "";
        for (int i = 0; i < t.length(); i++) {
            newT += t[i];
        }
        text_.setString(newT);
    }
}
