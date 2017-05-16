/* -*- c++ -*- 
   copy[write] by dirlt(dirtysalt1987@gmail.com) */
#ifndef _ODICT_H_
#define _ODICT_H_
/**
 * @file
 * @date   2016.07.07
 * @brief
 *
 */

enum {
    ODB_ADD_OK=0, // ��ӽڵ�ɹ�
    ODB_ADD_ERROR=1,// ��ӽڵ�ʧ�ܣ�δ֪ԭ��
    ODB_ADD_EXISTS=2,// �Ѿ����ڽڵ㵼�����ʧ��
    ODB_ADD_OVERWRITE=3,// �Ѿ����ڵ��¸���ԭ���ڵ�
    ODB_ADD_INVALID=4,// ����ڵ��ǩ����������{0,0}
    
    ODB_DEL_OK=0,// ɾ���ڵ�ɹ�
    ODB_DEL_ERROR=1,// ɾ���ڵ�ʧ�ܣ�δ֪ԭ��
    ODB_DEL_NOT_EXISTS=2,// Ҫɾ���Ľڵ㲻����
    
    ODB_SEEK_OK=0,// �ɹ��ҵ��ڵ�
    ODB_SEEK_ERROR=1,// ���ҽڵ�ʧ�ܣ�δ֪ԭ��
    ODB_SEEK_FAIL=2,// �ڵ㲻����
    
    ODB_MOD_OK=0,// �޸Ľڵ����ݳɹ�
    ODB_MOD_ERROR=1,// �޸Ľڵ�����ʧ�ܣ�δ֪ԭ��
    ODB_MOD_FAIL=2,// �޸Ľڵ����ݴ��󣨽ڵ㲻���ڣ�
    
    ODB_RENEW_OK=0,// ����ֵ�ɹ�
    ODB_RENEW_ERROR=1,// ����ֵ�ʧ�ܣ�δ֪ԭ��

    ODB_SAVE_OK=0,// �����ֵ�ɹ�
    ODB_SAVE_ERROR=1,// �����ֵ�ʧ�ܣ�δ֪ԭ��

    ODB_LOAD_NOT_EXISTS=1,// �����ֵ�ʱָ�����ֵ䲻����
    
    ODB_DESTROY_OK=0,// �ͷ��ֵ���Դ�ɹ�
};

// node number for block i/o
const int ODB_MID_NODE_NUM=4*1024;
// node number in node block
const int ODB_NODE_BLOCK_NUM=256*1024;
// i/o buffer
const unsigned int ODB_IO_BUFFSIZE=4*1024*1024;
// default hash number
const int ODB_DEFAULT_HASH_NUM=1000000;

typedef struct _sodict_snode_t{
    unsigned int sign1;
    unsigned int sign2;
    unsigned int cuint1;
    unsigned int cuint2;
}sodict_snode_t;

typedef struct _sodict128_snode_t{
    unsigned long long sign1;
    unsigned long long sign2;
    unsigned int cuint1;
    unsigned int cuint2;
}sodict128_snode_t;

typedef struct _sodict_build_t sodict_build_t;
typedef struct _sodict_search_t sodict_search_t;
typedef struct _sodict128_build_t sodict128_build_t;
typedef struct _sodict128_search_t sodict128_search_t;

/**
 *  ����һ�����ֵ�,�������㹻ʹ�õ�hash��Ԫ
 *
 *  @param[in]  hash_num  ʹ��hash��Ԫ�ĸ���
 *  @param[out] ��
 *  @return �ֵ��ָ��,���ָ��ͨ����Ϊ������������������,����::odb_add
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @note 1����hash_num>0ʱ,�ֵ佫����hash_num����hash����Ĵ�С;
 *  	  ����,����Ĭ��ֵ����hash����Ĵ�С,Ĭ��ֵΪ1000000
 *  	  2��hash_num����ܳ���(2^31-1)��
 */
sodict_build_t *odb_creat(int hash_num);

