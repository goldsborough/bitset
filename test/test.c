#include <assert.h>
#include <stdio.h>

#include "bitset.h"

int main(int argc, const char* argv[]) {
	size_t previous_size;
	size_t previous_capacity;
	size_t bytes;

	printf("TESTING SETUP ...\n");
	BitSet bitset = BITSET_INITIALIZER;
	assert(!bitset_is_initialized(&bitset));
	bitset_setup(&bitset, 100);
	assert(bitset_is_initialized(&bitset));

	bytes = BITS_TO_BYTES(100);

	assert(bitset.size == 100);
	assert(bitset_size_in_bytes(&bitset) == bytes);

	printf("TESTING BIT SETTING ...\n");

	for (size_t i = 0; i < bytes; ++i) {
		size_t index = (i * 8) + (i % 8);
		assert(bitset_set(&bitset, index) == BITSET_SUCCESS);
	}

	printf("TESTING BIT TESTING ...\n");

	for (size_t i = 0; i < bytes; ++i) {
		assert(bitset_test(&bitset, (i * 8) + (i % 8)));
	}

	printf("TESTING BIT RESETTING ...\n");

	for (size_t i = 0; i < bytes; ++i) {
		assert(bitset_reset(&bitset, (i * 8) + (i % 8)) == BITSET_SUCCESS);
	}

	printf("TESTING BIT TOGGLING ...\n");

	for (size_t i = 0; i < bytes; ++i) {
		assert(bitset_toggle(&bitset, i * 8) == BITSET_SUCCESS);
	}

	printf("TESTING ASSIGNMENT ...\n");

	for (size_t i = 0; i < bytes; ++i) {
		assert(bitset_assign(&bitset, i * 8, false) == BITSET_SUCCESS);
		assert(!bitset_test(&bitset, i * 8));
	}

	printf("TESTING PUSHING ...\n");

	previous_size = bitset.size;
	for (size_t i = 0; i < 10; ++i) {
		assert(bitset_push(&bitset, true) == BITSET_SUCCESS);
		assert(bitset_lsb(&bitset));
		assert(bitset.size == ++previous_size);
	}

	printf("TESTING POPPING ...\n");

	previous_size = bitset.size;
	for (size_t i = 0; i < 10; ++i) {
		assert(bitset_pop(&bitset) == BITSET_SUCCESS);
		assert(bitset.size == --previous_size);
	}

	printf("TESTING GROWING ...\n");

	previous_size = bitset.size;
	previous_capacity = bitset_capacity(&bitset);
	for (size_t i = 0; i < 10; ++i) {
		assert(bitset_grow(&bitset) == BITSET_SUCCESS);
		previous_capacity += 8;
		assert(bitset_capacity(&bitset) == previous_capacity);
		assert(bitset.size == previous_size);
	}

	printf("TESTING SHRINKING ...\n");

	previous_size = bitset.size;
	previous_capacity = bitset_capacity(&bitset);
	for (size_t i = 0; i < 10; ++i) {
		assert(bitset_shrink(&bitset) == BITSET_SUCCESS);
		previous_capacity -= 8;
		assert(bitset_capacity(&bitset) == previous_capacity);
		assert(bitset.size == previous_size);
	}

	printf("TESTING CLEAR ...\n");
	assert(bitset_clear(&bitset) == BITSET_SUCCESS);

	printf("TESTING COUNTING ...\n");
	assert(bitset_count(&bitset) == 0);
	assert(bitset_none(&bitset));
	assert(bitset_all(&bitset));
	assert(!bitset_any(&bitset));

	bitset_grow(&bitset);

	bitset_set_all(&bitset);
	assert(!bitset_none(&bitset));
	assert(bitset_all(&bitset));
	assert(bitset_any(&bitset));

	bitset_reset(&bitset, 0);
	assert(!bitset_none(&bitset));
	assert(!bitset_all(&bitset));
	assert(bitset_any(&bitset));

	bitset_destroy(&bitset);

	printf("TESTING CONSTRUCTION FROM VALUE ...\n");

	uint64_t value = 0x123456789ABCDEF0;
	bitset = bitset_from_value(value);
	assert(bitset.size == 64);

	for (int i = 63; i >= 0; --i, value >>= 1) {
		assert(bitset_test(&bitset, i) == (value & 1));
	}

	bitset_destroy(&bitset);

	printf("\033[92mALL TEST PASSED\033[0m\n");
}
