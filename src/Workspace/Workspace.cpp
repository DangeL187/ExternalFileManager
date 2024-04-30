#include "Workspace/Workspace.hpp"

#include "Elements/Element.hpp"
#include "Elements/Table.hpp"
#include "split.hpp"

Workspace::Workspace(QWidget* parent): QHBoxLayout(parent) {
    addStretch(1);
    loadConfig();
    loadPreset();
    setContentsMargins(5, 5, 5, 5);
}

void Workspace::checkHover() {
    for (int i = 0; i < count()-1; i++) {
        auto* v_layout = qobject_cast<QVBoxLayout*>(itemAt(i)->layout());
        for (int j = 0; j < v_layout->count()-1; j++) {
            auto* table = qobject_cast<Table*>(v_layout->itemAt(j)->widget());
            for (int k = 0; k < table->getLayout()->count()-1; k++) {
                if (k == 1) continue;
                auto* element = qobject_cast<Element*>(table->getLayout()->itemAt(k)->widget());
                if (element->underMouse()) {
                    element->select(true);

                    if (!element->isTitle()) continue;
                    auto parents = getParentElements(element->getFullPath());
                    for (auto parent: parents) {
                        parent->select(true, true);
                    }
                } else if (element->isSelected()) {
                    if (element->isTitle()) {
                        auto parents = getParentElements(element->getFullPath());
                        for (auto parent: parents) {
                            parent->select(false, true);
                        }
                    }
                    element->select(false);
                }
            }
        }
    }
}

void Workspace::checkTables() {
    for (int i = 0; i < count()-1; i++) {
        auto* v_layout = qobject_cast<QVBoxLayout*>(itemAt(i)->layout());
        for (int j = 0; j < v_layout->count()-1; j++) {
            auto* table = qobject_cast<Table*>(v_layout->itemAt(j)->widget());
            table->checkTable();
        }
    }
}

Table* Workspace::createTable(const std::string& folder_path) {
    auto* v_lay = new QVBoxLayout();
    auto* table = new Table(folder_path, this);
    v_lay->addWidget(table);
    v_lay->addStretch(1);
    insertLayout(count()-1, v_lay);
    return table;
}

std::pair<int, int> Workspace::getNewIndexes() {
    int dif_x = -1, dif_y = -1;
    int new_x = -1, new_y = -1;
    QPoint maximal_pos(0, 0);

    for (int i = 0; i < count(); i++) {
        QPoint pos(0, 0);

        if (i == -1) {
            // TODO: add ability to drag in the beginning
            /*auto* v_layout = qobject_cast<QVBoxLayout*>(itemAt(0)->layout());
            auto* table = qobject_cast<Table*>(v_layout->itemAt(0)->widget());
            pos = table->mapToGlobal(table->rect().center()) - QPoint(table->width()*2, 0);*/
        } else if (i == count()-1) {
            pos = maximal_pos;
        } else {
            auto* v_layout = qobject_cast<QVBoxLayout*>(itemAt(i)->layout());
            auto* table = qobject_cast<Table*>(v_layout->itemAt(0)->widget());
            pos = table->mapToGlobal(table->rect().center());
            if (i == count()-2) maximal_pos = pos + QPoint(table->width()*2, 0);
        }

        int diff = abs(pos.x() - QCursor::pos().x()); // horizontal difference between widget's center and mouse cursor
        if (dif_x != -1 && dif_x < diff) {
            break;
        } else {
            new_x = i;
            dif_x = diff;
        }
    }

    if (new_x == -1) {
        /*auto* v_lay = new QVBoxLayout();
        v_lay->addStretch(1);
        insertLayout(0, v_lay);
        return {0, 0};*/
    } else if (new_x == count()-1) {
        auto* v_lay = new QVBoxLayout();
        v_lay->addStretch(1);
        insertLayout(new_x, v_lay);
        return {new_x, 0};
    }

    auto* v_layout = qobject_cast<QVBoxLayout*>(itemAt(new_x)->layout());
    for (int i = 0; i < v_layout->count()-1; i++) {
        auto* table = qobject_cast<Table*>(v_layout->itemAt(i)->widget());
        QPoint pos = table->mapToGlobal(table->rect().center());
        int diff = abs(pos.y() - QCursor::pos().y()); // vertical difference between widget's center and mouse cursor
        if (dif_y != -1 && dif_y < diff) {
            break;
        } else {
            new_y = i;
            dif_y = diff;
        }
    }

    return {new_x, new_y};
}

