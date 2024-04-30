#ifndef EXTERNALFILEMANAGER_FOLDER_HPP
#define EXTERNALFILEMANAGER_FOLDER_HPP

#include "Element.hpp"

class OverlayDraggableWidget;
class Table;

class Folder: public Element {
public:
    explicit Folder(const std::string& name, Table* parent);
private:
    QPoint                  _drag_start_pos;
    OverlayDraggableWidget* _dragged_object = nullptr;
    Table*                  _dragged_new_table = nullptr;
    bool                    _is_left_mouse_pressed = false;
    Table*                  _parent = nullptr;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif //EXTERNALFILEMANAGER_FOLDER_HPP
