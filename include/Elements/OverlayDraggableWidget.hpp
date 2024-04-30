#ifndef CANDYPANEQT_OVERLAYDRAGGABLEWIDGET_HPP
#define CANDYPANEQT_OVERLAYDRAGGABLEWIDGET_HPP

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>

class CategoryWidget;
class Table;

class OverlayDraggableWidget: public QDialog {
Q_OBJECT
public:
    explicit OverlayDraggableWidget(Table& draggable_widget);

private:
    /*=============OverlayDraggableWidget==============*/
    std::shared_ptr<QVBoxLayout>    _layout;
    QWidget*                        _widget = nullptr;
    /*=================================================*/

    QLayout* copyLayout(QLayout* layout, bool return_hbox_layout);
    void initLayout(QVBoxLayout& layout);
};

#endif //CANDYPANEQT_OVERLAYDRAGGABLEWIDGET_HPP
