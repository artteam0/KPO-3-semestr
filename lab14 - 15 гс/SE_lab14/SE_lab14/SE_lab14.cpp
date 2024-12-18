//#include "stdafx.h"
#include <iostream>
#include <locale>
#include <cwchar>

#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "ru");
	//cout << "---- тест Error::geterror ---" << endl << endl;
	//try
	//{
	//	throw ERROR_THROW(100);
	//}
	//catch (Error::ERROR e)
	//{
	//	cout << "Ошибка" << e.id << ": " << e.message << endl << endl;
	//};

	//cout << "---- тест Error::geterrorin ---" << endl << endl;
	//try
	//{
	//	throw ERROR_THROW_IN(111, 7, 7);
	//}
	//catch (Error::ERROR e)
	//{
	//	cout << "Ошибка" << e.id << ": " << e.message << ", строка " << e.inext.line << ", позиция " << e.inext.col << endl << endl;
	//};

	//cout << "---- Тест Parm::getparm ----" << endl;
	//try {
	//    Parm::PARM parm = Parm::getparm(argc, argv);
	//    wcout << "-in:" << parm.in << ", -out:" << parm.out << ", -log:" << parm.log << endl << endl;
	//}
	//catch (Error::ERROR e)
	//{
	//    cout << "Ошибка " << e.id << ": " << e.message << endl << endl;
	//}

	cout << "тест  IN::getin" << endl << endl;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		cout << in.text << endl;
		cout << "Всего символов:" << in.size << endl;
		cout << "Всего строк:" << in.lines << endl;
		cout << "Пропущено:" << in.ignor << endl; 
		std::ofstream Out(parm.out);
		Out << in.text;
		Out.close();
	}
	catch (Error::ERROR e)
	{
		cout << "Ошибка " << e.id << ":" << e.message << endl << endl;
	};

	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, (char*)"Тест:", (char*)" без ошибок \n", "");
		Log::WriteLine(log, (wchar_t*)L"Тест: ", (wchar_t*)L"без ошибок\n ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log:WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	};

	system("pause");

	return 0;
};