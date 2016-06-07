!! Copyright (C) 2012-2015 M. Oliveira
!!
!! This program is free software; you can redistribute it and/or modify
!! it under the terms of the GNU Lesser General Public License as published by
!! the Free Software Foundation; either version 3 of the License, or 
!! (at your option) any later version.
!!
!! This program is distributed in the hope that it will be useful,
!! but WITHOUT ANY WARRANTY; without even the implied warranty of
!! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
!! GNU Lesser General Public License for more details.
!!
!! You should have received a copy of the GNU Lesser General Public License
!! along with this program; if not, write to the Free Software
!! Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
!!


!*********************************************************************!
! Routines                                                            !
!*********************************************************************!

! fetchall
subroutine fpspio_error_fetchall(error_msg)
  character(len=PSPIO_STRLEN_ERROR), intent(out) :: error_msg

  character(kind=c_char) :: c_error_msg(PSPIO_STRLEN_ERROR)
    
  call pspio_error_fetchall(c_error_msg)
  call c_to_f_string(c_error_msg, error_msg)

end subroutine fpspio_error_fetchall

! get_last
integer function fpspio_error_get_last(routine) result(last)
  character(len=*), intent(in) :: routine

  last = pspio_error_get_last(f_to_c_string(routine))

end function fpspio_error_get_last

! len
integer function fpspio_error_len() result(len)

  len = pspio_error_len()

end function fpspio_error_len

! string
subroutine fpspio_error_string(error_id, error_msg)
  integer,                           intent(in)  :: error_id
  character(len=PSPIO_STRLEN_ERROR), intent(out) :: error_msg

  character(kind=c_char) :: c_error_msg(PSPIO_STRLEN_ERROR)

  c_error_msg = pspio_error_string(error_id)
  call c_to_f_string(c_error_msg, error_msg)

end subroutine fpspio_error_string