/*****************************************************************************
 *
 * \file
 *
 * \brief 16-bit and 32-bit hamming windowing functions for the AVR32 UC3
 *
 * Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 ******************************************************************************/


#include "dsp.h"

#define WIN_HAMM_A0  0.53836
#define WIN_HAMM_A1  0.46164

#if defined(FORCE_ALL_GENERICS) || \
    defined(FORCE_GENERIC_WIN16_HAMM) || \
    !defined(TARGET_SPECIFIC_WIN16_HAMM)

// Hamming
// w(n) = 0.53836 - 0.46164*cos(2*PI*n/(N-1))
// avec
// N = signal width
// Constraints: size > 1
void dsp16_win_hamm(dsp16_t *vect1, dsp16_t *vect2, int size)
{
  dsp16_t s, t, w;
  int i;

  // Initialization
  t = DSP16_Q(0.);
  // Calculation of 2/(N-1) <- because a cos is in the range [-1; 1],
  // therefore -1 equals -PI and 1, PI.
  s = (DSP16_Q(1.)/(size - 1)) << 1;

  // Compute the window
  for(i=0; i<(size >> 1); i++)
  {
    w = DSP16_Q(WIN_HAMM_A0);
    w -= (((S32) DSP16_Q(WIN_HAMM_A1))*((S32) dsp16_op_cos(t))) >> DSP16_QB;
    vect1[i] = dsp16_op_mul(w, vect2[i]);
    vect1[size-i-1] = dsp16_op_mul(w, vect2[size-i-1]);
    t += s;
  }

  // If the size is odd
  if (size & 1)
    vect1[size >> 1] = vect2[size >> 1];
}

#endif

#if defined(FORCE_ALL_GENERICS) || \
    defined(FORCE_GENERIC_WIN32_HAMM) || \
    !defined(TARGET_SPECIFIC_WIN32_HAMM)

void dsp32_win_hamm(dsp32_t *vect1, dsp32_t *vect2, int size)
{
  dsp32_t s, t, w;
  int i;

  // Initialization
  t = DSP32_Q(0.);
  // Calculation of 2/(N-1) <- because a cos is in the range [-1; 1],
  // therefore -1 equals -PI and 1, PI.
  s = (DSP32_Q(1.)/(size - 1)) << 1;

  // Compute the window
  for(i=0; i<(size >> 1); i++)
  {
    w = DSP32_Q(WIN_HAMM_A0);
    w -= (((S64) DSP32_Q(WIN_HAMM_A1))*((S64) dsp32_op_cos(t))) >> DSP32_QB;
    vect1[i] = dsp32_op_mul(w, vect2[i]);
    vect1[size-i-1] = dsp32_op_mul(w, vect2[size-i-1]);
    t += s;
  }

  // If the size is odd
  if (size & 1)
    vect1[size >> 1] = vect2[size >> 1];
}

#endif
