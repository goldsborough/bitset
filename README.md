# bitset

[![GitHub license](https://img.shields.io/github/license/mashape/apistatus.svg?style=flat-square)](http://goldsborough.mit-license.org)

`bitset` is a feature-complete, generic and customizable dynamic bitset implementation in pure C.

## Usage

```C
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

```

## LICENSE

This project is released under the [MIT License](http://goldsborough.mit-license.org). For more information, see the `LICENSE` file.

## Authors

[Peter Goldsborough](http://www.goldsborough.me) + [cat](https://goo.gl/IpUmJn) :heart:

<a href="https://gratipay.com/~goldsborough/"><img src="http://img.shields.io/gratipay/goldsborough.png?style=flat-square"></a>
