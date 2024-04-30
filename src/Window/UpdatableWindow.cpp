#include "Window/UpdatableWindow.hpp"

#include "Application.hpp"
#include "Window/BackgroundWindow.hpp"

template <>
UpdatableWindow<Application>::UpdatableWindow(Application* owner): _owner(owner) {
    _background_window = std::make_shared<BackgroundWindow<UpdatableWindow<Application>>>(this);

    setAttribute(Qt::WA_Hover);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    setCentralWidget(_background_window.get());

    setMouseTracking(true);
}

template <>
void UpdatableWindow<Application>::changeEvent(QEvent* event) {
    QMainWindow::changeEvent(event);
}

template <>
void UpdatableWindow<Application>::checkGripHover() {
    if (!_is_fixed_window_size_mode) return;

    QCursor cursor;
    QPoint bottom_right = mapToGlobal(rect().bottomRight());

    if (bottom_right.x() - 5 <= QCursor::pos().x() && QCursor::pos().x() <= bottom_right.x()) {
        cursor.setShape(Qt::CursorShape::SizeHorCursor);
        _resize_dir = 1;
    }
    else if (bottom_right.y() - 5 <= QCursor::pos().y() && QCursor::pos().y() <= bottom_right.y()) {
        cursor.setShape(Qt::CursorShape::SizeVerCursor);
        _resize_dir = 2;
    } else {
        _resize_dir = 0; // TODO: fix non-smooth resizing
    }
    setCursor(cursor);
}

template <>
void UpdatableWindow<Application>::resizeWithMouse() {
    POINT pos;
    if (GetCursorPos(&pos) && _background_window->isResizing()) {
        int drag_distance;
        if (_resize_dir == 1) {
            drag_distance = pos.x - mapToGlobal(_rect_before_resizing.bottomRight()).x();
            resize(_rect_before_resizing.width() + drag_distance, height());
        } else if (_resize_dir == 2) {
            drag_distance = pos.y - mapToGlobal(_rect_before_resizing.bottomRight()).y();
            resize(width(),_rect_before_resizing.height() + drag_distance);
        }
    }
}

template <>
bool UpdatableWindow<Application>::event(QEvent* event) {
    if (_is_fixed_window_size_mode) {
        if (_background_window != nullptr && _background_window->isResizing()) {
            if (!_rect_before_resizing.isValid()) _rect_before_resizing = rect();
            resizeWithMouse();
        } else {
            _rect_before_resizing = QRect();
        }
    } else {
        resize(_owner->getWorkspaceSize() + QSize(10, 10));
    }

    if (event->type() == QEvent::HoverMove) {
        checkGripHover();
        _owner->checkHover();
        return true;
    } else {
        _owner->update();
        _owner->saveWindowSize(size());
        return QMainWindow::event(event);
    }
}

template <>
char UpdatableWindow<Application>::getResizeDir() {
    return _resize_dir;
}

template <>
bool UpdatableWindow<Application>::isFixedWindowSizeMode() {
    return _is_fixed_window_size_mode;
}

template <>
void UpdatableWindow<Application>::openNewFolder() {
    std::string folder_path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),".",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();
    if (!folder_path.empty()) _owner->createTable(folder_path);
}

template <>
void UpdatableWindow<Application>::resizeEvent(QResizeEvent* event) {
    _background_window->setFixedSize(size());
}

template <>
void UpdatableWindow<Application>::setFixedWindowSizeMode(bool value, bool from_app) {
    _is_fixed_window_size_mode = value;
    if (value) resize(273, 664); // TODO: add getDefaultWorkspaceSize method
    if (!from_app) _owner->setFixedWindowSizeMode(value);
}

template <>
void UpdatableWindow<Application>::stopResizing() {
    _resize_dir = 0;
}
