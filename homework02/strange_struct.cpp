#include "strange_struct.hpp"
#include <iostream>

namespace homework02
{
    template <typename T, typename Allocator>
    strange_struct<T, Allocator>::strange_struct() : _first(nullptr), _last(nullptr), _size(0){}

    template <typename T, typename Allocator>
    strange_struct<T, Allocator>::~strange_struct()
    {
        for (auto tmp = _first; tmp; tmp = _first)
        {
            _first = tmp->next;
            tmp.reset();
        }
    }

    template <typename T, typename Allocator>
    size_t strange_struct<T, Allocator>::size() const noexcept
    {
        return _size;
    }

    template <typename T, typename Allocator>
    template <typename... Args>
    void strange_struct<T, Allocator>::emplace_back(Args... args)
    {

        auto new_item = new (allocator.allocate(1)) T(args...);

        if (_first.get())
        {
            _last->next = std::make_shared<Node>(new_item);
            _last = _last->next;
        }
        else
        {
            _first = std::make_shared<Node>(new_item);
            _last = _first;
        }
        _size++;
    }

    template <typename T, typename Allocator>
    std::ostream& operator<<(std::ostream& stream, const strange_struct<T, Allocator>& ss)
    {
        for (auto tmp = ss._first; tmp; tmp = tmp->next)
            stream << *(tmp->data);
        return stream;
    }
} // namespace homework02