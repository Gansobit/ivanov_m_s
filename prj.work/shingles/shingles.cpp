#include"shingles.h"


std::vector<std::string> canonize(std::string sh) {
	const std::string stop_symbol[] = { "!", ".", ",", "?", ":", ";", "(", ")", "-", "\"", ">", "<", "»", "«", "|" };
	const std::string stop_words[] = { "это", "как", "так", "и", "в", "над", "к", "до", "не", "на", "но", "за", "то", "с", "ли", "а",
		"во", "от", "со", "для", "о", "же", "ну", "вы", "бы", "что", "кто", "он", "она", "оно", "я", "по" };
	//удаляем ненужные символы и слова из текста и приводим весь текст к нижнему регистру
	std::transform(sh.begin(), sh.end(), sh.begin(), ::tolower);
	sh.insert(sh.begin(), '!');
	for (ptrdiff_t i = 0; i < 32; i++)
	{
		ptrdiff_t pos = 0;
		if (sh.find("!" + stop_words[i] + " ") == 0) {
			sh.erase(0, stop_words[i].size() + 1);
		}

		while ((pos = sh.find(' ' + stop_words[i] + ' ', pos)) != sh.npos)
		{
			sh.erase(pos + 1, stop_words[i].size() + 1);
		}

	}

	for (ptrdiff_t i = 0; i < 14; i++)
	{
		int pos = 0;
		while ((pos = sh.find(stop_symbol[i], pos)) != sh.npos)
		{
			sh.erase(pos, stop_symbol[i].size());
		}
	}
	std::vector<std::string>result;
	std::string buffer = "";
	for (size_t i = 0; i < sh.size(); i++) {
		if (sh[i] != ' ') {
			buffer += sh[i];
		}
		else if (buffer.size() > 0) {
			result.push_back(buffer);
			buffer = "";
		}
	}
	return result;
}
//чтение текста из файла
std::string readFile(const std::string& fileName) {
	std::ifstream f(fileName);
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();
	std::string s(size, ' ');
	f.seekg(0);
	f.read(&s[0], size);
	return s;
}

//хэширование CRC32
unsigned int CRC32(std::string source) {
	unsigned char* buf = reinterpret_cast<unsigned char*>(const_cast<char*>(source.c_str()));
	unsigned long len = source.length();
	unsigned long crc_table[256];
	unsigned long crc;
	for (int i = 0; i < 256; i++)
	{
		crc = i;
		for (int j = 0; j < 8; j++)
			crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
		crc_table[i] = crc;
	};
	crc = 0xFFFFFFFFUL;
	while (len--)
		crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
	return crc ^ 0xFFFFFFFFUL;
}

//создаём шинглы и получаем массив хэшей
std::vector<unsigned int> genshingle(std::vector<std::string> source, int shingleLen) {
	std::vector<unsigned int> result;
	for (size_t i = 0; i <= source.size() - shingleLen; i++) {
		std::string temp = source[i];
		for (size_t j = i + 1; j < i + shingleLen; j++)
			temp += " " + source[j];
		result.push_back(CRC32(temp));
	}
	return result;
}
//сравниваем хэши шинглов двух текстов, возвращаем результат в процентах
double compaire(std::vector<unsigned int>cmp1, std::vector<unsigned int>cmp2) {
	std::vector<unsigned int>intersection;
	int same = 0;
	for (size_t i = 0; i < cmp1.size(); i++)
		for (size_t j = 0; j < cmp2.size(); j++)
			if (cmp1[i] == cmp2[j]) {
				same++;
				break;
			}
	ptrdiff_t sum = cmp1.size() + cmp2.size();
	return 200.0 * same / sum;
}