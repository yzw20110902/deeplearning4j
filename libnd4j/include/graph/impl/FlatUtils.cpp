//
// Created by raver119 on 22.11.2017.
//

#include <graph/FlatUtils.h>
#include <array/DataTypeConversions.h>
#include <array/DataTypeUtils.h>
#include <array/ByteOrderUtils.h>


namespace nd4j {
    namespace graph {
        std::pair<int, int> FlatUtils::fromIntPair(IntPair *pair) {
            return std::pair<int, int>(pair->first(), pair->second());
        }

        std::pair<Nd4jLong, Nd4jLong> FlatUtils::fromLongPair(LongPair *pair) {
            return std::pair<Nd4jLong, Nd4jLong>(pair->first(), pair->second());
        }

        template<typename T>
        NDArray<T> *FlatUtils::fromFlatArray(const nd4j::graph::FlatArray *flatArray) {
            nd4j_printf("      Copy step: %i\n", 0);
            auto rank = static_cast<int>(flatArray->shape()->Get(0));

            nd4j_printf("      Copy step: %i; rank: %i\n", 1, rank);

            auto length = shape::shapeInfoByteLength(rank);

            nd4j_printf("      Copy step: %i; length: %i\n", 2, static_cast<int>(length));

            auto newShape = new Nd4jLong[shape::shapeInfoLength(rank)];

            nd4j_printf("      Copy step: %i\n", 3);


            memcpy(newShape, flatArray->shape()->data(), length);

            nd4j_printf("      Copy step: %i\n", 4);

            auto newBuffer = new T[shape::length(newShape)];

            nd4j_printf("      Copy step: %i\n", 5);

            DataTypeConversions<T>::convertType(newBuffer, (void *) flatArray->buffer()->data(), DataTypeUtils::fromFlatDataType(flatArray->dtype()), ByteOrderUtils::fromFlatByteOrder(flatArray->byteOrder()),  shape::length(newShape));

            nd4j_printf("      Copy step: %i\n", 6);

            auto array = new NDArray<T>(newBuffer, newShape);

            nd4j_printf("      Copy step: %i\n", 7);

            array->triggerAllocationFlag(true, true);

            return array;
        }


        template NDArray<float> *FlatUtils::fromFlatArray<float>(const nd4j::graph::FlatArray *flatArray);
        template NDArray<float16> *FlatUtils::fromFlatArray<float16>(const nd4j::graph::FlatArray *flatArray);
        template NDArray<double> *FlatUtils::fromFlatArray<double>(const nd4j::graph::FlatArray *flatArray);
    }
}