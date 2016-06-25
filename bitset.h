#ifndef BITSET_H
#define BITSET_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vector/vector.h"

/****************** DEFINTIIONS ******************/

#define BITSET_ERROR VECTOR_ERROR
#define BITSET_SUCCESS VECTOR_SUCCESS

#define BITSET_INITIALIZER \
	{ VECTOR_INITIALIZER, 0 }

typedef void (*byte_operation_t)(uint8_t*, const uint8_t*);

/****************** STRUCTURES ******************/

typedef struct BitSet {
	Vector bits;
	size_t size;
} BitSet;

/****************** INTERFACE ******************/

/* Setup */
int bitset_setup(BitSet* bitset, size_t minimum_number_of_bits);

int bitset_copy(BitSet* destination, BitSet* source);
int bitset_move(BitSet* destination, BitSet* source);
int bitset_swap(BitSet* destination, BitSet* source);

int bitset_destroy(BitSet* bitset);

/* Factory */
BitSet bitset_from_value(uint64_t value);

/* Logical Operations */
int byte_wise_operation(BitSet* destination,
												const BitSet* source,
												byte_operation_t byte_operation);

int bitset_and(BitSet* destination, const BitSet* source);
int bitset_or(BitSet* destination, const BitSet* source);
int bitset_xor(BitSet* destination, const BitSet* source);
int bitset_flip(BitSet* bitset);

/* Access */
int bitset_set(BitSet* bitset, size_t index);
int bitset_reset(BitSet* bitset, size_t index);
int bitset_assign(BitSet* bitset, size_t index, bool value);
int bitset_toggle(BitSet* bitset, size_t index);

int bitset_test(const BitSet* bitset, size_t index);
const uint8_t* byte_const_get(const BitSet* bitset, size_t index);
uint8_t* byte_get(BitSet* bitset, size_t index);

int bitset_msb(BitSet* bitset);
int bitset_lsb(BitSet* bitset);

int bitset_reset_all(BitSet* bitset);
int bitset_set_all(BitSet* bitset);
int bitset_set_all_to_mask(BitSet* bitset, uint8_t mask);
int bitset_clear(BitSet* bitset);

/* Size Management */
int bitset_push(BitSet* bitset, bool value);
int bitset_push_one(BitSet* bitset);
int bitset_push_zero(BitSet* bitset);
int bitset_pop(BitSet* bitset);

/* Capacity Management */
int bitset_reserve(BitSet* bitset, size_t minimum_number_of_bits);
int bitset_grow(BitSet* bitset);
int bitset_shrink(BitSet* bitset);

/* Information */
bool bitset_is_initialized(const BitSet* bitset);
size_t bitset_capacity(const BitSet* bitset);
size_t bitset_size_in_bytes(const BitSet* bitset);

int bitset_count(BitSet* bitset);
int bitset_all(BitSet* bitset);
int bitset_any(BitSet* bitset);
int bitset_none(BitSet* bitset);

/****************** PRIVATE ******************/

#define LAST_BIT_INDEX(value) ((sizeof(value) * 8) - 1)
#define LAST_BIT_MASK(value) (1ULL << LAST_BIT_INDEX(value))
#define LAST_BIT(value) \
	((value & LAST_BIT_MASK(value)) >> LAST_BIT_INDEX(value))

#define MIN(a, b) ((a < b) ? (a) : (b))
#define CEIL(x) ((x == ((int)(x))) ? x : ((int)(x)) + 1)
#define BITS_TO_BYTES(bits) CEIL((bits) / 8.0)

/* Popcount Masks */
#define POPCOUNT_MASK1 0x55
#define POPCOUNT_MASK2 0x33
#define POPCOUNT_MASK3 0x0F

uint8_t _byte_popcount(uint8_t value);

int _bitset_increment_size(BitSet* bitset);

void _byte_and(uint8_t* first, const uint8_t* second);
void _byte_or(uint8_t* first, const uint8_t* second);
void _byte_xor(uint8_t* first, const uint8_t* second);

size_t _byte_index(size_t index);
uint8_t _bitset_index(size_t index);
uint8_t _bitset_offset(size_t index);

#endif /* BITSET_H */
