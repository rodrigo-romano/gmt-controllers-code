/*
 * File: M1SA_Control_CS.c
 *
 * Code generated for Simulink model 'M1SA_Control_CS'.
 *
 * Model version                  : 9.8
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Tue Sep 26 15:50:35 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objective: Execution efficiency
 * Validation result: All passed
 */

#include "M1SA_Control_CS.h"
#include <string.h>
#include "rtwtypes.h"

/* Model step function */
void M1SA_Control_CS_step(RT_MODEL_M1SA_Control_CS_T *const M1SA_Control_CS_M,
  ExtU_M1SA_Control_CS_T *M1SA_Control_CS_U, ExtY_M1SA_Control_CS_T
  *M1SA_Control_CS_Y)
{
  DW_M1SA_Control_CS_T *M1SA_Control_CS_DW = M1SA_Control_CS_M->dwork;

  /* local block i/o variables */
  real_T rtb_Fxcontroller;
  real_T rtb_Fycontroller;
  real_T rtb_Fzcontroller;
  real_T rtb_Mxcontroller;
  real_T rtb_Mycontroller;
  real_T rtb_Mzcontroller;
  real_T CS_SA_dyn_tmp[306];
  real_T rtb_CS_SA_dyn[306];
  real_T tmp[6];
  int32_T i;
  int32_T i_0;

  /* DiscreteStateSpace: '<S2>/Fx controller' */
  {
    rtb_Fxcontroller = (-7.3921740211573139)*
      M1SA_Control_CS_DW->Fxcontroller_DSTATE[0]
      + (7.4126298551022538)*M1SA_Control_CS_DW->Fxcontroller_DSTATE[1]
      + (1.8)*M1SA_Control_CS_DW->Fxcontroller_DSTATE[2];
    rtb_Fxcontroller += 0.012642385474274768*M1SA_Control_CS_U->LC_FxyzMxyz_CG[0];
  }

  /* DiscreteStateSpace: '<S2>/Fy controller' */
  {
    rtb_Fycontroller = (-7.3921740211573139)*
      M1SA_Control_CS_DW->Fycontroller_DSTATE[0]
      + (7.4126298551022538)*M1SA_Control_CS_DW->Fycontroller_DSTATE[1]
      + (1.8)*M1SA_Control_CS_DW->Fycontroller_DSTATE[2];
    rtb_Fycontroller += 0.012642385474274768*M1SA_Control_CS_U->LC_FxyzMxyz_CG[1];
  }

  /* DiscreteStateSpace: '<S2>/Fz controller' */
  {
    rtb_Fzcontroller = (12.828127654042241)*
      M1SA_Control_CS_DW->Fzcontroller_DSTATE[0]
      + (-8.7241200643849215)*M1SA_Control_CS_DW->Fzcontroller_DSTATE[1]
      + (2.4)*M1SA_Control_CS_DW->Fzcontroller_DSTATE[2];
    rtb_Fzcontroller += 0.014268776285624807*M1SA_Control_CS_U->LC_FxyzMxyz_CG[2];
  }

  /* DiscreteStateSpace: '<S2>/Mx controller' */
  {
    rtb_Mxcontroller = (10.967817725693546)*
      M1SA_Control_CS_DW->Mxcontroller_DSTATE[0]
      + (-7.4589652725422253)*M1SA_Control_CS_DW->Mxcontroller_DSTATE[1]
      + (2.0)*M1SA_Control_CS_DW->Mxcontroller_DSTATE[2];
    rtb_Mxcontroller += 0.012886532372532754*M1SA_Control_CS_U->LC_FxyzMxyz_CG[3];
  }

  /* DiscreteStateSpace: '<S2>/My controller' */
  {
    rtb_Mycontroller = (10.967817725693546)*
      M1SA_Control_CS_DW->Mycontroller_DSTATE[0]
      + (-7.4589652725422253)*M1SA_Control_CS_DW->Mycontroller_DSTATE[1]
      + (2.0)*M1SA_Control_CS_DW->Mycontroller_DSTATE[2];
    rtb_Mycontroller += 0.012886532372532754*M1SA_Control_CS_U->LC_FxyzMxyz_CG[4];
  }

  /* DiscreteStateSpace: '<S2>/Mz controller' */
  {
    rtb_Mzcontroller = (11.710424811124604)*
      M1SA_Control_CS_DW->Mzcontroller_DSTATE[0]
      + (-7.9639955894117387)*M1SA_Control_CS_DW->Mzcontroller_DSTATE[1]
      + (2.0)*M1SA_Control_CS_DW->Mzcontroller_DSTATE[2];
    rtb_Mzcontroller += 0.011890646904687337*M1SA_Control_CS_U->LC_FxyzMxyz_CG[5];
  }

  /* SignalConversion generated from: '<S1>/CS_Kbal' */
  tmp[0] = rtb_Fxcontroller;
  tmp[1] = rtb_Fycontroller;
  tmp[2] = rtb_Fzcontroller;
  tmp[3] = rtb_Mxcontroller;
  tmp[4] = rtb_Mycontroller;
  tmp[5] = rtb_Mzcontroller;
  for (i = 0; i < 306; i++) {
    int32_T tmp_0;

    /* Gain: '<S1>/CS_Kbal' */
    rtb_CS_SA_dyn[i] = 0.0;
    tmp_0 = 0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_CS_SA_dyn[i] += M1SA_Control_CS_ConstP.CS_Kbal_Gain[tmp_0 + i] *
        tmp[i_0];
      tmp_0 += 306;
    }

    real_T denAccum;

    /* DiscreteTransferFcn: '<S1>/CS_SA_dyn' incorporates:
     *  Gain: '<S1>/CS_Kbal'
     *  Sum: '<S1>/Add'
     */
    denAccum = (rtb_CS_SA_dyn[i] + M1SA_Control_CS_U->SA_offsetF_cmd[i]) -
      -0.53348809109110329 * M1SA_Control_CS_DW->CS_SA_dyn_states[i];
    rtb_CS_SA_dyn[i] = 0.25752323685913081 * denAccum + 0.208988672049766 *
      M1SA_Control_CS_DW->CS_SA_dyn_states[i];

    /* Outport: '<Root>/Res_Act_F' incorporates:
     *  Gain: '<S1>/CS_Kbal'
     */
    M1SA_Control_CS_Y->Res_Act_F[i] = rtb_CS_SA_dyn[i];

    /* DiscreteTransferFcn: '<S1>/CS_SA_dyn' incorporates:
     *  Gain: '<S1>/CS_Kbal'
     */
    CS_SA_dyn_tmp[i] = denAccum;
  }

  /* Update for DiscreteStateSpace: '<S2>/Fx controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.52775904867953072)*M1SA_Control_CS_DW->Fxcontroller_DSTATE[0]
      + (-1.2891560542128015E-6)*M1SA_Control_CS_DW->Fxcontroller_DSTATE[1]
      + (0.10924135978078692)*M1SA_Control_CS_DW->Fxcontroller_DSTATE[2];
    xnew[0] += (0.0021005747961215936)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[0];
    xnew[1] = (0.67526840564046886)*M1SA_Control_CS_DW->Fxcontroller_DSTATE[0]
      + (0.52589300864421529)*M1SA_Control_CS_DW->Fxcontroller_DSTATE[1]
      + (-0.046836283893988175)*M1SA_Control_CS_DW->Fxcontroller_DSTATE[2];
    xnew[1] += (-0.0007868586132831378)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[0];
    xnew[2] = (1.0)*M1SA_Control_CS_DW->Fxcontroller_DSTATE[2];
    xnew[2] += (0.019999999999999997)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[0];
    (void) memcpy(&M1SA_Control_CS_DW->Fxcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteStateSpace: '<S2>/Fy controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.52775904867953072)*M1SA_Control_CS_DW->Fycontroller_DSTATE[0]
      + (-1.2891560542128015E-6)*M1SA_Control_CS_DW->Fycontroller_DSTATE[1]
      + (0.10924135978078692)*M1SA_Control_CS_DW->Fycontroller_DSTATE[2];
    xnew[0] += (0.0021005747961215936)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[1];
    xnew[1] = (0.67526840564046886)*M1SA_Control_CS_DW->Fycontroller_DSTATE[0]
      + (0.52589300864421529)*M1SA_Control_CS_DW->Fycontroller_DSTATE[1]
      + (-0.046836283893988175)*M1SA_Control_CS_DW->Fycontroller_DSTATE[2];
    xnew[1] += (-0.0007868586132831378)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[1];
    xnew[2] = (1.0)*M1SA_Control_CS_DW->Fycontroller_DSTATE[2];
    xnew[2] += (0.019999999999999997)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[1];
    (void) memcpy(&M1SA_Control_CS_DW->Fycontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteStateSpace: '<S2>/Fz controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.21299171395697813)*M1SA_Control_CS_DW->Fzcontroller_DSTATE[0]
      + (-0.025706976978449959)*M1SA_Control_CS_DW->Fzcontroller_DSTATE[1]
      + (-0.13633756510415562)*M1SA_Control_CS_DW->Fzcontroller_DSTATE[2];
    xnew[0] += (-0.0025627416011340873)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[2];
    xnew[1] = (0.70895690762960162)*M1SA_Control_CS_DW->Fzcontroller_DSTATE[0]
      + (0.48299274286721938)*M1SA_Control_CS_DW->Fzcontroller_DSTATE[1]
      + (-0.0084732937815497674)*M1SA_Control_CS_DW->Fzcontroller_DSTATE[2];
    xnew[1] += (-0.00028551072748039764)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[2];
    xnew[2] = (1.0)*M1SA_Control_CS_DW->Fzcontroller_DSTATE[2];
    xnew[2] += (0.019999999999999997)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[2];
    (void) memcpy(&M1SA_Control_CS_DW->Fzcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteStateSpace: '<S2>/Mx controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.21299171395697802)*M1SA_Control_CS_DW->Mxcontroller_DSTATE[0]
      + (-0.025706976978449963)*M1SA_Control_CS_DW->Mxcontroller_DSTATE[1]
      + (-0.11656615864405333)*M1SA_Control_CS_DW->Mxcontroller_DSTATE[2];
    xnew[0] += (-0.0021910978372930165)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[3];
    xnew[1] = (0.7089569076296014)*M1SA_Control_CS_DW->Mxcontroller_DSTATE[0]
      + (0.48299274286721916)*M1SA_Control_CS_DW->Mxcontroller_DSTATE[1]
      + (-0.007244513325606502)*M1SA_Control_CS_DW->Mxcontroller_DSTATE[2];
    xnew[1] += (-0.00024410652140247619)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[3];
    xnew[2] = (1.0)*M1SA_Control_CS_DW->Mxcontroller_DSTATE[2];
    xnew[2] += (0.019999999999999997)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[3];
    (void) memcpy(&M1SA_Control_CS_DW->Mxcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteStateSpace: '<S2>/My controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.21299171395697802)*M1SA_Control_CS_DW->Mycontroller_DSTATE[0]
      + (-0.025706976978449963)*M1SA_Control_CS_DW->Mycontroller_DSTATE[1]
      + (-0.11656615864405333)*M1SA_Control_CS_DW->Mycontroller_DSTATE[2];
    xnew[0] += (-0.0021910978372930165)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[4];
    xnew[1] = (0.7089569076296014)*M1SA_Control_CS_DW->Mycontroller_DSTATE[0]
      + (0.48299274286721916)*M1SA_Control_CS_DW->Mycontroller_DSTATE[1]
      + (-0.007244513325606502)*M1SA_Control_CS_DW->Mycontroller_DSTATE[2];
    xnew[1] += (-0.00024410652140247619)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[4];
    xnew[2] = (1.0)*M1SA_Control_CS_DW->Mycontroller_DSTATE[2];
    xnew[2] += (0.019999999999999997)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[4];
    (void) memcpy(&M1SA_Control_CS_DW->Mycontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteStateSpace: '<S2>/Mz controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.21299171395697802)*M1SA_Control_CS_DW->Mzcontroller_DSTATE[0]
      + (-0.025706976978449959)*M1SA_Control_CS_DW->Mzcontroller_DSTATE[1]
      + (-0.12445859973812538)*M1SA_Control_CS_DW->Mzcontroller_DSTATE[2];
    xnew[0] += (-0.0023394523066634118)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[5];
    xnew[1] = (0.7089569076296014)*M1SA_Control_CS_DW->Mzcontroller_DSTATE[0]
      + (0.48299274286721938)*M1SA_Control_CS_DW->Mzcontroller_DSTATE[1]
      + (-0.00773502356753846)*M1SA_Control_CS_DW->Mzcontroller_DSTATE[2];
    xnew[1] += (-0.00026063444308454018)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[5];
    xnew[2] = (1.0)*M1SA_Control_CS_DW->Mzcontroller_DSTATE[2];
    xnew[2] += (0.019999999999999997)*M1SA_Control_CS_U->LC_FxyzMxyz_CG[5];
    (void) memcpy(&M1SA_Control_CS_DW->Mzcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteTransferFcn: '<S1>/CS_SA_dyn' */
  memcpy(&M1SA_Control_CS_DW->CS_SA_dyn_states[0], &CS_SA_dyn_tmp[0], 306U *
         sizeof(real_T));
}

/* Model initialize function */
void M1SA_Control_CS_initialize(RT_MODEL_M1SA_Control_CS_T *const
  M1SA_Control_CS_M)
{
  /* (no initialization code required) */
  UNUSED_PARAMETER(M1SA_Control_CS_M);
}

/* Model terminate function */
void M1SA_Control_CS_terminate(RT_MODEL_M1SA_Control_CS_T *const
  M1SA_Control_CS_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(M1SA_Control_CS_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
