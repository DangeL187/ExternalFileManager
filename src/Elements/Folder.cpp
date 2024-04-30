#include "Elements/Folder.hpp"
#include "Elements/Table.hpp"
#include "Elements/OverlayDraggableWidget.hpp"

Folder::Folder(const std::string& name, Table* parent): Element(name), _parent(parent) {
    setIcon("../img/folder.png");
    setBackgroundColor(67, 69, 74);
}

void Folder::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        _is_left_mouse_pressed = true;

        _drag_start_pos = event->globalPosition().toPoint() - mapToGlobal(rect().topLeft());

        _dragged_new_table = _parent->createTable(_full_path);
        _dragged_new_table->setVisible(false);

        _dragged_object = new OverlayDraggableWidget(*_dragged_new_table);
    }
}

void Folder::mouseMoveEvent(QMouseEvent* event) {
    if (_dragged_object != nullptr) {
        _dragged_new_table->setVisible(true);
        _dragged_new_table->showTable(false);

        if (_is_left_mouse_pressed) {
            delete _dragged_object;
            _dragged_object = new OverlayDraggableWidget(*_dragged_new_table);
        } _dragged_object->show();

        _is_left_mouse_pressed = false;

        QPoint pos = event->globalPosition().toPoint();
        pos -= _drag_start_pos;
        _dragged_object->move(pos);
        _dragged_new_table->relocate();
    }
}

void Folder::mouseReleaseEvent(QMouseEvent* event) {
    if (_is_left_mouse_pressed) {
        _parent->load(_full_path);
        _dragged_new_table->remove();
        _dragged_new_table = nullptr;
        _is_left_mouse_pressed = false;
        return;
    }

    if (_dragged_object != nullptr) {
        _dragged_new_table->showTable(true);
        _dragged_object->close();
        delete _dragged_object;
        _dragged_object = nullptr;
        _dragged_new_table = nullptr;
    }
}