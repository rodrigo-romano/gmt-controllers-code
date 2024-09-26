/*
 * File: Mount_Control.c
 *
 * Code generated for Simulink model 'Mount_Control'.
 *
 * Model version                  : 9.78
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Wed Sep 25 14:20:47 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objective: Execution efficiency
 * Validation result: All passed
 */

#include "Mount_Control.h"
#include "rtwtypes.h"

/* Model step function */
void Mount_Control_step(RT_MODEL_Mount_Control_T *const Mount_Control_M,
  ExtU_Mount_Control_T *Mount_Control_U, ExtY_Mount_Control_T *Mount_Control_Y)
{
  DW_Mount_Control_T *Mount_Control_DW = Mount_Control_M->dwork;

  /* local block i/o variables */
  real_T rtb_Sum1;
  real_T rtb_actuatorcommandbeforestruct;
  real_T rtb_Sum4;
  real_T rtb_AZFFcontroller;
  real_T rtb_ELFFcontroller;
  real_T rtb_GIRFFcontroller;
  real_T rtb_AZFBcontroller;
  real_T rtb_ELFBfilter;
  real_T rtb_GIRFBcontroller;
  real_T rtb_Drv_Pos_avg[3];
  real_T Derivativeterm_tmp;
  real_T I;
  real_T rtb_PIDoutput;
  real_T rtb_Switch;
  real_T rtb_error;
  real_T tmp;
  int32_T i;
  int32_T i_0;

  /* Gain: '<S1>/Drv_Pos_avg' */
  for (i = 0; i < 3; i++) {
    int32_T tmp_0;
    rtb_Drv_Pos_avg[i] = 0.0;
    tmp_0 = 0;
    for (i_0 = 0; i_0 < 14; i_0++) {
      rtb_Drv_Pos_avg[i] += Mount_Control_ConstP.Drv_Pos_avg_Gain[tmp_0 + i] *
        Mount_Control_U->Mount_FB[i_0];
      tmp_0 += 3;
    }
  }

  /* End of Gain: '<S1>/Drv_Pos_avg' */

  /* DiscreteStateSpace: '<S1>/AZ FF controller' */
  {
    rtb_AZFFcontroller = (22443.662121845842)*
      Mount_Control_DW->AZFFcontroller_DSTATE[0]
      + (-3782.4680247469041)*Mount_Control_DW->AZFFcontroller_DSTATE[1];
    rtb_AZFFcontroller += 1.959539391296397E+10*Mount_Control_U->Mount_SP[0];
  }

  /* DiscreteStateSpace: '<S1>/EL FF controller' */
  {
    rtb_ELFFcontroller = (19087.319196075161)*
      Mount_Control_DW->ELFFcontroller_DSTATE[0]
      + (-3216.8179214842985)*Mount_Control_DW->ELFFcontroller_DSTATE[1];
    rtb_ELFFcontroller += 1.4172825067229549E+10*Mount_Control_U->Mount_SP[1];
  }

  /* DiscreteStateSpace: '<S1>/GIR FF controller' */
  {
    rtb_GIRFFcontroller = (2805.9415678923297)*
      Mount_Control_DW->GIRFFcontroller_DSTATE[0]
      + (-472.89003916746015)*Mount_Control_DW->GIRFFcontroller_DSTATE[1];
    rtb_GIRFFcontroller += 3.0628364011891371E+8*Mount_Control_U->Mount_SP[2];
  }

  /* Sum: '<S1>/Sum1' */
  rtb_Sum1 = Mount_Control_U->Mount_SP[0] - rtb_Drv_Pos_avg[0];

  /* DiscreteStateSpace: '<S1>/AZ FB controller' */
  {
    {
      static const int_T colCidxRow0[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pCidx = &colCidxRow0[0];
      const real_T *pC0 = Mount_Control_ConstP.AZFBcontroller_C;
      const real_T *xd = &Mount_Control_DW->AZFBcontroller_DSTATE[0];
      real_T *y0 = &rtb_AZFBcontroller;
      int_T numNonZero = 6;
      *y0 = (*pC0++) * xd[*pCidx++];
      while (numNonZero--) {
        *y0 += (*pC0++) * xd[*pCidx++];
      }
    }

    rtb_AZFBcontroller += 8.60525757895686E+10*rtb_Sum1;
  }

  /* Sum: '<S2>/Sum' */
  rtb_error = Mount_Control_U->Mount_SP[1] - rtb_Drv_Pos_avg[1];

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Constant'
   *  Gain: '<S2>/Ki'
   *  Memory: '<S2>/Memory'
   */
  if (Mount_Control_DW->Memory_PreviousInput) {
    rtb_Switch = 0.0;
  } else {
    rtb_Switch = 3.18087E+10 * rtb_error;
  }

  /* End of Switch: '<S2>/Switch' */

  /* DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  I = 0.0005 * rtb_Switch + Mount_Control_DW->DiscreteTimeIntegrator_DSTATE;

  /* DiscreteTransferFcn: '<S2>/Derivative term' */
  Derivativeterm_tmp = rtb_Drv_Pos_avg[1] - -0.33333333333333331 *
    Mount_Control_DW->Derivativeterm_states;

  /* Sum: '<S2>/Sum3' incorporates:
   *  DiscreteTransferFcn: '<S2>/Derivative term'
   *  Gain: '<S2>/Kp'
   */
  rtb_PIDoutput = (8.588349E+9 * rtb_error + I) - (7.846146E+11 *
    Derivativeterm_tmp + -7.846146E+11 * Mount_Control_DW->Derivativeterm_states);

  /* Saturate: '<S2>/EL_drv_sat model' */
  if (rtb_PIDoutput > 400000.0) {
    /* Saturate: '<S2>/EL_drv_sat model' */
    rtb_actuatorcommandbeforestruct = 400000.0;
  } else if (rtb_PIDoutput < -400000.0) {
    /* Saturate: '<S2>/EL_drv_sat model' */
    rtb_actuatorcommandbeforestruct = -400000.0;
  } else {
    /* Saturate: '<S2>/EL_drv_sat model' */
    rtb_actuatorcommandbeforestruct = rtb_PIDoutput;
  }

  /* End of Saturate: '<S2>/EL_drv_sat model' */

  /* DiscreteStateSpace: '<S2>/EL FB filter' */
  {
    {
      static const int_T colCidxRow0[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pCidx = &colCidxRow0[0];
      const real_T *pC0 = Mount_Control_ConstP.ELFBfilter_C;
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *y0 = &rtb_ELFBfilter;
      int_T numNonZero = 10;
      *y0 = (*pC0++) * xd[*pCidx++];
      while (numNonZero--) {
        *y0 += (*pC0++) * xd[*pCidx++];
      }
    }

    rtb_ELFBfilter += 0.075950262747787892*rtb_actuatorcommandbeforestruct;
  }

  /* Sum: '<S1>/Sum4' */
  rtb_Sum4 = Mount_Control_U->Mount_SP[2] - rtb_Drv_Pos_avg[2];

  /* DiscreteStateSpace: '<S1>/GIR FB controller' */
  {
    {
      static const int_T colCidxRow0[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pCidx = &colCidxRow0[0];
      const real_T *pC0 = Mount_Control_ConstP.GIRFBcontroller_C;
      const real_T *xd = &Mount_Control_DW->GIRFBcontroller_DSTATE[0];
      real_T *y0 = &rtb_GIRFBcontroller;
      int_T numNonZero = 6;
      *y0 = (*pC0++) * xd[*pCidx++];
      while (numNonZero--) {
        *y0 += (*pC0++) * xd[*pCidx++];
      }
    }

    rtb_GIRFBcontroller += 1.523590268296159E+9*rtb_Sum4;
  }

  /* Outport: '<Root>/Mount_cmd' incorporates:
   *  Sum: '<S1>/Sum2'
   */
  Mount_Control_Y->Mount_cmd[0] = rtb_AZFFcontroller + rtb_AZFBcontroller;
  Mount_Control_Y->Mount_cmd[1] = rtb_ELFFcontroller + rtb_ELFBfilter;
  Mount_Control_Y->Mount_cmd[2] = rtb_GIRFFcontroller + rtb_GIRFBcontroller;

  /* Update for DiscreteStateSpace: '<S1>/AZ FF controller' */
  {
    real_T xnew[2];
    xnew[0] = (0.97873694552873847)*Mount_Control_DW->AZFFcontroller_DSTATE[0]
      + (0.00877514768931209)*Mount_Control_DW->AZFFcontroller_DSTATE[1];
    xnew[0] += (-22443.662121845849)*Mount_Control_U->Mount_SP[0];
    xnew[1] = (-0.0087751476893120212)*Mount_Control_DW->AZFFcontroller_DSTATE[0]
      + (0.9962872409073632)*Mount_Control_DW->AZFFcontroller_DSTATE[1];
    xnew[1] += (-3782.4680247469119)*Mount_Control_U->Mount_SP[0];
    (void) memcpy(&Mount_Control_DW->AZFFcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*2);
  }

  /* Update for DiscreteStateSpace: '<S1>/EL FF controller' */
  {
    real_T xnew[2];
    xnew[0] = (0.97873694552873847)*Mount_Control_DW->ELFFcontroller_DSTATE[0]
      + (0.0087751476893117575)*Mount_Control_DW->ELFFcontroller_DSTATE[1];
    xnew[0] += (-19087.319196075154)*Mount_Control_U->Mount_SP[1];
    xnew[1] = (-0.0087751476893119171)*Mount_Control_DW->ELFFcontroller_DSTATE[0]
      + (0.99628724090736254)*Mount_Control_DW->ELFFcontroller_DSTATE[1];
    xnew[1] += (-3216.817921484309)*Mount_Control_U->Mount_SP[1];
    (void) memcpy(&Mount_Control_DW->ELFFcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*2);
  }

  /* Update for DiscreteStateSpace: '<S1>/GIR FF controller' */
  {
    real_T xnew[2];
    xnew[0] = (0.97873694552873836)*Mount_Control_DW->GIRFFcontroller_DSTATE[0]
      + (0.0087751476893118685)*Mount_Control_DW->GIRFFcontroller_DSTATE[1];
    xnew[0] += (-2805.9415678923287)*Mount_Control_U->Mount_SP[2];
    xnew[1] = (-0.0087751476893118546)*Mount_Control_DW->GIRFFcontroller_DSTATE
      [0]
      + (0.99628724090736265)*Mount_Control_DW->GIRFFcontroller_DSTATE[1];
    xnew[1] += (-472.89003916746185)*Mount_Control_U->Mount_SP[2];
    (void) memcpy(&Mount_Control_DW->GIRFFcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*2);
  }

  /* Update for DiscreteStateSpace: '<S1>/AZ FB controller' */
  {
    real_T xnew[7];
    xnew[0] = (0.99999999999999978)*Mount_Control_DW->AZFBcontroller_DSTATE[0];
    xnew[0] += (-9571.8516486174049)*rtb_Sum1;

    {
      static const int_T colAidxRow1[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow1[0];
      const real_T *pA1 = &Mount_Control_ConstP.AZFBcontroller_A[1];
      const real_T *xd = &Mount_Control_DW->AZFBcontroller_DSTATE[0];
      real_T *pxnew1 = &xnew[1];
      int_T numNonZero = 5;
      *pxnew1 = (*pA1++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew1 += (*pA1++) * xd[*pAidx++];
      }
    }

    xnew[1] += (140463.338547439)*rtb_Sum1;

    {
      static const int_T colAidxRow2[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow2[0];
      const real_T *pA7 = &Mount_Control_ConstP.AZFBcontroller_A[7];
      const real_T *xd = &Mount_Control_DW->AZFBcontroller_DSTATE[0];
      real_T *pxnew2 = &xnew[2];
      int_T numNonZero = 5;
      *pxnew2 = (*pA7++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew2 += (*pA7++) * xd[*pAidx++];
      }
    }

    xnew[2] += (255831.97878329802)*rtb_Sum1;

    {
      static const int_T colAidxRow3[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow3[0];
      const real_T *pA13 = &Mount_Control_ConstP.AZFBcontroller_A[13];
      const real_T *xd = &Mount_Control_DW->AZFBcontroller_DSTATE[0];
      real_T *pxnew3 = &xnew[3];
      int_T numNonZero = 5;
      *pxnew3 = (*pA13++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew3 += (*pA13++) * xd[*pAidx++];
      }
    }

    xnew[3] += (-110648.8811233452)*rtb_Sum1;

    {
      static const int_T colAidxRow4[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow4[0];
      const real_T *pA19 = &Mount_Control_ConstP.AZFBcontroller_A[19];
      const real_T *xd = &Mount_Control_DW->AZFBcontroller_DSTATE[0];
      real_T *pxnew4 = &xnew[4];
      int_T numNonZero = 5;
      *pxnew4 = (*pA19++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew4 += (*pA19++) * xd[*pAidx++];
      }
    }

    xnew[4] += (23985.455482685655)*rtb_Sum1;

    {
      static const int_T colAidxRow5[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow5[0];
      const real_T *pA25 = &Mount_Control_ConstP.AZFBcontroller_A[25];
      const real_T *xd = &Mount_Control_DW->AZFBcontroller_DSTATE[0];
      real_T *pxnew5 = &xnew[5];
      int_T numNonZero = 5;
      *pxnew5 = (*pA25++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew5 += (*pA25++) * xd[*pAidx++];
      }
    }

    xnew[5] += (-2383.416200805339)*rtb_Sum1;

    {
      static const int_T colAidxRow6[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow6[0];
      const real_T *pA31 = &Mount_Control_ConstP.AZFBcontroller_A[31];
      const real_T *xd = &Mount_Control_DW->AZFBcontroller_DSTATE[0];
      real_T *pxnew6 = &xnew[6];
      int_T numNonZero = 5;
      *pxnew6 = (*pA31++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew6 += (*pA31++) * xd[*pAidx++];
      }
    }

    xnew[6] += (-19954.601912281483)*rtb_Sum1;
    (void) memcpy(&Mount_Control_DW->AZFBcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*7);
  }

  /* Signum: '<S2>/Sign_v' */
  if (rtb_PIDoutput < 0.0) {
    tmp = -1.0;
  } else {
    tmp = (rtb_PIDoutput > 0.0);
  }

  /* Signum: '<S2>/Sign_e' */
  if (rtb_error < 0.0) {
    rtb_error = -1.0;
  } else {
    rtb_error = (rtb_error > 0.0);
  }

  /* Update for Memory: '<S2>/Memory' incorporates:
   *  Logic: '<S2>/Logical Operator'
   *  RelationalOperator: '<S2>/Is_diff'
   *  RelationalOperator: '<S2>/Is_equal'
   *  Signum: '<S2>/Sign_e'
   *  Signum: '<S2>/Sign_v'
   */
  Mount_Control_DW->Memory_PreviousInput = ((rtb_actuatorcommandbeforestruct !=
    rtb_PIDoutput) && (tmp == rtb_error));

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  Mount_Control_DW->DiscreteTimeIntegrator_DSTATE = 0.0005 * rtb_Switch + I;

  /* Update for DiscreteTransferFcn: '<S2>/Derivative term' */
  Mount_Control_DW->Derivativeterm_states = Derivativeterm_tmp;

  /* Update for DiscreteStateSpace: '<S2>/EL FB filter' */
  {
    real_T xnew[11];

    {
      static const int_T colAidxRow0[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow0[0];
      const real_T *pA0 = Mount_Control_ConstP.ELFBfilter_A;
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *pxnew0 = &xnew[0];
      int_T numNonZero = 10;
      *pxnew0 = (*pA0++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew0 += (*pA0++) * xd[*pAidx++];
      }
    }

    xnew[0] += (-0.14896375042632709)*rtb_actuatorcommandbeforestruct;

    {
      static const int_T colAidxRow1[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow1[0];
      const real_T *pA11 = &Mount_Control_ConstP.ELFBfilter_A[11];
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *pxnew1 = &xnew[1];
      int_T numNonZero = 10;
      *pxnew1 = (*pA11++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew1 += (*pA11++) * xd[*pAidx++];
      }
    }

    xnew[1] += (-0.10394121680109142)*rtb_actuatorcommandbeforestruct;

    {
      static const int_T colAidxRow2[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow2[0];
      const real_T *pA22 = &Mount_Control_ConstP.ELFBfilter_A[22];
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *pxnew2 = &xnew[2];
      int_T numNonZero = 10;
      *pxnew2 = (*pA22++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew2 += (*pA22++) * xd[*pAidx++];
      }
    }

    xnew[2] += (0.24790593684022952)*rtb_actuatorcommandbeforestruct;

    {
      static const int_T colAidxRow3[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow3[0];
      const real_T *pA33 = &Mount_Control_ConstP.ELFBfilter_A[33];
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *pxnew3 = &xnew[3];
      int_T numNonZero = 10;
      *pxnew3 = (*pA33++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew3 += (*pA33++) * xd[*pAidx++];
      }
    }

    xnew[3] += (0.026166332953586387)*rtb_actuatorcommandbeforestruct;

    {
      static const int_T colAidxRow4[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow4[0];
      const real_T *pA44 = &Mount_Control_ConstP.ELFBfilter_A[44];
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *pxnew4 = &xnew[4];
      int_T numNonZero = 10;
      *pxnew4 = (*pA44++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew4 += (*pA44++) * xd[*pAidx++];
      }
    }

    xnew[4] += (0.081130054596925572)*rtb_actuatorcommandbeforestruct;

    {
      static const int_T colAidxRow5[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow5[0];
      const real_T *pA55 = &Mount_Control_ConstP.ELFBfilter_A[55];
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *pxnew5 = &xnew[5];
      int_T numNonZero = 10;
      *pxnew5 = (*pA55++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew5 += (*pA55++) * xd[*pAidx++];
      }
    }

    xnew[5] += (-0.068001253842862944)*rtb_actuatorcommandbeforestruct;

    {
      static const int_T colAidxRow6[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow6[0];
      const real_T *pA66 = &Mount_Control_ConstP.ELFBfilter_A[66];
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *pxnew6 = &xnew[6];
      int_T numNonZero = 10;
      *pxnew6 = (*pA66++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew6 += (*pA66++) * xd[*pAidx++];
      }
    }

    xnew[6] += (0.0095387129807723414)*rtb_actuatorcommandbeforestruct;

    {
      static const int_T colAidxRow7[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow7[0];
      const real_T *pA77 = &Mount_Control_ConstP.ELFBfilter_A[77];
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *pxnew7 = &xnew[7];
      int_T numNonZero = 10;
      *pxnew7 = (*pA77++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew7 += (*pA77++) * xd[*pAidx++];
      }
    }

    xnew[7] += (-0.002448883383641486)*rtb_actuatorcommandbeforestruct;

    {
      static const int_T colAidxRow8[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow8[0];
      const real_T *pA88 = &Mount_Control_ConstP.ELFBfilter_A[88];
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *pxnew8 = &xnew[8];
      int_T numNonZero = 10;
      *pxnew8 = (*pA88++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew8 += (*pA88++) * xd[*pAidx++];
      }
    }

    xnew[8] += (-0.015911125659322019)*rtb_actuatorcommandbeforestruct;

    {
      static const int_T colAidxRow9[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow9[0];
      const real_T *pA99 = &Mount_Control_ConstP.ELFBfilter_A[99];
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *pxnew9 = &xnew[9];
      int_T numNonZero = 10;
      *pxnew9 = (*pA99++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew9 += (*pA99++) * xd[*pAidx++];
      }
    }

    xnew[9] += (-0.014749498257852576)*rtb_actuatorcommandbeforestruct;

    {
      static const int_T colAidxRow10[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow10[0];
      const real_T *pA110 = &Mount_Control_ConstP.ELFBfilter_A[110];
      const real_T *xd = &Mount_Control_DW->ELFBfilter_DSTATE[0];
      real_T *pxnew10 = &xnew[10];
      int_T numNonZero = 10;
      *pxnew10 = (*pA110++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew10 += (*pA110++) * xd[*pAidx++];
      }
    }

    xnew[10] += (0.0008355747920475937)*rtb_actuatorcommandbeforestruct;
    (void) memcpy(&Mount_Control_DW->ELFBfilter_DSTATE[0], xnew,
                  sizeof(real_T)*11);
  }

  /* Update for DiscreteStateSpace: '<S1>/GIR FB controller' */
  {
    real_T xnew[7];
    xnew[0] = (1.0)*Mount_Control_DW->GIRFBcontroller_DSTATE[0];
    xnew[0] += (-1189.4121570919501)*rtb_Sum4;

    {
      static const int_T colAidxRow1[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow1[0];
      const real_T *pA1 = &Mount_Control_ConstP.GIRFBcontroller_A[1];
      const real_T *xd = &Mount_Control_DW->GIRFBcontroller_DSTATE[0];
      real_T *pxnew1 = &xnew[1];
      int_T numNonZero = 5;
      *pxnew1 = (*pA1++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew1 += (*pA1++) * xd[*pAidx++];
      }
    }

    xnew[1] += (-17028.864555104064)*rtb_Sum4;

    {
      static const int_T colAidxRow2[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow2[0];
      const real_T *pA7 = &Mount_Control_ConstP.GIRFBcontroller_A[7];
      const real_T *xd = &Mount_Control_DW->GIRFBcontroller_DSTATE[0];
      real_T *pxnew2 = &xnew[2];
      int_T numNonZero = 5;
      *pxnew2 = (*pA7++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew2 += (*pA7++) * xd[*pAidx++];
      }
    }

    xnew[2] += (-31350.698316730148)*rtb_Sum4;

    {
      static const int_T colAidxRow3[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow3[0];
      const real_T *pA13 = &Mount_Control_ConstP.GIRFBcontroller_A[13];
      const real_T *xd = &Mount_Control_DW->GIRFBcontroller_DSTATE[0];
      real_T *pxnew3 = &xnew[3];
      int_T numNonZero = 5;
      *pxnew3 = (*pA13++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew3 += (*pA13++) * xd[*pAidx++];
      }
    }

    xnew[3] += (22397.605203121362)*rtb_Sum4;

    {
      static const int_T colAidxRow4[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow4[0];
      const real_T *pA19 = &Mount_Control_ConstP.GIRFBcontroller_A[19];
      const real_T *xd = &Mount_Control_DW->GIRFBcontroller_DSTATE[0];
      real_T *pxnew4 = &xnew[4];
      int_T numNonZero = 5;
      *pxnew4 = (*pA19++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew4 += (*pA19++) * xd[*pAidx++];
      }
    }

    xnew[4] += (4262.3175327026147)*rtb_Sum4;

    {
      static const int_T colAidxRow5[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow5[0];
      const real_T *pA25 = &Mount_Control_ConstP.GIRFBcontroller_A[25];
      const real_T *xd = &Mount_Control_DW->GIRFBcontroller_DSTATE[0];
      real_T *pxnew5 = &xnew[5];
      int_T numNonZero = 5;
      *pxnew5 = (*pA25++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew5 += (*pA25++) * xd[*pAidx++];
      }
    }

    xnew[5] += (-3887.2197360677828)*rtb_Sum4;

    {
      static const int_T colAidxRow6[6] = { 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow6[0];
      const real_T *pA31 = &Mount_Control_ConstP.GIRFBcontroller_A[31];
      const real_T *xd = &Mount_Control_DW->GIRFBcontroller_DSTATE[0];
      real_T *pxnew6 = &xnew[6];
      int_T numNonZero = 5;
      *pxnew6 = (*pA31++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew6 += (*pA31++) * xd[*pAidx++];
      }
    }

    xnew[6] += (-1086.8945536880574)*rtb_Sum4;
    (void) memcpy(&Mount_Control_DW->GIRFBcontroller_DSTATE[0], xnew,
                  sizeof(real_T)*7);
  }
}

/* Model initialize function */
void Mount_Control_initialize(RT_MODEL_Mount_Control_T *const Mount_Control_M)
{
  /* (no initialization code required) */
  UNUSED_PARAMETER(Mount_Control_M);
}

/* Model terminate function */
void Mount_Control_terminate(RT_MODEL_Mount_Control_T *const Mount_Control_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(Mount_Control_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
