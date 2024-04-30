#include "Window/BackgroundContextMenu.hpp"

#include "Application.hpp"
#include "Window/BackgroundWindow.hpp"
#include "Window/UpdatableWindow.hpp"

BackgroundContextMenu::BackgroundContextMenu(BackgroundWindow<UpdatableWindow<Application>>* parent_widget):
    ContextMenu(parent_widget)
{
    BackgroundContextMenu::initActions();
    BackgroundContextMenu::loadStyle();
}

void BackgroundContextMenu::initActions() {
    _transparency_slider = new QSlider();
    _transparency_slider->setFixedSize(200, 20);
    _transparency_slider->setOrientation(Qt::Horizontal);
    _transparency_slider->setStyleSheet("background-color: transparent;");
    _transparency_slider->setMaximum(100);
    _transparency_slider->setSliderPosition(_parent_widget->getTransparency());

    _change_transparency = new QWidgetAction(this);
    _change_transparency->setDefaultWidget(_transparency_slider);

    _transparency_menu = new QMenu(this);
    _transparency_menu->setTitle("Change transparency");
    _transparency_menu->addAction(_change_transparency);

    _action_open_folder = addAction("Open new folder");
    _action_set_fixed_mode = addAction("Set fixed window size mode"); _action_set_fixed_mode->setCheckable(true);
    _action_change_transparency = addMenu(_transparency_menu);
    _action_close_app = addAction("Close application");

    QObject::connect(_action_close_app, &QAction::triggered, [&]() {
        QCoreApplication::quit();
    });

    QObject::connect(_action_open_folder, &QAction::triggered, [&]() {
        _parent_widget->openNewFolder();
    });

    QObject::connect(_action_set_fixed_mode, &QAction::triggered, [&]() {
        _parent_widget->setFixedWindowSizeMode(!_action_set_fixed_mode->isChecked());
    });

    QObject::connect(_transparency_slider, &QSlider::valueChanged, [&]() {
        _parent_widget->setTransparency(_transparency_slider->sliderPosition());
    });
}

void BackgroundContextMenu::loadStyle() {
    setStyleSheet("QMenu { font-size: 14px; background-color: rgb(32, 32, 32); border: 1px solid rgb(124, 58, 237); }"
                  "QMenu::item:selected { background-color: rgb(67, 69, 74); }");
}