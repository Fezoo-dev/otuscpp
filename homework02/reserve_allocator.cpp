#include "reserve_allocator.hpp"
#include <stdlib.h>
#include <exception>

namespace homework02
{
    template <class T, size_t size>
    reserve_allocator<T, size>::reserve_allocator() : data(NULL), used(0){}

    template <class T, size_t size>
    T* reserve_allocator<T, size>::allocate(size_t)
    {
        if (!data)
            create_data(size);

        if (size > 0 && used < size)
            return data + used++;
        throw std::bad_alloc();
    }

    template <class T, size_t size>
    void reserve_allocator<T, size>::deallocate(T *, std::size_t) noexcept
    {
        if (used > 0)
            used--;
    }

    template <class T, size_t size>
    template <class U>
    reserve_allocator<T, size>::reserve_allocator(const reserve_allocator<U, size> &) {}

    template <class T, size_t size>
    reserve_allocator<T, size>::~reserve_allocator()
    {
        if (data)
            free(data);
    }

    template <typename T, size_t size>
    template <typename U>
    constexpr bool reserve_allocator<T, size>::operator==(const reserve_allocator<U, size>&) noexcept
    {
        return true;
    }

    template <typename T, size_t size>
    template <typename U>
    constexpr bool reserve_allocator<T, size>::operator!=(const reserve_allocator<U, size>&) noexcept
    {
        return false;
    }

    template <class T, size_t size>
    void reserve_allocator<T, size>::create_data(size_t n)
    {
        data = reinterpret_cast<T *>(malloc(n * sizeof(T)));
        if (!data)
            throw std::bad_alloc();

        used = 0;
    }

} // namespace homework02