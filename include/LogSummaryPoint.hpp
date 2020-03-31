/*
 * Log Health (part of Equid project)
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include <string>

class LogSummaryPoint
{
public:
    LogSummaryPoint();
    LogSummaryPoint(const LogSummaryPoint &rhs) = default;
    LogSummaryPoint& operator=(const LogSummaryPoint &rhs) = default;
    virtual ~LogSummaryPoint() = default;

    /**
     * @brief      Account the simple message
     */
    void addMessage();
    /**
     * @brief      Account the simple error
     */
    void addError();

    /**
     * @brief      Get total message count for point.
     *
     * @return     The total message count.
     */
    int getTotalMessageCount() const;

    /**
     * @brief      Convert a point to a string representation
     *
     * @return     String representation of the summary point.
     */
    std::string toString(int maxPoints = 1000) const;

private:
    int _messageCount;
    int _errorCount;

};