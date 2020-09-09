#include "file-test.h"
#include <stdio.h>

int main(int argc, const char* argv[]){
  FileTest::testSockPair();
  printf("I could read static method outside of file\n");
  return 0;
}