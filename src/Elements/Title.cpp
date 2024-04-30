#include "Elements/Title.hpp"

#include "Elements/OverlayDraggableWidget.hpp"
#include "Elements/Table.hpp"
#include "Elements/TitleContextMenu.hpp"

Title::Title(const std::string& name, Table* parent): Element(name, true), _parent(parent) {
    _context_menu = std::make_shared<TitleContextMenu>(this);

    setIcon("../img/folder.png");
    setBackgroundColor(124, 58, 237);

    _layout.insertStretch(0, 1);
    _layout.addStretch(1);
}

void Title::contextMenuEvent(QContextMenuEvent *event) {
    _context_menu->exec(event->globalPos());
}

void Title::loadParentFolder() {
    _parent->deselectParent();
    _parent->load(_full_path.substr(0, _full_path.rfind('/')));
}

void Title::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        _is_left_mouse_pressed = true;

        _drag_start_pos = event->globalPosition().toPoint() - mapToGlobal(rect().topLeft());

        _dragged_object = new OverlayDraggableWidget(*_parent);
        _dragged_object->move(event->globalPosition().toPoint() - _drag_start_pos);
    }
}

void Title::mouseMoveEvent(QMouseEvent* event) {
    if (_dragged_object != nullptr) {
        _dragged_object->show();
        _parent->showTable(false);

        _is_left_mouse_pressed = false;

        QPoint pos = event->globalPosition().toPoint();
        pos -= _drag_start_pos;
        _dragged_object->move(pos);
        _parent->relocate();
    }
}

void Title::mouseReleaseEvent(QMouseEvent* event) {
    if (_is_left_mouse_pressed) {
        _parent->toggleShowContents();
        _is_left_mouse_pressed = false;
    }

    _parent->showTable(true);

    if (_dragged_object != nullptr) {
        _dragged_object->close();
        delete _dragged_object;
        _dragged_object = nullptr;
    }
}

void Title::openParentFolder() {
    _parent->createTable(_full_path.substr(0, _full_path.rfind('/')));
}

void Title::remove() {
    _parent->remove();
}