/**
 *  ����::odb_creat,����һ���ֵ�,���ҽ�ָ�����ļ�����load���ֵ���
 *
 *  @param[in]  path      load�ļ���·��
 *  @param[in]  filename  load�ļ����ļ���
 *  @param[in]  hash_num  ʹ��hash��Ԫ�ĸ���
 *  @param[out] ��
 *  @return �ֵ��ָ��,���ָ��ͨ����Ϊ������������������,����::odb_add
 * - ODB_LOAD_NOT_EXISTS   ָ��������ļ�������
 * - NULL                  load�ļ�ʧ��,�п����Ǵ����ֵ����,����ļ������
 * - ��������ֵ            �ֵ��ָ��
 *  @note 1����hash_num>0ʱ,�ֵ佫����hash_num����hash����Ĵ�С,
 *  		����,�����ƶ��ļ��е�ǰ�洢�����ݵ�Ԫ��������hash��Ԫ����
 *  	  2��hash_num����ܳ���(2^31-1)��
 */
sodict_build_t *odb_load(char *path, char *filename, int hash_num);



/**
 *  ����::odb_load,������������������ֻ����ѯ�õ��ֵ�
 *
 *  @param[in]  path      load�ļ���·��
 *  @param[in]  filename  load�ļ����ļ���
 *  @param[out] ��
 *  @return     �ֵ��ָ��
 * - ODB_LOAD_NOT_EXISTS   �ļ�������
 * - NULL                  load�ļ�ʧ��,�п����Ǵ����ֵ����,����ļ������
 * - ��������ֵ            �ֵ��ָ��
 */
sodict_search_t *odb_load_search(char *path, char *filename);


/**
 * @brief
 * ʹ��mmap��ʽ���ֵ��ļ������ڹ����ڴ�
 * @param [in/out] path   : char*
 * @param [in/out] filename   : char*
 * @return  sodict_search_t*
 * @retval
 * - ODB_LOAD_NOT_EXISTS   �ļ�������
 * - NULL                  load�ļ�ʧ��,�п����Ǵ����ֵ����,����ļ������
 * - ��������ֵ            �ֵ��ָ��
 * @see
 * @author yufan
 * @date 2008/10/22 19:40:59
**/
sodict_search_t *odb_load_search_mmap(char *path, char *filename);

/**
 * @brief
 * �ͷ�ʹ��odb_load_search_mmap�������ֵ�
 * @param [in/out] sdb   : sodict_search_t*
 * @return     ODB_DESTROY_OK
 * @see
 * @author yufan
 * @date 2008/10/22 20:04:24
**/
int odb_destroy_search_mmap(sodict_search_t *sdb);
/**
 *  �ͷ��ֵ���Դ
 *
 *  @param[in]  sdb      �ֵ�ָ��
 *  @param[out] ��
 *  @return     ODB_DESTROY_OK
 */
int odb_destroy(sodict_build_t *sdb);


/**
 *  �ͷ�ֻ���ֵ���Դ
 *
 *  @param[in]  sdb      �ֵ�ָ��
 *  @param[out] ��
 *  @return     ODB_DESTROY_OK
 */
int odb_destroy_search(sodict_search_t *sdb);


/**
 *  �����ֵ䵽ָ�����ļ���
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  path      �ļ���·��
 *  @param[in]  filename  �ļ���
 *  @param[out] ��
 *  @return     �����Ƿ�ɹ�
 * - ODB_SAVE_OK      ����ɹ�
 * - ODB_SAVE_ERROR   ����ʧ��
 */
int odb_save(sodict_build_t *sdb, char *path, char *filename);



/**
 *  �����ֵ䵽ָ�����ļ���,����odb_save��ֻ���ֻ���ֵ�
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  path      �ļ���·��
 *  @param[in]  filename  �ļ���
 *  @param[out] ��
 *  @return     �����Ƿ�ɹ�
 * - ODB_SAVE_OK      ����ɹ�
 * - ODB_SAVE_ERROR   ����ʧ��
 */
int odb_save_search(sodict_search_t *sdb, char *path, char *filename);




