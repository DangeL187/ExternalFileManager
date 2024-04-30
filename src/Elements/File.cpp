#include "Elements/File.hpp"

#include "Workspace/Workspace.hpp" // for Workspace::run()

File::File(const std::string& name): Element(name) {
    autoIcon();
    setBackgroundColor(67, 69, 74);
}

void File::autoIcon() {
    std::string name = _name->text().toStdString();
    name = name.substr(name.rfind('/') + 1);
    name = name.substr(name.rfind('.') + 1);
    setIcon("../img/" + name + ".png");
}

void File::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        _mouse_pressed = true;
    }
}

void File::mouseReleaseEvent(QMouseEvent* event) {
    if (_mouse_pressed) {
        Workspace::run(_full_path);
        _mouse_pressed = false;
    }
}