#include "Elements/Table.hpp"

#include "Elements/Folder.hpp"
#include "Elements/File.hpp"
#include "Elements/Title.hpp"
#include "Workspace/Workspace.hpp"

#include "clearLayout.hpp"
#include "parentLayout.hpp"

Table::Table(const std::string& folder_path, Workspace* parent): QFrame(), _parent(parent) {
    _watcher = std::make_shared<QFileSystemWatcher>(this);
    connect(_watcher.get(), SIGNAL(fileChanged(QString)), this, SLOT(changed(QString)));

    load(folder_path);

    setObjectName("table");
    setStyleSheet("QFrame#table { border: 1px solid rgb(124, 58, 237); border-radius: 6px; }");
    _layout.setContentsMargins(5, 5, 5, 5);
    setLayout(&_layout);
}

void Table::changed(const QString& full_path) {
    load();
}

void Table::checkTable() {
    if (!std::filesystem::exists(_folder_path)) {
        remove();
        return;
    }
    int dir_elements = 0;
    for (const auto& entry: std::filesystem::directory_iterator(_folder_path)) dir_elements++;
    if (dir_elements != _layout.count()-3) load();
}

Table* Table::createTable(const std::string& folder_path) {
    return _parent->createTable(folder_path);
}

void Table::deselectParent() {
    // TODO: still not working
    auto* element = qobject_cast<Element*>(_layout.itemAt(0)->widget());
    auto parents = _parent->getParentElements(element->getFullPath());
    for (auto parent: parents) {
        parent->select(false, false);
    }
}

std::pair<int, int> Table::getIndexes() {
    QLayout* parent_layout = parentLayout(this);
    return {_parent->indexOf(parent_layout), parent_layout->indexOf(this)};
}

QVBoxLayout* Table::getLayout() {
    return &_layout;
}

void Table::load(const std::string& folder_path) {
    _folder_path = folder_path;
    _watcher->removePaths(_watcher->directories());
    _watcher->removePaths(_watcher->files());

    clearLayout(&_layout);
    _layout.addStretch(1);

    int folders_amount = 0;
    auto* separator = new QWidget(); separator->setStyleSheet("background-color: rgb(124, 58, 237);"); separator->setFixedHeight(1);
    auto* title = new Title(folder_path, this);
    title->setToolTip(folder_path.c_str());
    _layout.insertWidget(0, title);
    _layout.insertWidget(1, separator);

    for (const auto& entry: std::filesystem::directory_iterator(folder_path)) {
        std::wstring w_full_path = entry.path().wstring();
        std::string full_path = _converter.to_bytes(w_full_path);
        _watcher->addPath(QString(full_path.c_str()));

        if (std::filesystem::is_directory(full_path)) {
            _layout.insertWidget(folders_amount+2, new Folder(full_path, this));
            folders_amount++;
        } else {
            _layout.insertWidget(_layout.count()-1, new File(full_path));
        }
    }
}

void Table::load() {
    load(_folder_path);
}

void Table::relocate() {
    _parent->relocateTable(getIndexes());
}

void Table::remove() {
    _parent->removeTable(getIndexes());
}

void Table::showContents(bool value) {
    auto* separator = qobject_cast<QWidget*>(_layout.itemAt(1)->widget());
    separator->setVisible(value);
    for (int i = 2; i < _layout.count()-1; i++) {
        auto* element = qobject_cast<Element*>(_layout.itemAt(i)->widget());
        element->setVisible(value);
    }
}

void Table::showTable(bool value) {
    if (!value) {
        setFixedSize(size());
    } else {
        setMinimumSize(0, 0);
        setMaximumSize(1920, 1080);
    }

    for (int i = 0; i < _layout.count()-1; i++) {
        if (i == 1) continue;
        auto* element = qobject_cast<Element*>(_layout.itemAt(i)->widget());
        element->showElement(value);
    }
}

void Table::toggleShowContents() {
    if (_is_hidden) {
        showContents(true);
        _is_hidden = false;
    } else {
        showContents(false);
        _is_hidden = true;
    }
}