/**
 *  ����::odb_save,�����ֵ䵽ָ�����ļ���,��ͬ����,������ȷ�����ļ���������
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  path      �ļ���·��
 *  @param[in]  filename  �ļ���
 *  @param[out] ��
 *  @return     �����Ƿ�ɹ�
 * - ODB_SAVE_OK      ����ɹ�
 * - ODB_SAVE_ERROR   ����ʧ��
 *  @note ��ͬ�����ļ�����ʱ,���ļ������".odb.ss."ǰ׺,�����󱣴�
 */
int odb_save_safely(sodict_build_t *sdb, char *path, char *filename);


/**
 *  ����::odb_save_search,����ֻ���ֵ䵽ָ�����ļ���,��ͬ����,������ȷ�����ļ���������
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  path      �ļ���·��
 *  @param[in]  filename  �ļ���
 *  @param[out] ��
 *  @return     �����Ƿ�ɹ�
 * - ODB_SAVE_OK      ����ɹ�
 * - ODB_SAVE_ERROR   ����ʧ��
 *  @note ��ͬ�����ļ�����ʱ,���ļ������".odb.ss."ǰ׺,�����󱣴�
 */

int odb_save_search_safely(sodict_search_t *sdb, char *path, char *filename);
/**
 *  ��յ�ǰdict����������,dict�ָ���odb_creat���ú�ʱ��״̬
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[out] ��
 *  @return     ״̬��Ϣ
 * - ODB_RENEW_OK      �ɹ�
 * - ODB_RENEW_ERROR   ʧ��
 *  @note ������ODB_RENEW_ERRORʱ,dict�п����Ѿ�������,���,�ٴ�ʹ��sdbָ���Ƿǳ�Σ�յ�,���������
 */
int odb_renew(sodict_build_t *sdb);



/**
 *  ��::odb_renew��ͬ,Ϊ�����¼��ݶ�����
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[out] ��
 *  @return     ״̬��Ϣ
 * - ODB_RENEW_OK      �ɹ�
 * - ODB_RENEW_ERROR   ʧ��
 *  @note ������ODB_RENEW_ERRORʱ,dict�п����Ѿ�������,���,�ٴ�ʹ��sdbָ���Ƿǳ�Σ�յ�,���������
 */
int odb_renew_ex(sodict_build_t *sdb);


/**
 *  ��dict���һ���ڵ�
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  snode     ��ӵĽڵ�����
 *  @param[in]  overwrite_if_exists       ���Ǳ�־,���overwrite_if_exists!=0,��dict������ͬ�ڵ�ʱ,���Ḳ��ԭ��ֵ,������ODB_ADD_OVERWRITE,���򷵻�ODB_ADD_EXISTS
 *  @param[out] ��
 *  @return     ״̬��Ϣ
 * - ODB_ADD_OK      dict�в����ڸýڵ�,���Ҳ���ɹ�
 * - ODB_ADD_ERROR   �������ʧ��
 * - ODB_ADD_OVERWRITE   dict���Ѿ�����ͬǩ��������,���Ҹ��Ǳ�־overwrite_if_exists!=0,ԭ���ݽڵ㱻����
 * - ODB_ADD_EXISTS   dict���Ѿ�����ͬǩ��������,���Ҹ��Ǳ�־overwrite_if_exists==0,ԭ���ݽڵ㱣��,�����������
 * - ODB_ADD_INVALID  �������ݲ��Ϸ���snode��ǩ����������{0,0}
 *   @notice	hash�ֵ���������Ŀ��������ܳ���(2^31-1)
 */
int odb_add(sodict_build_t *sdb, sodict_snode_t *snode, int overwrite_if_exists);


/**
 *  ���ָ���ڵ����,��dict��ɾ��ָ���ڵ�
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  snode     Ҫɾ���Ľڵ�
 *  @param[out] ��
 *  @return     ״̬��Ϣ
 * - ODB_DEL_OK      dict�д��ڸýڵ�,����ɾ���ɹ�
 * - ODB_DEL_NOT_EXISTS   dict���޴�����
 * - ODB_DEL_ERROR ɾ��ʧ��snode��sign1��sign2Ϊ0
 */
int odb_del(sodict_build_t *sdb, sodict_snode_t *snode);


