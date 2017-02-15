#include <catch.hpp>
#include <string.h>

#include "DefaultFormatter.h"

TEST_CASE("Formatting", "[DefaultFormatter]")
{
	auto formatter = new DefaultFormatter();

	const char* nullChar = nullptr;

	const char* formattedMessage = formatter->format(nullChar, nullChar, nullChar);
	REQUIRE(0 == strcmp("[NULL][NULL] NULL", formattedMessage));
	delete[] formattedMessage;

	formattedMessage = formatter->format("INFO", nullChar, nullChar);
	REQUIRE(0 == strcmp("[INFO][NULL] NULL", formattedMessage));
	delete[] formattedMessage;

	formattedMessage = formatter->format("INFO", "CATEGORY", nullChar);
	REQUIRE(0 == strcmp("[INFO][CATEGORY] NULL", formattedMessage));
	delete[] formattedMessage;

	formattedMessage = formatter->format("INFO", nullChar, "MESSAGE");
	REQUIRE(0 == strcmp("[INFO][NULL] MESSAGE", formattedMessage));
	delete[] formattedMessage;

	formattedMessage = formatter->format("INFO", "CATEGORY", "MESSAGE");
	REQUIRE(0 == strncmp("[INFO][CATEGORY] MESSAGE", formattedMessage, strlen(formattedMessage) - 1));
	delete[] formattedMessage;

	delete formatter;
}