/*    This file is distributed with 42,                               */
/*    the (mostly harmless) spacecraft dynamics simulation            */
/*    created by Eric Stoneking of NASA Goddard Space Flight Center   */

/*    Copyright 2010 United States Government                         */
/*    as represented by the Administrator                             */
/*    of the National Aeronautics and Space Administration.           */

/*    No copyright is claimed in the United States                    */
/*    under Title 17, U.S. Code.                                      */

/*    All Other Rights Reserved.                                      */


#include "42.h"

/* #ifdef __cplusplus
** namespace _42 {
** using namespace Kit;
** #endif
*/
/*********************************************************************/
/* Generic force/torque source, with harmonics or spread-spectrum    */
void ShakerFrcTrq(struct ShakerType *Sh, struct SCType *S)
{
      long i,It;
      double Sum,Signal;

      for(i=0;i<3;i++) {
         Sh->Frc[i] = 0.0;
         Sh->Trq[i] = 0.0;
      }
      
      Sum = 0.0;
      for(It=0;It<Sh->Ntone;It++) {
         Sum += Sh->ToneAmp[It]*sin(Sh->ToneFreq[It]*SimTime);
      }
      
      if (Sh->RandomActive) {
         Signal = GaussianRandom(Sh->RandomProc);
         Signal = SecondOrderLowpassFilter(Sh->Lowpass,Signal);
         if (Sh->LowBandLimit > 0.0) 
            Signal = SecondOrderHighpassFilter(Sh->Highpass,Signal);
         Sum += Sh->RandStd*Signal;
      }
      
      if (Sh->FrcTrq == FORCE) {
         for(i=0;i<3;i++) Sh->Frc[i] = Sum*Sh->Axis[i];
      }
      else {
         for(i=0;i<3;i++) Sh->Trq[i] = Sum*Sh->Axis[i];
      }
}
/*********************************************************************/
void WheelJitter(struct WhlType *W, struct SCType *S)
{
#if  0
      for(i=0;i<3;i++) {
         W->JitFrcB[i] = 0.0;
         W->JitTrqB[i] = 0.0;
      }
      
      for(Ih=0;Ih<W->NumHarm;Ih++) {
         for(i=0;i<3;i++)
            W->JitTrqB[i] = (c*W->Uhat[i]+s*W->Vhat[i]);
         }
      }
      
      /* Forces also exert Trq about Body cm */
      /* Forces and Torques contribute to flex */
#endif
}

/* #ifdef __cplusplus
** }
** #endif
*/
