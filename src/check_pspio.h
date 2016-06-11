/* Copyright (C) 2011-2016 Joseba Alberdi <alberdi@hotmail.es>
 *                         Matthieu Verstraete <matthieu.jean.verstraete@gmail.com>
 *                         Micael Oliveira <micaeljtoliveira@gmail.com>
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

#ifndef CHECK_PSPIO_H
#define CHECK_PSPIO_H

/**
 * @file check_pspio.h 
 * @brief pspsio check testsuites
 */

Suite *make_info_suite(void);
Suite *make_error_suite(void);
Suite *make_qn_suite(void);
Suite *make_mesh_suite(void);
Suite *make_meshfunc_suite(void);
Suite *make_potential_suite(void);
Suite *make_projector_suite(void);
Suite *make_state_suite(void);
Suite *make_xc_suite(void);
Suite *make_pspinfo_suite(void);
Suite *make_pspdata_suite(void);

#endif
