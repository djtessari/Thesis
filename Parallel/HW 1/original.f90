!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
! Bad coding example 1
!
! Shamefully written by Ross Walker (SDSC, 2006)
!
! This code reads a series of coordinates and charges from the file
! specified as argument $1 on the command line.
!
! This file should have the format:
!  I9
! 4F10.4   (repeated I9 times representing x,y,z,q)
!
! It then calculates the following fictional function:
!
!             exp(rij*qi)*exp(rij*qj)   1
!    E = Sum( ----------------------- - - )  (rij <= cut)
!        j<i           r(ij)            a
!
! where cut is a cut off value specified on the command line ($2), 
! r(ij) is a function of the coordinates read in for each atom and 
! a is a constant.
!
! The code prints out the number of atoms, the cut off, total number of
! atom pairs which were less than or equal to the distance cutoff, the
! value of E, the time take to generate the coordinates and the time
! taken to perform the calculation of E.
!
! All calculations are done in double precision.
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

program calc_energy

     implicit none

     integer :: nargs
     integer :: natom, ier, ios, i, j, cut_count

     !Timer variables
     REAL*8 :: time0, time1, time2

     character(len=80) :: arg, filename
     character(len=30) :: cval
     REAL*8 :: cut     !Cut off for Rij in distance units
     REAL*8, allocatable, dimension(:,:) :: coords
     REAL*8, allocatable, dimension(:) :: q
     REAL*8 :: total_e, current_e, vec2, rij
     REAL*8 :: a

     a = 3.2d0

     call cpu_time(time0)  !Start time
     write(6,'(''Value of system clock at start = '',F14.4,/)') time0

     ! Step 1 - obtain the filename of the coord file and the value of
     ! cut from the command line.
     !         Argument 1 should be the filename of the coord file (char).
     !         Argument 2 should be the cut off (float).

     nargs=command_argument_count()
     if ( nargs < 2 ) then
        stop "Not enough input values"
     else
        call get_command_argument(1,filename)
        write(6,'(''Coordinates will be read from file: '',A,/)') filename
        call get_command_argument(2,cval)
        read(cval,'(f10.4)') cut
     endif

     ! Step 2 - Open the coordinate file and read the first line to
     ! obtain the number of atoms
     open(unit=10,file=filename,form='FORMATTED',iostat=ios)
     read(10,'(i9)') natom
     
     write(6,*) 'Natom = ', natom
     write(6,*) '  cut = ', cut

     ! Step 3 - Allocate the arrays to store the coordinate and charge data
     ier = 0
     allocate ( coords(natom,3), stat=ier )
     if ( ier /= 0 ) then
       write(6,*) 'Allocation error coords'
       stop
     end if
     allocate ( q(natom), stat=ier )
     if ( ier /= 0 ) then
       write(6,*) 'Allocation error q'
       stop
     end if
 
     ! Step 4 - read the coordinates and charges.
     do i = 1, natom
        read(10,'(4f10.4)') coords(i,:),q(i)
     end do

     call cpu_time(time1)
     write(6,'(''Value of system clock after coord read = '',F14.4,/)') time1

     ! Step 5 - calculate the number of pairs and E. - this is the
     ! majority of the work.
     total_e = 0.0d0
     cut_count = 0
     do i = 1, natom
       do j = 1, natom
         if ( j < i ) then   !Avoid double counting.
           vec2 = (coords(i,1)-coords(j,1))**2 + (coords(i,2)-coords(j,2))**2 &
                + (coords(i,3)-coords(j,3))**2
                  !X^2 + Y^2 + Z^2
           rij = sqrt(vec2)
           !Check if this is below the cut off
           if ( rij <= cut ) then
              !Increment the counter of pairs below cutoff
             cut_count = cut_count+1
             current_e = (exp(rij*q(i))*exp(rij*q(j)))/rij
             total_e = total_e + current_e - 1.0d0/a
           end if
         end if
       end do
     end do

     !time after reading of file and calculation
     call cpu_time(time2)
     write(6,'(''Value of system clock after coord read and E calc = '',F14.4,/)') &
          time2

     ! Step 6 - write out the results
     write(6,*) '                         Final Results'
     write(6,*) '                         -------------'
     write(6,*) '                   Num Pairs = ',cut_count
     write(6,*) '                     Total E = ',total_e
     write(6,'(''     Time to read coord file = '',F14.4, '' Seconds'')') &
          (time1-time0)
     write(6,'(''         Time to calculate E = '',F14.4, '' Seconds'')') &
          (time2-time1)
     write(6,'(''        Total Execution Time = '',F14.4, '' Seconds'')') &
          (time2-time0)

     ! Step 7 - Deallocate the arrays - we should strictly check the
     ! return values here but for the purposes of this tutorial we
     ! can ignore this.
     deallocate(q, stat=ier)
     deallocate(coords, stat=ier)

     close (unit=10)
   
     stop

end program calc_energy
