#pragma once
#ifndef CCONTAIN_H
#define CCONTAIN_H
#include<vector>
#include<string>
class Ccontain
{
private:
	std::vector<std::string> cha;
public:
	Ccontain();
	bool changeC(int position);
	char* outchar(int position);
};
#endif
