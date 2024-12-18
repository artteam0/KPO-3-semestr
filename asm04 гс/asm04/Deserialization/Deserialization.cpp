#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Data {
    string type;
    long longValue;
    unsigned char ucharValue;
};

void deserialize(Data& data, const string& fileName) {
    ifstream inFile(fileName, ios::binary);

    // Десериализация типа данных
    size_t typeLength;
    inFile.read(reinterpret_cast<char*>(&typeLength), sizeof(typeLength));
    data.type.resize(typeLength);
    inFile.read(&data.type[0], typeLength);

    // Десериализация значения long
    inFile.read(reinterpret_cast<char*>(&data.longValue), sizeof(data.longValue));

    // Десериализация значения unsigned char
    inFile.read(reinterpret_cast<char*>(&data.ucharValue), sizeof(data.ucharValue));

    inFile.close();
}

string generateAssemblyCode(const Data& data) {
    string assemblyCode = "";

    assemblyCode += ".586P\n";
    assemblyCode += ".MODEL FLAT, STDCALL\n";
    assemblyCode += "includelib kernel32.lib\n\n";
    assemblyCode += "ExitProcess PROTO : DWORD\n";
    assemblyCode += "MessageBoxA PROTO : DWORD, : PTR BYTE, : PTR BYTE, : DWORD\n\n";
    assemblyCode += ".DATA\n";
    assemblyCode += "msgCaption    BYTE    \"Ассемблер\", 0\n";
    assemblyCode += "msgInfo       BYTE    \"В программе используется тип данных " + data.type;
    assemblyCode += " с представлением long: " + to_string(data.longValue) + ", uchar: " + to_string(data.ucharValue) + "\", 0\n\n";
    assemblyCode += ".CODE\n\n";
    assemblyCode += "main PROC\n";
    assemblyCode += "        INVOKE MessageBoxA, 0, addr msgInfo, addr msgCaption, 0\n\n";
    assemblyCode += "        INVOKE ExitProcess, 0\n";
    assemblyCode += "main ENDP\n\n";
    assemblyCode += "end main";

    return assemblyCode;
}

void writeAssemblyToFile(const string& assemblyCode, const string& fileName) {
    ofstream outFile(fileName);

    if (outFile.is_open()) {
        outFile << assemblyCode;
        outFile.close();
    }
    else {
        cout << "Ошибка при открытии файла для записи." << endl;
    }
}

int main() {
    setlocale(0, "");

    const string fileName = "data.bin";

    Data deserializedData;
    deserialize(deserializedData, fileName);

    string assemblyCode = generateAssemblyCode(deserializedData);

    const string asmFileName = "generated_code.asm";

    writeAssemblyToFile(assemblyCode, asmFileName);

    return 0;
}