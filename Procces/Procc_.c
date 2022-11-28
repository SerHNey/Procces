#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
int countsymbls(char* namefile);


int main() {
	system("chcp 1251>nul");
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	int size = countsymbls("data.txt");
	HANDLE file = CreateFile(L"data.txt", GENERIC_READ, NULL, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file != INVALID_HANDLE_VALUE) {
		DWORD countreadbytes = 100;
		DWORD readingbytes = 100;
		char* stroka = calloc(size, sizeof(char));
		if (!(ReadFile(file, stroka, size, &readingbytes, NULL))) {
			file = CreateFile(L"result.txt", GENERIC_READ, NULL, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			sprintf(stroka, "Ошибка");
			WriteFile(file, stroka, strlen(stroka), &readingbytes, NULL);
			return 1;
		}
		CloseHandle(file);
		int procc = CreateProcessA("..\\x64\\Debug\\Newprocc.exe",stroka, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	
		WaitForSingleObject(pi.hProcess, INFINITE);
		DWORD dwCode;
		GetExitCodeProcess(pi.hProcess, &dwCode);


		if (dwCode == 1) {
			size = countsymbls("result.txt");
			stroka = calloc(countsymbls("result.txt"), sizeof(char));

			HANDLE filee = CreateFile(L"result.txt", GENERIC_READ, NULL, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			ReadFile(filee, stroka, size, &readingbytes, NULL);
			printf("%s", stroka);
		}
	}
}

int countsymbls(char* namefile) {
	FILE* pFile = fopen(namefile, "r");
	int size = 0;
	if (!pFile) {
		perror("Error opening file");
		return 0;
	}
	else
	{
		fseek(pFile, 0, SEEK_END);
		size = ftell(pFile);
		fclose(pFile);
		return size;
	}
}