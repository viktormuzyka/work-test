#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>

class writer {
 public:
  virtual ~writer() {}
  writer() = default;
  writer(WIN32_FIND_DATA &data);
};
class txtwriter : public writer {
 public:
  txtwriter(WIN32_FIND_DATA &data){
    std::ofstream out;
  			out.exceptions(std::fstream::badbit);
	   		try {
		        out.open("out.txt",std::fstream::app);
		        out << data.cFileName <<';';
		        out << data.dwReserved1 << ';';
				out << data.nFileSizeLow << ';' << std::endl;
		        out.close();
   			}
		    catch (const std::fstream::failure& exc)
		    {
		        std::cout << "failed to open/write file"<<std::endl;
		    }
  }
};
class csvwriter : public writer {
 public:
  csvwriter(WIN32_FIND_DATA &data){
    std::ofstream csv;
		    csv.exceptions(std::fstream::badbit);
		    try {
		        csv.open("out.csv",std::fstream::app);
		        csv << data.cFileName <<';';
		        csv << data.dwReserved1 << ';';
				csv << data.nFileSizeLow << ';' << std::endl;
		        csv.close();
		    }
		    catch (const std::fstream::failure& exc)
		    {
		        std::cout << "failed to open/write file" << std::endl;
		    }
  }
};