/**
 *  ��dict�в���ָ���ڵ������
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  snode     Ҫ���ҵĽڵ�
 *  @param[out] snode     ����ҵ�,���ڵ����ݴ洢�˴�
 *  @return     ״̬��Ϣ
 * - ODB_SEEK_OK      ��dict���ҵ�ָ���ڵ�,�����ڵ����������snode��
 * - ODB_SEEK_FAIL    dict���޴�����
 */
int odb_seek(sodict_build_t *sdb, sodict_snode_t *snode);


/**
 *  ��ֻ��dict�в���ָ���ڵ������
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  snode     Ҫ���ҵĽڵ�
 *  @param[out] snode     ����ҵ�,���ڵ����ݴ洢�˴�
 *  @return     ״̬��Ϣ
 * - ODB_SEEK_OK      ��dict���ҵ�ָ���ڵ�,�����ڵ����������snode��
 * - ODB_SEEK_FAIL    dict���޴�����
 */
int odb_seek_search(sodict_search_t *sdb, sodict_snode_t *snode);



/**
 *  ��dict���޸�ָ���ڵ����Ϣ
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  snode     Ҫ���ҵĽڵ�
 *  @param[out] ��
 *  @return     ״̬��Ϣ
 * - ODB_MOD_OK       ��dict���ҵ�ָ���ڵ�,���޸��˽ڵ��е�����
 * - ODB_MOD_FAIL     ��dict��δ�ҵ�ָ���ڵ�
 */
int odb_mod(sodict_build_t *sdb, sodict_snode_t *snode);


/**
 *  �����ֵ������е�Ԫ
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[in]  include_deleted     �Ƿ������ɾ���ڵ�
 *  @param[in]  traverse_handler    �������̽��о�������ĺ������
 *  @param[out] ��
 *  @return     ��
 *  @note
 *  traverse_handler�������ݱ��������������,���в���snodeΪ�������̵�һ���ڵ�,stop_now�����������������ֹͣ����������
 */
void odb_traverse(sodict_build_t *sdb, int include_deleted,
                  void (*traverse_handler)(sodict_snode_t *snode, int *stop_now));



/**
 *  �����ֵ������е�Ԫ(���ڱ����������������Ӵ������)
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[in]  include_deleted     �Ƿ������ɾ���ڵ�
 *  @param[in]  traverse_handler    �������̽��о�������ĺ������
 *  @param[in]  ex_arg              ���������������Ĳ���
 *  @param[out] ��
 *  @return     ��
 *  @note traverse_handler�������ݱ��������������,���в���snodeΪ�������̵�һ���ڵ�,stop_now�����������������ֹͣ����������
 */
void odb_traverse_ex(sodict_build_t *sdb, int include_deleted,
                     void (*traverse_handler)(sodict_snode_t *snode, int *stop_now, void *arg), void *ex_arg);



/**
 *  ����ֻ���ֵ������е�Ԫ
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[in]  traverse_handler    �������̽��о�������ĺ������
 *  @param[out] ��
 *  @return     ��
 *  @note traverse_handler�������ݱ��������������,���в���snodeΪ�������̵�һ���ڵ�,stop_now�����������������ֹͣ����������
 */
void odb_traverse_search(sodict_search_t *sdb, void (*traverse_handler)(sodict_snode_t *snode, int *stop_now));

/**
 *  ����ֻ���ֵ������е�Ԫ(���ڱ����������������Ӵ������)
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[in]  traverse_handler    �������̽��о�������ĺ������
 *  @param[out] ��
 *  @return     ��
 *  @note traverse_handler�������ݱ��������������,���в���snodeΪ�������̵�һ���ڵ�,stop_now�����������������ֹͣ����������
 */
void odb_traverse_search_ex(sodict_search_t *sdb, void (*traverse_handler)(sodict_snode_t *snode, int *stop_now,void *arg),
                            void *ex_arg);
/**
 *  ����ֵ䵱ǰ״̬(debugʱʹ��)
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[out] ��
 *  @return     ��
 */
void odb_build_report(sodict_build_t *sdb);


/**
 *  ���ֻ���ֵ䵱ǰ״̬(debugʱʹ��)
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[out] ��
 *  @return     ��
 */
void odb_search_report(sodict_search_t *sdb);

