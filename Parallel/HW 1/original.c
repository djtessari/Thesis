/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
double **alloc_2D_double(int nrows, int ncolumns);
void double_2D_array_free(double **array);

int main(int argc, char *argv[])
{
    long natom, i, j;
    long cut_count;

    /* Timer variables */
    clock_t time0, time1, time2;

    double cut;     /* Cut off for Rij in distance units */
    double **coords;
    double *q;
    double total_e, current_e, vec2, rij;
    double a;
    FILE *fptr;
    char *cptr;

    a = 3.2;

    time0 = clock(); /*Start Time*/
    printf("Value of system clock at start = %ld\n",time0);

    /* Step 1 - obtain the filename of the coord file and the value of
       cut from the command line.
                Argument 1 should be the filename of the coord file (char).
                Argument 2 should be the cut off (float). */
    /* Quit therefore if iarg does not equal 3 = executable name,
       filename, cut off */
    if (argc != 3)
    {
        printf("ERROR: only %d command line options detected", argc-1);
        printf (" - need 2 options, filename and cutoff.\n");
        exit(1);
    }
    printf("Coordinates will be read from file: %s\n",argv[1]);

    /* Step 2 - Open the coordinate file and read the first line to
       obtain the number of atoms */
    if ((fptr=fopen(argv[1],"r"))==NULL)
    {
        printf("ERROR: Could not open file called %s\n",argv[1]);
        exit(1);
    }
    else
    {
        fscanf(fptr, "%ld", &natom);
    }

    printf("Natom = %ld\n", natom);

    cut = strtod(argv[2],&cptr);
    printf("cut = %10.4f\n", cut);

    /* Step 3 - Allocate the arrays to store the coordinate and charge
       data */
    coords=alloc_2D_double(3,natom);
    if ( coords==NULL )
    {
        printf("Allocation error coords");
        exit(1);
    }
    q=(double *)malloc(natom*sizeof(double));
    if ( q == NULL )
    {
        printf("Allocation error q");
        exit(1);
    }

    /* Step 4 - read the coordinates and charges. */
    for (i = 0; i<natom; ++i)
    {
        fscanf(fptr, "%lf %lf %lf %lf",&coords[0][i],
               &coords[1][i],&coords[2][i],&q[i]);
    }

    time1 = clock(); /*time after file read*/
    printf("Value of system clock after coord read = %ld\n",time1);


    /* Step 5 - calculate the number of pairs and E. - this is the
       majority of the work. */
    total_e = 0.0;
    cut_count = 0;

    /*double coords_x;
    double coords_y;
    double coords_z;*/


    double coords_xi;
	double coords_yi;
	double coords_zi;
    double coords_xj;
	double coords_yj;
	double coords_zj;/**/

    for (i=1; i<=natom; ++i)
    {
    	coords_xi = coords[0][i-1];
    	coords_yi = coords[1][i-1];
    	coords_zi = coords[2][i-1];

        for (j=1; j<=natom; ++j)
        {
            if ( j < i )   /* Avoid double counting. */
            {
                /* X^2 + Y^2 + Z^2 */

            	/*coords_x = (coords[0][i-1]-coords[0][j-1]);
            	coords_y = (coords[1][i-1]-coords[1][j-1]);
            	coords_z = (coords[2][i-1]-coords[2][j-1]);

                vec2 = (coords_x * coords_x) +
                		(coords_y * coords_y) +
                		(coords_z * coords_z);*/

            	/**/coords_xj = coords[0][j-1];
            	coords_yj = coords[1][j-1];
            	coords_zj = coords[2][j-1];

            	vec2 = ((coords_xi - coords_xj) * (coords_xi - coords_xj)) +
            			((coords_yi - coords_yj) * (coords_yi - coords_yj)) +
            			((coords_zi - coords_zj) * (coords_zi - coords_zj));/**/

                /*vec2 = ((coords[0][i-1]-coords[0][j-1])* (coords[0][i-1]-coords[0][j-1])) +
                		((coords[1][i-1]-coords[1][j-1])* (coords[1][i-1]-coords[1][j-1])) +
                		((coords[2][i-1]-coords[2][j-1])* (coords[2][i-1]-coords[2][j-1]));/**/

                /* Check if this is below the cut off */
                if ( vec2 <= (cut*cut) )
                {
                	rij = sqrt(vec2);
                	double i_rij = 1.0/rij;
                    /* Increment the counter of pairs below cutoff */
                    ++cut_count;

                    current_e = (exp(rij*(q[i-1]+q[j-1])))* i_rij;
                    total_e = total_e + current_e - 1.0/a;
                }
            }
        }
    }

    time2 = clock(); /* time after reading of file and calculation */
    printf("Value of system clock after coord read and E calc = %ld\n",
           time2);

    /* Step 6 - write out the results */
    printf("                         Final Results\n");
    printf("                         -------------\n");
    printf("                   Num Pairs = %ld\n",cut_count);
    printf("                     Total E = %14.10f\n",total_e);
    printf("     Time to read coord file = %14.4f Seconds\n",
           ((double )(time1-time0))/(double )CLOCKS_PER_SEC);
    printf("         Time to calculate E = %14.4f Seconds\n",
           ((double )(time2-time1))/(double )CLOCKS_PER_SEC);
    printf("        Total Execution Time = %14.4f Seconds\n",
           ((double )(time2-time0))/(double )CLOCKS_PER_SEC);

    /* Step 7 - Deallocate the arrays - we should strictly check the
       return values here but for the purposes of this tutorial we can
       ignore this. */
    free(q);
    double_2D_array_free(coords);

    fclose(fptr);

    exit(0);
}

double **alloc_2D_double(int nrows, int ncolumns)
{
    /* Allocates a 2d_double_array consisting of a series of pointers
       pointing to each row that are then allocated to be ncolumns
       long each. */

    /* Try's to keep contents contiguous - thus reallocation is
       difficult! */

    /* Returns the pointer **array. Returns NULL on error */
    int i;

    double **array = (double **)malloc(nrows*sizeof(double *));
    if (array==NULL)
        return NULL;
    array[0] = (double *)malloc(nrows*ncolumns*sizeof(double));
    if (array[0]==NULL)
        return NULL;

    for (i = 1; i < nrows; ++i)
        array[i] = array[0] + i * ncolumns;

    return array;

}

void double_2D_array_free(double **array)
{
    /* Frees the memory previously allocated by alloc_2D_double */
    free(array[0]);
    free(array);
}
