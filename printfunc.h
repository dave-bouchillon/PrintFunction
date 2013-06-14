#pragma once

#define WM_PRINT_NUMBER WM_USER+1

bool printFunc(HWND hwnd, int nstart, int nend, char* replacementRules);