/**
 * �õ��ֵ�ʵ��ʹ�õĽڵ���
 *
 * @param[in] sdb   �ֵ�ָ��
 * @return	    ʵ�ʽڵ���
 */
int odb_get_nodenum(sodict_build_t *sdb);

int odb_search_get_nodenum(sodict_search_t *sdb);

/**
 * �õ�hash�Ĵ�С
 * @param[in] sdb   �ֵ�ָ��
 * @return          ʵ��hash��С
 */
int odb_get_hashnum(sodict_build_t *sdb);

int odb_search_get_hashnum(sodict_search_t *sdb);

/**
 * ���ݵ�ǰ�ֵ��нڵ���������ֵ�hash����������߲�ѯ����
 *
 * @param[in] sdb   �ֵ�ָ��
 * @return          0:�ɹ���-1:ʧ��
 */
int odb_adjust(sodict_build_t *sdb);

/**
 * ����ֻ���ֵ䣬�Ƚ�sdb1��sdb2�Ƿ���ȫ��ͬ�������ֵ���ȫ��ͬ����Ҫ���ֵ��������ȫ��ͬ��ÿ��
 * hashͰ��Ԫ��˳��ҲҪ��ͬ��
 *
 * @param[in] sdb1 �ֵ�ָ��
 * @param[in] sdb2 �ֵ�ָ��
 * @return  1 ���ֵ���ȫ��ͬ, 0 ���ֵ䲻��ͬ
 */

int odb_is_equal_search(sodict_search_t *sdb1, sodict_search_t *sdb2);


/**
 *  ����һ�����ֵ�,�������㹻ʹ�õ�hash��Ԫ
 *
 *  @param[in]  hash_num  ʹ��hash��Ԫ�ĸ���
 *  @param[out] ��
 *  @return �ֵ��ָ��,���ָ��ͨ����Ϊ������������������,����::odb_add
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @note 1����hash_num>0ʱ,�ֵ佫����hash_num����hash����Ĵ�С,
 *  		����,����Ĭ��ֵ����hash����Ĵ�С,Ĭ��ֵΪ1000000
 *  	  2��hash_num����ܳ���2^31-1��
 */
sodict128_build_t *odb128_creat(int hash_num);




/**
 *  ����::odb128_creat,����һ���ֵ�,���ҽ�ָ�����ļ�����load���ֵ���
 *
 *  @param[in]  path      load�ļ���·��
 *  @param[in]  filename  load�ļ����ļ���
 *  @param[in]  hash_num  ʹ��hash��Ԫ�ĸ���
 *  @param[out] ��
 *  @return �ֵ��ָ��,���ָ��ͨ����Ϊ������������������,����::odb_add
 * - ODB_LOAD_NOT_EXISTS   ָ��������ļ�������
 * - NULL                  load�ļ�ʧ��,�п����Ǵ����ֵ����,����ļ������
 * - ��������ֵ            �ֵ��ָ��
 *  @note 1����hash_num>0ʱ,�ֵ佫����hash_num����hash����Ĵ�С,
 *  		����,�����ƶ��ļ��е�ǰ�洢�����ݵ�Ԫ��������hash��Ԫ����
 *  	  2��hash_num����ܳ���2^31-1��
 */
sodict128_build_t *odb128_load(char *path, char *filename, int hash_num);



/**
 *  ����::odb128_load,������������������ֻ����ѯ�õ��ֵ�
 *
 *  @param[in]  path      load�ļ���·��
 *  @param[in]  filename  load�ļ����ļ���
 *  @param[out] ��
 *  @return     �ֵ��ָ��
 * - ODB_LOAD_NOT_EXISTS   �ļ�������
 * - NULL                  load�ļ�ʧ��,�п����Ǵ����ֵ����,����ļ������
 * - ��������ֵ            �ֵ��ָ��
 */
sodict128_search_t *odb128_load_search(char *path, char *filename);


