#include "system_info.h"

#ifdef __linux__
char os_path_sep = '/';
#else
char os_path_sep = '\\';
#endif