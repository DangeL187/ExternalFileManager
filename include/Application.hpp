#ifndef CANDYPANEQT_APPLICATION_HPP
#define CANDYPANEQT_APPLICATION_HPP

#include <memory>

#include <QApplication>
#include <QHBoxLayout>
#include <QRect>
#include <QScrollArea>

template <typename T> class UpdatableWindow;
class Workspace;

class Application {
public:
    Application(int argc, char* argv[]);

    void checkHover();
    void createTable(const std::string& folder_path);
    QSize getWorkspaceSize();
    void saveWindowSize(QSize window_size);
    void setFixedWindowSizeMode(bool value);
    void update();
private:
    /*==========================Application==========================*/
    QApplication                                    _application;
    QHBoxLayout                                     _main_layout;
    QScrollArea                                     _scroll_area;
    QWidget                                         _scroll_area_widget;
    std::shared_ptr<UpdatableWindow<Application>>   _window;
    std::shared_ptr<Workspace>                      _workspace;
    /*===============================================================*/

    /*=========================initializers==========================*/
    void initScrollArea();
    void initWorkspace();
    void initWindow();
    /*===============================================================*/
};

#endif //CANDYPANEQT_APPLICATION_HPP
