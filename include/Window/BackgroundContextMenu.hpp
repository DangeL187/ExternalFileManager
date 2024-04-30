#ifndef EXTERNALFILEMANAGER_BACKGROUNDCONTEXTMENU_HPP
#define EXTERNALFILEMANAGER_BACKGROUNDCONTEXTMENU_HPP

#include <QSlider>
#include <QVBoxLayout>
#include <QWidgetAction>

#include "ContextMenu.hpp"

template <typename B>
class BackgroundWindow;

class Application;

template <typename U>
class UpdatableWindow;

class BackgroundContextMenu: public ContextMenu<BackgroundWindow<UpdatableWindow<Application>>> {
public:
    explicit BackgroundContextMenu(BackgroundWindow<UpdatableWindow<Application>>* parent_widget);
private:
    QAction*        _action_change_transparency{};
    QAction*        _action_close_app{};
    QAction*        _action_open_folder{};
    QAction*        _action_set_fixed_mode{};

    QWidgetAction*  _change_transparency{};
    QMenu*          _transparency_menu{};
    QSlider*        _transparency_slider{};

    void initActions() override;
    void loadStyle() override;
};

#endif //EXTERNALFILEMANAGER_BACKGROUNDCONTEXTMENU_HPP
