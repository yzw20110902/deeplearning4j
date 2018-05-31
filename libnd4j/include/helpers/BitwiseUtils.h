//
// Created by raver119 on 10.11.2017.
//

#ifndef LIBND4J_BITWISEUTILS_H
#define LIBND4J_BITWISEUTILS_H

#include <vector>
#include <array/ByteOrder.h>
#include <op_boilerplate.h>
#include <pointercast.h>
#include <climits>

namespace nd4j {
    class BitwiseUtils {
    public:


        /**
         * This method returns first non-zero bit index
         * @param holder
         * @return
         */
        static int valueBit(int holder);

        /**
         *  This method returns vector representation of bits.
         * 
         *  PLEASE NOTE: Result is ALWAYS left-to-right 
         */
        static std::vector<int> valueBits(int holder);

        /**
         *  This method returns TRUE if it's called on Big-Endian system, and false otherwise
         */
        static bool isBE();

        /**
         * This method returns enum
         * @return
         */
        static nd4j::ByteOrder asByteOrder();

        /**
         * This method swaps bytes: LE vs BE
         * @tparam T
         * @param v
         * @return
         */
        template <typename T>
        static T swap_bytes(T v);

        /**
         * This method flips bits in given value
         *
         * @tparam T
         * @param v
         * @return
         */
        static int FORCEINLINE flip_bits(int v) {
            return ~v;
        }

        static Nd4jLong FORCEINLINE flip_bits(Nd4jLong v) {
            return ~v;
        }
    };
}


#endif //LIBND4J_BITWISEUTILS_H
