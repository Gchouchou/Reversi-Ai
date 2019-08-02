#ifndef OCCUPANT_HEADER
#define OCCUPANT_HEADER

namespace reversi
{
    enum occupant {
        disabled = -1,
        empty,
        white,
        black,
        tie
    };
    inline occupant flip(const occupant o) {
        return (occupant)(3 - o);
    }
    inline bool isOccupied(const occupant o) {
        return o > empty;
    }
} // namespace reversi


#endif