#ifndef EXTERNALFILEMANAGER_WORKSPACE_HPP
#define EXTERNALFILEMANAGER_WORKSPACE_HPP

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <filesystem>
#include <fstream>
#include <unordered_map>

class Element;
class Table;

class Workspace: public QHBoxLayout {
public:
    explicit Workspace(QWidget* parent = nullptr);

    void checkHover();
    void checkTables();
    Table* createTable(const std::string& folder_path);

    std::pair<int, int> getNewIndexes();
    QSize getSize();
    QSize getWindowSize();
    std::vector<Element*> getParentElements(const std::string& element_full_path);

    static void loadConfig();
    void loadPreset();

    void relocateTable(std::pair<int, int> table_indexes);
    void removeTable(std::pair<int, int> table_indexes);

    static void run(const std::string& full_file_path);
    void saveWindowSize(QSize window_size);
    void setFixedWindowSizeMode(bool value);

private:
    inline static std::unordered_map<std::string, std::string>  _associations;
    bool                                                        _is_fixed_window_size_mode = false;
    QSize                                                       _window_size;
};

#endif //EXTERNALFILEMANAGER_WORKSPACE_HPP
