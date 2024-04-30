#include "Window/BackgroundWindow.hpp"

#include "Application.hpp"
#include "Window/BackgroundContextMenu.hpp"
#include "Window/UpdatableWindow.hpp"

template <>
void BackgroundWindow<UpdatableWindow<Application>>::setTransparency(short percentage) {
    short value = 255.0f / 100 * percentage;
    setStyleSheet(("background-color: rgba(32, 32, 32," + std::to_string(value) + "); border-radius: 6px;").c_str());
    _transparency = percentage;
}

template <>
BackgroundWindow<UpdatableWindow<Application>>::BackgroundWindow(UpdatableWindow<Application>* parent):
    QWidget(parent), _parent(parent)
{
    setTransparency(70);
    _context_menu = std::make_shared<BackgroundContextMenu>(this);
}

template <>
void BackgroundWindow<UpdatableWindow<Application>>::contextMenuEvent(QContextMenuEvent* event) {
    _context_menu->exec(event->globalPos());
}

template <>
short BackgroundWindow<UpdatableWindow<Application>>::getTransparency() {
    return _transparency;
}

template <>
bool BackgroundWindow<UpdatableWindow<Application>>::isResizing() {
    return _is_resizing;
}

template <>
void BackgroundWindow<UpdatableWindow<Application>>::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (_parent->getResizeDir() == 0 && !_is_resizing) {
            _is_dragging = true;
        } else if (_parent->getResizeDir() != 0 && !_is_dragging) {
            _is_resizing = true;
        }
        _drag_start_pos = event->globalPosition().toPoint() - mapToGlobal(rect().topLeft());
    }
}

template <>
void BackgroundWindow<UpdatableWindow<Application>>::mouseMoveEvent(QMouseEvent* event) {
    if (!_is_dragging || _is_resizing) return;

    QPoint pos = event->globalPosition().toPoint();
    pos -= _drag_start_pos;
    _parent->move(pos);
}

template <>
void BackgroundWindow<UpdatableWindow<Application>>::mouseReleaseEvent(QMouseEvent* event) {
    if (_is_dragging) _is_dragging = false;
    if (_is_resizing) {
        _parent->stopResizing();
        _is_resizing = false;
    }
}

template <>
void BackgroundWindow<UpdatableWindow<Application>>::openNewFolder() {
    _parent->openNewFolder();
}

template <>
void BackgroundWindow<UpdatableWindow<Application>>::setFixedWindowSizeMode(bool value) {
    _parent->setFixedWindowSizeMode(value);
}
