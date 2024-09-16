// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

// Last modified: 2024-09-20

#if !defined(R_ATOMS_H_INCLUDED)
#define R_ATOMS_H_INCLUDED

#include "R/Configure.h"
#include "R/Boolean.h"
#include "R/Size.h"

/// @breif Atoms are interned (canonicalized) UTF8 strings such that they can be compared by address.
typedef struct R_Atom R_Atom;
typedef R_Atom* R_AtomValue;

/// @brief Startup the atoms.
void
R_Atoms_startup
  (
  );

/// @brief Shutdown the atoms.
void
R_Atoms_shutdown
  (
  );

/// Must be invoked before the pre mark phase.
void
R_Atoms_onPreMark
  (
  );

/// Must be invoked after the finalize phase.
void
R_Atoms_onPostFinalize
  (
    bool shutdown
  );

R_AtomValue
R_Atoms_getOrCreateAtom
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  );

/// @brief Update the age of this atom.
/// @param self The atom.
void
R_Atom_visit
  (
    R_AtomValue self
  );

/// @brief Get the hash value of this atom.
/// @param self The atom.
/// @return The hash value.
R_SizeValue
R_Atom_getHashValue
  (
    R_AtomValue self
  );

#endif // R_ATOMS_H_INCLUDED
