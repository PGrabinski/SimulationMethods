#include "rng.h"
/* Code taken from the lecture resources */

void RNG::setseeds(long seed, int lux){
  const long e_a= 40014,
             e_b= 2147483563,
             e_c= 53668,
             e_d= 12211;
  long e_k,nextseed, iseeds[24];
  const int lux_levels[5]={0,24,73,199,365};

  if( (lux > 4) || (lux < 0) )
       nskip=lux_levels[3];  // domyslny poziom 3
    else
       nskip=lux_levels[lux];

 nextseed= seed;
 // wybor 24 liczb calkowitych losowch

  for(int i=0; i<24; i++)
   {e_k=nextseed/e_c;
    nextseed= e_a*(nextseed -e_k*e_c) -e_k*e_d;
    if( nextseed < 0) nextseed += e_b;
    iseeds[i] = nextseed % two24;
   }
  for(int i=0; i<24; i++)
    dseeds[i] = iseeds[i] * twom24;

    i24=23;
    j24=9;
    carry=0.0;
    if (dseeds[23]==0.0) carry = twom24;
    count24=0;
};

double RNG::rnlx(){
    double tymcz, los;
    
  tymcz=dseeds[j24] - dseeds[i24] - carry;

  if (tymcz<0.0) {
     tymcz+=1.0;
     carry= twom24;}
    else
     carry=0.0;

  dseeds[i24]=tymcz;
  i24--;
  if (i24<0) i24=23;
  j24--;
  if (j24<0) j24=23;

// mniej niz 12 bitowe mantysy lub problem zera

  if (tymcz < twom12) {
    tymcz +=twom24* dseeds[j24];
    if (tymcz == 0.0) tymcz= twom24*twom24;
 }
  los= tymcz;
  count24++;

// odrzucenie nskip liczb po 24 kolejnych

if (count24==24) {
    count24=0;
  for (int i=0;i<nskip;i++) {
   tymcz=dseeds[j24] - dseeds[i24] - carry;

  if (tymcz<0.0) {
     tymcz+=1.0;
     carry= twom24;}
    else
     carry=0.0;
   dseeds[i24]=tymcz;
  i24--;
  if (i24<0) i24=23;
  j24--;
  if (j24<0) j24=23;
 }
}
  return (los);
}