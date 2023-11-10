#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "FormGUI.h"
#include <memory>
#include "HandlerWindowForm.h"

using namespace sf;

void FillForm(FormGUI* form)
{
    Font font;
    Text text;
    assert(font.loadFromFile("../Galindo-Regular.ttf"));

    // ������ ������
    Point position = { 100, 100 };
    Point size = { 100, 30 };

    Button* button = new Button(position, size);
    button->SetSize(size);
    button->SetRotation(90.0f);
    button->SetFont(font);

    std::cout << form->GetNumberCE() << std::endl;
    form->AddControlElement(button); // ��������� ������ �� �����
    std::cout << form->GetNumberCE() << std::endl;

    // ������ ������
    Button* button1 = new Button({ 200, 200 }, { 100, 50 }, { 0,0 }, 45.0f);
    button1->SetFont(font);

    form->AddControlElement(button1); // ��������� ������ �� �����
    std::cout << form->GetNumberCE() << std::endl;

    // ������ Image
    Texture texture;
    assert(texture.loadFromFile("../a.jpg"));

    ImageN* image = new ImageN({ 500, 300 }, { 100, 50 });
    image->SetFont(font);
    image->SetTexture(texture);
    image->SetRotation(-45.0f);

    form->AddControlElement(image); // ��������� Image �� �����
    std::cout << form->GetNumberCE() << std::endl;

    // ������ Edit
    Edit* edit = new Edit({ 400, 200 }, { 100, 50 });
    edit->SetFont(font);

    form->AddControlElement(edit); // ��������� Edit �� �����
    std::cout << form->GetNumberCE() << std::endl;

    // ������ Edit
    Edit* edit1 = new Edit({ 300, 400 }, { 100, 50 });
    edit1->SetFont(font);

    form->AddControlElement(edit1); // ��������� Edit �� �����
    int inx = form->GetNumberCE() - 1;
    
    edit = form->GetControlElement<Edit*>(inx); //
    edit->SetVisible(false); // ������ ���������

    std::cout << form->GetNumberCE() << std::endl;

    form->DeleteControlElement(0); // ������� ������� � ����� (������ ������)
    std::cout << form->GetNumberCE() << std::endl;

    // ������ ������
    Button* button2 = new Button(position, size);
    button2->SetSize(size);
    button2->SetRotation(90.0f);
    button2->SetFont(font);

    std::cout << form->GetNumberCE() << std::endl;
    form->AddControlElement(button2); // ��������� ������ �� �����
    std::cout << form->GetNumberCE() << std::endl;
}

int main()
{
    HandlerWindowForm handler;
    FormGUI* form1 = handler.AddNewForm();
    FillForm(form1);

    FormGUI* form2 = handler.AddNewForm();
    FillForm(form2);

    handler.ReDraw();

    return 0;
}