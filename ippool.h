#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "ipv4.h"

using IPPoolDataType = std::vector<IPv4>;
using IPPoolConstIterator = IPPoolDataType::const_iterator;
using IPPoolIterator = IPPoolDataType::iterator;
using IPPoolReverseIterator = IPPoolDataType::reverse_iterator;

class IPPool {
public:
    void push_back(const IPv4StringVector& ip);

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
            , delimeter(delimeter){}

        template <typename Action
        //,typename Function = typename std::enable_if_t<std::is_function_v<Action>, void>
            >
        void for_each(Action action) {
            reset();

            for(next(); !end(); next())
                action(*current);
            
        }

        friend std::ostream& operator<<(std::ostream& stream, Filter<Predicate>& f) {
            f.reset();

            for(f.next(); !f.end(); f.next())
                stream << *(f.current) << f.delimeter;

            return stream;
        }

    private:
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

        void reset() {
            filter_used = false;
            current = ip_pool.cbegin();
        }        

    private:
        const IPPool& ip_pool;
        IPPoolConstIterator current;
        Predicate predicate;
        bool filter_used = false;
        char delimeter;
    };

    template <typename Predicate>
    Filter<Predicate> filter(Predicate predicate) const {
        return Filter<Predicate>(*this, predicate);
    }

private:
    IPPoolDataType pool;
};