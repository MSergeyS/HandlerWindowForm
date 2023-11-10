#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ControlElement.h"

// Define keys:
#define DELETE_KEY 8
#define SIZE_DEFAULT {400, 300}
#define NAME_DEFAULT "NewForm"
#define CLEAR_COLOR Color(150, 150, 150)

using namespace sf;

enum class Type_EC { None, Button, Image, Edit };
using var_t = std::variant<ControlElement*, Button*, ImageN*, Edit*>;

class FormGUI {
public:
	// конструктор класса
	FormGUI(Point size = SIZE_DEFAULT, std::string name = NAME_DEFAULT);
	~FormGUI();

	RenderWindow* GetWindow();

	void SetName(const std::string name);
	void SetSize(const Point size);

	template <typename CtrlElement>
	void AddControlElement(CtrlElement* control_element)
	{
		control_elements_.push_back(std::move(control_element));
		std::pair<ControlElement*, Type_EC> element = GetCE(GetNumberCE()-1);
		int inx;
		switch (element.second) {
		case (Type_EC::Button):
			++count_button_;
			inx = count_button_;
			break;
		case (Type_EC::Image):
			++count_image_;
			inx = count_image_;
			break;
		case (Type_EC::Edit):
			++count_edit_;
			inx = count_edit_;
			break;
		}
		std::string name = element.first->GetName() + std::to_string(inx);
		element.first->SetName(name);
	}

	template<typename CtrlElement>
	CtrlElement GetControlElement(const int inx) const = delete;

	template<>
	Button* GetControlElement(const int inx) const
	{
		Button* result = nullptr;
	    std::pair<ControlElement*, Type_EC> control_element = GetCE(inx);
	    if (control_element.second == Type_EC::Button) {
			result = static_cast<Button*>(control_element.first);
		}
		return result;
	}

	template<>
	ImageN* GetControlElement(const int inx) const
	{
		ImageN* result = nullptr;
		std::pair<ControlElement*, Type_EC> control_element = GetCE(inx);
		if (control_element.second == Type_EC::Image) {
			result = static_cast<ImageN*>(control_element.first);
		}
		return result;
	}

	template<>
	Edit* GetControlElement(const int inx) const
	{
		Edit* result = nullptr;
		std::pair<ControlElement*, Type_EC> control_element = GetCE(inx);
		if (control_element.second == Type_EC::Edit) {
			result = static_cast<Edit*>(control_element.first);
		}
		return result;
	}

	void DeleteControlElement(int inx);

	std::string GetName() const;
	int GetNumberCE() const;

	void DrawControlElement(RenderWindow& window, const Button* control_element) const;
	void DrawControlElement(RenderWindow& window, const ImageN* control_element) const;
	void DrawControlElement(RenderWindow& window, const Edit* control_element) const;

	void ReDraw();
	void fDisplay(RenderWindow* window);
	void fMouseMoved(Point mouse_position);

private:
	RenderWindow* window_;
	Point size_;
	std::string name_;
	std::vector<var_t> control_elements_;
	Edit* select_edit_ = nullptr;
	int count_button_ = 0;
	int count_image_ = 0;
	int count_edit_ = 0;
	
	std::pair<ControlElement*, Type_EC> GetCE(int inx) const;
	void ClearAll();
};



