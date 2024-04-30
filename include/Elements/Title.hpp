#ifndef EXTERNALFILEMANAGER_TITLE_HPP
#define EXTERNALFILEMANAGER_TITLE_HPP

#include "Element.hpp"

#include <QMouseEvent>

class OverlayDraggableWidget;
class Table;
class TitleContextMenu;

class Title: public Element {
public:
    Title(const std::string& name, Table* parent);
    void loadParentFolder();
    void openParentFolder();
    void remove();
private:
    std::shared_ptr<TitleContextMenu>   _context_menu;
    QPoint                              _drag_start_pos;
    OverlayDraggableWidget*             _dragged_object = nullptr;
    bool                                _is_left_mouse_pressed = false;
    Table*                              _parent = nullptr;

    void contextMenuEvent(QContextMenuEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif //EXTERNALFILEMANAGER_TITLE_HPP
