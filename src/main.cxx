#include <iostream>
#include "TFClassifier.h"
#include "CSVReader.h"

int main(int argc, char * argv[]) {
  if(argc != 3) {
    std::cout<<"fashio_mnist [csv test file] [model_directory]"<<std::endl;

    return -1;
  }

  unsigned int width = 28;
  unsigned int height = 28;

  CSVReader csvreader(argv[1], width * height);
  TfClassifier tf(argv[2], width, height);

  unsigned int positive = 0;
  unsigned int all = 0;

  while(true) {
    auto in = csvreader.read();
    if(in.second.size() == 0)
      break;

    auto result = tf.predict(in.second);

    if(result == in.first) {
      positive++;
    }
    all++;
  }

  std::cout << (double)positive/all << std::endl;

  return 0;
}
