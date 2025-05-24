/// @ingroup os
/// @brief Get the executable path.
/// @return A pointer to the executable path dx_string object. The null pointer on failure.
/// @success The caller acquired a reference to the string.
Core_Result Core_getExecutablePath(Core_String** RETURN);
