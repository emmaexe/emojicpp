#include <gtest/gtest.h>
#include <emojicpp/emoji.hpp>

TEST(parserWorks, helloWorld) {
    EXPECT_EQ(
        emojicpp::emoji::parse("Hello, world!"),
        reinterpret_cast<const char*>(u8"Hello, world!")
    );
}

TEST(parserWorks, simpleEmoji) {
    EXPECT_EQ(
        emojicpp::emoji::parse(":admission_tickets:"),
        reinterpret_cast<const char*>(u8"\U0001F39F")
    );
}

TEST(parserWorks, complexEmoji) {
    EXPECT_EQ(
        emojicpp::emoji::parse(":keycap_digit_one:"),
        reinterpret_cast<const char*>(u8"\U00000031\U000020E3")
    );
}

TEST(parserWorks, emojiWithText) {
    EXPECT_EQ(
        emojicpp::emoji::parse("Ok :+1:"),
        reinterpret_cast<const char*>(u8"Ok \U0001F44D")
    );
}

TEST(parserWorks, ignoreUnrelatedColon) {
    EXPECT_EQ(
        emojicpp::emoji::parse("This is an emoji: :tv:"),
        reinterpret_cast<const char*>(u8"This is an emoji: \U0001F4FA")
    );
}

TEST(parserWorks, fakeEmoji) {
    EXPECT_EQ(
        emojicpp::emoji::parse(":kekw:"),
        reinterpret_cast<const char*>(u8":kekw:")
    );
}

TEST(parserWorks, fakeAndRealMix) {
    EXPECT_EQ(
        emojicpp::emoji::parse(":xdx:taco:"),
        reinterpret_cast<const char*>(u8":xdx\U0001F32E")
    );
}

TEST(parserWorks, chaos) {
    EXPECT_EQ(
        emojicpp::emoji::parse("::::::::::::::::kekw:::::::::::::::::::::question::::::::::::::xdx:::::::::::::::::"),
        reinterpret_cast<const char*>(u8"::::::::::::::::kekw::::::::::::::::::::\U00002753:::::::::::::xdx:::::::::::::::::")
    );
}
