#pragma once

#include <SFML/Graphics.hpp>
#include "FormGUI.h"

#define SIZE_WINDOW_DEFAULT { 1000, 700 }

class HandlerWindowForm
{
public:
	// конструктор класса ControlElement
	HandlerWindowForm() = default;
	~HandlerWindowForm();

	FormGUI* AddNewForm();
	void DeleteForm(int inx);

	void ReDraw();

	int GetNumberForms();

private:
	std::string name_;
	std::vector<FormGUI*> gui_forms_;
	int count_form_ = 0;

	bool CheckOpenWindows();
	void ClearAll();
};

