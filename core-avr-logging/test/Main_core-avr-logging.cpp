#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "Log.h"
#include "Logger.h"
#include "DefaultFormatter.h"

#include <Tuple.h>
#include <LinkedList.h>

template class Tuple<const char, Logger>;
template class LinkedList<Tuple<const char, Logger>>;

TEST_CASE("Logger creation and reuse.", "[Log]")
{
	auto a = Log::logger("a");
}