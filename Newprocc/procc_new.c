#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <math.h>
DWORD countreadbytes = 100;
DWORD readingbytes = 100;
int main(int argc, char* argv[]) {
	char* stroka = calloc(100, 1);

	strcat(stroka, argv[0]);
	strcat(stroka, " ");
	strcat(stroka, argv[1]);
	strcat(stroka, " ");
	strcat(stroka, argv[2]);

	HANDLE file2 = CreateFile(L"result2.txt", GENERIC_WRITE, NULL, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	HANDLE file = CreateFile(L"result.txt", GENERIC_WRITE, NULL, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);


	char* p = strchr(stroka, 'э');
	if (p)
		*(p) = '\0';
	puts(stroka);
	WriteFile(file2, stroka, strlen(stroka), &readingbytes, NULL);


	int i = 0;
	//while (stroka[i]) {
	//	i++;
	//	if (stroka[i] > 96 || stroka[i] < -1 ) {
	//		sprintf(stroka, "Ошибка данных2");
	//		readingbytes = strlen(stroka);
	//		WriteFile(file, stroka, readingbytes, &readingbytes, NULL);
	//		return 1;
	//	}
	//}
	char* number;
	number = strtok(stroka, " ");
	double numbers[3];

	numbers[0] = atof(number);

	i = 1;
	while (number != NULL)
	{
		number = strtok(NULL, " ");
		if (number != NULL) {
			if (number[0] != '\r') {
				numbers[i] = atof(number);
				i++;
			}
		}
		if (i > 3)
			break;
	}
	double a = numbers[0]; double b = numbers[1]; double c = numbers[2];

	double diskrimenant = sqrt(pow(b, 2) - 4 * a * c);
	if (diskrimenant < 0) {
		sprintf(stroka, "Дискриминант меньше 0\n Корней нет");
		readingbytes = strlen(stroka);
		WriteFile(file, stroka, readingbytes, &readingbytes, NULL);
	}
	if (diskrimenant == 0) {
		c = (-b) / (2 * a);
		sprintf(stroka, "Дискрименант равен = 0\n x1 = %f\n x2 = %f", c, c);
		readingbytes = strlen(stroka);
		WriteFile(file, stroka, readingbytes, &readingbytes, NULL);
	}
	if (diskrimenant > 0) {
		c = (-b + diskrimenant) / (2 * a);
		a = (-b - diskrimenant) / (2 * a);
		sprintf(stroka, "Корень дискрименанта равен = %f\n x1 = %f\n x2 = %f", diskrimenant, c, a);
		readingbytes = strlen(stroka);
		WriteFile(file, stroka, readingbytes, &readingbytes, NULL);
	}
	CloseHandle(file);
	return 1;
}
