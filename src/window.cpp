#include <ebb/window.hpp>
#include <ebb/util/file.hpp>

Ebb::Window::Window(int width, int height, const std::string& title = "Ebb Engine") : _title(title) {
    Ebb::Window::setup();
    if (width + height == 0) return;
    this->_win = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (this->_win == nullptr) {
        // TODO: show error message or smth
        return;
    }
    glfwMakeContextCurrent(this->_win);

    if (!gladLoadGLLoader(((GLADloadproc)glfwGetProcAddress))) {
        printf("GLAD failed to initialize.\n");
        exit(1);
    }

    this->_width  =  width;
    this->_height = height;
}

void Ebb::Window::update() {
    if (this->_win == nullptr) return;
    if (glfwWindowShouldClose(this->_win)) {
        glfwDestroyWindow(this->_win);
        this->_win = nullptr;
        return;
    }

    glfwSwapBuffers(this->_win);
    glfwPollEvents(); // TODO: actually do stuff with the events
}

bool Ebb::Window::initialized = false;
void Ebb::Window::setup() {
    if (Ebb::Window::initialized) return;
    Ebb::Window::initialized = true;
    if (glfwInit() == GLFW_FALSE) {
        printf("GLFW failed to initialize.\n");
        exit(1);
    }
}

void Ebb::Window::teardown() {
    if (!Ebb::Window::initialized) return;
    Ebb::Window::initialized = false;
    glfwTerminate();
}

/**
 * |width: i32| |height: i32| |title: nts/c-str|
*/
void Ebb::Window::save(FILE *file) {
    fwrite(&this->_width, 1, sizeof(this->_width), file);
    fwrite(&this->_height, 1, sizeof(this->_height), file);

    Ebb::Util::Files::writeNts(file, this->_title);
}

void Ebb::Window::load(FILE *file) {
    fread(&this->_width, 1, sizeof(this->_width), file);
    fread(&this->_height, 1, sizeof(this->_height), file);

    Ebb::Util::Files::readNts(file, this->_title);

    this->Ebb::Window::~Window();
    new (this) Ebb::Window(this->_width, this->_height, this->_title);
}