// TranslateGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "iostream"
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <Windows.h>

namespace fs = std::filesystem;

void generateOutFile(const std::string fileName_str,std::ofstream& out_str_stream) {
	

	std::ifstream infile;
	infile.open(fileName_str, std::ifstream::in);
	if (!infile.is_open()) {
		std::cout << " file do not open ";

		return;
	}


	std::string str;
	int i_numberPacket = 0;
	std::string last_str; std::getline(infile, last_str);
	while (std::getline(infile, str))
	{
		size_t last_pos_resh = last_str.find("#"), last_pos_kav = last_str.find("\"");
		if (last_pos_resh != std::string::npos) {
			//std::cout << last_str.substr(last_pos_resh + 1, last_pos_kav - last_pos_resh - 1);
			if (str.find(last_str.substr(last_pos_resh + 1, last_pos_kav - last_pos_resh - 1)) != std::string::npos) {
				std::cout << "!!!!!" << last_str.substr(last_pos_resh + 1, last_pos_kav - last_pos_resh - 1);

				std::string str_help = last_str.substr(last_pos_kav + 1, last_str.length() - last_pos_kav - 2);
				if (str_help.length()>2)
					std::cout << "+++ " << str_help << "\n";
				out_str_stream << str_help << " %(@^ ";
				std::string;
			}
		}
		//std::cout << str << "\n";
		last_str = str;

	}
	infile.close();

}


void writeTranslateInFiles(const std::string fileName_str, std::ifstream& in_str_stream, std::string& str_stream) {


	std::ifstream infile;
	infile.open(fileName_str, std::ifstream::in);
	if (!infile.is_open()) {
		std::cout << " file do not open ";
		return;
	}

	std::string translate_str_from_file;
	std::string str;
	int i_numberPacket = 0;
	std::string last_str; std::getline(infile, last_str);
	while (std::getline(infile, str))
	{
		size_t last_pos_resh = last_str.find("#"), last_pos_kav = last_str.find("\"");
		if (last_pos_resh != std::string::npos) {
			//std::cout << last_str.substr(last_pos_resh + 1, last_pos_kav - last_pos_resh - 1);
			if (str.find(last_str.substr(last_pos_resh + 1, last_pos_kav - last_pos_resh - 1)) != std::string::npos) {
				std::cout << "!!!!!" << last_str.substr(last_pos_resh + 1, last_pos_kav - last_pos_resh - 1);

				std::string str_help = last_str.substr(last_pos_kav + 1, last_str.length() - last_pos_kav - 2);
				if (str_help.length() > 2)
					std::cout << "+++ " << str_help << "\n";
				///out_str_stream << str_help << " %(@^ ";
				
				if (str_stream.find("%(@^") == std::string::npos) {
					std::string str_n_h;
					std::getline(in_str_stream, str_n_h);
					str_stream += str_n_h;
				}

				std::size_t pos = str_stream.find("%(@^");
				std::string transl_str = str_stream.substr(0, pos);
				str_stream.erase(0,pos+4);
				//str_stream.erase(pos, 4);

				std::cout<< str_help <<" : " << transl_str << "\n";

				

			}
		}
		//std::cout << str << "\n";
		last_str = str;

	}
	infile.close();

}

std::string str_file_cur="";

int main()
{
	//setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "hello ";
	std::string path = "E:\\ProjTranslate\\TranslateGame\\TranslateGame\\russian";
	std::ofstream resultStream("result_eng.txt");
	

	std::ifstream translatefile("translate_rus_ansi.txt");
	//infile.open(fileName_str, std::ifstream::in);
	if (!translatefile.is_open()) {
		std::cout << " file do not open ";
		return 1;
	}
	
	std::string translate_str = "";
	for (auto entry : fs::recursive_directory_iterator(path))
	{
		
		std::cout <<"\n QQQQQQQQQQQQQQQQQQQQQQQQQQQ+++++++++QQQ   "<< entry.path() << "\n";
		writeTranslateInFiles(entry.path().generic_u8string(), translatefile, translate_str);
		//generateOutFile(entry.path().generic_u8string(), resultStream);
		
	}
		
	resultStream.close();
	
}


