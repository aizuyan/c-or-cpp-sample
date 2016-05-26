/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_myglobals.h"

/* If you declare any globals in php_myglobals.h uncomment this:
*/
ZEND_DECLARE_MODULE_GLOBALS(myglobals);

unsigned long hashLen = 50000;

/* True global resources - no need for thread safety here */

unsigned long calc_hash(const char *key, unsigned int keyLen)
{
     unsigned long hash = 5381;

    /* variant with the hash unrolled eight times */
    for (; keyLen >= 8; keyLen -= 8) {
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
    }
    switch (keyLen) {
        case 7: hash = ((hash << 5) + hash) + *key++; /* fallthrough... */
        case 6: hash = ((hash << 5) + hash) + *key++; /* fallthrough... */
        case 5: hash = ((hash << 5) + hash) + *key++; /* fallthrough... */
        case 4: hash = ((hash << 5) + hash) + *key++; /* fallthrough... */
        case 3: hash = ((hash << 5) + hash) + *key++; /* fallthrough... */
        case 2: hash = ((hash << 5) + hash) + *key++; /* fallthrough... */
        case 1: hash = ((hash << 5) + hash) + *key++; break;
        case 0: break;
    }
    return hash;
}


MyBucket *hash_key_string_insert(MyBucket **arr, const char *key, const char *value)
{
    unsigned long hash = calc_hash(key, strlen(key));
    unsigned long solt = hash % hashLen - 1;

    //判断槽位是否为空
    MyBucket *element = (MyBucket *)malloc(sizeof(MyBucket));
    char *newKey = strdup(key);
    char *newVal = strdup(value);
    element->key = newKey;
    element->val = newVal;
    element->next = arr[solt];
    arr[solt] = element;

    return element;
}
char *hash_key_string_find(MyBucket **arr, const char *key)
{
    unsigned long hash = calc_hash(key, strlen(key));
    unsigned int solt = hash % hashLen - 1;
    MyBucket *p = arr[solt];
    while(p != NULL)
    {
        if(0 == strcmp(key, p->key))
        {
            break;
        }
        p = p->next;
    }
    if(p == NULL)
        return NULL;

    return strdup(p->val);
}

const char *get_key_from_line(const char *line, char *ret)
{   
    int i = 0;
    while(*line)
    {   
        if(*line != ',')
        {   
            ret[i] = *line;
        }else {
            break;
        }
        i++;
        line++;
    }
    ret[i] = '\0';
    return ret;
}

const char *get_val_from_line(const char *line, char *ret)
{   
    int i = 0; 
    int flag = 0;
    while(*line)
    {   
        
        if(*line == ',')
        {   
            flag = 1;
            line++;
            continue;
        }else if(!flag) {
            line++;
            continue;
        }
        ret[i] = *line;
        i++;
        line++;
    }
    ret[i] = '\0';
    return ret;
}

//最多扫描10个words文件，按顺序从0开始
void scan_words_from_dir(const char *dir)
{
    const char *path = "%swords_%d";
    int i = 0;
    char file[MAX_FILE_PATH_SIZE], line[MAX_WORD_LINE_SIZE], key[MAX_WORD_WORD_SIZE], val[MAX_WORD_WORD_SIZE];
    FILE *fp;
    for(; i<MAX_READ_WORD_NUM; i++)
    {
        sprintf(file, path, dir, i);
        if(access(file, 0) == -1)
            continue;
        fp  = fopen(file, "r");
        while(fgets(line, 100, fp))
        {
            get_key_from_line(line, key);
            get_val_from_line(line, val);
            hash_key_string_insert(myglobals_globals.myArr, key, val);
        }
        fclose(fp);
        fp = NULL;
    }
}

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
*/
/* }}} */
PHP_INI_BEGIN()
    PHP_INI_ENTRY("myglobals.dir", "/tmp/mypinyin/", PHP_INI_SYSTEM, NULL)
PHP_INI_END()

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string my_test(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(my_test)
{
    char *str;
    str = hash_key_string_find(myglobals_globals.myArr, "yrt");
    php_printf("%s\n", str);
    str = hash_key_string_find(myglobals_globals.myArr, "踉踉跄跄");   
    php_printf("%s\n", str);

    RETURN_TRUE;
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_myglobals_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_myglobals_init_globals(zend_myglobals_globals *myglobals_globals)
{
	myglobals_globals->global_value = 0;
	myglobals_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(myglobals)
{
    REGISTER_INI_ENTRIES();
    myglobals_globals.myArr = (MyBucket **)calloc(hashLen, sizeof(MyBucket *));
    const char *pinyindir = INI_STR("myglobals.dir");
    php_printf("%s\n", pinyindir);
    scan_words_from_dir(pinyindir);
    hash_key_string_insert(myglobals_globals.myArr, "yrt", "燕睿涛");
    hash_key_string_insert(myglobals_globals.myArr, "yanruitao", "燕睿涛");
    
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(myglobals)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(myglobals)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(myglobals)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(myglobals)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "myglobals support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ myglobals_functions[]
 *
 * Every user visible function must have an entry in myglobals_functions[].
 */
const zend_function_entry myglobals_functions[] = {
	PHP_FE(my_test,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in myglobals_functions[] */
};
/* }}} */

/* {{{ myglobals_module_entry
 */
zend_module_entry myglobals_module_entry = {
	STANDARD_MODULE_HEADER,
	"myglobals",
	myglobals_functions,
	PHP_MINIT(myglobals),
	PHP_MSHUTDOWN(myglobals),
	PHP_RINIT(myglobals),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(myglobals),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(myglobals),
	PHP_MYGLOBALS_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYGLOBALS
ZEND_GET_MODULE(myglobals)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
