/*
 * Log Health (part of Equid project)
 * (C) Maxim Menshikov 2019-2020
 */
#include <exception>
#include <stdexcept>
#include "LogSummary.hpp"

/* See the description in LogSummary.hpp */
LogSummaryPoint&
LogSummary::getPoint(size_t i)
{
    if (i >= _totalPoints)
    {
        throw std::out_of_range("Point index is out of range");
    }
    return _points[i];
}

/* See the description in LogSummary.hpp */
int
LogSummary::getCount()
{
    return _totalPoints;
}

std::string
LogSummary::toString() const
{
    std::string s;
    const int   defaultMaxMessages = 5;
    int         maxMessages = defaultMaxMessages;

    s.reserve(_totalPoints);

    for (auto &p : _points)
    {
        maxMessages = std::max(maxMessages, p.getTotalMessageCount());
    }

    for (auto &p : _points)
    {
        s += p.toString(maxMessages);
    }

    return s;
}