/**
 * @brief
 * ʹ��mmap��ʽ���ֵ��ļ������ڹ����ڴ�
 * @param [in/out] path   : char*
 * @param [in/out] filename   : char*
 * @return  sodict128_search_t*
 * @retval
 * - ODB_LOAD_NOT_EXISTS   �ļ�������
 * - NULL                  load�ļ�ʧ��,�п����Ǵ����ֵ����,����ļ������
 * - ��������ֵ            �ֵ��ָ��
 * @see
 * @author yufan
 * @date 2008/10/22 19:40:59
**/
sodict128_search_t *odb128_load_search_mmap(char *path, char *filename);

/**
 * @brief
 * �ͷ�ʹ��odb_load_search_mmap�������ֵ�
 * @param [in/out] sdb   : sodict128_search_t*
 * @return     ODB_DESTROY_OK
 * @see
 * @author yufan
 * @date 2008/10/22 20:04:24
**/
int odb_destroy_search_mmap(sodict128_search_t *sdb);
/**
 *  �ͷ��ֵ���Դ
 *
 *  @param[in]  sdb      �ֵ�ָ��
 *  @param[out] ��
 *  @return     ODB_DESTROY_OK
 */
int odb_destroy(sodict128_build_t *sdb);


/**
 *  �ͷ�ֻ���ֵ���Դ
 *
 *  @param[in]  sdb      �ֵ�ָ��
 *  @param[out] ��
 *  @return     ODB_DESTROY_OK
 */
int odb_destroy_search(sodict128_search_t *sdb);


/**
 *  �����ֵ䵽ָ�����ļ���
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  path      �ļ���·��
 *  @param[in]  filename  �ļ���
 *  @param[out] ��
 *  @return     �����Ƿ�ɹ�
 * - ODB_SAVE_OK      ����ɹ�
 * - ODB_SAVE_ERROR   ����ʧ��
 */
int odb_save(sodict128_build_t *sdb, char *path, char *filename);



/**
 *  �����ֵ䵽ָ�����ļ���,����odb_save��ֻ���ֻ���ֵ�
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  path      �ļ���·��
 *  @param[in]  filename  �ļ���
 *  @param[out] ��
 *  @return     �����Ƿ�ɹ�
 * - ODB_SAVE_OK      ����ɹ�
 * - ODB_SAVE_ERROR   ����ʧ��
 */
int odb_save_search(sodict128_search_t *sdb, char *path, char *filename);




/**
 *  ����::odb_save,�����ֵ䵽ָ�����ļ���,��ͬ����,������ȷ�����ļ���������
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  path      �ļ���·��
 *  @param[in]  filename  �ļ���
 *  @param[out] ��
 *  @return     �����Ƿ�ɹ�
 * - ODB_SAVE_OK      ����ɹ�
 * - ODB_SAVE_ERROR   ����ʧ��
 *  @note ��ͬ�����ļ�����ʱ,���ļ������".odb.ss."ǰ׺,�����󱣴�
 */
int odb_save_safely(sodict128_build_t *sdb, char *path, char *filename);


/**
 *  ����::odb_save_search,����ֻ���ֵ䵽ָ�����ļ���,��ͬ����,������ȷ�����ļ���������
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  path      �ļ���·��
 *  @param[in]  filename  �ļ���
 *  @param[out] ��
 *  @return     �����Ƿ�ɹ�
 * - ODB_SAVE_OK      ����ɹ�
 * - ODB_SAVE_ERROR   ����ʧ��
 *  @note ��ͬ�����ļ�����ʱ,���ļ������".odb.ss."ǰ׺,�����󱣴�
 */

int odb_save_search_safely(sodict128_search_t *sdb, char *path, char *filename);
/**
 *  ��յ�ǰdict����������,dict�ָ���odb_creat���ú�ʱ��״̬
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[out] ��
 *  @return     ״̬��Ϣ
 * - ODB_RENEW_OK      �ɹ�
 * - ODB_RENEW_ERROR   ʧ��
 *  @note ������ODB_RENEW_ERRORʱ,dict�п����Ѿ�������,���,�ٴ�ʹ��sdbָ���Ƿǳ�Σ�յ�,���������
 */
int odb_renew(sodict128_build_t *sdb);



