#include "Application.hpp"
#include "Window/UpdatableWindow.hpp"
#include "Workspace/Workspace.hpp"

Application::Application(int argc, char* argv[]): _application(argc, argv) {
    initScrollArea();
    initWorkspace();
    initWindow();

    setFixedWindowSizeMode(true);
}

void Application::checkHover() {
    _workspace->checkHover();
}

void Application::createTable(const std::string& folder_path) {
    _workspace->createTable(folder_path);
}

QSize Application::getWorkspaceSize() {
    return _workspace->getSize();
}

void Application::initScrollArea() {
    _scroll_area.setFrameShape(QFrame::NoFrame);
    _scroll_area.setWidgetResizable(true);
    _scroll_area.setWidget(&_scroll_area_widget);
    _scroll_area.setStyleSheet("background-color: transparent");
}

void Application::initWorkspace() {
    _workspace = std::make_shared<Workspace>(&_scroll_area_widget);
}

void Application::initWindow() {
    _window = std::make_shared<UpdatableWindow<Application>>(this);

    auto* layout = _window->layout(); delete layout;
    _main_layout.setContentsMargins(5, 20, 5, 5);
    _main_layout.addWidget(&_scroll_area);
    _window->setLayout(&_main_layout);

    _window->show();
}

void Application::saveWindowSize(QSize window_size) {
    _workspace->saveWindowSize(window_size);
}

void Application::setFixedWindowSizeMode(bool value) {
    _workspace->setFixedWindowSizeMode(value);
    _window->setFixedWindowSizeMode(value, true);
    if (value) {
        _scroll_area.setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _scroll_area.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    } else {
        _scroll_area.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _scroll_area.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
    _window->move(960, 240);
}

void Application::update() {
    _workspace->checkTables();
}
