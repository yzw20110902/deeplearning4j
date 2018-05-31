//
// Created by raver119 on 21.11.17.
//

#ifndef LIBND4J_DATATYPECONVERSIONS_H
#define LIBND4J_DATATYPECONVERSIONS_H

#include <pointercast.h>
#include <helpers/logger.h>
#include <op_boilerplate.h>
#include <array/DataType.h>
#include <types/float16.h>
#include <helpers/BitwiseUtils.h>

namespace nd4j {
    template <typename T>
    class DataTypeConversions {
    public:
        static FORCEINLINE void convertType(T* buffer, void* src, DataType dataType, ByteOrder order, Nd4jLong length) {
            bool isBe = BitwiseUtils::isBE();
            bool canKeep = (isBe && order == ByteOrder::BE) || (!isBe && order == ByteOrder::LE);

            nd4j_printf("BE: %i; canKeep: %i;\n", (int) isBe, (int) canKeep);

            switch (dataType) {
                case DataType_FLOAT: {
                        auto tmp = reinterpret_cast<float *>(src);

                        //#pragma omp parallel for simd schedule(guided)
                        for (Nd4jLong e = 0; e < length; e++) {
                            buffer[e] = canKeep ? static_cast<T>(tmp[e]) : BitwiseUtils::swap_bytes<T>(static_cast<T>(tmp[e]));
                        }
                    }
                    break;
                case DataType_DOUBLE: {
                        nd4j_printf("Going double way: %lld\n", length)
                        auto tmp = reinterpret_cast<double *>(src);

                        //#pragma omp parallel for simd schedule(guided)
                        for (Nd4jLong e = 0; e < length; e++) {
                            if (canKeep)
                                buffer[e] = static_cast<T>(tmp[e]);
                            else
                                buffer[e] = BitwiseUtils::swap_bytes<T>(static_cast<T>(tmp[e]));
                        }
                    }
                    break;
                case DataType_HALF: {
                        auto tmp = reinterpret_cast<float16 *>(src);

                        //#pragma omp parallel for simd schedule(guided)
                        for (Nd4jLong e = 0; e < length; e++)
                            buffer[e] = canKeep ? static_cast<T>(tmp[e]) : BitwiseUtils::swap_bytes<T>(static_cast<T>(tmp[e]));
                    }
                    break;
                default: {
                    nd4j_printf("Unsupported DataType requested: [%i]\n", (int) dataType);
                    throw "Unsupported DataType";
                }
            }
        }
    };
}



#endif //LIBND4J_DATATYPECONVERSIONS_H
