/*
 * Log Health (part of Equid project)
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include <string>
#include "LogSummaryPoint.hpp"

class LogSummary
{
public:
    LogSummary() = default;
    LogSummary(const LogSummary &rhs) = default;
    LogSummary& operator=(const LogSummary &rhs) = default;
    virtual ~LogSummary() = default;

    /**
     * @brief      Get the point for the direct access
     *
     * @param      i     Index of the point
     *
     * @return     The reference to the point
     */
    LogSummaryPoint& getPoint(size_t i);

    /**
     * @brief      Get the number of points.
     *
     * @return     The number of points in the summary.
     */
    static int getCount();

    /**
     * @brief      Get a string representation of the summary.
     *
     * @return     String representation of the summary
     */
    std::string toString() const;

private:
    static const int _totalPoints = 40;
    LogSummaryPoint  _points[LogSummary::_totalPoints];
};