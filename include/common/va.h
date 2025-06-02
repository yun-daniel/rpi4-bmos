// va.h
#ifndef __INTERNAL_VA_H__
#define __INTERNAL_VA_H__


#define va_list         __builtin_va_list
#define va_start(ap, x) __builtin_va_start(ap, x)
#define va_arg(ap, t)   __builtin_va_arg(ap, t)
#define va_end(ap)      __builtin_va_end(ap)


#endif // __INTERNAL_VA_H__
