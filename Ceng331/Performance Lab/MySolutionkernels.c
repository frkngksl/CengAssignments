/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/*
 * Please fill in the following student struct
 */
team_t team = {
    "2237436",              /* Student ID */

    "Furkan Goksel",     /* full name */
    "e223743@metu.edu.tr",  /* email address */

    "",                   /* leave blank */
    ""                    /* leave blank */
};


/***************
 * Sobel KERNEL
 ***************/

/******************************************************
 * Your different versions of the sobel functions  go here
 ******************************************************/

/*
 * naive_sobel - The naive baseline version of Sobel
 */
char naive_sobel_descr[] = "sobel: Naive baseline implementation";
void naive_sobel(int dim,int *src, int *dst) {
    int i,j,k,l;
    int ker[3][3] = {{-1, 0, 1},
                     {-2, 0, 2},
                     {-1, 0, 1}};

    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++) {
	   dst[j*dim+i]=0;
            if(!((i == 0) || (i == dim-1) || (j == 0) || (j == dim-1))){
            for(k = -1; k <= 1; k++)
                for(l = -1; l <= 1; l++) {
                 dst[j*dim+i]=dst[j*dim+i]+src[(j + l)*dim+(i + k)] * ker[(l+1)][(k+1)];
                }


      }

}
}
/*
 * sobel - Your current working version of sobel
 * IMPORTANT: This is the version you will be graded on
 */

char sobel_descr[] = "Dot product: Current working version";
void sobel(int dim,int *src,int *dst)
{
    int i,j,aradeger,aradeger1,aradeger2,aradeger3;
    aradeger2 = dim-1;
    aradeger3 = dim*(dim-1);
    aradeger1 = 0;
    for(i=dim-1;i>=0;i--){
        dst[i] = 0;
        dst[aradeger3+i] = 0;
        dst[i*dim+aradeger2] = 0;
        dst[i*dim] = 0;
    }
    for(i = 1; i < dim-1; i++){
      aradeger1+=dim;
      for(j = 1; j < dim-1; j++) {
               aradeger = aradeger1+j;
               dst[aradeger] = -src[aradeger-dim-1]+src[aradeger-dim+1]+(src[aradeger+1]-src[aradeger-1])*2-src[aradeger+dim-1]+src[aradeger+dim+1];
             }
    }
}

/*
for(i=dim-1;i>=0;i--){
  dst[i] = 0;
  dst[aradeger3+i] = 0;
  dst[i*dim+aradeger2] = 0;
  dst[i*dim] = 0;

}
*/

/*
char sobel_descr_v1[] = "Sobel version 1 CPE: 10.5";
void sobel_v1(int dim,int *src,int *dst)
{
  int i,j,aradeger,aradeger1,aradeger2,aradeger3;
      aradeger2 = dim-1;
      aradeger3 = dim*(dim-1);
      aradeger1 = 0;
      for(i=0;i<dim;i++){
        dst[i] = 0;
        dst[aradeger3+i] = 0;
        dst[i*dim+aradeger2] = 0;
        dst[i*dim] = 0;

      }
      for(i = 1; i < dim-1; i++){
        aradeger1+=dim;
        for(j = 1; j < dim-1; j++) {
               aradeger = aradeger1+j;
                 dst[aradeger] = -src[aradeger-dim-1]+src[aradeger-dim+1]+(src[aradeger+1]-src[aradeger-1])*2-src[aradeger+dim-1]+src[aradeger+dim+1];
               }
      }
}*/



/*********************************************************************
 * register_sobel_functions - Register all of your different versions
 *     of the sobel functions  with the driver by calling the
 *     add_sobel_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_sobel_functions() {
    //add_sobel_function(&naive_sobel, naive_sobel_descr);
    //add_sobel_function(&sobel_v2, sobel_descr_v2);
    add_sobel_function(&sobel, sobel_descr);
    /* ... Register additional test functions here */
}




/***************
 * MIRROR KERNEL
 ***************/

/******************************************************
 * Your different versions of the mirror func  go here
 ******************************************************/

/*
 * naive_mirror - The naive baseline version of mirror
 */
char naive_mirror_descr[] = "Naive_mirror: Naive baseline implementation";
void naive_mirror(int dim,int *src,int *dst) {

 	int i,j;

  for(j = 0; j < dim; j++)
        for(i = 0; i < dim; i++) {
            dst[RIDX(j,i,dim)]=src[RIDX(j,dim-1-i,dim)];

        }


}


/*
 * mirror - Your current working version of mirror
 * IMPORTANT: This is the version you will be graded on
 */
char mirror_descr[] = "Mirror: Current working version";
void mirror(int dim,int *src,int *dst)
{
    int i,j,i1,aradeger2,aradeger3;
    j=dim*dim;
    aradeger3=0;
    aradeger2=0;
    //aradeger2= dim-1;
    //aradeger1= dim-2;
    //j=dim*dim;
    i1=0;
    //i2=1;
    for(i = 0; i < j;i+=32){
        if(i == aradeger3){
            //aradeger1= i1;
            aradeger3+=dim;
            aradeger2= i1+dim-1;
            //aradeger1 = i1+dim-2;
        }
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;
            dst[i1]=src[aradeger2];
            dst[i1+1]=src[aradeger2-1];
            aradeger2-=2;
            //aradeger1-=2;
            i1+=2;
            //i2+=2;

    }

}

/*********************************************************************
 * register_mirror_functions - Register all of your different versions
 *     of the mirror functions  with the driver by calling the
 *     add_mirror_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

/*
char mirror_descr1[] = "Mirror: Current working version2 ";
void mirror1(int dim,int *src,int *dst)
{
    int i,j,i1,i2,aradeger2,aradeger1,aradeger3;
    aradeger3=dim;
    aradeger2= dim-1;
    aradeger1= dim-2;
    j=dim*dim;
    i1=0;
    i2=1;

    for(i = 0; i < j;i+=32){
        if(i == aradeger3){
            //aradeger1= i1;
            aradeger3+=dim;
            aradeger2= i1+dim-1;
            aradeger1 = i1+dim-2;
        }
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;
            dst[i1]=src[aradeger2];
            dst[i2]=src[aradeger1];
            aradeger2-=2;
            aradeger1-=2;
            i1+=2;
            i2+=2;

    }

}
*/

void register_mirror_functions() {
    //add_mirror_function(&naive_mirror, naive_mirror_descr);
    add_mirror_function(&mirror, mirror_descr);
    //add_mirror_function(&mirror1, mirror_descr1);
    /* ... Register additional test functions here */
}
