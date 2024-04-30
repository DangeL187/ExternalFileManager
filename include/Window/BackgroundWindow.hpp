#ifndef EXTERNALFILEMANAGER_BACKGROUNDWINDOW_HPP
#define EXTERNALFILEMANAGER_BACKGROUNDWINDOW_HPP

#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QWidget>

class BackgroundContextMenu;

template <typename T>
class BackgroundWindow: public QWidget {
public:
    explicit BackgroundWindow(T* parent);
    short getTransparency();
    bool isResizing();
    void openNewFolder();
    void setFixedWindowSizeMode(bool value);
    void setTransparency(short percentage);

private:
    std::shared_ptr<BackgroundContextMenu>  _context_menu;
    QPoint                                  _drag_start_pos;
    bool                                    _is_dragging = false;
    bool                                    _is_resizing = false;
    T*                                      _parent;
    short                                   _transparency;

    void contextMenuEvent(QContextMenuEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif //EXTERNALFILEMANAGER_BACKGROUNDWINDOW_HPP
