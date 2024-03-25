#include "expresscpp/console.hpp"

#include <iostream>

#ifdef EXPRESSCPP_USE_STACKTRACE
#include "boost/stacktrace.hpp"
#endif

#include "expresscpp/date.hpp"
#include "expresscpp/impl/utils.hpp"

namespace expresscpp {

std::mutex Console::mutex_;

LogLevel Console::log_level_ = LogLevel::kError;

void Console::PrintMessage(const std::string_view prefix, const std::string_view color,
                           const std::string_view message) {
  std::cout << color << "[" << Date::getTime() << "]" << prefix << " -- " << message << kReset << std::endl;
}

void Console::Log(const std::string_view message) {
  std::scoped_lock<std::mutex> lock(mutex_);
  PrintMessage(" -L- ", kReset, message);
}

void Console::Trace(const std::string_view message) {
  std::scoped_lock<std::mutex> lock(mutex_);
  PrintMessage(" -T- ", kBoldcyan, message);
#ifdef EXPRESSCPP_USE_STACKTRACE
  std::cerr << boost::stacktrace::stacktrace();
#endif
}

void Console::Error(const std::string_view message) {
  if (log_level_ > LogLevel::kError) {
    return;
  }
  std::scoped_lock<std::mutex> lock(mutex_);
  PrintMessage(" -E- ", kBoldred, message);
}

void Console::Debug(const std::string_view message) {
  if (log_level_ > LogLevel::kDebug) {
    return;
  }
  std::scoped_lock<std::mutex> lock(mutex_);
  PrintMessage(" -D- ", kBlue, message);
}

void Console::setLogLevel(const LogLevel &log_level) {
  log_level_ = log_level;
}

}  // namespace expresscpp
