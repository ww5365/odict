#include <cassert>
#include <cstdlib>
#include <cstdio>
#include "odict.h"

const int hash_num=100;
const unsigned int start=1;
const unsigned int end=2;
const unsigned int end2=200;

int shutdown(){
    system("rm -rf fuck.n fuck.ind1 fuck.ind2");
    return 0;
}

int add(sodict_build_t *dict){
    sodict_snode_t node;
    unsigned int i=0;
    unsigned int j=0;
    for(j=start;j<end;j++){
        node.sign1=i;
        node.sign2=j;
        node.cuint1=i+1;
        node.cuint2=j+1;
        assert(odb_add(dict,&node,0)==ODB_ADD_OK);
    }
    return 0;
}

void handler_ex(sodict_snode_t *snode,int *stop_now,void *ex_arg){
    assert(snode->sign1==(snode->cuint1-1));
    assert(snode->sign2==(snode->cuint2-1));
    *stop_now=0;
    return ;
}
void handler(sodict_snode_t *snode,int *stop_now){
    assert(snode->sign1==(snode->cuint1-1));
    assert(snode->sign2==(snode->cuint2-1));
    *stop_now=0;
    return ;
}
int traverse_ex(sodict_build_t *dict){
    odb_traverse_ex(dict,0,handler_ex,NULL);
    return 0;
}
int traverse(sodict_build_t *dict){
    odb_traverse(dict,0,handler);
    return 0;
}
int traverse_search_ex(sodict_search_t *search){
    odb_traverse_search_ex(search,handler_ex,NULL);
    return 0;
}
int traverse_search(sodict_search_t *search){
    odb_traverse_search(search,handler);
    return 0;
}
int del(sodict_build_t *dict){
    sodict_snode_t node;
    unsigned int i=0;
    unsigned int j=0;
    for(j=start;j<end;j++){
        node.sign1=i;
        node.sign2=j;
        assert(odb_del(dict,&node)==ODB_ADD_OK);
    }
    for(j=end;j<end2;j++){
        node.sign1=i;
        node.sign2=j;
        assert(odb_del(dict,&node)==ODB_DEL_NOT_EXISTS);
    }
    node.sign1=0;
    node.sign2=0;
    assert(odb_del(dict,&node)==ODB_DEL_ERROR);
    return 0;
}

int check(sodict_build_t *dict){
    sodict_snode_t node;
    unsigned int i=0;
    unsigned int j=0;
    for(j=start;j<end;j++){
        node.sign1=i;
        node.sign2=j;
        assert(odb_seek(dict,&node)==ODB_SEEK_OK);
    }
    for(j=end;j<end2;j++){
        node.sign1=i;
        node.sign2=j;
        assert(odb_seek(dict,&node)==ODB_SEEK_FAIL);
    }
    assert(odb_get_nodenum(dict)==(end-start));
    assert(odb_get_hashnum(dict)==hash_num);
    return 0;
}

int check_search(sodict_search_t *dict){
    sodict_snode_t node;
    unsigned int i=0;
    unsigned int j=0;
    for(j=start;j<end;j++){
        node.sign1=i;
        node.sign2=j;
        assert(odb_seek_search(dict,&node)==ODB_SEEK_OK);
    }
    for(j=end;j<end2;j++){
        node.sign1=i;
        node.sign2=j;
        assert(odb_seek_search(dict,&node)==ODB_SEEK_FAIL);
    }
    assert(odb_search_get_nodenum(dict)==(end-start));
    assert(odb_search_get_hashnum(dict)==hash_num);
    return 0;
}

int mod(sodict_build_t *dict){
    sodict_snode_t node;
    unsigned int i=0;
    unsigned int j=0;
    for(j=start;j<end;j++){
        node.sign1=i;
        node.sign2=j;
        node.cuint1=i+1;
        node.cuint2=j+1;
        assert(odb_mod(dict,&node)==ODB_MOD_OK);
    }
    for(j=end;j<end2;j++){
        node.sign1=i;
        node.sign2=j;
        assert(odb_seek(dict,&node)==ODB_MOD_FAIL);
    }
    return 0;
}

