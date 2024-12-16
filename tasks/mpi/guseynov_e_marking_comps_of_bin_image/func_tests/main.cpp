#include <gtest/gtest.h>

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <vector>

#include "mpi/guseynov_e_marking_comps_of_bin_image/include/ops_mpi.hpp"

TEST(guseynov_e_marking_comps_of_bin_image_mpi, fixed_test_1) {
  boost::mpi::communicator world;
  const int rows = 3;
  const int cols = 3;
  std::vector<int> image = {1, 0, 1, 0, 1, 0, 1, 0, 1};
  std::vector<int> global_labeled_image(rows * cols);
  std::vector<int> expected_label = {1, 2, 1, 2, 1, 3, 1, 3, 1};
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataPar->inputs_count.emplace_back(rows);
    taskDataPar->inputs_count.emplace_back(cols);
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_labeled_image.data()));
    taskDataPar->outputs_count.emplace_back(rows);
    taskDataPar->outputs_count.emplace_back(cols);
  }

  guseynov_e_marking_comps_of_bin_image_mpi::TestMPITaskParallel testMpiTaskParallel(taskDataPar);
  ASSERT_TRUE(testMpiTaskParallel.validation());
  testMpiTaskParallel.pre_processing();
  testMpiTaskParallel.run();
  testMpiTaskParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int> reference_labeled_image(rows * cols);

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataSeq->inputs_count.emplace_back(rows);
    taskDataSeq->inputs_count.emplace_back(cols);
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_labeled_image.data()));
    taskDataSeq->outputs_count.emplace_back(rows);
    taskDataSeq->outputs_count.emplace_back(cols);

    // Create Task
    guseynov_e_marking_comps_of_bin_image_mpi::TestMPITaskSequential testMpiTaskSequential(taskDataSeq);
    ASSERT_TRUE(testMpiTaskSequential.validation());
    testMpiTaskSequential.pre_processing();
    testMpiTaskSequential.run();
    testMpiTaskSequential.post_processing();

    ASSERT_EQ(reference_labeled_image, expected_label);
    ASSERT_EQ(reference_labeled_image, global_labeled_image);
  }
}

TEST(guseynov_e_marking_comps_of_bin_image_mpi, fixed_test_2) {
  boost::mpi::communicator world;
  const int rows = 3;
  const int cols = 3;
  std::vector<int> image = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<int> global_labeled_image(rows * cols);
  std::vector<int> expected_label = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataPar->inputs_count.emplace_back(rows);
    taskDataPar->inputs_count.emplace_back(cols);
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_labeled_image.data()));
    taskDataPar->outputs_count.emplace_back(rows);
    taskDataPar->outputs_count.emplace_back(cols);
  }

  guseynov_e_marking_comps_of_bin_image_mpi::TestMPITaskParallel testMpiTaskParallel(taskDataPar);
  ASSERT_TRUE(testMpiTaskParallel.validation());
  testMpiTaskParallel.pre_processing();
  testMpiTaskParallel.run();
  testMpiTaskParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int> reference_labeled_image(rows * cols);

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataSeq->inputs_count.emplace_back(rows);
    taskDataSeq->inputs_count.emplace_back(cols);
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_labeled_image.data()));
    taskDataSeq->outputs_count.emplace_back(rows);
    taskDataSeq->outputs_count.emplace_back(cols);

    // Create Task
    guseynov_e_marking_comps_of_bin_image_mpi::TestMPITaskSequential testMpiTaskSequential(taskDataSeq);
    ASSERT_TRUE(testMpiTaskSequential.validation());
    testMpiTaskSequential.pre_processing();
    testMpiTaskSequential.run();
    testMpiTaskSequential.post_processing();

    ASSERT_EQ(reference_labeled_image, expected_label);
    ASSERT_EQ(reference_labeled_image, global_labeled_image);
  }
}

