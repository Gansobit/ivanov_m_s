#include"shingles/shingles.h"

int main()
{
	std::string text1 = readFile("../../../data/text4.txt");
	std::string text2 = readFile("../../../data/text3.txt");
	int shingleLen = 10;
	auto begin = std::chrono::steady_clock::now();
	setlocale(LC_ALL, "Russian");
	std::cout << "Совпадение шинглов в процентах: " << compaire(genshingle(canonize(text1), shingleLen),
		genshingle(canonize(text2), shingleLen)) << " %\n";
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
	std::cout << "Время работы в секундах: " << elapsed_ms.count();
}