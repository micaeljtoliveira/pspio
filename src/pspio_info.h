/*
 Copyright (C) 2011 J. Alberdi, M. Oliveira, Y. Pouillon, and M. Verstraete

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 3 of the License, or 
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 $Id$
*/

/**
 * @file pspio_info.h
 * @brief Libpspio version information 
 */

#if !defined PSPIO_INFO_H
#define PSPIO_INFO_H

/**********************************************************************
 * Global routines                                                    *
 **********************************************************************/

/**
 * Provide the version number of the library.
 * @param[out] major major version number, -1 if not found
 * @param[out] minor minor version number, -1 if not found
 * @param[out] micro micro version number, -1 if not found
 * @return error code
 */
int pspio_version(int *major, int *minor, int *micro);


/**
 * Provide the package string of the library.
 * @param[out] info: package name and version
 * @return error code
 */
int pspio_info_string(char *info);

#endif