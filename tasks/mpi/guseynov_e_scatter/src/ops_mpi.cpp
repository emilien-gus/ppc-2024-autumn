#include "mpi/guseynov_e_scatter/include/ops_mpi.hpp"

#include <algorithm>
#include <random>
#include <vector>

std::vector<int> guseynov_e_scatter_mpi::getRandomVector(int sz) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<int> vec(sz);
  for (int i = 0; i < sz; i++) {
    vec[i] = gen() % 100;
  }
  return vec;
}

bool guseynov_e_scatter_mpi::TestMPITaskSequential::pre_processing() {
  internal_order_test();
  // Init Vectors
  input_ = std::vector<int>(taskData->inputs_count[0]);
  auto* tmp_ptr = reinterpret_cast<int*>(taskData->inputs[0]);
  for (unsigned i = 0; i < taskData->inputs_count[0]; i++) {
    input_[i] = tmp_ptr[i];
  }
  // Init value for output
  res_ = 0;
  return true;
}

bool guseynov_e_scatter_mpi::TestMPITaskSequential::validation() {
  internal_order_test();
  return taskData->outputs_count[0] == 1;
}

bool guseynov_e_scatter_mpi::TestMPITaskSequential::run() {
  internal_order_test();
  res_ = std::accumulate(input_.begin(), input_.end(), 0);
  return true;
}

bool guseynov_e_scatter_mpi::TestMPITaskSequential::post_processing() {
  internal_order_test();
  reinterpret_cast<int*>(taskData->outputs[0])[0] = res_;
  return true;
}

bool guseynov_e_scatter_mpi::TestMPITaskParallel::pre_processing() {
  internal_order_test();
  res_ = 0;
  return true;
}

bool guseynov_e_scatter_mpi::TestMPITaskParallel::validation() {
  internal_order_test();
  if (world.rank() == 0) {
    return taskData->outputs_count[0] == 1;
  }
  return true;
}

bool guseynov_e_scatter_mpi::TestMPITaskParallel::run() {
  internal_order_test();
  unsigned int delta = 0;
  if (world.rank() == 0) {
    input_ = std::vector<int>(taskData->inputs_count[0]);
    auto* tmp_ptr = reinterpret_cast<int*>(taskData->inputs[0]);
    std::copy(tmp_ptr, tmp_ptr + taskData->inputs_count[0], input_.begin());
    delta = input_.size() / world.size();
    local_input_ = std::vector<int>(delta + input_.size() % world.size());
  }
  broadcast(world, delta, 0);

  if (world.rank() != 0) {
    local_input_ = std::vector<int>(delta);
  }

  boost::mpi::scatter(world, input_, local_input_.data(), delta, 0);
  if (world.rank() == 0) {
    std::copy(input_.begin() + delta * world.size(), input_.end(), local_input_.begin() + delta);
  }

  int local_res = std::accumulate(local_input_.begin(), local_input_.end(), 0);
  reduce(world, local_res, res_, std::plus(), 0);

  return true;
}

bool guseynov_e_scatter_mpi::TestMPITaskParallel::post_processing() {
  internal_order_test();
  if (world.rank() == 0) {
    reinterpret_cast<int*>(taskData->outputs[0])[0] = res_;
  }
  return true;
}

bool guseynov_e_scatter_mpi::MyScatterTestMPITaskParallel::pre_processing() {
  internal_order_test();
  res_ = 0;
  return true;
}

bool guseynov_e_scatter_mpi::MyScatterTestMPITaskParallel::validation() {
  internal_order_test();
  if (world.rank() == 0) {
    return taskData->outputs_count[0] == 1;
  }
  return true;
}

bool guseynov_e_scatter_mpi::MyScatterTestMPITaskParallel::run() {
  internal_order_test();
  unsigned int delta = 0;
  if (world.rank() == 0) {
    input_ = std::vector<int>(taskData->inputs_count[0]);
    auto* tmp_ptr = reinterpret_cast<int*>(taskData->inputs[0]);
    std::copy(tmp_ptr, tmp_ptr + taskData->inputs_count[0], input_.begin());
    delta = input_.size() / world.size();
    local_input_ = std::vector<int>(delta + input_.size() % world.size());
  }
  broadcast(world, delta, 0);

  if (world.rank() != 0) {
    local_input_ = std::vector<int>(delta);
  }

  my_scatter(world, input_, local_input_.data(), delta, 0);
  if (world.rank() == 0) {
    std::copy(input_.begin() + delta * world.size(), input_.end(), local_input_.begin() + delta);
  }

  int local_res = std::accumulate(local_input_.begin(), local_input_.end(), 0);
  reduce(world, local_res, res_, std::plus(), 0);

  return true;
}

bool guseynov_e_scatter_mpi::MyScatterTestMPITaskParallel::post_processing() {
  internal_order_test();
  if (world.rank() == 0) {
    reinterpret_cast<int*>(taskData->outputs[0])[0] = res_;
  }
  return true;
}