/* Copyright (C) 2011-2016 Joseba Alberdi <alberdi@hotmail.es>
 *                         Matthieu Verstraete <matthieu.jean.verstraete@gmail.com>
 *                         Micael Oliveira <micael.oliveira@mpsd.mpg.de>
 *                         Yann Pouillon <notifications@materialsevolution.es>
 *
 * This file is part of Libpspio.
 *
 * Libpspio is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, version 3 of the License, or (at your option) any later
 * version.
 *
 * Libpspio is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Libpspio.  If not, see <http://www.gnu.org/licenses/> or write to
 * the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA.
 */

#ifndef PSPIO_COMMON_H
#define PSPIO_COMMON_H

/**
 * @file pspio_common.h
 * @brief include file with low-level stuff 
 */

/* IMPORTANT: this file must contain defines only, in order to be readable from Fortran. */

/* Strings */
#define PSPIO_STRLEN_ERROR 1024
#define PSPIO_STRLEN_LINE 256
#define PSPIO_STRLEN_TITLE 256
#define PSPIO_STRLEN_DESCRIPTION 4096



/**
 * Error codes
 *
 * Note: except for SUCCESS and ERROR, please keep alphabetical order.
 */
#define PSPIO_SUCCESS  0 
#define PSPIO_ERROR   -1
#define PSPIO_EFILE_CORRUPT 1
#define PSPIO_EFILE_FORMAT 2
#define PSPIO_EGSL 3
#define PSPIO_EIO 4
#define PSPIO_ENOFILE 5
#define PSPIO_ENOMEM 6
#define PSPIO_ENOSUPPORT 7
#define PSPIO_ETYPE 8
#define PSPIO_EVALUE 9


/**
 * File formats
 *
 * Note: keep the number of formats up-to-date
 *
 * Note: FHI98PP must be checked before ABINIT and thus must have a lower
 *       index than that of Abinit
 */
#define PSPIO_FMT_NFORMATS 19
#define PSPIO_FMT_UNKNOWN -1
#define PSPIO_FMT_NONE 0
#define PSPIO_FMT_ATOM         1 /* Jose Luis Martin's ATOM */
#define PSPIO_FMT_FHI98PP      2 /* FHI98PP */
#define PSPIO_FMT_OCTOPUS_HGH  3 /* HGH for OCtopus != Goedecker's HGH */
#define PSPIO_FMT_SIESTA       4 /* SIESTA ATOM's PSF */
#define PSPIO_FMT_UPF          5 /* UPF 1 */
#define PSPIO_FMT_XML          6 /* FSatom-pp */
#define PSPIO_FMT_ABINIT_1    11 /* Teter */
#define PSPIO_FMT_ABINIT_2    12 /* GTH */
#define PSPIO_FMT_ABINIT_3    13 /* HGH */
#define PSPIO_FMT_ABINIT_4    14 /* Teter */
#define PSPIO_FMT_ABINIT_5    15 /* Phoney */
#define PSPIO_FMT_ABINIT_6    16 /* FHI */
#define PSPIO_FMT_ABINIT_7    17 /* PAW */
#define PSPIO_FMT_ABINIT_8    18 /* Hamann ONCV */
#define PSPIO_FMT_ABINIT_9    19 /* XML */
#define PSPIO_FMT_ABINIT_10   20 /* HGH, with full h/k matrix */
#define PSPIO_FMT_ABINIT_11   21 /* UPF */
#define PSPIO_FMT_ABINIT_17   22 /* PAW XML */


/**
 * Wave-equations 
 */
#define PSPIO_EQN_DIRAC 1
#define PSPIO_EQN_SCALAR_REL 2
#define PSPIO_EQN_SCHRODINGER 3


/**
 * Pseudopotential generation schemes
 */
#define PSPIO_SCM_UNKNOWN 0
#define PSPIO_SCM_BHS 1
#define PSPIO_SCM_GTH 2
#define PSPIO_SCM_HAMANN 3
#define PSPIO_SCM_HGH 4
#define PSPIO_SCM_HSC 5
#define PSPIO_SCM_KERKER 6
#define PSPIO_SCM_MRPP 7
#define PSPIO_SCM_RRKJ 8
#define PSPIO_SCM_TM 9
#define PSPIO_SCM_TM2 10
#define PSPIO_SCM_RTM 11
#define PSPIO_SCM_ONCV 12


/**
 * Mesh types
 */
#define PSPIO_MESH_UNKNOWN -1 /**< unkown type of mesh */
#define PSPIO_MESH_NONE    0 /**< mesh not set yet */
#define PSPIO_MESH_LOG1    1 /**< r_i = b*exp(a*i) */
#define PSPIO_MESH_LOG2    2 /**< r_i = b*(exp(a*i) - 1) */
#define PSPIO_MESH_LINEAR  3 /**< r_i = a*i + b */


/**
 * Comparison
 */
#define PSPIO_DIFF    -1
#define PSPIO_EQUAL   -2
#define PSPIO_MTEQUAL -3


/**
 * Interpolation methods
 */
#define PSPIO_INTERP_GSL_CSPLINE 1
#define PSPIO_INTERP_JB_CSPLINE 2


/** 
 * values for NLCC scheme - could add possibilities for different schemes
 */
#define PSPIO_NLCC_UNKNOWN -1
#define PSPIO_NLCC_NONE 0
#define PSPIO_NLCC_FHI 1 /* M. Fuchs and M. Scheffler. Ab initio pseudopotentials for electronic structure calculations of poly-atomic systems using density-functional theory. Comp. Phys. Comm. 119:67-98, 1999. */
#define PSPIO_NLCC_LOUIE 2 /* S. G. Louie, S. Froyen, and M. L. Cohen. Nonlinear ionic pseudopotentials in spin-density-functional calculations. Phys. Rev. B, 26:1738-1742, 1982. */
#define PSPIO_NLCC_TETER1 3 /* 7 May 1992 by M. Teter abinit version for pspcod 4 */
#define PSPIO_NLCC_TETER2 4 /* 5 Nov 1992 by M. Teter abinit version for pspcod 1 */
#define PSPIO_NLCC_ATOM 5 /* Scheme implemented in the ATOM pseudopotential generator code. */
#define PSPIO_NLCC_ONCV 6 /* Scheme implemented in the ONCVPSP pseudopotential generator code. */

#endif
