/*
 * Log Health (part of Equid project)
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include "LogTimePoint.hpp"

class LogTimeSpan
{
public:
    LogTimeSpan();
    LogTimeSpan(LogTimePoint start,
                LogTimePoint end);
    LogTimeSpan(const LogTimeSpan &rhs) = default;
    LogTimeSpan& operator=(const LogTimeSpan &rhs) = default;
    virtual ~LogTimeSpan() = default;

    /**
     * @brief      Determine whether the time span is sane.
     *
     * @return     @c true if the time span is valid, @c false otherwise.
     */
    bool isValid() const;

    /**
     * @brief      Get the start of the log's time span.
     *
     * @return     The starting point of log's time span.
     */
    LogTimePoint getStart() const;

    /**
     * @brief      Get the right boundary of log's time span.
     *
     * @return     The ending point of log's time span.
     */
    LogTimePoint getEnd() const;

    /**
     * @brief      Get span's duration
     *
     * @return     The duration.
     */
    LogTimePoint getDuration() const;

private:
    LogTimePoint    _start;
    LogTimePoint    _end;
};