/*
 * File: M1SA_Control_OA.c
 *
 * Code generated for Simulink model 'M1SA_Control_OA'.
 *
 * Model version                  : 9.9
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Fri Sep 22 11:47:30 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objective: Execution efficiency
 * Validation result: All passed
 */

#include "M1SA_Control_OA.h"
#include <string.h>
#include "rtwtypes.h"

/* Model step function */
void M1SA_Control_OA_step(RT_MODEL_M1SA_Control_OA_T *const M1SA_Control_OA_M,
  ExtU_M1SA_Control_OA_T *M1SA_Control_OA_U, ExtY_M1SA_Control_OA_T
  *M1SA_Control_OA_Y)
{
  DW_M1SA_Control_OA_T *M1SA_Control_OA_DW = M1SA_Control_OA_M->dwork;

  /* local block i/o variables */
  real_T rtb_Fxcontroller;
  real_T rtb_Fycontroller;
  real_T rtb_Fzcontroller;
  real_T rtb_Mxcontroller;
  real_T rtb_Mycontroller;
  real_T rtb_Mzcontroller;
  real_T OA_SA_dyn_tmp[335];
  real_T rtb_OA_SA_dyn[335];
  real_T tmp[6];
  int32_T i;
  int32_T i_0;

  /* DiscreteStateSpace: '<S2>/Fx controller' */
  {
    rtb_Fxcontroller = (7.5622535257455974)*
      M1SA_Control_OA_DW->Fxcontroller_DSTATE[0]
      + (-6.8579527778000955)*M1SA_Control_OA_DW->Fxcontroller_DSTATE[1]
      + (1.8)*M1SA_Control_OA_DW->Fxcontroller_DSTATE[2];
    rtb_Fxcontroller += 0.025658831817905264*M1SA_Control_OA_U->LC_FxyzMxyz_CG[0];
  }

  /* DiscreteStateSpace: '<S2>/Fy controller' */
  {
    rtb_Fycontroller = (7.5622535257455974)*
      M1SA_Control_OA_DW->Fycontroller_DSTATE[0]
      + (-6.8579527778000955)*M1SA_Control_OA_DW->Fycontroller_DSTATE[1]
      + (1.8)*M1SA_Control_OA_DW->Fycontroller_DSTATE[2];
    rtb_Fycontroller += 0.025658831817905264*M1SA_Control_OA_U->LC_FxyzMxyz_CG[1];
  }

  /* DiscreteStateSpace: '<S2>/Fz controller' */
  {
    rtb_Fzcontroller = (-8.0452180712686552)*
      M1SA_Control_OA_DW->Fzcontroller_DSTATE[0]
      + (12.880901848926591)*M1SA_Control_OA_DW->Fzcontroller_DSTATE[1]
      + (2.4)*M1SA_Control_OA_DW->Fzcontroller_DSTATE[2];
    rtb_Fzcontroller += 0.028976737947344153*M1SA_Control_OA_U->LC_FxyzMxyz_CG[2];
  }

  /* DiscreteStateSpace: '<S2>/Mx controller' */
  {
    rtb_Mxcontroller = (-6.8785163157715967)*
      M1SA_Control_OA_DW->Mxcontroller_DSTATE[0]
      + (11.012938710276934)*M1SA_Control_OA_DW->Mxcontroller_DSTATE[1]
      + (2.0)*M1SA_Control_OA_DW->Mxcontroller_DSTATE[2];
    rtb_Mxcontroller += 0.026094106686655082*M1SA_Control_OA_U->LC_FxyzMxyz_CG[3];
  }

  /* DiscreteStateSpace: '<S2>/My controller' */
  {
    rtb_Mycontroller = (-6.8785163157715967)*
      M1SA_Control_OA_DW->Mycontroller_DSTATE[0]
      + (11.012938710276934)*M1SA_Control_OA_DW->Mycontroller_DSTATE[1]
      + (2.0)*M1SA_Control_OA_DW->Mycontroller_DSTATE[2];
    rtb_Mycontroller += 0.026094106686655082*M1SA_Control_OA_U->LC_FxyzMxyz_CG[4];
  }

  /* DiscreteStateSpace: '<S2>/Mz controller' */
  {
    rtb_Mzcontroller = (11.755367117629582)*
      M1SA_Control_OA_DW->Mzcontroller_DSTATE[0]
      + (-6.20439479463091)*M1SA_Control_OA_DW->Mzcontroller_DSTATE[1]
      + (2.0)*M1SA_Control_OA_DW->Mzcontroller_DSTATE[2];
    rtb_Mzcontroller += 0.02487949996962166*M1SA_Control_OA_U->LC_FxyzMxyz_CG[5];
  }

  /* SignalConversion generated from: '<S1>/OAseg_Kbal' */
  tmp[0] = rtb_Fxcontroller;
  tmp[1] = rtb_Fycontroller;
  tmp[2] = rtb_Fzcontroller;
  tmp[3] = rtb_Mxcontroller;
  tmp[4] = rtb_Mycontroller;
  tmp[5] = rtb_Mzcontroller;
  for (i = 0; i < 335; i++) {
    int32_T tmp_0;

    /* Gain: '<S1>/OAseg_Kbal' */
    rtb_OA_SA_dyn[i] = 0.0;
    tmp_0 = 0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_OA_SA_dyn[i] += M1SA_Control_OA_ConstP.OAseg_Kbal_Gain[tmp_0 + i] *
        tmp[i_0];
      tmp_0 += 335;
    }

    real_T denAccum;

    /* DiscreteTransferFcn: '<S1>/OA_SA_dyn' incorporates:
     *  Gain: '<S1>/OAseg_Kbal'
     *  Sum: '<S1>/Add'
     */
    denAccum = (rtb_OA_SA_dyn[i] + M1SA_Control_OA_U->SA_offsetF_cmd[i]) -
      -0.53348809109110329 * M1SA_Control_OA_DW->OA_SA_dyn_states[i];
    rtb_OA_SA_dyn[i] = 0.25752323685913081 * denAccum + 0.20898867204976596 *
      M1SA_Control_OA_DW->OA_SA_dyn_states[i];

    /* Outport: '<Root>/Res_Act_F' incorporates:
     *  Gain: '<S1>/OAseg_Kbal'
     */
    M1SA_Control_OA_Y->Res_Act_F[i] = rtb_OA_SA_dyn[i];

    /* DiscreteTransferFcn: '<S1>/OA_SA_dyn' incorporates:
     *  Gain: '<S1>/OAseg_Kbal'
     */
    OA_SA_dyn_tmp[i] = denAccum;
  }

  /* Update for DiscreteStateSpace: '<S2>/Fx controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.511351229220175)*M1SA_Control_OA_DW->Fxcontroller_DSTATE[0]
      + (-0.001576998122077304)*M1SA_Control_OA_DW->Fxcontroller_DSTATE[1]
      + (-0.11036019858665438)*M1SA_Control_OA_DW->Fxcontroller_DSTATE[2];
    xnew[0] += (-0.004238743449428482)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[0];
    xnew[1] = (0.6610857933659714)*M1SA_Control_OA_DW->Fxcontroller_DSTATE[0]
      + (0.57592772818597882)*M1SA_Control_OA_DW->Fxcontroller_DSTATE[1]
      + (0.043538003578442772)*M1SA_Control_OA_DW->Fxcontroller_DSTATE[2];
    xnew[1] += (0.0014542111181502554)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[0];
    xnew[2] = (1.0)*M1SA_Control_OA_DW->Fxcontroller_DSTATE[2];
    xnew[2] += (0.039999999999999994)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[0];
    (void) memcpy(&M1SA_Control_OA_DW->Fxcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteStateSpace: '<S2>/Fy controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.511351229220175)*M1SA_Control_OA_DW->Fycontroller_DSTATE[0]
      + (-0.001576998122077304)*M1SA_Control_OA_DW->Fycontroller_DSTATE[1]
      + (-0.11036019858665438)*M1SA_Control_OA_DW->Fycontroller_DSTATE[2];
    xnew[0] += (-0.004238743449428482)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[1];
    xnew[1] = (0.6610857933659714)*M1SA_Control_OA_DW->Fycontroller_DSTATE[0]
      + (0.57592772818597882)*M1SA_Control_OA_DW->Fycontroller_DSTATE[1]
      + (0.043538003578442772)*M1SA_Control_OA_DW->Fycontroller_DSTATE[2];
    xnew[1] += (0.0014542111181502554)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[1];
    xnew[2] = (1.0)*M1SA_Control_OA_DW->Fycontroller_DSTATE[2];
    xnew[2] += (0.039999999999999994)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[1];
    (void) memcpy(&M1SA_Control_OA_DW->Fycontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteStateSpace: '<S2>/Fz controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.525031511317383)*M1SA_Control_OA_DW->Fzcontroller_DSTATE[0]
      + (0.69841472402646065)*M1SA_Control_OA_DW->Fzcontroller_DSTATE[1]
      + (-0.0098680755354391848)*M1SA_Control_OA_DW->Fzcontroller_DSTATE[2];
    xnew[0] += (-0.00062903137264610479)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[2];
    xnew[1] = (-0.0372950980458177)*M1SA_Control_OA_DW->Fzcontroller_DSTATE[0]
      + (0.20224709032275345)*M1SA_Control_OA_DW->Fzcontroller_DSTATE[1]
      + (-0.13638868105322574)*M1SA_Control_OA_DW->Fzcontroller_DSTATE[2];
    xnew[1] += (-0.0051217175975894645)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[2];
    xnew[2] = (1.0)*M1SA_Control_OA_DW->Fzcontroller_DSTATE[2];
    xnew[2] += (0.039999999999999994)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[2];
    (void) memcpy(&M1SA_Control_OA_DW->Fzcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteStateSpace: '<S2>/Mx controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.52503151131738313)*M1SA_Control_OA_DW->Mxcontroller_DSTATE[0]
      + (0.69841472402646065)*M1SA_Control_OA_DW->Mxcontroller_DSTATE[1]
      + (-0.00843702656341808)*M1SA_Control_OA_DW->Mxcontroller_DSTATE[2];
    xnew[0] += (-0.00053781047593109391)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[3];
    xnew[1] = (-0.037295098045817723)*M1SA_Control_OA_DW->Mxcontroller_DSTATE[0]
      + (0.20224709032275345)*M1SA_Control_OA_DW->Mxcontroller_DSTATE[1]
      + (-0.11660986185838015)*M1SA_Control_OA_DW->Mxcontroller_DSTATE[2];
    xnew[1] += (-0.0043789761505169771)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[3];
    xnew[2] = (1.0)*M1SA_Control_OA_DW->Mxcontroller_DSTATE[2];
    xnew[2] += (0.039999999999999994)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[3];
    (void) memcpy(&M1SA_Control_OA_DW->Mxcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteStateSpace: '<S2>/My controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.52503151131738313)*M1SA_Control_OA_DW->Mycontroller_DSTATE[0]
      + (0.69841472402646065)*M1SA_Control_OA_DW->Mycontroller_DSTATE[1]
      + (-0.00843702656341808)*M1SA_Control_OA_DW->Mycontroller_DSTATE[2];
    xnew[0] += (-0.00053781047593109391)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[4];
    xnew[1] = (-0.037295098045817723)*M1SA_Control_OA_DW->Mycontroller_DSTATE[0]
      + (0.20224709032275345)*M1SA_Control_OA_DW->Mycontroller_DSTATE[1]
      + (-0.11660986185838015)*M1SA_Control_OA_DW->Mycontroller_DSTATE[2];
    xnew[1] += (-0.0043789761505169771)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[4];
    xnew[2] = (1.0)*M1SA_Control_OA_DW->Mycontroller_DSTATE[2];
    xnew[2] += (0.039999999999999994)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[4];
    (void) memcpy(&M1SA_Control_OA_DW->Mycontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteStateSpace: '<S2>/Mz controller' */
  {
    real_T xnew[3];
    xnew[0] = (0.18754561954320326)*M1SA_Control_OA_DW->Mzcontroller_DSTATE[0]
      + (-0.063992506646270764)*M1SA_Control_OA_DW->Mzcontroller_DSTATE[1]
      + (-0.12459343930533558)*M1SA_Control_OA_DW->Mzcontroller_DSTATE[2];
    xnew[0] += (-0.0046698885471101962)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[5];
    xnew[1] = (0.66987249869485166)*M1SA_Control_OA_DW->Mzcontroller_DSTATE[0]
      + (0.60163169912030934)*M1SA_Control_OA_DW->Mzcontroller_DSTATE[1]
      + (-0.011330373333918045)*M1SA_Control_OA_DW->Mzcontroller_DSTATE[2];
    xnew[1] += (-0.00066724539247526248)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[5];
    xnew[2] = (1.0)*M1SA_Control_OA_DW->Mzcontroller_DSTATE[2];
    xnew[2] += (0.039999999999999994)*M1SA_Control_OA_U->LC_FxyzMxyz_CG[5];
    (void) memcpy(&M1SA_Control_OA_DW->Mzcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteTransferFcn: '<S1>/OA_SA_dyn' */
  memcpy(&M1SA_Control_OA_DW->OA_SA_dyn_states[0], &OA_SA_dyn_tmp[0], 335U *
         sizeof(real_T));
}

/* Model initialize function */
void M1SA_Control_OA_initialize(RT_MODEL_M1SA_Control_OA_T *const
  M1SA_Control_OA_M)
{
  /* (no initialization code required) */
  UNUSED_PARAMETER(M1SA_Control_OA_M);
}

/* Model terminate function */
void M1SA_Control_OA_terminate(RT_MODEL_M1SA_Control_OA_T *const
  M1SA_Control_OA_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(M1SA_Control_OA_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
