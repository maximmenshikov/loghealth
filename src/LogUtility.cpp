/*
 * Log Health (part of Equid project)
 * (C) Maxim Menshikov 2019-2020
 */
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <math.h>
#include "LogUtility.hpp"
#include "LogSummary.hpp"

/* See the description in LogUtility.hpp */
LogTimePoint
LogUtility::pointFromLine(const std::string &line)
{
    auto start = line.find("[");
    auto end = line.find("]");

    if (start == std::string::npos || end == std::string::npos)
        return LogTimePoint();

    return std::stoull(line.substr(start + 1, end - start - 1));
}

/* See the description in LogUtility.hpp */
LogTimeSpan
LogUtility::readTimeSpan(const std::string &path)
{
    std::ifstream ifs(path);
    std::string   line;
    LogTimePoint  ptStart = 0;
    LogTimePoint  ptEnd = 0;
    int           fileLength;

    if (!std::getline(ifs, line, '\n'))
        return LogTimeSpan();

    ptStart = pointFromLine(line);

    ifs.seekg(0, ifs.end);
    fileLength = ifs.tellg();
    ifs.seekg((fileLength > _maxLineLength)
                ? (fileLength - _maxLineLength)
                : 0, ifs.beg);

    while (std::getline(ifs, line, '\n'))
    {
        ptEnd = pointFromLine(line);
    }

    return LogTimeSpan(ptStart, ptEnd);
}

/* See the description in LogUtility.hpp */
std::map<std::string, LogTimeSpan>
LogUtility::readTimeSpans(const std::string &path)
{
    std::map<std::string, LogTimeSpan> map;

    for (auto& p: std::filesystem::directory_iterator(path))
    {
        if (p.path().extension() == ".log")
        {
            map[p.path().filename().string()] = readTimeSpan(p.path());
        }
    }

    return map;
}

/* See the description in LogUtility.hpp */
LogTimeSpan
LogUtility::getAggregateTimeSpan(std::map<std::string, LogTimeSpan> &map)
{
    LogTimePoint start = 0;
    LogTimePoint end = 0;

    for (auto &kv : map)
    {
        if (!kv.second.isValid())
            continue;

        if (start > kv.second.getStart() || start == 0)
            start = kv.second.getStart();
        if (end < kv.second.getEnd() || end == 0)
            end = kv.second.getEnd();
    }

    return LogTimeSpan(start, end);
}

/* See the description in LogUtility.hpp */
LogSummary
LogUtility::getLogSummary(const std::string &path,
                          const LogTimeSpan &aggrTimeSpan)
{
    LogSummary    ls;
    std::ifstream ifs(path);
    std::string   line;
    LogTimePoint  pt;
    int           fileLength;
    LogTimePoint  duration = aggrTimeSpan.getEnd() - aggrTimeSpan.getStart();

    while (std::getline(ifs, line, '\n'))
    {
        int ptIndex = (pointFromLine(line) - aggrTimeSpan.getStart()) /
            (duration / LogSummary::getCount());

        if (ptIndex >= LogSummary::getCount())
            ptIndex = LogSummary::getCount() - 1;
        auto &pt = ls.getPoint(ptIndex);

        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        if (line.find("error") != std::string::npos ||
            line.find("failed") != std::string::npos)
        {
            pt.addError();
        }
        else
        {
            pt.addMessage();
        }
    }

    return ls;
}

/* See the description in LogUtility.hpp */
std::map<std::string, LogSummary>
LogUtility::getLogSummaries(const std::string &path,
                            const LogTimeSpan &aggrTimeSpan)
{
    std::map<std::string, LogSummary> map;

    for (auto& p: std::filesystem::directory_iterator(path))
    {
        if (p.path().extension() == ".log")
        {
            map[p.path().filename().string()] = getLogSummary(p.path().string(),
                aggrTimeSpan);
        }
    }

    return map;
}

/* See the description in LogUtility.hpp */
std::map<std::string, int>
LogUtility::getTimePercentage(
    std::map<std::string, LogTimeSpan> &map,
    LogTimeSpan aggrTimeSpan)
{
    std::map<std::string, int> result;

    for (auto &obj : map)
    {
        double percentage = (double)obj.second.getDuration() /
            (double)aggrTimeSpan.getDuration() * 100.0;

        result[obj.first] = (int)floor(percentage);
    }

    return result;
}