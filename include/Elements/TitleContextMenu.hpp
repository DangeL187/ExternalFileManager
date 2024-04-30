#ifndef EXTERNALFILEMANAGER_TITLECONTEXTMENU_HPP
#define EXTERNALFILEMANAGER_TITLECONTEXTMENU_HPP

#include "ContextMenu.hpp"

class Title;

class TitleContextMenu: public ContextMenu<Title> {
public:
    explicit TitleContextMenu(Title* parent_widget);
private:
    QAction*    _action_close{};
    QAction*    _action_goto_parent{};
    QAction*    _action_open_parent{};

    void initActions() override;
    void loadStyle() override;
};

#endif //EXTERNALFILEMANAGER_TITLECONTEXTMENU_HPP
