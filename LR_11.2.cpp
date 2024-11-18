#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <Windows.h>

using namespace std;

// �������, ��� �������� ����� � ����������� ������� ����
void processLine(char* line, ofstream& outputFile) {
    int i = 0;
    int len = strlen(line);

    while (i < len) {
        if (isdigit(line[i])) {
            bool precededByDot = (i > 0 && line[i - 1] == '.');
            int j = i;

            while (j < len && isdigit(line[j])) {
                j++;
            }

            char digitGroup[1024];
            int groupLen = j - i;
            strncpy(digitGroup, &line[i], groupLen);
            digitGroup[groupLen] = '\0';

            if (!precededByDot) {
                // ��������� �������� ���
                int k = 0;
                while (digitGroup[k] == '0' && digitGroup[k + 1] != '\0') {
                    k++;
                }

                // ���� �� ����� ���� ������ � ���� ��� ��� ������, �������� ���� ����
                if (digitGroup[k] == '\0' && line[j] == '.') {
                    strcpy(digitGroup, "0");
                }
                else {
                    int m = 0;
                    while (digitGroup[k] != '\0') {
                        digitGroup[m++] = digitGroup[k++];
                    }
                    digitGroup[m] = '\0';
                }
            }
            else {
                // ��������� ������� ������� �� ���� ����
                if (strlen(digitGroup) > 2) {
                    digitGroup[2] = '\0';
                }
            }

            // �������� ��������� ����� ���� � �������� ����
            outputFile << digitGroup;
            i = j;
        }
        else {
            // �������� ������ � �������� ����
            outputFile.put(line[i]);
            i++;
        }
    }
    outputFile.put('\n');  
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const char* inputFileName = "t1.txt";  // ������� ����
    const char* outputFileName = "t2.txt"; // �������� ����

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open()) {
        cerr << "������� �������� �������� �����!" << endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        cerr << "������� �������� ��������� �����!" << endl;
        return 1;
    }

    char line[1024];  

    while (inputFile.getline(line, sizeof(line))) {
        processLine(line, outputFile);
    }

    inputFile.close();
    outputFile.close();

    cout << "������� ���������. ��������� �������� � ���� " << outputFileName << endl;
    return 0;
}
