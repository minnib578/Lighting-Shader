#pragma once
#include <windows.h>
#include <Commdlg.h>
#include <stdio.h>
#include<iostream>
#include <string>
using namespace std;

string w2s(const wstring& path)
{
    int nLen = ::WideCharToMultiByte(CP_ACP, 0, path.c_str(), path.length(), NULL, 0, NULL, NULL);
    std::string str;
    str.resize(nLen, ' ');
    ::WideCharToMultiByte(CP_ACP, 0, path.c_str(), path.length(), (LPSTR)str.c_str(), nLen, NULL, NULL);
    return str;
}

string New_path()
{
    OPENFILENAME ofn;
    WCHAR FILE[MAX_PATH] = L"";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = FILE;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(FILE);
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    if (GetOpenFileName(&ofn))
    {
        string new_path = w2s(FILE);
        return new_path;
    }
    else
    {
        printf("Please try again!");
    }
    return 0;
}
