#include "Elements/TitleContextMenu.hpp"

#include "Elements/Title.hpp"

TitleContextMenu::TitleContextMenu(Title* parent_widget): ContextMenu(parent_widget) {
    TitleContextMenu::initActions();
    TitleContextMenu::loadStyle();
}

void TitleContextMenu::initActions() {
    _action_goto_parent = addAction("Go to parent folder");
    _action_open_parent = addAction("Open parent folder");
    _action_close = addAction("Close folder");

    QObject::connect(_action_close, &QAction::triggered, [&]() {
        _parent_widget->remove();
    });

    QObject::connect(_action_open_parent, &QAction::triggered, [&]() {
        _parent_widget->openParentFolder();
    });

    QObject::connect(_action_goto_parent, &QAction::triggered, [&]() {
        _parent_widget->loadParentFolder();
    });
}

void TitleContextMenu::loadStyle() {
    setStyleSheet("QMenu { font-size: 14px; background-color: rgb(32, 32, 32); border: 1px solid rgb(124, 58, 237); }"
                  "QMenu::item:selected { background-color: rgb(67, 69, 74); }");
}