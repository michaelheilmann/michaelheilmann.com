#include "dx/core/memory.h"

// malloc, realloc, free
#include <malloc.h>

// memmove, memcpy, memset
#include <string.h>

Core_Result Core_Memory_copy(void* p, void const* q, Core_Size n) {
  if (!p || !q) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  memcpy(p, q, n);
  return Core_Success;
}

Core_Result Core_Memory_move(void* p, void const* q, Core_Size n) {
  if (!p || !q) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  memmove(p, q, n);
  return Core_Success;
}

Core_Result Core_Memory_zero(void* p, Core_Size n) {
  return Core_Memory_fill(p, n, 0);
}

Core_Result Core_Memory_fill(void* p, Core_Size n, Core_Natural8 v) {
  if (!p) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  memset(p, v, n);
  return Core_Success;
}

Core_Result Core_Memory_allocate(void **RETURN, Core_Size n) {
  void* p = malloc(n > 0 ? n : 1);
  if (!p) {
    Core_setError(Core_Error_AllocationFailed);
    return Core_Failure;
  }
  *RETURN = p;
  return Core_Success;
}

Core_Result Core_Memory_reallocate(void** RETURN, void* p, Core_Size n) {
  if (!RETURN || !p) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  void* q = realloc(p, n > 0 ? n : 1);
  if (!q) {
    Core_setError(Core_Error_AllocationFailed);
    return Core_Failure;
  }
  *RETURN = q;
  return Core_Success;
}

void dx_memory_deallocate(void* p) {
  if (p) {
    free(p);
  }
}

int dx_memory_compare(void const* p, void const* q, Core_Size n) {
  if (!p || !q) {
    Core_setError(Core_Error_ArgumentInvalid);
    return 0;
  }
  return memcmp(p, q, n);
}

Core_Result Core_Memory_compare(Core_Integer8* RETURN, void const* p, void const* q, Core_Size n) {
  if (!RETURN || !p || !q) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  int temporary = memcmp(p, q, n);
  *RETURN = temporary < 0 ? -1 : (temporary > 0 ? +1 : 0);
  return Core_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Core_Result dx_allocator_statistics_initialize(dx_allocator_statistics *statistics) {
	if (!statistics) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
	}
	DX_DEBUG_ASSERT(NULL != statistics);
	statistics->numberOfBlocks = 0;
	statistics->smallestBlock = 0;
	statistics->greatestBlock = 0;
	statistics->numberOfBytes = 0;
	statistics->numberOfKiloBytes = 0;
	return Core_Success;
}

void dx_allocator_statistics_uninitialize(dx_allocator_statistics *statistics) {
	DX_DEBUG_ASSERT(NULL != statistics);
	statistics->numberOfBlocks = 0;
	statistics->smallestBlock = 0;
	statistics->greatestBlock = 0;
	statistics->numberOfBytes = 0;
	statistics->numberOfKiloBytes = 0;
}

Core_Result dx_allocator_statistics_on_block_allocated(dx_allocator_statistics* statistics, Core_Size number_of_bytes) {
	if (!statistics) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
	}
	Core_Size number_of_kilo_bytes = 0;
	while (number_of_bytes > 1000) {
		number_of_bytes -= 1000;
		number_of_kilo_bytes += 1;
	}
  if (Core_Size_Greatest - statistics->numberOfBytes < number_of_bytes) {
    Core_setError(Core_Error_AllocationFailed);
    return Core_Failure;
  }
  if (Core_Size_Greatest - statistics->numberOfKiloBytes < number_of_kilo_bytes) {
    Core_setError(Core_Error_AllocationFailed);
    return Core_Failure;
  }
  if (Core_Size_Greatest - statistics->numberOfBlocks < 1) {
    Core_setError(Core_Error_AllocationFailed);
    return Core_Failure;   
  }
	statistics->numberOfBytes += number_of_bytes;
	statistics->numberOfKiloBytes += number_of_kilo_bytes;
	statistics->numberOfBlocks += 1;
	if (statistics->smallestBlock > number_of_bytes) {
		statistics->smallestBlock = number_of_bytes;
	}
	if (statistics->greatestBlock < number_of_bytes) {
		statistics->greatestBlock = number_of_bytes;
	}
	return Core_Success;
}

Core_Result dx_allocator_statistics_on_block_deallocated(dx_allocator_statistics* statistics, Core_Size number_of_bytes) {
	if (!statistics) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
	}
  Core_Size number_of_kilo_bytes = 0;
	while (number_of_bytes > 1000) {
		number_of_bytes -= 1000;
		number_of_kilo_bytes += 1;
	}
	statistics->numberOfBlocks -= 1;
	statistics->numberOfKiloBytes -= number_of_kilo_bytes;
	statistics->numberOfBytes -= number_of_bytes;
	return Core_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
