```c
ZEND_BEGIN_MODULE_GLOBALS(yaconf)
  char *directory;
  int parse_err;
#ifndef ZTS
  long check_delay;
  time_t last_check;
  time_t directory_mtime;
#endif
ZEND_END_MODULE_GLOBALS(yaconf)
```

上面的代码用于定义一个结构体，展开之后如下所示：
```c
typedef struct _zend_yaconf_globals {
  char *directory;
  int parse_err;
#ifndef ZTS
  long check_delay;
  time_t last_check;
  time_t directory_mtime;
#endif
} zend_yaconf_globals;
```

上面这个类一般会声明在`*.h`文件中，使用的时候在`*.c`文件中，一般也是使用宏。

```c
ZEND_DECLARE_MODULE_GLOBALS(yaconf);
```

这里展开的时候要根据情况，分线程安全和非线程安全两个版本，线程安全版本只会定义一个用于标示资源序号的id，
非线程安全版本则会定义一个结构体。
```c
...
#ifdef ZTS
#define ZEND_DECLARE_MODULE_GLOBALS(module_name)    \
  ts_rsrc_id module_name##_globals_id;
#else
  zend_##module_name##_globals module_name#_globals;
#endif
...
```
