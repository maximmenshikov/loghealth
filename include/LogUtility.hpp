/*
 * Log Health (part of Equid project)
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include <string>
#include <map>
#include "LogTimeSpan.hpp"
#include "LogSummary.hpp"

class LogUtility
{
public:
    /**
     * @brief      Get the time point from the log line.
     *
     * @param      line  The log line ("[time point] data")
     *
     * @return     The log time point
     */
    static LogTimePoint pointFromLine(const std::string &line);

    /**
     * @brief      Read a complete time span from the log, i.e. the starting
     *             and ending points
     *
     * @param      path  The path to a single log file
     *
     * @return     The log time span
     */
    static LogTimeSpan readTimeSpan(const std::string &path);

    /**
     * @brief      Reads time spans for all files in the folder
     *
     * @param      path  The path to the directory containing log files
     *
     * @return     Map of <file path, time span> objects
     */
    static std::map<std::string, LogTimeSpan> readTimeSpans(
        const std::string &path);

    /**
     * @brief      Get the aggregate time span for the map of
     *             <file path, time span> objects.
     *
     * @param      map   The <file path, time span> map
     *
     * @return     The aggregate time span
     */
    static LogTimeSpan getAggregateTimeSpan(
        std::map<std::string, LogTimeSpan> &map);

    /**
     * @brief      Get the log summary for the file
     *
     * @param      path          The path to the file
     * @param      aggrTimeSpan  The aggregate time span
     *
     * @return     The log summary
     */
    static LogSummary getLogSummary(const std::string &path,
                                    const LogTimeSpan &aggrTimeSpan);

    /**
     * @brief      Get log summaries for all files in specified directory
     *
     * @param      path          The path to the directory
     * @param      aggrTimeSpan  The aggregate time span
     *
     * @return     The map <file path, LogSummary> for all files
     */
    static std::map<std::string, LogSummary> getLogSummaries(
        const std::string &path,
        const LogTimeSpan &aggrTimeSpan);

    /**
     * @brief      Get the time allocation for all spans in the map
     *
     * @param      map           The map of <file name, time span>
     * @param      aggrTimeSpan  The aggregate time span.
     *
     * @return     The map <file name, time percentage>
     */
    static std::map<std::string, int> getTimePercentage(
        std::map<std::string, LogTimeSpan> &map,
        LogTimeSpan aggrTimeSpan);
private:
    static const int _maxLineLength = 1000;
};