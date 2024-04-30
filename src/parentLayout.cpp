#include "parentLayout.hpp"

/*
    Original authors of this part of code are:
    Ivan Babulic - https://stackoverflow.com/users/2039441/ivan-babulic
    emkey08 - https://stackoverflow.com/users/1070129/emkey08
*/

QLayout* parentLayout(const QWidget *widget, QLayout *layout) {
    int itemCount = layout ? layout->count() : 0;
    for (int i = 0; i < itemCount; i++) {
        if (layout->itemAt(i)->widget() == widget) {
            return layout;
        } else if (QLayout *itemLayout = parentLayout(widget, layout->itemAt(i)->layout())) {
            return itemLayout;
        }
    }
    return nullptr;
}

QLayout* parentLayout(const QWidget* widget) {
    QLayout *layout = widget->parentWidget() ? widget->parentWidget()->layout() : nullptr;
    return parentLayout(widget, layout);
}