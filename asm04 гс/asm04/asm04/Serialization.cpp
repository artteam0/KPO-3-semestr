#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Data {
	string type;
	long longV;
	unsigned char ucharV;
};

void serialize(const Data& data, const string& filename) {
	ofstream outfile(filename, ios::binary);
	if (!outfile) {
		cout << "Ошибка открытия файла." << endl;
		return;
	}

	size_t typeLen = data.type.size();
	outfile.write(reinterpret_cast<const char*>(&typeLen), sizeof(typeLen));
	outfile.write(data.type.c_str(), typeLen);

	outfile.write(reinterpret_cast<const char*>(&data.longV), sizeof(data.longV));
	outfile.write(reinterpret_cast<const char*>(&data.ucharV), sizeof(data.ucharV));

	outfile.close();
	cout << "Сериализировано в " << filename << endl;
}

int main() {
	Data data = { "long & uchar", 1234567890, 255 };

	string filename = "data.txt";
	serialize(data, filename);

	return 0;
}