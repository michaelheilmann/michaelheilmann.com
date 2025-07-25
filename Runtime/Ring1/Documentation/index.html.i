@{include("header.i")}

@{include("1.files.i")}

@{include("2.further-references.i")}

<h2>Foundational Types</h2>
@{include("foundational-types/Arcadia_BooleanValue.i")}
@{include("foundational-types/Arcadia_ForeignProcedureValue.i")}
@{include("foundational-types/Arcadia_IntegerValue.i")}
@{include("foundational-types/Arcadia_NaturalValue.i")}
@{include("foundational-types/Arcadia_ObjectReferenceValue.i")}
@{include("foundational-types/Arcadia_RealValue.i")}
@{include("foundational-types/Arcadia_SizeValue.i")}
@{include("foundational-types/Arcadia_VoidValue.i")}

<h2>Union Types</h2>
@{include("3.documentation.2.value.i")}

<h2>Status codes and status variables</h2>
@{include("3.documentation.3.status-codes.i")}
@{include("3.documentation.4.status-variable.i")}

<h2>Jumps and jump targets</h2>
@{include("3.documentation.5.jumps-and-jump-targets.i")}

<h2>Numeric functions</h2>
@{include("numeric-functions/Arcadia_ceil.i")}
@{include("numeric-functions/Arcadia_clamp.i")}
@{include("numeric-functions/Arcadia_cos.i")}
@{include("numeric-functions/Arcadia_countLeadingZeroes.i")}
@{include("numeric-functions/Arcadia_countSignificandBits.i")}
@{include("numeric-functions/Arcadia_countTrailingZeroes.i")}
@{include("numeric-functions/Arcadia_floor.i")}
@{include("numeric-functions/Arcadia_hash.i")}
@{include("numeric-functions/Arcadia_isPowerOfTwo.i")}
@{include("numeric-functions/Arcadia_maximum.i")}
@{include("numeric-functions/Arcadia_minimum.i")}
@{include("numeric-functions/Arcadia_nextPowerOfTwoGreaterThan.i")}
@{include("numeric-functions/Arcadia_nextPowerOfTwoGreaterThanOrEqualTo.i")}
@{include("numeric-functions/Arcadia_quotientRemainder.i")}
@{include("numeric-functions/Arcadia_safeAdd.i")}
@{include("numeric-functions/Arcadia_safeMultiply.i")}
@{include("numeric-functions/Arcadia_sin.i")}
@{include("numeric-functions/Arcadia_RealValue_getBits.i")}

<h2>Time and date functions</h2>
@{include("time-and-date-functions/Arcadia_getTickCount.i")}

<h2>Unicode functions</h2>
@{include("unicode-functions/Arcadia_Unicode_EncodeCodePointCallbackContext.i")}
@{include("unicode-functions/Arcadia_Unicode_EncodeCodePointCallbackFunction.i")}
@{include("unicode-functions/Arcadia_Unicode_encodeCodePointsUtf8.i")}
@{include("unicode-functions/Arcadia_Unicode_isUtf8.i")}

<h2>Memory functions</h2>
@{include("memory-functions/Memory_allocateUnmanaged.i")}
@{include("memory-functions/Memory_compare.i")}
@{include("memory-functions/Memory_copy.i")}
@{include("memory-functions/Memory_deallocateUnmanaged.i")}
@{include("memory-functions/Memory_fill.i")}
@{include("memory-functions/Memory_reallocateUnmanaged.i")}

<h2>Miscellaneous functions</h2>
@{include("miscellaneous-functions/getNumberOfCores.i")}
@{include("miscellaneous-functions/getPageSize.i")}

@{include("miscellaneous-functions/CompilerC.i")}
@{include("miscellaneous-functions/CompilerC_Gcc.i")}
@{include("miscellaneous-functions/CompilerC_Clang.i")}
@{include("miscellaneous-functions/CompilerC_Msvc.i")}

@{include("miscellaneous-functions/Version_Major.i")}
@{include("miscellaneous-functions/Version_Minor.i")}

@{include("miscellaneous-functions/OperatingSystem_Cygwin.i")}
@{include("miscellaneous-functions/OperatingSystem_Ios.i")}
@{include("miscellaneous-functions/OperatingSystem_IosEmulator.i")}
@{include("miscellaneous-functions/OperatingSystem_Linux.i")}
@{include("miscellaneous-functions/OperatingSystem_Macos.i")}
@{include("miscellaneous-functions/OperatingSystem_Mingw.i")}
@{include("miscellaneous-functions/OperatingSystem_Msys.i")}
@{include("miscellaneous-functions/OperatingSystem_Unix.i")}
@{include("miscellaneous-functions/OperatingSystem_Windows.i")}

<h2>Annotations</h2>
@{include("annotations/Arcadia_Likely.i")}
@{include("annotations/Arcadia_NoReturn.i")}
@{include("annotations/Arcadia_ThreadLocal.i")}
@{include("annotations/Arcadia_Unlikely.i")}

@{include("footer.i")}
