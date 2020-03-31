/*
 * Log Health (part of Equid project)
 * (C) Maxim Menshikov 2019-2020
 */
#include <array>
#include "LogSummaryPoint.hpp"
#include <array>

/* See the description in LogSummaryPoint.hpp */
LogSummaryPoint::LogSummaryPoint()
{
    _messageCount = 0;
    _errorCount = 0;
}

/* See the description in LogSummaryPoint.hpp */
void
LogSummaryPoint::addMessage()
{
    _messageCount++;
}

/* See the description in LogSummaryPoint.hpp */
void
LogSummaryPoint::addError()
{
    _errorCount++;
}

/* See the description in LogSummaryPoint.hpp */
int
LogSummaryPoint::getTotalMessageCount() const
{
    return _errorCount + _messageCount;
}

/* See the description in LogSummaryPoint.hpp */
std::string
LogSummaryPoint::toString(int maxPoints) const
{
    std::array<std::string, 5> messageCounters = { "𝍠", "𝍡", "𝍢", "𝍣", "𝍤"};
    size_t  counterIndex;

    if (_errorCount > 0)
        return "𝍭";

    if (_messageCount == 0)
        return messageCounters[0];

    counterIndex = (_messageCount / maxPoints * (messageCounters.size() - 1))
        + 1;
    if (counterIndex > (messageCounters.size() - 1))
        counterIndex = messageCounters.size() -1;
    return messageCounters[counterIndex];
}