/**
 *  ��::odb_renew��ͬ,Ϊ�����¼��ݶ�����
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[out] ��
 *  @return     ״̬��Ϣ
 * - ODB_RENEW_OK      �ɹ�
 * - ODB_RENEW_ERROR   ʧ��
 *  @note ������ODB_RENEW_ERRORʱ,dict�п����Ѿ�������,���,�ٴ�ʹ��sdbָ���Ƿǳ�Σ�յ�,���������
 */
int odb_renew_ex(sodict128_build_t *sdb);


/**
 *  ��dict���һ���ڵ�
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  snode     ��ӵĽڵ�����
 *  @param[in]  overwrite_if_exists       ���Ǳ�־,���overwrite_if_exists!=0,��dict������ͬ�ڵ�ʱ,���Ḳ��ԭ��ֵ,������ODB_ADD_OVERWRITE,���򷵻�ODB_ADD_EXISTS
 *  @param[out] ��
 *  @return     ״̬��Ϣ
 * - ODB_ADD_OK      dict�в����ڸýڵ�,���Ҳ���ɹ�
 * - ODB_ADD_ERROR   �������ʧ��
 * - ODB_ADD_OVERWRITE   dict���Ѿ�����ͬǩ��������,���Ҹ��Ǳ�־overwrite_if_exists!=0,ԭ���ݽڵ㱻����
 * - ODB_ADD_EXISTS   dict���Ѿ�����ͬǩ��������,���Ҹ��Ǳ�־overwrite_if_exists==0,ԭ���ݽڵ㱣��,�����������
 * - ODB_ADD_INVALID  �������ݲ��Ϸ���snode��ǩ����������{0,0}
 */
int odb_add(sodict128_build_t *sdb, sodict128_snode_t *snode, int overwrite_if_exists);


/**
 *  ���ָ���ڵ����,��dict��ɾ��ָ���ڵ�
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  snode     Ҫɾ���Ľڵ�
 *  @param[out] ��
 *  @return     ״̬��Ϣ
 * - ODB_DEL_OK      dict�д��ڸýڵ�,����ɾ���ɹ�
 * - ODB_DEL_NOT_EXISTS   dict���޴�����
 * - ODB_DEL_ERROR ɾ��ʧ��snode��sign1��sign2Ϊ0
 */
int odb_del(sodict128_build_t *sdb, sodict128_snode_t *snode);


/**
 *  ��dict�в���ָ���ڵ������
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  snode     Ҫ���ҵĽڵ�
 *  @param[out] snode     ����ҵ�,���ڵ����ݴ洢�˴�
 *  @return     ״̬��Ϣ
 * - ODB_SEEK_OK      ��dict���ҵ�ָ���ڵ�,�����ڵ����������snode��
 * - ODB_SEEK_FAIL    dict���޴�����
 */
int odb_seek(sodict128_build_t *sdb, sodict128_snode_t *snode);


/**
 *  ��ֻ��dict�в���ָ���ڵ������
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  snode     Ҫ���ҵĽڵ�
 *  @param[out] snode     ����ҵ�,���ڵ����ݴ洢�˴�
 *  @return     ״̬��Ϣ
 * - ODB_SEEK_OK      ��dict���ҵ�ָ���ڵ�,�����ڵ����������snode��
 * - ODB_SEEK_FAIL    dict���޴�����
 */
int odb_seek_search(sodict128_search_t *sdb, sodict128_snode_t *snode);



/**
 *  ��dict���޸�ָ���ڵ����Ϣ
 *
 *  @param[in]  sdb       �ֵ�ָ��
 *  @param[in]  snode     Ҫ���ҵĽڵ�
 *  @param[out] ��
 *  @return     ״̬��Ϣ
 * - ODB_MOD_OK       ��dict���ҵ�ָ���ڵ�,���޸��˽ڵ��е�����
 * - ODB_MOD_FAIL     ��dict��δ�ҵ�ָ���ڵ�
 */
int odb_mod(sodict128_build_t *sdb, sodict128_snode_t *snode);


/**
 *  �����ֵ������е�Ԫ
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[in]  include_deleted     �Ƿ������ɾ���ڵ�
 *  @param[in]  traverse_handler    �������̽��о�������ĺ������
 *  @param[out] ��
 *  @return     ��
 *  @note
 *  traverse_handler�������ݱ��������������,���в���snodeΪ�������̵�һ���ڵ�,stop_now�����������������ֹͣ����������
 */
