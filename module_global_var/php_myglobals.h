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

#ifndef PHP_MYGLOBALS_H
#define PHP_MYGLOBALS_H

extern zend_module_entry myglobals_module_entry;
#define phpext_myglobals_ptr &myglobals_module_entry

#define PHP_MYGLOBALS_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_MYGLOBALS_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_MYGLOBALS_API __attribute__ ((visibility("default")))
#else
#	define PHP_MYGLOBALS_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     
*/

PHP_MINIT_FUNCTION(myglobals);
PHP_MSHUTDOWN_FUNCTION(myglobals);
ZEND_FUNCTION(my_test);

typedef struct mybucket {
    char *key;
    char *val;
    struct mybucket *next;
} MyBucket;

ZEND_BEGIN_MODULE_GLOBALS(myglobals)
    MyBucket **myArr;
ZEND_END_MODULE_GLOBALS(myglobals)

//calculate hash by string and keyLen
unsigned long calc_hash(const char *key, unsigned int keyLen);
MyBucket *hash_key_string_insert(MyBucket **arr, const char *key, const char *value);
char *hash_key_string_find(MyBucket **arr, const char *key);
void scan_words_from_dir(const char *dir);
const char *get_key_from_line(const char *line, char *ret);
const char *get_val_from_line(const char *line, char *ret);

#define MAX_READ_WORD_NUM 10
#define MAX_FILE_PATH_SIZE 50
#define MAX_WORD_LINE_SIZE 100
#define MAX_WORD_WORD_SIZE 50

/* In every utility function you add that needs to use variables 
   in php_myglobals_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as MYGLOBALS_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define MYGLOBALS_G(v) TSRMG(myglobals_globals_id, zend_myglobals_globals *, v)
#else
#define MYGLOBALS_G(v) (
#endif

#endif	/* PHP_MYGLOBALS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
