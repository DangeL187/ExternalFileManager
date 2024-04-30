#ifndef PARENTLAYOUT_HPP
#define PARENTLAYOUT_HPP

#include <QLayout>
#include <QWidget>

QLayout* parentLayout(const QWidget* widget, QLayout* layout);
QLayout* parentLayout(const QWidget* widget);

#endif //PARENTLAYOUT_HPP
