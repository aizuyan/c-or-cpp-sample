### ZEND_HASH_FOREACH_STR_KEY_VAL展开
```c
ZEND_HASH_FOREACH_STR_KEY_VAL(ht, key, element) {

} ZEND_HASH_FOREACH_END();
```
展开之后为：
```c
do{
  Bucket *_p = (ht)->arData;
  Bucket *_end = _p + (ht)->nNumUsed;
  for(;_p != _end; _p++) {
    zval *_z = &_p->val;
    if(UNEXPECTED(Z_TYPE_P(_z)) == IS_UNDEF)
      continue;
    key = _p->key;
    element = _z;
  }
}while(0);
```

PHP_FUNCTION(test_foreach)
{
  HashTable *arr;

  if (zend_parse_parameters(ZEND_NUM_ARGS(), "h", &arr) == FAILURE) {
    return;
  }

  zend_string *key;
  zval *element;
  Bucket *bucket;

  ZEND_HASH_FOREACH_BUCKET(arr, bucket) {
    if(bucket->key) {
      printf("键值为字符串：%s\n", bucket->key->val);
    }else{
      printf("键值为数字：%d\n", bucket->h);
    }
  }ZEND_HASH_FOREACH_END();

  ZEND_HASH_FOREACH_STR_KEY_VAL(arr, key, element) {
    if(key){
      printf("键=>%s", key->val);
    }
    if(element) {
        switch(Z_TYPE_P(element))
        {
          case IS_STRING:
            printf(" string=>%s\n", element->value.str->val);
            break;
          case IS_NULL:
            printf(" null=>NULL\n");
            break;
          case IS_LONG:
            printf(" long=>%ld\n", element->value.lval);
            break;
          case IS_DOUBLE:
            printf(" double=>%lf\n", element->value.dval);
            break;
        }
    }else {
        printf("\t none=>非字符串、NULL、LONG、DOUBLE");
    }
  }ZEND_HASH_FOREACH_END();

  RETURN_TRUE;
}

## php里面调用自己定义的函数
PHP_FUNCTION(test_call_func)
{
  zval retval;
  zend_fcall_info fci;
  zend_fcall_info_cache fci_cache;

  if(zend_parse_parameters(ZEND_NUM_ARGS(), "f*", &fci, &fci_cache, &fci.params, &fci.param_count) == FAILURE) {
    return ;
  }

  fci.retval = &retval;

  if(zend_call_function(&fci, &fci_cache) == SUCCESS && Z_TYPE(retval) != IS_UNDEF) {
    ZVAL_COPY_VALUE(return_value, &retval);
  }

}