TEST(guseynov_e_marking_comps_of_bin_image_mpi, fixed_test_3) {
  boost::mpi::communicator world;
  const int rows = 3;
  const int cols = 3;
  std::vector<int> image = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<int> global_labeled_image(rows * cols);
  std::vector<int> expected_label = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataPar->inputs_count.emplace_back(rows);
    taskDataPar->inputs_count.emplace_back(cols);
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_labeled_image.data()));
    taskDataPar->outputs_count.emplace_back(rows);
    taskDataPar->outputs_count.emplace_back(cols);
  }

  guseynov_e_marking_comps_of_bin_image_mpi::TestMPITaskParallel testMpiTaskParallel(taskDataPar);
  ASSERT_TRUE(testMpiTaskParallel.validation());
  testMpiTaskParallel.pre_processing();
  testMpiTaskParallel.run();
  testMpiTaskParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int> reference_labeled_image(rows * cols);

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataSeq->inputs_count.emplace_back(rows);
    taskDataSeq->inputs_count.emplace_back(cols);
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_labeled_image.data()));
    taskDataSeq->outputs_count.emplace_back(rows);
    taskDataSeq->outputs_count.emplace_back(cols);

    // Create Task
    guseynov_e_marking_comps_of_bin_image_mpi::TestMPITaskSequential testMpiTaskSequential(taskDataSeq);
    ASSERT_TRUE(testMpiTaskSequential.validation());
    testMpiTaskSequential.pre_processing();
    testMpiTaskSequential.run();
    testMpiTaskSequential.post_processing();

    ASSERT_EQ(reference_labeled_image, expected_label);
    ASSERT_EQ(reference_labeled_image, global_labeled_image);
  }
}

TEST(guseynov_e_marking_comps_of_bin_image_mpi, fixed_test_4) {
  boost::mpi::communicator world;
  const int rows = 3;
  const int cols = 3;
  std::vector<int> image = {0, 1, 1, 1, 1, 0, 0, 1, 1};
  std::vector<int> global_labeled_image(rows * cols);
  std::vector<int> expected_label = {2, 1, 1, 1, 1, 3, 4, 1, 1};
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataPar->inputs_count.emplace_back(rows);
    taskDataPar->inputs_count.emplace_back(cols);
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_labeled_image.data()));
    taskDataPar->outputs_count.emplace_back(rows);
    taskDataPar->outputs_count.emplace_back(cols);
  }

  guseynov_e_marking_comps_of_bin_image_mpi::TestMPITaskParallel testMpiTaskParallel(taskDataPar);
  ASSERT_TRUE(testMpiTaskParallel.validation());
  testMpiTaskParallel.pre_processing();
  testMpiTaskParallel.run();
  testMpiTaskParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int> reference_labeled_image(rows * cols);

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataSeq->inputs_count.emplace_back(rows);
    taskDataSeq->inputs_count.emplace_back(cols);
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_labeled_image.data()));
    taskDataSeq->outputs_count.emplace_back(rows);
    taskDataSeq->outputs_count.emplace_back(cols);

    // Create Task
    guseynov_e_marking_comps_of_bin_image_mpi::TestMPITaskSequential testMpiTaskSequential(taskDataSeq);
    ASSERT_TRUE(testMpiTaskSequential.validation());
    testMpiTaskSequential.pre_processing();
    testMpiTaskSequential.run();
    testMpiTaskSequential.post_processing();

    ASSERT_EQ(reference_labeled_image, expected_label);
    ASSERT_EQ(reference_labeled_image, global_labeled_image);
  }
}

TEST(guseynov_e_marking_comps_of_bin_image_mpi, fixed_test_5) {
  boost::mpi::communicator world;
  const int rows = 3;
  const int cols = 3;
  std::vector<int> image(rows * cols, 0);
  std::vector<int> global_labeled_image(rows * cols);
  std::vector<int> expected_label(rows * cols, 2);
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataPar->inputs_count.emplace_back(rows);
    taskDataPar->inputs_count.emplace_back(cols);
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_labeled_image.data()));
    taskDataPar->outputs_count.emplace_back(rows);
    taskDataPar->outputs_count.emplace_back(cols);
  }

  guseynov_e_marking_comps_of_bin_image_mpi::TestMPITaskParallel testMpiTaskParallel(taskDataPar);
  ASSERT_TRUE(testMpiTaskParallel.validation());
  testMpiTaskParallel.pre_processing();
  testMpiTaskParallel.run();
  testMpiTaskParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int> reference_labeled_image(rows * cols);

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataSeq->inputs_count.emplace_back(rows);
    taskDataSeq->inputs_count.emplace_back(cols);
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_labeled_image.data()));
    taskDataSeq->outputs_count.emplace_back(rows);
    taskDataSeq->outputs_count.emplace_back(cols);

    // Create Task
    guseynov_e_marking_comps_of_bin_image_mpi::TestMPITaskSequential testMpiTaskSequential(taskDataSeq);
    ASSERT_TRUE(testMpiTaskSequential.validation());
    testMpiTaskSequential.pre_processing();
    testMpiTaskSequential.run();
    testMpiTaskSequential.post_processing();

    ASSERT_EQ(reference_labeled_image, expected_label);
    ASSERT_EQ(reference_labeled_image, global_labeled_image);
  }
}