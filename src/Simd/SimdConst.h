/*
* Simd Library.
*
* Copyright (c) 2011-2013 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy 
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
* copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#ifndef __SimdConst_h__
#define __SimdConst_h__

#include "Simd/SimdInit.h"

namespace Simd
{
    namespace Base
    {
    }

#ifdef SIMD_SSE2_ENABLE    
    namespace Sse2
    {
        const size_t A = sizeof(__m128i);
        const size_t DA = 2*A;
        const size_t QA = 4*A;
		const size_t OA = 8*A;
        const size_t HA = A/2;

        const __m128i K_ZERO = SIMD_MM_SET1_EPI8(0);
		const __m128i K_INV_ZERO = SIMD_MM_SET1_EPI8(0xFF);

		const __m128i K16_0001 = SIMD_MM_SET1_EPI16(0x0001);
		const __m128i K16_0002 = SIMD_MM_SET1_EPI16(0x0002);
		const __m128i K16_0003 = SIMD_MM_SET1_EPI16(0x0003);
		const __m128i K16_0004 = SIMD_MM_SET1_EPI16(0x0004);
		const __m128i K16_0005 = SIMD_MM_SET1_EPI16(0x0005);
        const __m128i K16_0006 = SIMD_MM_SET1_EPI16(0x0006);
		const __m128i K16_0008 = SIMD_MM_SET1_EPI16(0x0008);
		const __m128i K16_0020 = SIMD_MM_SET1_EPI16(0x0020);
		const __m128i K16_0080 = SIMD_MM_SET1_EPI16(0x0080);
        const __m128i K16_00FF = SIMD_MM_SET1_EPI16(0x00FF);
        
		const __m128i K32_000000FF = SIMD_MM_SET1_EPI32(0x000000FF);
    }
#endif// SIMD_SSE2_ENABLE

#ifdef SIMD_SSE42_ENABLE    
    namespace Sse42
    {
        using namespace Sse2;
    }
#endif// SIMD_SSE42_ENABLE
}
#endif//__SimdConst_h__