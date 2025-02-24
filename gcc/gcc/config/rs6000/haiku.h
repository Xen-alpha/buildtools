/* Definitions for PowerPC running Haiku
   Copyright (C) 1998, 1999, 2000, 2001, 2002, 2004, 2005
   Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */


/* long double is 128 bits wide; the documentation claims
   LIBGCC2_LONG_DOUBLE_TYPE_SIZE to default to LONG_DOUBLE_TYPE_SIZE, but
   it apparently does not */
/*#undef LONG_DOUBLE_TYPE_SIZE
#define LONG_DOUBLE_TYPE_SIZE 128
#undef LIBGCC2_LONG_DOUBLE_TYPE_SIZE
#define LIBGCC2_LONG_DOUBLE_TYPE_SIZE 128*/

/* Undef gnu-user.h macros we don't want.  */
#undef CPLUSPLUS_CPP_SPEC
#undef LINK_GCC_C_SEQUENCE_SPEC

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()					\
  do									\
    {									\
	builtin_define ("__HAIKU__");					\
	builtin_define ("__POWERPC__");					\
	builtin_define ("__powerpc__");					\
	builtin_define ("__STDC_ISO_10646__=201103L"); \
	builtin_assert ("system=haiku");					\
	builtin_assert ("cpu=powerpc");					\
	builtin_assert ("machine=powerpc");					\
	TARGET_OS_SYSV_CPP_BUILTINS ();					\
    }									\
  while (0)

/* Provide a LINK_SPEC appropriate for Haiku.  Here we provide support
   for the special GCC options -static and -shared, which allow us to
   link things in one of these three modes by applying the appropriate
   combinations of options at link-time.  */

/* If ELF is the default format, we should not use /lib/elf.  */

#undef	LINK_SPEC
#define LINK_SPEC "-m elf32ppchaiku %{!r:-shared} %{nostart:-e 0} %{shared:-e 0} %{!shared: %{!nostart: -no-undefined}}"

/* override options from sysv4.h */
#undef SUBTARGET_OVERRIDE_OPTIONS
#define SUBTARGET_OVERRIDE_OPTIONS                                    \
 do {                                                                  \
	rs6000_abi_name = "sysv";                                      \
	rs6000_current_abi = ABI_V4;                                   \
	rs6000_sdata = SDATA_DATA;                                     \
	rs6000_sdata_name = "data";                                    \
	/*secure_plt = true;*/                                         \
	rs6000_isa_flags |= OPTION_MASK_MINIMAL_TOC;                   \
	TARGET_NO_FP_IN_TOC = 1;                                       \
	haiku_override_options ();                                     \
   }
 while (0)
