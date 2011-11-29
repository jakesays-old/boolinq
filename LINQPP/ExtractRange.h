#pragma once

#include <list>
#include <deque>
#include <vector>

template<typename R>
std::list<typename R::traits::value_type> extract_list(R r)
{
    std::list<typename R::traits::value_type> result;
    for (; !r.empty(); r.popFront())
        result.push_back(r.front());
    return result;
}

template<typename R>
std::deque<typename R::traits::value_type> extract_deque(R r)
{
    std::deque<typename R::traits::value_type> result;
    for (; !r.empty(); r.popFront())
        result.push_back(r.front());
    return result;
}

template<typename R>
std::vector<typename R::traits::value_type> extract_vector(R r)
{
    std::vector<typename R::traits::value_type> result;
    for (; !r.empty(); r.popFront())
        result.push_back(r.front());
    return result;
}
