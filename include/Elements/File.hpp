#ifndef EXTERNALFILEMANAGER_FILE_HPP
#define EXTERNALFILEMANAGER_FILE_HPP

#include "Element.hpp"

class File: public Element {
public:
    explicit File(const std::string& name);
private:
    bool    _mouse_pressed = false;

    void autoIcon();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif //EXTERNALFILEMANAGER_FILE_HPP
