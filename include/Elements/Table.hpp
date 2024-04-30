#ifndef EXTERNALFILEMANAGER_TABLE_HPP
#define EXTERNALFILEMANAGER_TABLE_HPP

#include <filesystem>
#include <vector>

#include <QFileSystemWatcher>
#include <QFrame>
#include <QVBoxLayout>

class Element;
class Title;
class Workspace;

class Table: public QFrame {
Q_OBJECT
public:
    explicit Table(const std::string& folder_path, Workspace* parent = nullptr);
    void checkTable();
    Table* createTable(const std::string& folder_path);
    void deselectParent();
    QVBoxLayout* getLayout();
    void load();
    void load(const std::string& folder_path);
    void relocate();
    void remove();
    void showTable(bool value);
    void toggleShowContents();

private:
    std::wstring_convert<std::codecvt_utf8<wchar_t>>    _converter;
    std::string                                         _folder_path;
    bool                                                _is_hidden = false;
    QVBoxLayout                                         _layout;
    Workspace*                                          _parent;
    std::shared_ptr<QFileSystemWatcher>                 _watcher;

    std::pair<int, int> getIndexes();
    void showContents(bool value);

private slots:
    void changed(const QString& full_path);
};

#endif //EXTERNALFILEMANAGER_TABLE_HPP
