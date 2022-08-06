//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include <common/compilers.h>

#include <gsl/gsl>

// Disable compiler and linter warnings originating from 'fmt' and for which we
// cannot do anything.
ASAP_DIAGNOSTIC_PUSH
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wsigned-enum-bitfield"
#endif
#include <fmt/core.h>
ASAP_DIAGNOSTIC_POP

#include <gmock/gmock-more-matchers.h>
#include <gtest/gtest.h>

// Disable compiler and linter warnings originating from the unit test framework
// and for which we cannot do anything. Additionally, every TEST or TEST_X macro
// usage must be preceded by a '// NOLINTNEXTLINE'.
ASAP_DIAGNOSTIC_PUSH
#if defined(__clang__) && ASAP_HAS_WARNING("-Wused-but-marked-unused")
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wunused-member-function"
#endif
// NOLINTBEGIN(used-but-marked-unused)

using ::testing::Eq;
using ::testing::HasSubstr;
using ::testing::IsFalse;
using ::testing::IsTrue;
using ::testing::Ne;

#include <logging/logging.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <mutex>
#include <sstream>

template <typename Mutex>
class TestSink : public spdlog::sinks::base_sink<Mutex> {
public:
  void Reset() {
    out_.clear();
    called_ = 0;
  }

  std::ostringstream out_;
  int called_{0};

protected:
  void sink_it_(const spdlog::details::log_msg &msg) override {
    ++called_;
    out_.write(
        msg.payload.data(), static_cast<std::streamsize>(msg.payload.size()));
    out_.write("\n", 1);
  }

  void flush_() override {
    out_.flush();
  }
};

using TestSink_mt = TestSink<std::mutex>;
using TestSink_st = TestSink<spdlog::details::null_mutex>;

namespace asap::logging {

class Foo : Loggable<Foo> {
public:
  Foo() {
    ASLOG(trace, "Foo constructor");
  }

  static const char *const LOGGER_NAME;
};
const char *const Foo::LOGGER_NAME = "foo";

// NOLINTNEXTLINE
TEST(Logging, Loggable) {
  auto *test_sink = gsl::owner<TestSink_mt *>(new TestSink_mt());
  auto test_sink_ptr = std::shared_ptr<spdlog::sinks::sink>(test_sink);

  Registry::PushSink(test_sink_ptr);

  Foo foo;
  EXPECT_THAT(test_sink->called_, Eq(1));
  auto msg = test_sink->out_.str();
  EXPECT_THAT(msg.empty(), IsFalse());
  EXPECT_THAT(msg.find("Foo constructor"), Ne(std::string::npos));

  Registry::PopSink();
}

// NOLINTNEXTLINE
TEST(Logging, MultipleThreads) {
  auto *test_sink = gsl::owner<TestSink_mt *>(new TestSink_mt());
  spdlog::set_pattern("%v");
  auto test_sink_ptr = std::shared_ptr<spdlog::sinks::sink>(test_sink);
  Registry::PushSink(test_sink_ptr);

  constexpr auto c_num_iterations = 5;

  std::thread th1([&]() {
    for (auto ii = 0; ii < c_num_iterations; ++ii) {
      ASLOG_MISC(debug, "THREAD_1: {}", ii);
    }
  });
  std::thread th2([&]() {
    auto &test_logger = Registry::GetLogger("testing");
    for (auto ii = 0; ii < c_num_iterations; ++ii) {
      ASLOG_TO_LOGGER(test_logger, trace, "THREAD_2: {}", ii);
    }
  });
  th1.join();
  th2.join();

  EXPECT_THAT(test_sink->called_, Eq(2 * c_num_iterations));
  std::istringstream msg_reader(test_sink->out_.str());
  std::string line;
  auto expected_seq_th1 = 0;
  auto expected_seq_th2 = 0;
  while (std::getline(msg_reader, line)) {
    if (line.find("THREAD_1") != std::string::npos) {
      EXPECT_THAT(line.find(std::string("THREAD_1: ") +
                            std::to_string(expected_seq_th1)),
          Ne(std::string::npos));
      ++expected_seq_th1;
    }
    if (line.find("THREAD_2") != std::string::npos) {
      EXPECT_THAT(line.find(std::string("THREAD_2: ") +
                            std::to_string(expected_seq_th2)),
          Ne(std::string::npos));
      ++expected_seq_th2;
    }
  }
  EXPECT_THAT(expected_seq_th1, Eq(c_num_iterations));
  EXPECT_THAT(expected_seq_th2, Eq(c_num_iterations));

  Registry::PopSink();
}

// NOLINTNEXTLINE
TEST(Logging, LogWithPrefix) {
  auto *test_sink = gsl::owner<TestSink_mt *>(new TestSink_mt());
  auto test_sink_ptr = std::shared_ptr<spdlog::sinks::sink>(test_sink);
  Registry::PushSink(test_sink_ptr);

  auto &test_logger = Registry::GetLogger("testing");

  AS_DO_LOG(test_logger, debug, "message");
  EXPECT_THAT(test_sink->called_, Eq(1));
  EXPECT_THAT(test_sink->out_.str(), HasSubstr("message"));
  test_sink->Reset();

  AS_DO_LOG(test_logger, debug, "message {}", 1);
  EXPECT_THAT(test_sink->called_, Eq(1));
  EXPECT_THAT(test_sink->out_.str(), HasSubstr("message 1"));
  test_sink->Reset();

  AS_DO_LOG(test_logger, debug, "message {} {}", 1, 2);
  EXPECT_THAT(test_sink->called_, Eq(1));
  EXPECT_THAT(test_sink->out_.str(), HasSubstr("message 1 2"));
  test_sink->Reset();

  AS_DO_LOG(test_logger, debug, "message {} {} {}", 1, 2, 3);
  EXPECT_THAT(test_sink->called_, Eq(1));
  EXPECT_THAT(test_sink->out_.str(), HasSubstr("message 1 2 3"));
  test_sink->Reset();

  AS_DO_LOG(test_logger, debug, "message {} {} {} {}", 1, 2, 3, 4);
  EXPECT_THAT(test_sink->called_, Eq(1));
  EXPECT_THAT(test_sink->out_.str(), HasSubstr("message 1 2 3 4"));
  test_sink->Reset();

  Registry::PopSink();
}

namespace {
class MockSink : public spdlog::sinks::sink {
public:
  void log(const spdlog::details::log_msg & /*msg*/) override {
    ++called_;
  }
  void flush() override {
  }
  void set_pattern(const std::string & /*pattern*/) override {
  }
  void set_formatter(
      std::unique_ptr<spdlog::formatter> /*sink_formatter*/) override {
  }

