#ifndef CANDYPANEQT_CONTEXTMENU_HPP
#define CANDYPANEQT_CONTEXTMENU_HPP

#include <QContextMenuEvent>
#include <QMenu>

template <typename T>
class ContextMenu: public QMenu {
protected:
    T* _parent_widget;

    explicit ContextMenu(T* parent_widget);

    virtual void initActions() = 0;
    virtual void loadStyle() = 0;
};

#endif //CANDYPANEQT_CONTEXTMENU_HPP
