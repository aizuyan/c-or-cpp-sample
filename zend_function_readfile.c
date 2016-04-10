/**
 * 1. 扫描文件夹中的文件
 * 2. 读取文件中的内容，并存放的数组中返回给用户
 *
 */
PHP_FUNCTION(myscandir)
{
    zend_string *dirname;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &dirname) == FAILURE) {
        return;
    }   

    HashTable *ht;
    ht = (HashTable*)pemalloc(sizeof(HashTable), 0); 
    zend_hash_init(ht, 100, 0, 0, 0); 
    FILE *fp = VCWD_FOPEN(dirname->val, "r");
    char msg[200] = {0};
    int index = 3;
    while(fgets(msg, 200, fp))
    {   
        msg[strlen(msg) - 1] = '\0';
        zval tmp;
        zend_string *index_val = zend_string_init(msg, strlen(msg), 0); 
        ZVAL_STR(&tmp, index_val);
        zend_hash_index_add(ht, index++, &tmp);
    };  

    fclose(fp);
    /*struct dirent **namelist;
    int ndir;
    ndir = php_scandir(dirname->val, &namelist, 0, 0);
    int i = 0;
    for(;i<ndir;i++)
    {
        zend_string *key = zend_string_init(namelist[i]->d_name, strlen(namelist[i]->d_name), 0);
        free(namelist[i]);
        zval tmp;
        ZVAL_STR(&tmp, key);
        zend_hash_update(ht, key, &tmp);
    }
    free(namelist);*/
    RETURN_ARR(ht);
}
