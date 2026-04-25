#include "attacks.h"
#include "test.h"
#include "types.h"
#include <stdio.h>

int test_king_movegen() {
    BB blockers, expected, actual;

    blockers = 0ULL;
    expected = bb_rook_mask(D4, blockers);
    actual = get_rook_attacks(D4, blockers);
    ASSERT_EQ(actual, expected, "Rook Magic D4 failed on empty board");

    blockers = BB_D6 | BB_B4;
    expected = bb_rook_mask(D4, blockers);
    actual = get_rook_attacks(D4, blockers);
    ASSERT_EQ(actual, expected, "Rook Magic D4 failed with blockers at D6, B4");

    blockers = BB_A2 | BB_B1;
    expected = bb_rook_mask(A1, blockers);
    actual = get_rook_attacks(A1, blockers);
    ASSERT_EQ(actual, expected, "Rook Magic A1 failed with tight blockers");

    return 0;
}

int test_bishop_magics() {
    BB blockers, expected, actual;

    blockers = 0ULL;
    expected = bb_bishop_mask(E4, blockers);
    actual = get_bishop_attacks(E4, blockers);
    ASSERT_EQ(actual, expected, "Bishop Magic E4 failed on empty board");

    blockers = BB_C2 | BB_C6 | BB_G6 | BB_G2;
    expected = bb_bishop_mask(E4, blockers);
    actual = get_bishop_attacks(E4, blockers);
    ASSERT_EQ(actual, expected, "Bishop Magic E4 failed with 4 blockers");

    return 0;
}

int test_all_magics_randomly() {
    BB blockers = BB_C2 | BB_C6 | BB_G6 | BB_G2;
    for (int sq = 0; sq < 64; sq++) {
        ASSERT_EQ(get_rook_attacks(sq, blockers), bb_rook_mask(sq, blockers), "Exhaustive Rook test failed");
        ASSERT_EQ(get_bishop_attacks(sq, blockers), bb_bishop_mask(sq, blockers), "Exhaustive Bishop test failed");
    }
    return 0;
}

int main() {
    int res = 0;
    res |= test_king_movegen();
    res |= test_bishop_magics();
    res |= test_all_magics_randomly();
    return res;
}