  void Reset() {
    called_ = 0;
  }

  int called_{0};
};
} // namespace

// NOLINTNEXTLINE
TEST(Logging, LogPushSink) {
  auto *first_mock = gsl::owner<MockSink *>(new MockSink());
  auto *second_mock = gsl::owner<MockSink *>(new MockSink());
  auto first_sink_ptr = std::shared_ptr<spdlog::sinks::sink>(first_mock);
  auto second_sink_ptr = std::shared_ptr<spdlog::sinks::sink>(second_mock);

  auto &test_logger = Registry::GetLogger("testing");
  Registry::PushSink(first_sink_ptr);
  ASLOG_TO_LOGGER(test_logger, debug, "message");

  EXPECT_THAT(first_mock->called_, Eq(1));
  first_mock->Reset();
  second_mock->Reset();

  Registry::PushSink(second_sink_ptr);
  ASLOG_TO_LOGGER(test_logger, debug, "message");

  EXPECT_THAT(first_mock->called_, Eq(0));
  EXPECT_THAT(second_mock->called_, Eq(1));
  first_mock->Reset();
  second_mock->Reset();

  Registry::PopSink();
  ASLOG_TO_LOGGER(test_logger, debug, "message");

  EXPECT_THAT(first_mock->called_, Eq(1));
  EXPECT_THAT(second_mock->called_, Eq(0));
  first_mock->Reset();
  second_mock->Reset();

  Registry::PopSink();
  // mute the logger output
  auto *test_sink = gsl::owner<TestSink_mt *>(new TestSink_mt());
  auto test_sink_ptr = std::shared_ptr<spdlog::sinks::sink>(test_sink);
  Registry::PushSink(test_sink_ptr);
  ASLOG_TO_LOGGER(test_logger, debug, "message");

  EXPECT_THAT(first_mock->called_, Eq(0));
  EXPECT_THAT(second_mock->called_, Eq(0));

  Registry::PopSink();
}

} // namespace asap::logging
