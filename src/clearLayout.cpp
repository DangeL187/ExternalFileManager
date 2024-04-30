#include "clearLayout.hpp"

void clearLayout(QLayout* layout) {
    if (layout != nullptr) {
        while (layout->count()) {
            QLayoutItem* item = layout->takeAt(0);
            QWidget* widget = item->widget();
            if (widget != nullptr) {
                widget->setParent(nullptr);
            } else {
                clearLayout(item->layout());
            }
        }
    }
}
