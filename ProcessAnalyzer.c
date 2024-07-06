#include <stdio.h>
#include <windows.h>
#include <psapi.h>
#include <tchar.h>

void PrintModules(char *nProcess, DWORD processID); // Allows you to display the final result

int main() {
    DWORD processIds[1024]; // Array that stores process IDs.
    DWORD bytesNeeded; // Number of bytes returned in the processus array by EnumProcesses.
    DWORD processesRetrieved; // Number of processes found.
    DWORD dwSize = sizeof(processIds); // Size of the process table in bytes.
    DWORD dwError; // Variable to display errors.
    DWORD dwI; // for loop variable.
    DWORD dwGetProcessInformation; // Variable to retrieve the result of GetModuleBaseNameA.
    HANDLE hProcess; // Process handle.
    char nProcess[256]; // Array to store the process name.

    // Enumeration of processes to retrieve IDs
    if (!EnumProcesses(processIds, dwSize, &bytesNeeded)) {
        _tprintf(_T("Error in EnumProcesses Function\n"));
        dwError = GetLastError();
        _tprintf(_T("Error: %lu\n"), dwError);
        return 1;
    }

    processesRetrieved = bytesNeeded / sizeof(DWORD);

    // Extraction of process handles if they are not null and then extracting their names.
    for (dwI = 0; dwI < processesRetrieved; dwI++) {
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processIds[dwI]);
        if (hProcess != NULL) {
            dwGetProcessInformation = GetModuleBaseNameA(hProcess, NULL, nProcess, sizeof(nProcess));
            if(dwGetProcessInformation > 0) {
                PrintModules(nProcess, processIds[dwI]);
            }           
            CloseHandle(hProcess); // Closing the process handle
        }
    }

    return 0;
}

void PrintModules(char *nProcess, DWORD processID) {
    printf("Process ID: %lu, Process Name: %s\n", processID, nProcess); // Shows process name and ID
}