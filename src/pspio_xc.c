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

#include <stdlib.h>

#include "pspio_xc.h"

#if defined HAVE_CONFIG_H
#include "config.h"
#endif


int pspio_xc_alloc(pspio_xc_t **xc, const int nlcc_scheme, const int np){
  int ierr;

  ASSERT (xc != NULL, PSPIO_EVALUE);
  ASSERT (*xc == NULL, PSPIO_EVALUE);
  switch (nlcc_scheme) {
  case PSPIO_NLCC_NONE:
    break;
  case PSPIO_NLCC_UNKNOWN:
    break;
  case PSPIO_NLCC_LOUIE:
    break;
  case PSPIO_NLCC_FHI:
    break;
  case PSPIO_NLCC_TETER1:
    break;
  case PSPIO_NLCC_TETER2:
    break;
  default:
    return PSPIO_EVALUE;
  }

  *xc = (pspio_xc_t *) malloc (sizeof(pspio_xc_t));
  ASSERT(*xc != NULL, PSPIO_ENOMEM);

  (*xc)->nlcc_scheme = nlcc_scheme;
  (*xc)->core_dens = NULL;
  if (nlcc_scheme != PSPIO_NLCC_NONE) {
    ASSERT (np > 1, PSPIO_EVALUE);
    ierr = pspio_meshfunc_alloc(&(*xc)->core_dens, np);
    if (ierr) {
      pspio_xc_free(xc);
      HANDLE_ERROR (ierr);
    }
  }

  return PSPIO_SUCCESS;
}


int pspio_xc_set(pspio_xc_t **xc, const int exchange, const int correlation){
  ASSERT (*xc != NULL, PSPIO_EVALUE);

  (*xc)->exchange = exchange;
  (*xc)->correlation = correlation;

  return PSPIO_SUCCESS;
}


int pspio_xc_nlcc_set(pspio_xc_t **xc, const pspio_mesh_t *mesh, const double *core_dens){

  HANDLE_FUNC_ERROR (pspio_meshfunc_set(&(*xc)->core_dens, mesh, core_dens));

  return PSPIO_SUCCESS;
}


int pspio_xc_free(pspio_xc_t **xc){
  if (*xc != NULL) {
    HANDLE_FUNC_ERROR (pspio_meshfunc_free(&(*xc)->core_dens));
    free(*xc);
    *xc = NULL;
  }

  return PSPIO_SUCCESS;
}


int pspio_xc_has_nlcc(pspio_xc_t *xc, int *has_nlcc) {
  ASSERT (xc != NULL, PSPIO_EVALUE);

  *has_nlcc = (xc->nlcc_scheme != PSPIO_NLCC_NONE);

  return PSPIO_SUCCESS;
}