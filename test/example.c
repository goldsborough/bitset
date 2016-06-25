#include <stdio.h>
#include "bitset.h"

int main(int argc, const char* argv[]) {
	BitSet bitset = BITSET_INITIALIZER;
	bitset_setup(&bitset, 100);

	bitset_set(&bitset, 10);

	if (bitset_test(&bitset, 10)) {
		bitset_toggle(&bitset, 10);
	} else {
		bitset_assign(&bitset, 10, true);
	}

	if (bitset_any(&bitset)) {
		bitset_clear(&bitset);
	} else {
		bitset_push(&bitset, true);
		printf("%d bit(s) are set\n", bitset_count(&bitset));
	}

	bitset_destroy(&bitset);

	uint64_t value = 0x123456789ABCDEF0;
	bitset = bitset_from_value(value);

	printf("The MSB is: %d\n", bitset_msb(&bitset));

	bitset_destroy(&bitset);
}
