#pragma once

#include <memory>
#include <iostream>

namespace homework02
{
    template <typename T, typename Allocator = std::allocator<T>>
    class strange_struct
    {
    public:
        strange_struct();
        ~strange_struct();

        size_t size() const noexcept;

        template <typename... Args>
        void emplace_back(Args... args);

        template <typename Type, typename A>
        friend std::ostream& operator<<(std::ostream& stream, const strange_struct<Type, A>&);

    private:
        struct Node
        {
            T *data;
            std::shared_ptr<Node> next;
            explicit Node(T *item) : data(item), next(nullptr) {}
            ~Node() = default;
        };

        Allocator allocator;

        std::shared_ptr<Node> _first;
        std::shared_ptr<Node> _last;

        size_t _size;
    };
} // namespace homework02