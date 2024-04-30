#include "ContextMenu.hpp"

#include "Elements/Title.hpp"

#include "Application.hpp"
#include "Window/BackgroundWindow.hpp"
#include "Window/UpdatableWindow.hpp"

template <>
ContextMenu<Title>::ContextMenu(Title* parent_widget): QMenu(parent_widget), _parent_widget(parent_widget) {}

template <>
ContextMenu<BackgroundWindow<UpdatableWindow<Application>>>::ContextMenu(BackgroundWindow<UpdatableWindow<Application>>* parent_widget):
    QMenu(parent_widget), _parent_widget(parent_widget) {}
