#include "transform.h"


__device__ double op(double d1,double *params) {
       double min = params[0];
       double max = params[1];
       if(origin >= min && origin <= max)
                return d1;
        if(min == 0 && max == 1) {
               double val = 1 / (1 + expf(-origin));
               return (floorf(val * (max - min)) + min);
         }
       
         double ret =  (floorf(origin * (max - min)) + min);
         return ret;
     
}

extern "C"
__global__ void setrange_strided_double(int n,int idx,double *dy,int incy,double *params,double *result) {
       transform(n,idx,dy,incy,params,result);

 }
