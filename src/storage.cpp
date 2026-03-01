#include "storage.h"
#include <iostream>

Storage::Storage(const std::string& fname) : filename(fname) {
}

Storage::~Storage() {
    closeFile();
}

void Storage::closeFile() {
    if (file.is_open()) {
        file.close();
    }
}

void Storage::openForWriting() {
    closeFile();
    file.open(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw FileOpenException(filename);
    }
}

void Storage::openForReading() {
    closeFile();
    file.open(filename, std::ios::in);
    if (!file.is_open()) {
        throw FileOpenException(filename);
    }
}

bool Storage::fileExists() const {
    return std::filesystem::exists(filename);
}

void Storage::saveLogs(const std::vector<std::unique_ptr<DailyLog>>& logs) {
    try {
        openForWriting();
        file << logs.size() << "\n";
        for (const auto& log : logs) {
            file << log->serialize() << "\n";
            if (file.fail()) {
                throw StorageException("Failed to write to file");
            }
        }

        std::cout << "Saved " << logs.size() << " logs to " << filename << "\n";
        closeFile();
    } catch (const std::exception& e) {
        closeFile();
        throw;
    }
}
std::optional<std::vector<std::unique_ptr<DailyLog>>> Storage::loadLogs() {
    if (!fileExists()) {
        return std::nullopt;
    }

    try {
        openForReading();
        size_t logCount;
        file >> logCount;
        file.ignore();

        std::vector<std::unique_ptr<DailyLog>> logs;

        for (size_t i = 0; i < logCount; ++i) {
            std::string line;
            std::getline(file, line);
            if (file.fail()) {
                throw ParseException("Failed to read line " + std::to_string(i));
            }
            try {
                auto log = DailyLog::deserialize(line);
                logs.push_back(std::move(log));
            } catch (const std::exception& e) {
                throw ParseException("Line " + std::to_string(i) + ": " + e.what());
            }
        }
        std::cout << "Loaded " << logs.size() << " logs from " << filename << "\n";
        closeFile();
        return logs;

    } catch (const FileOpenException& e) {
        throw;
    } catch (const std::exception& e) {
        closeFile();
        throw;
    }
}