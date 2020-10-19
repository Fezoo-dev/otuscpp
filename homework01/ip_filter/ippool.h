#pragma once
#include <vector>
#include <iostream>
#include <iterator>
#include "ipv4.h"

using IPPoolDataType = std::vector<IpV4>;
using IPPoolConstIterator = IPPoolDataType::const_iterator;
using IPPoolIterator = IPPoolDataType::iterator;
using IPPoolReverseIterator = IPPoolDataType::reverse_iterator;

class IPPool {
public:
    void push_back(const IpV4StringVector& ip);

    IPPoolConstIterator cbegin() const;
    IPPoolConstIterator cend() const;
    IPPoolIterator begin();
    IPPoolIterator end();
    IPPoolReverseIterator rbegin();
    IPPoolReverseIterator rend();

    template <typename Predicate>
    class Filter
    {
    public:
        Filter(const IPPool& ip_pool, Predicate predicate, char delimeter = '\n')
            : ip_pool(ip_pool)
            , current(ip_pool.pool.begin())
            , predicate(predicate)
            , filter_used(false)
            , delimeter(delimeter){}

        bool end() const {
            return current == ip_pool.cend();
        }

        IPPoolConstIterator next() {
            if (filter_used)
                ++current;
            else
                filter_used = true;

            if (end())
                return current;
            
            current = std::find_if(current, ip_pool.cend(), predicate);
            return current;
        }

        void Reset() {
            filter_used = false;
            current = ip_pool.cbegin();
        }

        /// <summary>
        /// Maybe it's a bad idea to change inner state here,
        /// but if you just want to display filtered data,
        /// you can do it simply.
        /// </summary>
        friend std::ostream& operator<<(std::ostream& stream, Filter<Predicate>& f) {
            f.Reset();

            for(f.next(); !f.end(); f.next())
                stream << *(f.current) << f.delimeter;

            f.Reset();
            return stream;
        }

    private:
        const IPPool& ip_pool;
        Predicate predicate;
        IPPoolConstIterator current;
        bool filter_used;
        char delimeter;
    };

    template <typename Predicate>
    Filter<Predicate> filter(Predicate predicate) const {
        return Filter<Predicate>(*this, predicate);
    }

private:
    IPPoolDataType pool;
};