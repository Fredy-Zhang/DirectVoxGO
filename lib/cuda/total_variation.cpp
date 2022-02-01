#include <torch/extension.h>

#include <vector>

// CUDA forward declarations

void total_variation_add_grad_cuda(torch::Tensor param, torch::Tensor grad, float weight);


// C++ interface

#define CHECK_CUDA(x) TORCH_CHECK(x.type().is_cuda(), #x " must be a CUDA tensor")
#define CHECK_CONTIGUOUS(x) TORCH_CHECK(x.is_contiguous(), #x " must be contiguous")
#define CHECK_INPUT(x) CHECK_CUDA(x); CHECK_CONTIGUOUS(x)

void total_variation_add_grad(torch::Tensor param, torch::Tensor grad, float weight) {
  CHECK_INPUT(param);
  CHECK_INPUT(grad);
  total_variation_add_grad_cuda(param, grad, weight);
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  m.def("total_variation_add_grad", &total_variation_add_grad, "Add total variation grad");
}

