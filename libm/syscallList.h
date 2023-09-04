#pragma once

#define SYSCALL_GET_ARGC 100
#define SYSCALL_GET_ARGV 101
#define SYSCALL_GET_ENV 102

#define SYSCALL_EXIT  190
#define SYSCALL_CRASH  191
#define SYSCALL_YIELD  192
#define SYSCALL_WAIT  193

#define SYSCALL_SERIAL_PRINT  200
#define SYSCALL_SERIAL_PRINTLN 201

#define SYSCALL_SERIAL_PRINT_CHAR 202
#define SYSCALL_SERIAL_READ_CHAR 203
#define SYSCALL_SERIAL_CAN_READ_CHAR 204


#define SYSCALL_GLOBAL_PRINT  301
#define SYSCALL_GLOBAL_PRINTLN 302
#define SYSCALL_GLOBAL_PRINT_CHAR  303
#define SYSCALL_GLOBAL_CLS  310

#define SYSCALL_ENV_GET_TIME_MS 400

#define SYSCALL_RNG_UINT64 500
