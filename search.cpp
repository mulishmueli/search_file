
#include <tchar.h>
#include <strsafe.h>
#include <sys/stat.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <fstream>
#include <sys/types.h>
#ifdef WIN32
#define stat _stat
#endif
#include "dirnet.h"
#include <sstream>

#include <windows.h>
#include <io.h>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>
#include <clocale>
#include <locale>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

using std::experimental::filesystem::directory_iterator;

using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;
using namespace std::chrono_literals;

namespace fs = std::experimental::filesystem;

std::string to_string(FILETIME ftime) // ISO format, time zone designator Z == zero (UTC)
{
	SYSTEMTIME utc;
	::FileTimeToSystemTime(std::addressof(ftime), std::addressof(utc));

	std::ostringstream stm;
	const auto w2 = std::setw(2);
	stm << std::setfill('0') << std::setw(4) << utc.wYear << '-' << w2 << utc.wMonth
		<< '-' << w2 << utc.wDay << ' ' << w2 << utc.wYear << ' ' << w2 << utc.wHour
		<< ':' << w2 << utc.wMinute << ':' << w2 << utc.wSecond << 'Z';

	return stm.str();
}


int main() 
{
	vector<string> FolderPath;
	vector<string> FileName;
	vector<string > CreationDate;
	vector<string > ModifiedDate;
	vector<string > DateAccessed;
	string path = "/Windows";
	for (const auto & file : directory_iterator(path))
	{
		string buffer = file.path().string();
		FolderPath.push_back(file.path().string());
		cout << file.path().string() << endl;

		std::string fileName;
		fileName = file.path().filename().string();
		int pos = fileName.rfind(".");
		FileName.push_back(std::string(fileName, 0, pos));
		fileName.clear();

		WIN32_FIND_DATA wfd;
		HANDLE hFind = FindFirstFile(buffer.c_str(), &wfd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			FindClose(hFind);
			ModifiedDate.push_back(to_string(wfd.ftCreationTime));
			CreationDate.push_back(to_string(wfd.ftLastAccessTime));
			DateAccessed.push_back(to_string(wfd.ftLastWriteTime));
		}
	}
	DIR *dir;
	int a = 0; int b = 0; int c = 0; int d = 0; int e = 0;
	struct dirent *ent;
	if ((dir = opendir("C:/Windows")) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			printf("%s\n", ent->d_name);
			FileName.push_back(ent->d_name);

		}
		closedir(dir);
	}
	else {
		perror("");
		return EXIT_FAILURE;
	}

	fstream fout;
	fout.open("report.csv", ios::out | ios::app);
	int i;
	for (i = 0; i < FolderPath.size(); i++) 
	{
		size_t found = FileName[i].find("XT.ec");
		size_t found2 = FileName[i].find("AcGenral");
		string str1 = FileName[i].substr(0, 3);
		string str2 = FileName[i].substr(FileName[i].size()-3, FileName[i].size());
		if (FileName[i] == "ERRORREP" || str1 == "QHE" || str2 == "GNOFF" || FolderPath[i] == "C:\Windows\addins"|| 
			FileName[i].substr(FileName[i].find_last_of(".") + 1) == "sdb" || found != std::string::npos || found2 != std::string::npos)
		{
			fout << FolderPath[i] << ", "
				<< FileName[i] << ", "
				<< CreationDate[i] << ", "
				<< ModifiedDate[i] << ", "
				<< DateAccessed[i] << ", "
				<< "\n";
		}
	}
	fout.close();
	return 0;
}

