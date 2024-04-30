#include "Elements/Element.hpp"

Element::Element(const std::string& full_path, bool is_title) {
    _is_title = is_title;
    _full_path = full_path;
    std::replace(_full_path.begin(), _full_path.end(), '\\', '/');

    std::string name = _full_path;
    name = name.substr(name.rfind('/') + 1);

    _name = std::make_shared<QLabel>(name.c_str());
    _icon = std::make_shared<QWidget>();
    _reserved_name = name;

    _layout.setContentsMargins(0, 0, 0, 0);
    _layout.addWidget(_icon.get());
    _layout.addWidget(_name.get());
    _layout.addStretch(1);

    setLayout(&_layout);
}

std::string Element::getFullPath() {
    return _full_path;
}

bool Element::isHighlighted() const {
    return _is_highlighted;
}

bool Element::isSelected() const {
    return _is_selected;
}

bool Element::isTitle() const {
    return _is_title;
}

void Element::select(bool value, bool highlight) {
    std::string style = _background_color;

    if (highlight) {
        if (value) {
            style = "background-color: transparent;";
            setIcon("../img/folder_highlight.png");
        } else {
            setIcon("../img/folder.png");
        }
    }

    if (value) {
        setStyleSheet((style + "border-radius: 4px;").c_str());
        _is_selected = true;
    } else {
        setStyleSheet("background-color: transparent; border-radius: 4px;");
        _is_selected = false;
    }
}

void Element::setBackgroundColor(unsigned short r, unsigned short g, unsigned short b) {
    _background_color = "background-color: rgb(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ");";
}

void Element::setIcon(std::string url, QSize size) {
    if (!std::filesystem::exists(url)) url = "../img/txt.png";
    _icon->setStyleSheet(("background-image: url(" + url + ");").c_str());

    _icon->setFixedSize(size);
    _reserved_icon_size = size;
    _reserved_icon_url = url;
}

void Element::setIcon() {
    _icon->setStyleSheet(("background-image: url(" + _reserved_icon_url + ");").c_str());
    _icon->setFixedSize(_reserved_icon_size);
}

void Element::setName() {
    _name->setText(_reserved_name.c_str());
}

void Element::showElement(bool value) {
    if (value) {
        setIcon();
        setName();
    } else {
        _icon->setStyleSheet("background-color: transparent;");
        _name->setText("");
    }
}