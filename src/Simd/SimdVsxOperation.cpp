/*
* Simd Library.
*
* Copyright (c) 2011-2014 Yermalayeu Ihar.
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
#include "Simd/SimdVsx.h"
#include "Simd/SimdMemory.h"
#include "Simd/SimdConst.h"
#include "Simd/SimdLoad.h"
#include "Simd/SimdStore.h"
#include "Simd/SimdMath.h"
#include "Simd/SimdLog.h"

namespace Simd
{
#ifdef SIMD_VSX_ENABLE  
    namespace Vsx
    {
        template <SimdOperationBinary8uType type> SIMD_INLINE v128_u8 OperationBinary8u(const v128_u8 & a, const v128_u8 & b);

        template <> SIMD_INLINE v128_u8 OperationBinary8u<SimdOperationBinary8uAverage>(const v128_u8 & a, const v128_u8 & b)
        {
            return vec_avg(a, b);
        }

        template <> SIMD_INLINE v128_u8 OperationBinary8u<SimdOperationBinary8uAnd>(const v128_u8 & a, const v128_u8 & b)
        {
            return vec_and(a, b);
        }

        template <> SIMD_INLINE v128_u8 OperationBinary8u<SimdOperationBinary8uMaximum>(const v128_u8 & a, const v128_u8 & b)
        {
            return vec_max(a, b);
        }

        template <> SIMD_INLINE v128_u8 OperationBinary8u<SimdOperationBinary8uSaturatedSubtraction>(const v128_u8 & a, const v128_u8 & b)
        {
            return vec_subs(a, b);
        }

        template <bool align, SimdOperationBinary8uType type> void OperationBinary8u(const uint8_t * a, size_t aStride, const uint8_t * b, size_t bStride, 
            size_t width, size_t height, size_t channelCount, uint8_t * dst, size_t dstStride)
        {
            assert(width*channelCount >= A);
            if(align)
                assert(Aligned(a) && Aligned(aStride) && Aligned(b) && Aligned(bStride) && Aligned(dst) && Aligned(dstStride));

            size_t size = channelCount*width;
            size_t alignedSize = Simd::AlignLo(size, A);
            for(size_t row = 0; row < height; ++row)
            {
                for(size_t offset = 0; offset < alignedSize; offset += A)
                {
                    const v128_u8 _a = Load<align>(a + offset);
                    const v128_u8 _b = Load<align>(b + offset);
                    Store<align>(dst + offset, OperationBinary8u<type>(_a, _b));
                }
                if(alignedSize != size)
                {
                    const v128_u8 _a = Load<false>(a + size - A);
                    const v128_u8 _b = Load<false>(b + size - A);
                    Store<false>(dst + size - A, OperationBinary8u<type>(_a, _b));
                }
                a += aStride;
                b += bStride;
                dst += dstStride;
            }
        }

        template <bool align> void OperationBinary8u(const uint8_t * a, size_t aStride, const uint8_t * b, size_t bStride, 
            size_t width, size_t height, size_t channelCount, uint8_t * dst, size_t dstStride, SimdOperationBinary8uType type)
        {
            switch(type)
            {
            case SimdOperationBinary8uAverage:
                return OperationBinary8u<align, SimdOperationBinary8uAverage>(a, aStride, b, bStride, width, height, channelCount, dst, dstStride);
            case SimdOperationBinary8uAnd:
                return OperationBinary8u<align, SimdOperationBinary8uAnd>(a, aStride, b, bStride, width, height, channelCount, dst, dstStride);
            case SimdOperationBinary8uMaximum:
                return OperationBinary8u<align, SimdOperationBinary8uMaximum>(a, aStride, b, bStride, width, height, channelCount, dst, dstStride);
            case SimdOperationBinary8uSaturatedSubtraction:
                return OperationBinary8u<align, SimdOperationBinary8uSaturatedSubtraction>(a, aStride, b, bStride, width, height, channelCount, dst, dstStride);
            default:
                assert(0);
            }
        }

        void OperationBinary8u(const uint8_t * a, size_t aStride, const uint8_t * b, size_t bStride, 
            size_t width, size_t height, size_t channelCount, uint8_t * dst, size_t dstStride, SimdOperationBinary8uType type)
        {
            if(Aligned(a) && Aligned(aStride) && Aligned(b) && Aligned(bStride) && Aligned(dst) && Aligned(dstStride))
                OperationBinary8u<true>(a, aStride, b, bStride, width, height, channelCount, dst, dstStride, type);
            else
                OperationBinary8u<false>(a, aStride, b, bStride, width, height, channelCount, dst, dstStride, type);
        }
    }
#endif// SIMD_VSX_ENABLE
}