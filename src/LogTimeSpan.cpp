/*
 * Log Health (part of Equid project)
 * (C) Maxim Menshikov 2019-2020
 */
#include "LogTimeSpan.hpp"
#include "LogTimePoint.hpp"

LogTimeSpan::LogTimeSpan()
{
    _start = 0;
    _end = 0;
}

LogTimeSpan::LogTimeSpan(LogTimePoint start,
                         LogTimePoint end)
    : LogTimeSpan()
{
    _start = start;
    _end = end;
}

/* See the description in LogTimeSpan.hpp */
bool
LogTimeSpan::isValid() const
{
    return _start != 0 && _end != 0;
}

/* See the description in LogTimeSpan.hpp */
LogTimePoint
LogTimeSpan::getStart() const
{
    return _start;
}

/* See the description in LogTimeSpan.hpp */
LogTimePoint
LogTimeSpan::getEnd() const
{
    return _end;
}

/* See the description in LogTimeSpan.hpp */
LogTimePoint
LogTimeSpan::getDuration() const
{
    return _end - _start;
}