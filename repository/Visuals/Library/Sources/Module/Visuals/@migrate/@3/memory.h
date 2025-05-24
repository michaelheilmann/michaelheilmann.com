/// @brief Assign the values of an object to another object.
/// @param p A pointer to the target object.
/// @param q A pointer to the source object.
/// @param n The number of Bytes to copy.
/// @error #Core_Error_ArgumentInvalid @a p is a null pointer
/// @error #Core_Error_ArgumentInvalid @a q is a null pointer
/// @warning The objects denoted by <code>(p,n)</code> and <code>(q,n)</code> must not overlap.
/// @procedure
Core_Result Core_Memory_copy(void* p, void const* q, Core_Size n);
// http://localhost/core#core-memory-copy
Core_Result Core_Memory_copy(void* p, void const* q, Core_Size n);

/// @brief Assign the values of an object to another object.
/// @param p A pointer to the target object.
/// @param q A pointer to the source object.
/// @param n The number of Bytes to copy.
/// @error #Core_Error_ArgumentInvalid @a p is a null pointer
/// @error #Core_Error_ArgumentInvalid @a q is a null pointer
/// @warning The object denoted by <code>(p,n)</code> and <code>(q,n)</code> may overlap.
/// @procedure
Core_Result Core_Memory_move(void* p, void const* q, Core_Size n);
// http://localhost/core#core-memory-move
Core_Result Core_Memory_move(void* p, void const* q, Core_Size n);

// http://primordialmachine.com/core/ring-1/#core-memory-zero
Core_Result Core_Memory_zero(void* p, Core_Size n);
// http://localhost/core#core-memory-zero
Core_Result Core_Memory_zero(void* p, Core_Size n);


/// @brief Assign the Bytes of a memory block the specified values.
/// @param p A pointer to the memory block.
/// @param n The size of the memory block.
/// @param v The value.
/// @error #Core_Error_ArgumentInvalid @a p is a null pointer.
/// @error #Core_Error_AllocationFailed an allocation failed.
/// @procedure
Core_Result Core_Memory_fill(void* p, Core_Size n, Core_Natural8 v);
// http://localhost/core#core-memory-fill
Core_Result Core_Memory_fill(void* p, Core_Size n, Core_Natural8 v);

// http://primordialmachine.com/core/ring-1/#core-memory-allocate
Core_Result Core_Memory_allocate(void** RETURN, Core_Size n);
// http://localhost/core#core-memory-allocate
Core_Result Core_Memory_allocate(void** RETURN, Core_Size n);


/// @brief Reallocate an object.
/// @param p A pointer to an object previously allocated by a call to dx_allocate.
/// @param n The number of Bytes to reallocate the object to. The size may be @a 0.
/// @return A pointer to the reallocated object on success. The null pointer on failure.
/// @success The old object was deallocated (as if dx_deallocate was called with @a p as
/// the argument) and a new object was allocated (as if dx_allocate with argument @a n
/// was called). The first <code>min(x,y)</code> Bytes of the new object and the old object
/// are equal where <code>x</code> is the length of the old object and <code>y</code>
/// is the length of the new object.
/// @default-failure
/// The old memory block was not modified.
Core_Result Core_Memory_reallocate(void** RETURN, void* p, Core_Size n);
// http://localhost/core#core-memory-reallocate
Core_Result Core_Memory_reallocate(void** RETURN, void* p, Core_Size n);

/// @brief Deallocate an object.
/// @param p A pointer to the object previously allocated by call to dx_allocate or the null pointer.
/// @undefined @a p does not point to a object previousl allocated by a call to dx_allocate and is not the null pointer.
void dx_memory_deallocate(void* p);
// http://localhost/core#core-memory-deallocate
void Core_Memory_deallocate(void* p);


/// @brief Compare the values of objects.
/// @details This functin compares the Byte values of the objects lexicographically.
/// @param p A pointer to the first object.
/// @param q A pointer to the second object.
/// @param n The number of Bytes to compare.
/// @return
/// The zero value if the memory blocks are lexicographically equal.
/// A negative value if the first memory block is lexicographically smaller.
/// A positive value if the first memory block is lexicographically greater.
int dx_memory_compare(void const* p, void const* q, Core_Size n);

Core_Result Core_Memory_compare(Core_Integer8* RETURN, void const* p, void const* q, Core_Size n);
// http://localhost/core#core-memory-compare
Core_Result Core_Memory_compare(Core_Integer8* RETURN, void const* p, void const* q, Core_Size n);












