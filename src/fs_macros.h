/** \file fs_macros.h
 ** \brief contains function and configuration macros
 **/

#ifndef FS_MACROS_H
#define FS_MACROS_H

#define VERSION "3.0.0"
#define AUTHOR "Frank Suarez"
#define EMAIL "fsuarez@emich.edu"

// ====================================================
// configuration macros

#define BUFFER_SIZE 256
#define DEFAULT_PORT 20750
#define DEFAULT_HOSTNAME "localhost"
#define BACKLOG 5
#define CHATLOG_FILENAME "fs_chatlog.txt"
#define CHATLOG_HEADER "================ CHAT LOG ================"
#define CHATLOG_FOOTER "=========================================="

// ====================================================
// function macros
// macro to make __LINE__ a string
#define stringify(s) #s
#define xstringify(s) stringify(s)
#define __LINESTR__ xstringify(__LINE__)

// concatenates
#define __cat(a,b) a##b
#define __xcat(a,b) __cat(a,b)

#endif // FS_MACROS
