/*
 * Log Health (part of Equid project)
 * (C) Maxim Menshikov 2019-2020
 */
#include <algorithm>
#include <any>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "LogUtility.hpp"

const int maxNameWidth = 20;

/**
 * @brief      Duplicates a space as many times as @p len suggsets
 *
 * @param      len   The number of spaces
 *
 * @return     A string consisting of a spaces.
 */
static std::string
dupSpace(int len)
{
    std::string s;

    if (len < 0)
        return s;

    s.reserve(len);
    for (int i = 0; i < len; ++i)
        s += " ";
    return s;
}

int
main(int argc, const char *argv[])
{
    std::string logFolderPath;

    if (argc != 2)
    {
        std::cerr << "Usage: " << std::string(argv[0]) << " log_folder_path"
                  << std::endl;
        return 1;
    }

    logFolderPath.assign(argv[1]);

    auto spans = LogUtility::readTimeSpans(logFolderPath);
    auto aggrTimeSpan = LogUtility::getAggregateTimeSpan(spans);
    auto percentages = LogUtility::getTimePercentage(spans, aggrTimeSpan);
    auto summaries = LogUtility::getLogSummaries(logFolderPath, aggrTimeSpan);

    for (auto &kv : summaries)
    {
        std::filesystem::path p = kv.first;
        std::string fileNameWithoutExt = p.stem().string();

        std::cout << fileNameWithoutExt
                  << dupSpace(maxNameWidth - fileNameWithoutExt.size())
                  << std::setw(3) << percentages[kv.first] << "% "
                  << kv.second.toString() << std::endl;
    }
    return 0;
}