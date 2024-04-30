#ifndef EXTERNALFILEMANAGER_ELEMENT_HPP
#define EXTERNALFILEMANAGER_ELEMENT_HPP

#include <filesystem>
#include <memory>

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>

class Element: public QFrame {
Q_OBJECT
public:
    explicit Element(const std::string& full_path, bool is_title = false);
    std::string getFullPath();
    [[nodiscard]] bool isHighlighted() const;
    [[nodiscard]] bool isSelected() const;
    [[nodiscard]] bool isTitle() const;
    void select(bool value, bool highlight = false);
    void setBackgroundColor(unsigned short r, unsigned short g, unsigned short b);
    void setIcon(std::string url, QSize size = QSize(15, 14));
    void setIcon();
    void setName();
    void showElement(bool value);
protected:
    bool                        _is_highlighted = false;
    bool                        _is_selected = false;
    bool                        _is_title;

    std::string                 _background_color;
    std::string                 _full_path;
    std::shared_ptr<QWidget>    _icon;
    QHBoxLayout                 _layout;
    std::shared_ptr<QLabel>     _name;

    QSize                       _reserved_icon_size;
    std::string                 _reserved_icon_url;
    std::string                 _reserved_name;
};

#endif //EXTERNALFILEMANAGER_ELEMENT_HPP
