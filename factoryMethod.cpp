#include <iostream>
#include <string>

class Button {
public:
    virtual void render() = 0;
};

class HtmlButton : public Button {
public:
    void render() override {
        std::cout << "<button>Test Button</button>" << std::endl;
        std::cout << "Click! Button says - 'Hello World!'" << std::endl;
    }
};

class WindowsButton : public Button {
public:
    void render() override {
        std::cout << "[Windows Button] Hello World!" << std::endl;
        std::cout << "[Windows Button] Clicked: Exiting..." << std::endl;
    }
};

class Dialog {
public:
    virtual Button* createButton() = 0;

    void renderWindow() {
        Button* button = createButton();
        button->render();
        delete button;
    }
};

class HtmlDialog : public Dialog {
public:
    Button* createButton() override {
        return new HtmlButton();
    }
};

class WindowsDialog : public Dialog {
public:
    Button* createButton() override {
        return new WindowsButton();
    }
};

int main() {
    std::string os;
    std::cout << "Enter OS (windows/html): ";
    std::cin >> os;

    Dialog* dialog;

    if (os == "windows") {
        dialog = new WindowsDialog();
    } else {
        dialog = new HtmlDialog();
    }

    dialog->renderWindow();
    delete dialog;

    return 0;
}