void odb_traverse(sodict128_build_t *sdb, int include_deleted,
                  void (*traverse_handler)(sodict128_snode_t *snode, int *stop_now));



/**
 *  �����ֵ������е�Ԫ(���ڱ����������������Ӵ������)
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[in]  include_deleted     �Ƿ������ɾ���ڵ�
 *  @param[in]  traverse_handler    �������̽��о�������ĺ������
 *  @param[in]  ex_arg              ���������������Ĳ���
 *  @param[out] ��
 *  @return     ��
 *  @note traverse_handler�������ݱ��������������,���в���snodeΪ�������̵�һ���ڵ�,stop_now�����������������ֹͣ����������
 */
void odb_traverse_ex(sodict128_build_t *sdb, int include_deleted,
                     void (*traverse_handler)(sodict128_snode_t *snode, int *stop_now, void *arg), void *ex_arg);



/**
 *  ����ֻ���ֵ������е�Ԫ
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[in]  traverse_handler    �������̽��о�������ĺ������
 *  @param[out] ��
 *  @return     ��
 *  @note traverse_handler�������ݱ��������������,���в���snodeΪ�������̵�һ���ڵ�,stop_now�����������������ֹͣ����������
 */
void odb_traverse_search(sodict128_search_t *sdb, void (*traverse_handler)(sodict128_snode_t *snode, int *stop_now));

/**
 *  ����ֻ���ֵ������е�Ԫ(���ڱ����������������Ӵ������)
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[in]  traverse_handler    �������̽��о�������ĺ������
 *  @param[out] ��
 *  @return     ��
 *  @note traverse_handler�������ݱ��������������,���в���snodeΪ�������̵�һ���ڵ�,stop_now�����������������ֹͣ����������
 */
void odb_traverse_search_ex(sodict128_search_t *sdb, void (*traverse_handler)(sodict128_snode_t *snode, int *stop_now,void *arg),
                            void *ex_arg);
/**
 *  ����ֵ䵱ǰ״̬(debugʱʹ��)
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[out] ��
 *  @return     ��
 */
void odb_build_report(sodict128_build_t *sdb);


/**
 *  ���ֻ���ֵ䵱ǰ״̬(debugʱʹ��)
 *
 *  @param[in]  sdb                 �ֵ�ָ��
 *  @param[out] ��
 *  @return     ��
 */
void odb_search_report(sodict128_search_t *sdb);

/**
 * �õ��ֵ�ʵ��ʹ�õĽڵ���
 *
 * @param[in] sdb   �ֵ�ָ��
 * @return	    ʵ�ʽڵ���
 */
int odb_get_nodenum(sodict128_build_t *sdb);

int odb_search_get_nodenum(sodict128_search_t *sdb);

/**
 * �õ�hash�Ĵ�С
 * @param[in] sdb   �ֵ�ָ��
 * @return          ʵ��hash��С
 */
int odb_get_hashnum(sodict128_build_t *sdb);

int odb_search_get_hashnum(sodict128_search_t *sdb);

/**
 * ���ݵ�ǰ�ֵ��нڵ���������ֵ�hash����������߲�ѯ����
 *
 * @param[in] sdb   �ֵ�ָ��
 * @return          0:�ɹ���-1:ʧ��
 */
int odb_adjust(sodict128_build_t *sdb);

/**
 * ����ֻ���ֵ䣬�Ƚ�sdb1��sdb2�Ƿ���ȫ��ͬ�������ֵ���ȫ��ͬ����Ҫ���ֵ��������ȫ��ͬ��ÿ��
 * hashͰ��Ԫ��˳��ҲҪ��ͬ��
 *
 * @param[in] sdb1 �ֵ�ָ��
 * @param[in] sdb2 �ֵ�ָ��
 * @return  1 ���ֵ���ȫ��ͬ, 0 ���ֵ䲻��ͬ
 */
int odb_is_equal_search(sodict128_search_t *sdb1, sodict128_search_t *sdb2);

#endif
