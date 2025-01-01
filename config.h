/* The config file for the brainf*ck interpreter
   Copyright (C) 2025 Mitchell <mitchell@segfault.net>

This file is part of BF.

BF is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

BF is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with BF; see the file LICENSE.  If not see
<http://www.gnu.org/licenses/>.  */

#ifndef CONFIG_H
#define CONFIG_H
#include <stdbool.h>

#define VERSION "0.1"
#define TAPESIZE 30000           // The length of TAPE
char EOF_NUM = -1;               // The EOF number (if enabled)
bool OMIT_EOF = true;            // Whether to omit EOF
bool BOUNDS_ENABLED = true;      // Whether to enable circular tape

#endif // CONFIG_H
