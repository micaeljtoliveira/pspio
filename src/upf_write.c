/* Copyright (C) 2012-2016 Micael Oliveira <micael.oliveira@mpsd.mpg.de>
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

/** 
 * @file upf_write.c
 * @brief routines to write UPF files 
 */
#include <math.h>

#include "upf.h"
#include "pspio.h"

#if defined HAVE_CONFIG_H
#include "config.h"
#endif


void upf_write_info(FILE *fp, const pspio_pspdata_t *pspdata)
{
  const char *description;

  description = pspio_pspinfo_get_description(pspdata->pspinfo);

  fprintf(fp, "<PP_INFO>\n");
  if (description != NULL) {
    fprintf(fp, "%s", description);
  }
  fprintf(fp, "</PP_INFO>\n");
}


int upf_write_header(FILE *fp, const pspio_pspdata_t *pspdata)
{
  int is, l;
  double occ;
  const char *label;
  int exchange, correlation;
  char shortname[5], longname[21];

  /* Write init tag */
  fprintf(fp, "<PP_HEADER>\n");
  
  /* Write the version number */
  fprintf(fp, "   0                   Version Number\n");
 
  /* Write the atomic symbol */
  fprintf(fp, "  %2s                   Element\n", pspio_pspdata_get_symbol(pspdata));

  /* Write the kind of pseudo-potentials US|NC|PAW
     At the moment we only support norm-conversing psp */
  fprintf(fp, "   NC                  Norm - Conserving pseudopotential\n");
  
  /* Write the if there are nonlinear core corrections */
  if (pspio_xc_has_nlcc(pspdata->xc)) {
    fprintf(fp, "    T                  Nonlinear Core Correction\n");
  } else {
    fprintf(fp, "    F                  Nonlinear Core Correction\n");
  }

  /* Write exchange-correlation functional */
  exchange = pspio_xc_get_exchange(pspdata->xc);
  correlation = pspio_xc_get_correlation(pspdata->xc);
  SUCCEED_OR_RETURN(libxc_to_upf(exchange, correlation, longname, shortname));
  fprintf(fp, " %20s  %4s Exchange-Correlation functional\n",
    longname, shortname);

  /* Write the Z valence */
  fprintf(fp, "%17.11f      Z valence\n", pspdata->zvalence);

  /* Write the total energy */
  fprintf(fp, "%17.11f      Total energy\n", pspdata->total_energy);
  
  /* Write the suggested cutoff for wfc and rho */
  fprintf(fp, "%11.7f%11.7f Suggested cutoff for wfc and rho\n", 0.0, 0.0);
  
  /* Write the max angular momentun component */
  fprintf(fp, "%5d                  Max angular momentum component\n",
    pspdata->projectors_l_max);
 
  /* Write the number of points in mesh */
  fprintf(fp, "%5d                  Number of points in mesh\n",
    pspdata->mesh->np);
  
  /* Write the number of wavefunctions and projectors */
  fprintf(fp, "%5d%5d             Number of Wavefunctions, Number of Projectors\n", pspdata->n_states, pspdata->n_projectors);

  /* Write wavefunctions description */
  fprintf(fp, " Wavefunctions         nl  l   occ\n");
  for (is=0; is<pspdata->n_states; is++) {
    label = pspio_state_get_label(pspdata->states[is]);
    l = pspio_qn_get_l(pspio_state_get_qn(pspdata->states[is]));
    occ = pspio_state_get_occ(pspdata->states[is]);
    fprintf(fp, "                       %2s%3d%6.2f\n", label, l, occ);    
  }

  /* Write end tag */
  fprintf(fp, "</PP_HEADER>\n");

  return PSPIO_SUCCESS;
}

void upf_write_mesh(FILE *fp, const pspio_pspdata_t *pspdata)
{
  int i;

  /* Write init tag */
  fprintf(fp, "<PP_MESH>\n");

  /* Write mesh points */
  fprintf(fp, "  <PP_R>\n");
  for (i=0; i<pspdata->mesh->np; i++) {
    if (i != 0 && i % 4 == 0) fprintf(fp, "\n");
    fprintf(fp, " %18.11E", pspdata->mesh->r[i]);
  }
  fprintf(fp, "\n  </PP_R>\n");

  /* Write Rab */
  fprintf(fp, "  <PP_RAB>\n");
  for (i=0; i<pspdata->mesh->np; i++) {
    if (i != 0 && i % 4 == 0) fprintf(fp, "\n");
    fprintf(fp, " %18.11E", pspdata->mesh->rab[i]);
  }
  fprintf(fp, "\n  </PP_RAB>\n");

  /* Write end tag */
  fprintf(fp, "</PP_MESH>\n");
}

void upf_write_nlcc(FILE *fp, const pspio_pspdata_t *pspdata)
{
  int i;
  double rho;

  /* Write init tag */
  fprintf(fp, "<PP_NLCC>\n");

  /* Print density */
  for (i=0; i<pspdata->mesh->np; i++) {
    rho = pspio_xc_nlcc_density_eval(pspdata->xc, pspdata->mesh->r[i]);
    if (i != 0 && i % 4 == 0) fprintf(fp, "\n");
    fprintf(fp, " %18.11E", rho);
  }

  /* Write end tag */
  fprintf(fp, "\n</PP_NLCC>\n");
}

