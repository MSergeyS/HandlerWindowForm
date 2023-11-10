#include "HandlerWindowForm.h"

HandlerWindowForm::~HandlerWindowForm()
{
    ClearAll();
}

FormGUI* HandlerWindowForm::AddNewForm()
{  
    // создаём новую форму
    FormGUI* form = new FormGUI(SIZE_WINDOW_DEFAULT);
    ++count_form_;
    form->SetName("Form" + std::to_string(count_form_));
    gui_forms_.push_back(form);
    return form;
}

void HandlerWindowForm::DeleteForm(int inx)
{
    delete gui_forms_.at(inx);
    gui_forms_.erase(gui_forms_.begin() + inx);
}

bool HandlerWindowForm::CheckOpenWindows()
{
    return true;
}

void HandlerWindowForm::ClearAll()
{
    if (GetNumberForms() == 0) {
        return;
    }
    for (int inx = GetNumberForms() - 1; inx < 0; inx--) {
        DeleteForm(inx);
    }
}

void HandlerWindowForm::ReDraw()
{
    bool windows_is_open = CheckOpenWindows();
    while (windows_is_open)
    {
        for (FormGUI* form : gui_forms_) {
            form->ReDraw();
        }
    }
}

int HandlerWindowForm::GetNumberForms()
{
    return gui_forms_.size();
}
