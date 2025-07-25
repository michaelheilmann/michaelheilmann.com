# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
#
# Permission to use, copy, modify, and distribute this software for any
# purpose without fee is hereby granted, provided that this entire notice
# is included in all copies of any software which is or includes a copy
# or modification of this software and in all copies of the supporting
# documentation for such software.
#
# THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
# WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
# REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
# OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

cmake_minimum_required(VERSION 3.20)

add_subdirectory(BigIntegerTests)
add_subdirectory(ClampTests)
add_subdirectory(CountLeadingZeroesTests)
add_subdirectory(CountTrailingZeroesTests)
add_subdirectory(MaximumTests)
add_subdirectory(MinimumTests)
add_subdirectory(RealTypesTests)

add_subdirectory(IntegerToStringTests)
add_subdirectory(NaturalToStringTests)
add_subdirectory(RealToStringTests)

add_subdirectory(SafeAddTests)
add_subdirectory(SafeMultiplyTests)
add_subdirectory(StringToIntegerTests)
add_subdirectory(StringToNaturalTests)
add_subdirectory(StringToRealTests)
add_subdirectory(NextPowerOfTwoTests)

add_subdirectory(WeakReferences)
