#include "FormGUI.h"
#include <cassert>

FormGUI::FormGUI(Point size, std::string name)
    : size_(size), name_(name)
{
    //// Переменной window назначен тип графическое окно ( RenderWindow )
    //// Параметр VideoMode ( 1500, 900 ), определяет размер графического окна по горизонтали 1500 и по вертикали 900
    //// L"Новый проект" - название графического окна
    //// Style::Default - стиль окна по умолчанию.

    window_ = new RenderWindow(VideoMode(size_.x, size_.y), name, Style::Default);

    Font font;
    Text text;
    assert(font.loadFromFile("../Galindo-Regular.ttf"));
}

FormGUI::~FormGUI()
{
    ClearAll();
}

void FormGUI::SetName(const std::string name)
{
    name_ = name;
}

void FormGUI::SetSize(const Point size)
{
    size_ = size;
}

void FormGUI::DeleteControlElement(int inx)
{
    std::pair<ControlElement*, Type_EC> control_element = GetCE(inx);
    switch (control_element.second) {
        case (Type_EC::Button):
            delete static_cast<Button*>(control_element.first);
            break;
        case (Type_EC::Image):
            delete static_cast<ImageN*>(control_element.first);
            break;
        case (Type_EC::Edit):
            delete static_cast<Edit*>(control_element.first);
            break;
    }
    control_elements_.erase(control_elements_.begin() + inx);
}

std::pair<ControlElement*, Type_EC> FormGUI::GetCE(int inx) const
{
    ControlElement* result = nullptr;
    Type_EC type = Type_EC::None;

    if (inx < control_elements_.size()) {
        if (std::holds_alternative<Button*>(control_elements_.at(inx))) {
            result = std::get<Button*>(control_elements_.at(inx));
            type = Type_EC::Button;
        }
        else if (std::holds_alternative<ImageN*>(control_elements_.at(inx))) {
            result = std::get<ImageN*>(control_elements_.at(inx));
            type = Type_EC::Image;
        }
        else if (std::holds_alternative<Edit*>(control_elements_.at(inx))) {
            result = std::get<Edit*>(control_elements_.at(inx));
            type = Type_EC::Edit;
        }
    }
    return { result, type };
}

void FormGUI::ClearAll()
{
    if (GetNumberCE() == 0) {
        return;
    }
    for (int inx = GetNumberCE() - 1; inx < 0; inx--) {
        DeleteControlElement(inx);
    }
}


std::string FormGUI::GetName() const
{
    return name_;
}

int FormGUI::GetNumberCE() const
{
    return control_elements_.size();
}

void FormGUI::ReDraw()
{
    RenderWindow* window = GetWindow();

    // цикл будет работать пока графическое окно открыто
    //while (window->isOpen())
    //{
        // В переменную event типа Event, сохраняется событие, например нажатие мышкой на крестик окна 
        // или нажатие клавиши на клавиатуре
        Event event;

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            if (select_edit_) {         
                select_edit_->SetSelected(false);
                select_edit_->SetColor();
                select_edit_ = nullptr;
            }
        }

        // цикл включается в работу когда возникает какое-либо событие и записывает его 
        // с помощью метода pollEvent( ) в переменную event
        while (window->pollEvent(event))
        {
            Point mouse_position = { Mouse::getPosition(*window).x,
                                     Mouse::getPosition(*window).y };
            switch (event.type) {
                case Event::Closed:
                    // Обработчик события нажатие на крестик графического окна, метод Close() закрывает окно
                    window->close();
                    break;
                case Event::TextEntered:
                    if (select_edit_) {
                        select_edit_->typedOn(event);
                    }
                    break;
                case Event::MouseMoved:
                    fMouseMoved(mouse_position);
                    break;
                case Event::MouseButtonPressed:
                    std::cout << name_;
                    for (const auto& control_element : control_elements_) {
                        if (std::holds_alternative<Button*>(control_element)) {
                            Button* button = std::get<Button*>(control_element);
                            if (!button->GetVisible()) continue;
                            if (button->isMouseOver(mouse_position)) {
                                 std::cout << "->" << button->GetName();
                            }
                        }
                        if (std::holds_alternative<Edit*>(control_element)) {
                            Edit* edit = std::get<Edit*>(control_element);
                            if (!edit->GetVisible()) continue;
                            if (edit->isMouseOver(mouse_position)) {                             
                                edit->SetSelected(true);
                                edit->SetColor(Color::White);
                                if (select_edit_) {
                                    if (select_edit_ != edit) {
                                        select_edit_->SetSelected(false);
                                        select_edit_->SetColor();
                                    }
                                }
                                select_edit_ = edit;
                            }
                            if (edit->isMouseOver(mouse_position)) {
                                std::cout << "->" << edit->GetName();
                            }
                        }
                        if (std::holds_alternative<ImageN*>(control_element)) {
                            ImageN* image = std::get<ImageN*>(control_element);
                            if (!image->GetVisible()) continue;
                            if (image->isMouseOver(mouse_position)) {
                                std::cout << "->" << image->GetName();
                            }
                        }
                    }
                    std::cout << std::endl;
                    break;
            }
        }

        // Метод clear(Color::Blue), очищает графическое окно и разукрашивает его в синий цвет
        window->clear(CLEAR_COLOR);

        fDisplay(window);
    //}
}

void FormGUI::fDisplay(RenderWindow* window)
{
    // Рисуем
    for (const auto& control_element : control_elements_) {
        if (std::holds_alternative<Button*>(control_element)) {
            DrawControlElement(*window, std::get<Button*>(control_element));
        }
        else if (std::holds_alternative<ImageN*>(control_element)) {
            DrawControlElement(*window, std::get<ImageN*>(control_element));
        }
        else if (std::holds_alternative<Edit*>(control_element)) {
            DrawControlElement(*window, std::get<Edit*>(control_element));
        }  
    }

    // Метод display() выводит нарисованные объекты методом draw() в графическое окно
    window->display();
}

void FormGUI::fMouseMoved(Point mouse_position)
{
    for (const auto& control_element : control_elements_) {
        if (std::holds_alternative<Button*>(control_element)) {
            Button* button = std::get<Button*>(control_element);
            if (button->isMouseOver(mouse_position)) {
                button->SetColor(Color::Magenta);
            }
            else {
                button->SetColor(sf::Color::Green);
            }
        }
    }
}

RenderWindow* FormGUI::GetWindow()
{
    return window_;
}

void FormGUI::DrawControlElement(RenderWindow& window, const Button* control_element) const
{
    if (control_element->GetVisible()) {
        window.draw(control_element->GetShape());
        window.draw(control_element->GetText());
    }
}

void FormGUI::DrawControlElement(RenderWindow& window, const ImageN* control_element) const
{
    if (control_element->GetVisible()) {
        window.draw(control_element->GetShape());
        window.draw(control_element->GetImage());
        window.draw(control_element->GetText());
    }
}

void FormGUI::DrawControlElement(RenderWindow& window, const Edit* control_element) const
{
    if (control_element->GetVisible()) {
        window.draw(control_element->GetShape());
        window.draw(control_element->GetText());
    }
}
