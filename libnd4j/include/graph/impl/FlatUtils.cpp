//
// Created by raver119 on 22.11.2017.
//

#include <stdexcept>
#include <memory/Workspace.h>
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
            auto rank = static_cast<int>(flatArray->shape()->Get(0));

            // we need to make sure flat
            if (flatArray->shape()->size() != shape::shapeInfoLength(rank))
                throw std::runtime_error("FlatArray shape length doesn't matches its own rank. Shape array is malformed.");

            // TODO: we might want to allow real workspace here?
            nd4j::memory::Workspace *ws = nullptr;

            auto length = shape::shapeInfoByteLength(rank);
            Nd4jLong *newShape = nullptr;
            ALLOCATE(newShape, ws, shape::shapeInfoLength(rank), Nd4jLong);

            memcpy(newShape, flatArray->shape()->data(), length);

            auto bLength = shape::length(newShape);
            T *newBuffer = nullptr;

            ALLOCATE(newBuffer, ws, bLength, T);

            DataTypeConversions<T>::convertType(newBuffer, (void *) flatArray->buffer()->data(), DataTypeUtils::fromFlatDataType(flatArray->dtype()), ByteOrderUtils::fromFlatByteOrder(flatArray->byteOrder()),  bLength);

            auto array = new NDArray<T>(newBuffer, newShape);
            array->triggerAllocationFlag(true, true);

            return array;
        }


        template NDArray<float> *FlatUtils::fromFlatArray<float>(const nd4j::graph::FlatArray *flatArray);
        template NDArray<float16> *FlatUtils::fromFlatArray<float16>(const nd4j::graph::FlatArray *flatArray);
        template NDArray<double> *FlatUtils::fromFlatArray<double>(const nd4j::graph::FlatArray *flatArray);
    }
}