void upf_write_nonlocal(FILE *fp, const pspio_pspdata_t *pspdata)
{
  int ikb, i;
  double proj, ekb;
  const pspio_qn_t *qn;

  /* Write init tag */
  fprintf(fp, "<PP_NONLOCAL>\n");

  /* Write projectors */
  for (ikb=0; ikb<pspdata->n_projectors; ikb++) {
    qn = pspio_projector_get_qn(pspdata->projectors[ikb]);
    fprintf(fp, "  <PP_BETA>\n");
    fprintf(fp, "%5d%5d             Beta    L\n", ikb+1, pspio_qn_get_l(qn));
    fprintf(fp, "%6d\n", pspdata->mesh->np);
    for (i=0; i<pspdata->mesh->np; i++) {
      proj = pspio_projector_eval(pspdata->projectors[ikb], pspdata->mesh->r[i]);
      if (i != 0 && i % 4 == 0) fprintf(fp, "\n");
      proj *= 2.0*pspdata->mesh->r[i];
      fprintf(fp, " %18.11E", proj);
    }
    fprintf(fp, "\n  </PP_BETA>\n");
  }

  /* Write the KB energies */
  fprintf(fp, "  <PP_DIJ>\n");
  fprintf(fp, "%5d                  Number of nonzero Dij\n",
    pspdata->n_projectors);
  for (ikb=0; ikb<pspdata->n_projectors; ikb++) {
    ekb = pspio_projector_get_energy(pspdata->projectors[ikb]);
    ekb /= 2.0;
    fprintf(fp, "%5d%5d%19.11E\n", ikb+1, ikb+1, ekb);
  }
  fprintf(fp, "  </PP_DIJ>\n");

  /* Write end tag */
  fprintf(fp, "</PP_NONLOCAL>\n");
}

void upf_write_local(FILE *fp, const pspio_pspdata_t *pspdata)
{
  int i;
  double vlocal;

  /* Write init tag */
  fprintf(fp, "<PP_LOCAL>\n");
  
  /* Print vlocal */
  for (i=0; i<pspdata->mesh->np; i++) {
    if (i != 0 && i % 4 == 0) fprintf(fp, "\n");
    vlocal = pspio_potential_eval(pspdata->vlocal, pspdata->mesh->r[i]);
    vlocal *= 2.0;
    fprintf(fp, " %18.11E", vlocal);
  }

  /* Write end tag */
  fprintf(fp, "\n</PP_LOCAL>\n");
}

void upf_write_pswfc(FILE *fp, const pspio_pspdata_t *pspdata)
{
  int is, i, l;
  double occ, wf;
  const char *label;

  /* Write init tag */
  fprintf(fp, "<PP_PSWFC>\n");

  /* Write wavefunctions */
  for (is=0; is<pspdata->n_states; is++) {
    label = pspio_state_get_label(pspdata->states[is]);
    l = pspio_qn_get_l(pspio_state_get_qn(pspdata->states[is]));
    occ = pspio_state_get_occ(pspdata->states[is]);
    fprintf(fp, "%s %4d %5.2f          Wavefunction\n", label, l, occ);
    for (i=0; i<pspdata->mesh->np; i++) {
      if (i != 0 && i % 4 == 0) fprintf(fp, "\n");
      wf = pspio_state_wf_eval(pspdata->states[is], pspdata->mesh->r[i]);
      wf *= pspdata->mesh->r[i];
      fprintf(fp, " %18.11E", wf);
    }
    fprintf(fp, "\n");
  }

  /* Write end tag */
  fprintf(fp, "</PP_PSWFC>\n");
}

void upf_write_rhoatom(FILE *fp, const pspio_pspdata_t *pspdata)
{
  int i;
  double rho;
  
  /* Write init tag */
  fprintf(fp, "<PP_RHOATOM>\n");

  /* Print valence density */
  for (i=0; i<pspdata->mesh->np; i++) {
    if (i != 0 && i % 4 == 0) fprintf(fp, "\n");
    rho = pspio_meshfunc_eval(pspdata->rho_valence, pspdata->mesh->r[i]);
    rho *= 4.0*M_PI*pspdata->mesh->r[i]*pspdata->mesh->r[i];
    fprintf(fp, " %18.11E", rho);
  }

  /* Write end tag */
  fprintf(fp, "\n</PP_RHOATOM>\n");
}

void upf_write_addinfo(FILE *fp, const pspio_pspdata_t *pspdata)
{
  int is;
  double occ;
  const char *label;
  const pspio_qn_t *qn;

  /* Write init tag */
  fprintf(fp, "<PP_ADDINFO>\n");

  /* Write wavefunctions data */
  for (is=0; is<pspdata->n_states; is++) {
    label = pspio_state_get_label(pspdata->states[is]);
    qn = pspio_state_get_qn(pspdata->states[is]);
    occ = pspio_state_get_occ(pspdata->states[is]);
    fprintf(fp, "%2s  %1d  %1d  %4.2f  %4.2f\n", label, pspio_qn_get_n(qn), pspio_qn_get_l(qn), pspio_qn_get_j(qn), occ);
  }
  
  /* Write projectors data */
  for (is=0; is<pspdata->n_projectors; is++) {
    qn = pspio_projector_get_qn(pspdata->projectors[is]);
    fprintf(fp, "  %2d  %4.2f\n", pspio_qn_get_l(qn), pspio_qn_get_j(qn));
  }

  /* Write extra line (we will put all the numbers to zero for the moment) */
  fprintf(fp, "  %12.6f%12.6f%12.6f%12.6f\n", 0.0, 0.0, 0.0, 0.0);

  /* Write end tag */
  fprintf(fp, "</PP_ADDINFO>\n");
}
