### zend中trsm
写php扩展的时候，经常会遇到tsrm多线程ZTS问题，经常会用到下面这个：
```c
#ifdef ZTS
#define YACONF_G(v) TSRMG(yaconf_globals_id, zend_yaconf_globals *, v)
#else
#define YACONF_G(v) (yaconf_globals.v)
#endif
```
`TSRMG`是个宏：`#define TSRMG(id, type, element)    (((type) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(id)])->element)`
`TSRM_UNSHUFFLE_RSRC_ID`是个宏，用来减1用的`#define TSRM_UNSHUFFLE_RSRC_ID(rsrc_id)     ((rsrc_id)-1)`
把宏`TSRMG`展开就是（这里拿鸟哥的yaconf中的定义举例子，其他的都一样）
```c
#ifdef ZTS
#define YACONF_G(v) (((zend_yaconf_globals *) (*((void ***) tsrm_ls))[yaconf_globals_id-1])->v)
#else
#define YACONF_G(v) (yaconf_globals.v)
#endif
```
最主要的是`(((zend_yaconf_globals *) (*((void ***) tsrm_ls))[yaconf_globals_id-1])->v)`这一段，这个怎么理解呢？
首先是`tsrm_ls`这个在php各种module的入口中定义的，所有线程共享一个，用来通过id存储不同线程的全局变量
1. 首先将`tsrm_ls`转为`void ***`类型。 => `(void ***) tsrm_ls`
2. 取`tsrm_ls`的值，值的类型为`void **`。=> `*((void ***) tsrm_ls)`
3. 取上一步得到的值的第`yaconf_globals_id-1`个值（这里相当于数组），类型为`void *`。=> `(*((void ***) tsrm_ls))[yaconf_globals_id-1]`
4. 将上一步获取到的`void *`类型的值转化为`zend_yaconf_globals *`类型。=> `(zend_yaconf_globals *) (*((void ***) tsrm_ls))[yaconf_globals_id-1]`
5. 获取`zend_yaconf_globals`结构体中的v值。
