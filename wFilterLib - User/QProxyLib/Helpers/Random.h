#pragma once
#include <random>

class Random
{
public:
	static int Generate(const int min,const int max);

private:

};

int Random::Generate(const int min, const int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(min, max);
	return (int)dist(mt);
}