int check_renew(sodict_build_t *dict){
    sodict_snode_t node;
    unsigned int i=0;
    unsigned int j=0;
    for(j=0;j<100;j++){
        node.sign1=i;
        node.sign2=j;
        assert(odb_seek(dict,&node)==ODB_SEEK_FAIL);
    }
    assert(odb_get_nodenum(dict)==0);
    assert(odb_get_hashnum(dict)==hash_num);
    return 0;
}

int save(sodict_build_t *dict){
    shutdown();
    assert(odb_save(dict,".","fuck")==ODB_SAVE_OK);
    return 0;
}

int save_safely(sodict_build_t *dict){
    shutdown();
    assert(odb_save_safely(dict,".","fuck")==ODB_SAVE_OK);
    return 0;
}

sodict_build_t *load(){
    sodict_build_t *res=odb_load(".","fuck",hash_num);
    assert(res && ((int)(long long)res!=ODB_LOAD_NOT_EXISTS));
    return res;
}

int save_search(sodict_search_t *search){
    shutdown();
    assert(odb_save_search(search,".","fuck")==ODB_SAVE_OK);
    return 0;
}

int save_search_safely(sodict_search_t *search){
    shutdown();
    assert(odb_save_search_safely(search,".","fuck")==ODB_SAVE_OK);
    return 0;
}

sodict_search_t *load_search(){
    sodict_search_t *res=odb_load_search(".","fuck");
    assert(res && ((int)(long long)res!=ODB_LOAD_NOT_EXISTS));
    return res;
}

sodict_search_t *load_search_mmap(){
    sodict_search_t *res=odb_load_search_mmap(".","fuck");
    assert(res && ((int)(long long)res!=ODB_LOAD_NOT_EXISTS));
    return res;
}

int test_odb(){
    sodict_build_t *dict=NULL;
    sodict_search_t *search=NULL;
    sodict_search_t *search2=NULL;
    {
        dict=odb_creat(hash_num);
        assert(dict);
        add(dict);
        traverse_ex(dict);
        traverse(dict);
        check(dict);
        mod(dict);
        check(dict);
        save(dict);
    }
    {
        shutdown();
        save_safely(dict);
    }
    {
        assert(odb_renew(dict)==ODB_RENEW_OK);
        check_renew(dict);
        assert(odb_destroy(dict)==ODB_DESTROY_OK);
    }
    {
        dict=load();
        check(dict);
    }
    {
        assert(odb_renew_ex(dict)==ODB_RENEW_OK);
        check_renew(dict);
        assert(odb_destroy(dict)==ODB_DESTROY_OK);
    }
    {
        dict=load();
        check(dict);
    }
    {
        assert(odb_destroy(dict)==ODB_DESTROY_OK);
    }
    {
        search=load_search();
        check_search(search);
        traverse_search_ex(search);
        traverse_search(search);
        save_search(search);
    }
    {
        shutdown();
        save_search_safely(search);
    }
    {
        assert(odb_destroy_search(search)==ODB_DESTROY_OK);
    }
    {
        search=load_search_mmap();
        check_search(search);
        save_search(search);
        assert(odb_destroy_search_mmap(search)==ODB_DESTROY_OK);
    }
    {
        search=load_search_mmap();
        search2=load_search_mmap();
        assert(odb_is_equal_search(search,search2)==1);
        assert(odb_destroy_search_mmap(search)==ODB_DESTROY_OK);
        assert(odb_destroy_search_mmap(search2)==ODB_DESTROY_OK);
    }
    return 0;
}

int main(){
    //printf("%d\n",sizeof(sodict_snode_t));
    test_odb();
    shutdown();
    return 0;
}
