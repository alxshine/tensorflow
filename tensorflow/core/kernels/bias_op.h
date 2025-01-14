/* Copyright 2015 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_CORE_KERNELS_BIAS_OP_H_
#define TENSORFLOW_CORE_KERNELS_BIAS_OP_H_
// Functor definition for BiasOp, must be compilable by nvcc.

#include "third_party/eigen3/unsupported/Eigen/CXX11/Tensor"
#include "tensorflow/core/framework/tensor_types.h"

namespace tensorflow {
namespace functor {

// Functor used by BiasOp to do the computations.
template <typename Device, typename T, int Dims>
struct Bias {
  // Add "bias" to "input", broadcasting it on all dimensions but the last one.
  void operator()(const Device& d, typename TTypes<T, Dims>::ConstTensor input,
                  typename TTypes<T>::ConstVec bias,
                  typename TTypes<T, Dims>::Tensor output) {
    const Eigen::Index bias_size = bias.dimension(0);
    const Eigen::Index rest_size = input.size() / bias_size;
    Eigen::DSizes<Eigen::Index, 1> one_d(input.size());
    Eigen::DSizes<Eigen::Index, 1> bcast(rest_size);
    MaybeWith32BitIndexing<Device>(
        [&](auto input32, auto bias32, auto output32, const auto& one_d32,
            const auto& bcast32) {
          output32.reshape(one_d32).device(d) =
              input32.reshape(one_d32) + bias32.broadcast(bcast32);
        },
        input, bias, output, one_d, bcast);
  }
};

}  // namespace functor
}  // namespace tensorflow

#endif  // TENSORFLOW_CORE_KERNELS_BIAS_OP_H_
