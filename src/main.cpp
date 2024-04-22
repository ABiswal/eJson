
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "jsont.hh"
#include "eJson.hh"

int main(int argc, char * argv[]) {
  
  std::cout<<"Hello eJson<<std::endl";

  // uncomment the below code if required to test the import
  // the eJson file must be present in work/build_linux/src
  //TODO: use copy later
  #if 0
  eJson::eJsonTokenizer E("test.eJson");
  jsont::Token tok;
  tok=E.tockenizer.next();
  
  printf("tocken %d",tok);
  #endif

}
