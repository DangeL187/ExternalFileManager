#ifndef CANDYPANEQT_UPDATABLEWINDOW_HPP
#define CANDYPANEQT_UPDATABLEWINDOW_HPP

#include <windows.h>

#include <QContextMenuEvent>
#include <QFileDialog>
#include <QMainWindow>
#include <QMouseEvent>

template <typename X>
class BackgroundWindow;

template <typename T>
class UpdatableWindow: public QMainWindow {
public:
    explicit UpdatableWindow(T* owner);
    char getResizeDir();
    bool isFixedWindowSizeMode();
    void openNewFolder();
    void stopResizing();
    void setFixedWindowSizeMode(bool value, bool from_app = false);

protected:
    void changeEvent(QEvent* event) override;
    bool event(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    std::shared_ptr<BackgroundWindow<UpdatableWindow<T>>>   _background_window;
    bool                                                    _is_fixed_window_size_mode = false;
    T*                                                      _owner;
    char                                                    _resize_dir = 0;
    QRect                                                   _rect_before_resizing;

    void checkGripHover();
    void resizeWithMouse();
};

#endif //CANDYPANEQT_UPDATABLEWINDOW_HPP
