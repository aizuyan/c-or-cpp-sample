//声明全局变量
static HashTable *test_ini_hash;

//展示全局中的某个变量
PHP_FUNCTION(show_global_zval)
{ 
  /*zval *test_zv;
  MAKE_STD_ZVAL(test_zv);
  Z_TYPE_P(test_zv) = IS_ARRAY;
  Z_ARRVAL_P(test_zv) = test_ini_hash;
*/
  char *name;
  int len;
  
  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &len) == FAILURE) {
    zend_error(E_ERROR, "参数错误，请至少传入一个参数");
  }
  
  zval **ret_val;
  if(zend_hash_find(test_ini_hash, name, len + 1, (void **)&ret_val) == FAILURE) {
    zend_error(E_ERROR, "get test from test_ini_hash error!");
    RETURN_FALSE;
  }
  
  RETURN_ZVAL(*ret_val, 1, 0);
}

//创建一个常驻内存的字符串zval
zval *create_p_zval(const char *str)
{
  zval *tmp;
  int sizeof_str = 0;

  tmp = (zval *)pemalloc(sizeof(zval), 1); 
  sizeof_str = strlen(str) + 1;
  Z_STRVAL_P(tmp) = (char *)pemalloc(sizeof_str, 1); 
  memcpy(Z_STRVAL_P(tmp), str, sizeof_str);
  Z_TYPE_P(tmp) = IS_STRING;
  Z_STRLEN_P(tmp) = sizeof_str;
  return tmp;
}


#define ADD_TO_GOLBAL_ZVAL(name, zv) do{  \
  if(zend_hash_add(test_ini_hash, #name, sizeof(#name), (void *)&zv, sizeof(zval *), NULL) == FAILURE) {  \
    zend_error(E_ERROR, "add a element falied!!");  \
  } \
} while(0)

//将变量添加到全局变量中
PHP_FUNCTION(add_global_zval)
{
  zval *add1 = create_p_zval("Hello World !!!");
  ADD_TO_GOLBAL_ZVAL(test, add1);
  zval *add2 = create_p_zval("Hello World!! What is Eorngsss 是");
  ADD_TO_GOLBAL_ZVAL(what, add2);
  zval *add3 = create_p_zval("你说我是谁啊！！——");
  ADD_TO_GOLBAL_ZVAL(who, add3);
  zval *add4 = create_p_zval("你是哪一位啊，先生~~！~！");
  ADD_TO_GOLBAL_ZVAL(sir, add4);

  RETURN_TRUE;
}

/* {{{ test1_functions[]
 *
 * Every user visible function must have an entry in test1_functions[].
 */
const zend_function_entry test1_functions[] = {
  PHP_FE(show_global_zval,  NULL)   /* For testing, remove later. */
  PHP_FE(add_global_zval, NULL)   /* For testing, remove later. */
  PHP_FE_END  /* Must be the last line in test1_functions[] */
};

//结束之后释放内存
//还有问题TODO
void destory_test_hashtable(HashTable *ht)
{
  Bucket *p, *q; 
  p = ht->pListHead;
  while(p != NULL) {
    q = p->pListNext;
    printf("%s\n", Z_STRVAL_P((zval *)p->pData));
   // pefree(p->pData, 1);
    pefree(p, 1); 
    p = q;
  }
  pefree(ht->arBuckets, 1); 
}
PHP_MSHUTDOWN_FUNCTION(test1)
{
  /* uncomment this line if you have INI entries
  UNREGISTER_INI_ENTRIES();
  */

  destory_test_hashtable(test_ini_hash);
 // zend_hash_destroy(test_ini_hash);
  return SUCCESS;
}



