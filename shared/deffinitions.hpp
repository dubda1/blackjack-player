#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <numeric>
#include <span>
#include <string>
#include <string_view>

using chip_t = int32_t;

enum class Suit : uint8_t
{
    HEARTS   = 0,
    DIAMONDS = 1,
    CLUBS    = 2,
    SPADES   = 3,
};

inline std::string_view to_sv(const Suit& suit)
{
    switch (suit)
    {
        case Suit::HEARTS:
            return "HEARTS";
        case Suit::DIAMONDS:
            return "DIAMONDS";
        case Suit::CLUBS:
            return "CLUBS";
        case Suit::SPADES:
            return "SPADES";
    }
    assert(false);
}

enum class Rank : uint8_t
{
    ACE   = 0,
    KING  = 1,
    QUEEN = 2,
    JACK  = 3,
    TEN   = 4,
    NINE  = 5,
    EIGHT = 6,
    SEVEN = 7,
    SIX   = 8,
    FIVE  = 9,
    FOUR  = 10,
    THREE = 11,
    TWO   = 12,
};

inline std::string_view to_sv(const Rank& status)
{
    switch (status)
    {
        case Rank::ACE:
            return "ACE";
        case Rank::KING:
            return "KING";
        case Rank::QUEEN:
            return "QUEEN";
        case Rank::JACK:
            return "JACK";
        case Rank::TEN:
            return "TEN";
        case Rank::NINE:
            return "NINE";
        case Rank::EIGHT:
            return "EIGHT";
        case Rank::SEVEN:
            return "SEVEN";
        case Rank::SIX:
            return "SIX";
        case Rank::FIVE:
            return "FIVE";
        case Rank::FOUR:
            return "FOUR";
        case Rank::THREE:
            return "THREE";
        case Rank::TWO:
            return "TWO";
    }
    assert(false);
}

enum class BlackJackAction : uint8_t
{
    STAND       = 0,
    HIT         = 1,
    DOUBLE_DOWN = 2,
    SPLIT       = 3,
    SURRENDER   = 4,
};

inline std::string_view to_sv(const BlackJackAction& status)
{
    switch (status)
    {
        case BlackJackAction::STAND:
            return "STAND";
        case BlackJackAction::HIT:
            return "HIT";
        case BlackJackAction::DOUBLE_DOWN:
            return "DOUBLE_DOWN";
        case BlackJackAction::SPLIT:
            return "SPLIT";
        case BlackJackAction::SURRENDER:
            return "SURRENDER";
    }
    assert(false);
}

enum class BlackJackHandStatus : uint8_t
{
    NONE    = 0,
    DOUBLED = 1,
    SPLIT   = 2
};

inline std::string_view to_sv(const BlackJackHandStatus& status)
{
    switch (status)
    {
        case BlackJackHandStatus::NONE:
            return "NONE";

        case BlackJackHandStatus::DOUBLED:
            return "DOUBLED";
        case BlackJackHandStatus::SPLIT:
            return "SPLIT";
    }
    assert(false);
}

struct Card
{
    Rank rank;
    Suit suit;

    

    Card() = default;
    constexpr Card(Rank rank_, Suit suit_) : rank(rank_), suit(suit_) {}
    constexpr Card(Suit suit_, Rank rank_) : rank(rank_), suit(suit_) {}

    // Yes, this could be a string_view to for performance
    // However small string optimization might be my friend here
    // Unfortunately that is implementation defined
    // However for Ubuntu 24.04 and systemGC it is 15 chars
    explicit operator std::string() const
    {
        auto rank_str = std::string(to_sv(this->rank));
        auto suit_sv  = to_sv(this->suit);
        rank_str.append(suit_sv);
        return rank_str;
    }
};