#pragma once

#include <iostream>
#include <fstream>

class Logger
{
public:
	Logger(std::string filePath)
	{
		file.open(filePath);
	}

	~Logger()
	{
		file.close();
	}

	void Output(std::string log)
	{
		if (file.is_open()) {
			file << log << std::endl;
		}
	}
private:
	std::ofstream file;
};
