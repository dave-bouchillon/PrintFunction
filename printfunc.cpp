#include "printfunc.h"
// function that checks for a number divisible by 3, 5, or any number specified
// sends out the number or a string specified by a replacement rule
// hwnd must be valid
// nstart is the start of the range
// nend is the end of the range
// replacementRules contains the replacement rules needed by the caller and must be 
// in the format of "n string" separated by commas. number must be greater than zero
// e.g. "12 dog, 11 cat, 22 fish"

bool printFunc(HWND hwnd, int nstart, int nend, char* replacementRules)
{
    // check for hwnd
    if (!hwnd)
        return false;

    char number[256];
    char ruleString[256];
    char tokenRules[1024];

    for (int i=nstart; i<nend+1; i++)
    {
        bool bprinted = false;
        memset(number, 0, sizeof(number));
        if (i%3 == 0)
        {
            SendMessage(hwnd, WM_PRINT_NUMBER, (WPARAM)"fizz", 0);
            bprinted = true;
        }
        if (i%5 == 0)
        {
            SendMessage(hwnd, WM_PRINT_NUMBER, (WPARAM)"buzz", 0);
            bprinted = true;
        }
        if (replacementRules)
        {
            strcpy(tokenRules, replacementRules);
            char *rule = strtok(tokenRules, ",");
            while (rule)
            {
                int ruleNum = 0;
                memset(ruleString, 0, sizeof(ruleString));
                sscanf(rule, "%d%s", &ruleNum, &ruleString);
                // if number or string is missing, skip rule
                if (ruleNum <= 0 || !*ruleString)
                    continue;
                if (i%ruleNum == 0)
                {                    
                    SendMessage(hwnd, WM_PRINT_NUMBER, (WPARAM)ruleString, 0);
                    bprinted = true;
                }
                rule = strtok(NULL, ",");
            }
        }
        if (!bprinted)
        {
            memset(number, 0, sizeof(number));
            itoa(i, number, 10);
            SendMessage(hwnd, WM_PRINT_NUMBER, (WPARAM)number, 0);
        }
    }
    return true;
}
