#include <catch.hpp>

#include "log.h"
#include "logger.h"
#include "default_formatter.h"

#include "dummy_log_target.h"
#include "dummy_formatter.h"

TEST_CASE("End to end logging.", "[Log]")
{
	SECTION("Null cases")
	{
		// should not throw exceptions
		
		Log::log("Level", "Category", "Message");

		const char* nullChar = nullptr;
		auto logger = Log::logger(nullChar);
		REQUIRE(nullptr == logger);

		LogTarget* nullLogtarget = nullptr;
		Log::addTarget(nullLogtarget);
		Log::removeTarget(nullLogtarget);
	}

	SECTION("Adding and removing LogTargets.")
	{
		auto target = new DummyLogTarget();

		Log::addTarget(target);

		const char* message = "Message";
		Log::log("", "", message);
		REQUIRE(target->lastMessage == message);
		target->lastMessage = nullptr;

		Log::removeTarget(target);
		Log::log("", "", message);
		REQUIRE(target->lastMessage == nullptr);

		delete target;
	}

	SECTION("Multiple targets.")
	{
		auto dummy = new DummyLogTarget();
		auto dummy2 = new DummyLogTarget();

		Log::addTarget(dummy);
		Log::addTarget(dummy2);

		REQUIRE(dummy->lastMessage == dummy2->lastMessage);

		Log::removeTarget(dummy);
		Log::removeTarget(dummy2);

		delete dummy;
		delete dummy2;
	}

	SECTION("Integration.")
	{
		const char* expected = "EXPECTED";
		auto target = new DummyLogTarget();
		auto formatter = new DummyFormatter(expected);

		Log::addTarget(target);
		Log::setFormatter(formatter);

		const char* category = "Test";
		const char* message = "TestMessage";
		auto logger = Log::logger(category);
		logger->debug(message);

		REQUIRE(0 == strncmp(
			expected,
			target->lastMessage,
			strlen(expected) - 1));

		REQUIRE(0 == strcmp("debug", formatter->level));
		REQUIRE(0 == strcmp(category, formatter->category));
		REQUIRE(0 == strcmp(message, formatter->message));

		Log::removeTarget(target);
		Log::setFormatter(nullptr);

		delete formatter;
		delete target;
	}

	SECTION("Logger creation and reuse.")
	{
		auto a = Log::logger("a");
		auto b = Log::logger("b");

		REQUIRE(a != b);

		auto a2 = Log::logger("a");

		REQUIRE(a2 == a);
	}
}