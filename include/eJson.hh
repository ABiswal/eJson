#ifndef EJSON_CXX_INCLUDED
#define EJSON_CXX_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "jsont.hh"

namespace eJson{

class eJsonTokenizer:public jsont::Tokenizer{

public:
    eJsonTokenizer(const std::string& filepath);
    ~eJsonTokenizer(){}
    jsont::Tokenizer tockenizer;

private:
    eJsonTokenizer();
    jsont::Tokenizer& getTockenizer();
    int getImportNestCount();
    int _importNestCount;
    const char * inbuf2;
    //jsont::Tokenizer tockenizer;

};

eJsonTokenizer::eJsonTokenizer(){
    Tokenizer();
}

eJsonTokenizer::eJsonTokenizer(const std::string& filepath){
std::string fileText;
  //std::string filepath="test.eJson";
  std::ifstream file;

  std::regex rgx("import\\s+\"(\\S*)\"");
  std::smatch regexMatch;

  std::string line;
  file.open(filepath);
  if (file.is_open()){
    while(std::getline(file,line)){
      //fileText.append(line);
      std::cout<<line<<std::endl;
      if(std::regex_match(line,regexMatch,rgx)){
        std::cout<<regexMatch[1]<<std::endl;
        std::ifstream tfile;
        std::string tline;
        std::string tfilepath=regexMatch[1].str();
        tfile.open(tfilepath);
        std::cout<<tfilepath;
        if(tfile.is_open()){
            while(std::getline(tfile,tline)){
                fileText.append(tline);
                std::cout<<tline<<std::endl;
            }
            tfile.close();

        } 
        else{
          std::cout<<"could not import";
        }     

      }//regex match
      else{
          fileText.append(line);
      }
    }
    file.close();
  }
  inbuf2=fileText.c_str();
  tockenizer=jsont::Tokenizer((const char *)inbuf2, strlen(inbuf2),jsont::TextEncoding::UTF8TextEncoding);
  tockenizer.reset((const char *)inbuf2, strlen(inbuf2),jsont::TextEncoding::UTF8TextEncoding);
}

jsont::Tokenizer& eJsonTokenizer::getTockenizer(){
    return tockenizer;
}

}
#endif //EJSON_CXX_INCLUDED