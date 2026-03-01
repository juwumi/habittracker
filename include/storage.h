#ifndef HABITTRACKER_STORAGE_H
#define HABITTRACKER_STORAGE_H

#include "dailylog.h"
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <fstream>
#include <filesystem>
#include <stdexcept>

class StorageException : public std::runtime_error {
public:
    explicit StorageException(const std::string& msg)
        : std::runtime_error("Storage error: " + msg) {}
};

class FileOpenException : public StorageException {
public:
    explicit FileOpenException(const std::string& path)
        : StorageException("Cannot open file: " + path) {}
};

class ParseException : public StorageException {
public:
    explicit ParseException(const std::string& line)
        : StorageException("Failed to parse line: " + line) {}
};

class Storage {
private:
    std::string filename;
    mutable std::fstream file;

public:
    explicit Storage(const std::string& fname);

    ~Storage();
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;

    void saveLogs(const std::vector<std::unique_ptr<DailyLog>>& logs);
    std::optional<std::vector<std::unique_ptr<DailyLog>>> loadLogs();

private:
    void openForWriting();
    void openForReading();
    void closeFile();
    bool fileExists() const;
};
#endif //HABITTRACKER_STORAGE_H