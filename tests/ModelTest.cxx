#include "CSVReader.h"
#include "TFClassifier.h"

#include <gtest/gtest.h>

#ifdef _WIN32
	const std::string testCasesPath = ".\\tests\\test_cases\\";
#else
	const std::string testCasesPath = "./tests/test_cases/";
#endif

TEST(FashionMnistTest, First) {
  unsigned int width = 28;
  unsigned int height = 28;

  CSVReader csvreader("./tests/test.csv", width * height);
  TfClassifier tf("./tests/saved_model", width, height);

  unsigned int positive = 0;
  unsigned int all = 0;

  while(true)  {
    auto in = csvreader.read();
    if(in.second.size() == 0)
      break;

    auto result = tf.predict(in.second);

    if(result == in.first) {
      positive++;
    }
    all++;
  }

  ASSERT_NEAR(static_cast<double>(positive)/all, 0.91, 1e-2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
