//
// Created by nils on 7/16/22.
//

#include "sysinfo.h"

#include <qglobal.h>

#ifdef Q_OS_WIN
#include <windows.h>
unsigned long long SysInfo::totalRam() {
    MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullTotalPhys;
}
#else
#include <unistd.h>
unsigned long long SysInfo::totalRam() {
    return sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);
}
#endif