//﻿#include "stdafx.h"
#include "Log.h"
#include <iostream>
#include <fstream>
using namespace std;

#pragma warning(disable:4996) //отключение предупреждения 4996, связанного с использованием небезопасных функций

namespace Log 
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new ofstream;
		log.stream->open(logfile); //открывает файл для записи лога
		if (log.stream->fail())
			throw ERROR_THROW(112); //иначе 112
		wcscpy_s(log.logfile, logfile); //сохранение имени файла
		return log;
	}

	void WriteLine(LOG log, const char* c, ...)
	{
		const char** ptr = &c;
		int i = 0;
		while (ptr[i] != "") //запись строк до первой пустой
			*log.stream << ptr[i++]; //запись символа новой строки
		*log.stream << endl;
	}

	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char temp[100];
		int i = 0;
		while (ptr[i] != L"")
		{
			wcstombs(temp, ptr[i++], sizeof(temp));
			*log.stream << temp;
		}
		*log.stream << endl;
	}

	void WriteLog(LOG log) 
	{
		char date[100];
		tm local;
		time_t currentTime;
		currentTime = time(NULL); //получение времени
		localtime_s(&local, &currentTime);
		strftime(date, 100, "%d.%m.%Y %H:%M:%S", &local); //форматирование времени в строку
		*log.stream << "--- Протокол --- " << date << endl; //запись

	}
	void WriteParm(LOG log, Parm::PARM parm) 
	{

		char buff[PARM_MAX_SIZE];
		size_t tsize = 0;

		*log.stream << "--- Параметры --- " << endl;
		wcstombs_s(&tsize, buff, parm.in, PARM_MAX_SIZE); //преобразование из wchar_t в char
		*log.stream << "-in : " << buff << endl; //запись
		wcstombs_s(&tsize, buff, parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << buff << endl;
		wcstombs_s(&tsize, buff, parm.log, PARM_MAX_SIZE);
		*log.stream << "-log: " << buff << endl;
	}
	void WriteIn(LOG log, In::IN in) 
	{

		*log.stream << "--- Исходные данные --- " << endl;
		*log.stream << "Количество символов : " << in.size << endl; //из структуры IN
		*log.stream << "Количество строк    : " << in.lines << endl;
		*log.stream << "Проигнорировано     : " << in.ignor << endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		if (log.stream) //если файл лога открыт, то запись в файл
		{
			*log.stream << "--- Ошибка!!! --- " << endl;
			*log.stream << "Ошибка " << error.id << ": " << error.message << endl;
			if (error.inext.line != -1) //если указаны строки и столбцы
			{
				*log.stream << "Строка: " << error.inext.line << endl << "Столбец: " << error.inext.col << endl << endl;
			}
		}
		else //если файл лога закрыт, то вывод на консоль
			cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << endl << endl;
	}
	void Close(LOG log) 
	{
		log.stream->close(); //закрытие
		delete log.stream;
	}
}