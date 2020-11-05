#pragma once
#include <stdlib.h>
#include <exception>

namespace homework02
{
    template <class T, size_t size>
    class reserve_allocator
    {
    public:
        using value_type = T;

        template <typename U>
        struct rebind
        {
            using other = reserve_allocator<U, size>;
        };

        reserve_allocator();

        template <class U>
        reserve_allocator(const reserve_allocator<U, size>&);

        T *allocate(size_t);
        void deallocate(T*, std::size_t) noexcept;

        ~reserve_allocator();

        template <typename U>
        constexpr bool operator==(const reserve_allocator<U, size> &) noexcept;

        template <typename U>
        constexpr bool operator!=(const reserve_allocator<U, size> &) noexcept;

    private:
        void create_data(size_t n);

    private:
        T *data;
        size_t used;
    };
} // namespace homework02