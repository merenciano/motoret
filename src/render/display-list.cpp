#include "display-list.h"
#include "core/manager.h"
#include "render/renderer.h"

namespace leep
{
    DisplayList::DisplayList()
    {

    }

    DisplayList::DisplayList(DisplayList &&other)
    {
        std::swap(command_list_, other.command_list_);
    }

    DisplayList::~DisplayList()
    {

    }

    const std::list<std::unique_ptr<DisplayListCommand>>& DisplayList::command_list() const
    {
        return command_list_;
    }

    void DisplayList::submit()
    {
        Manager::instance().renderer().addDisplayListToQueue(std::move(*this));
    }
}