QSize Workspace::getSize() {
    int width = 5, max_height = 0;

    for (int i = 0; i < count()-1; i++) {
        bool block_width = false;
        int height = 5;
        auto* v_layout = qobject_cast<QVBoxLayout*>(itemAt(i)->layout());
        for (int j = 0; j < v_layout->count()-1; j++) {
            auto* table = qobject_cast<Table*>(v_layout->itemAt(j)->widget());
            if (!block_width) {
                width += table->width() + 5;
                block_width = true;
            } height += table->height() + 5;
        }
        if (height > max_height) max_height = height;
    }
    if (width == 5 && max_height == 0) {
        width = 200; max_height = 200;
    }

    return {width, max_height+20};
}

QSize Workspace::getWindowSize() {
    return _window_size;
}

std::vector<Element*> Workspace::getParentElements(const std::string& element_full_path) {
    std::vector<Element*> parent_elements;
    std::string parent_full_path = element_full_path.substr(0, element_full_path.rfind('/'));

    for (int i = 0; i < count()-1; i++) {
        auto* v_layout = qobject_cast<QVBoxLayout*>(itemAt(i)->layout());
        for (int j = 0; j < v_layout->count()-1; j++) {
            auto* table = qobject_cast<Table*>(v_layout->itemAt(j)->widget());
            for (int k = 0; k < table->getLayout()->count()-1; k++) {
                if (k == 1) continue;
                auto* element = qobject_cast<Element*>(table->getLayout()->itemAt(k)->widget());
                if (element->getFullPath() == parent_full_path) {
                    parent_elements.push_back(element);
                }
            }
        }
    }
    return parent_elements;
}

void Workspace::loadConfig() {
    std::ifstream file("config.txt");
    if (!file.is_open()) return;

    try {
        std::string line;
        while (std::getline(file, line)) {
            _associations[line.substr(0, line.find(' '))] = line.substr(line.find(' ')+1);
        } file.close();
    } catch (std::exception& e) {
        throw std::runtime_error("Failed to load config: " + std::string(e.what()));
        file.close();
    }
}

void Workspace::loadPreset() {
    std::ifstream file("preset.txt");
    if (!file.is_open()) return;

    try {
        bool first_line = true;
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> row = split(line, " ");

            if (first_line) {
                for (int i = 0; i < row.size(); i++) {
                    auto* new_lay = new QVBoxLayout();
                    new_lay->addStretch(1);
                    insertLayout(count()-1, new_lay);
                } first_line = false;
            }

            for (int i = 0; i < row.size(); i++) {
                auto* v_layout = qobject_cast<QVBoxLayout*>(itemAt(i)->layout());
                auto* table = new Table(row[i], this);
                table->toggleShowContents();
                v_layout->insertWidget(v_layout->count()-1, table);
            }
        } file.close();
    } catch (std::exception& e) {
        throw std::runtime_error("Failed to load preset: " + std::string(e.what()));
        file.close();
    }
}

void Workspace::relocateTable(std::pair<int, int> table_indexes) {
    std::pair<int, int> new_indexes = getNewIndexes();
    if (new_indexes == table_indexes || new_indexes.first == -1) return; // mb remove 2nd statement

    auto* v_layout_item = itemAt(table_indexes.first);
    auto* v_layout = qobject_cast<QVBoxLayout*>(v_layout_item->layout());
    auto* new_v_layout = qobject_cast<QVBoxLayout*>(itemAt(new_indexes.first)->layout());
    auto* table = qobject_cast<Table*>(v_layout->itemAt(table_indexes.second)->widget());

    if (_is_fixed_window_size_mode && getWindowSize().width() < getSize().width() + table->width() + 5) {
        if (new_v_layout->count() == 1) {
            removeItem(new_v_layout);
            delete new_v_layout;
            return;
        }
    }

    v_layout->removeWidget(table);
    new_v_layout->insertWidget(new_indexes.second, table);

    if (v_layout->count() == 1) {
        removeItem(v_layout_item);
        delete v_layout_item;
    }
}

void Workspace::removeTable(std::pair<int, int> table_indexes) {
    auto* v_layout_item = itemAt(table_indexes.first);
    auto* v_layout = qobject_cast<QVBoxLayout*>(v_layout_item->layout());
    auto* table = qobject_cast<Table*>(v_layout->itemAt(table_indexes.second)->widget());

    v_layout->removeWidget(table);
    delete table;

    if (v_layout->count() == 1) {
        removeItem(v_layout_item);
        delete v_layout_item;
    }
}

void Workspace::run(const std::string& full_file_path) {
    std::string extension = full_file_path.substr(full_file_path.rfind('.') + 1);
    system(std::string(_associations[extension] + " " + full_file_path).c_str());
}

void Workspace::saveWindowSize(QSize window_size) {
    _window_size = window_size;
}

void Workspace::setFixedWindowSizeMode(bool value) {
    _is_fixed_window_size_mode = value;
}