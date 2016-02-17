//
//  main.c
//  HashSearch
//
//  Created by chenyufeng on 16/2/17.
//  Copyright © 2016年 chenyufengweb. All rights reserved.
//

#include "stdio.h"
#include "stdlib.h"

#define HASHSIZE 7 // 定义散列表长为数组的长度
#define NULLKEY -32768

typedef int Status;
typedef struct{
    int *elem; // 数据元素存储地址，动态分配数组
    int count; //  当前数据元素个数
}HashTable;

// 散列表表长，全局变量
int m = 0;

void InitHashTable(HashTable *hashTable);
Status Hash(int key);
void Insert(HashTable *hashTable,int key);
Status Search(HashTable *hashTable,int key);
void DisplayHashTable(HashTable *hashTable);

int main(int argc, const char * argv[]) {

    int result;
    HashTable hashTable;
    int arr[HASHSIZE] = {13,29,27,28,26,30,38};

    //初始化哈希表
    InitHashTable(&hashTable);

    /**
     *  向哈希表中插入数据;
     也就是把元素使用哈希函数映射到哈希表中；
     */
    for (int i = 0;i < HASHSIZE;i++){
        Insert(&hashTable,arr[i]);
    }
    //数据已存到哈希表中，打印观察哈希表，元素的位置和原数组是完全不一样的
    DisplayHashTable(&hashTable);

    //查找数据
    result = Search(&hashTable,30);
    if (result == -1){
        printf("没有找到！");
    }else{
        printf("在哈希表中的位置是:%d\n",result);
    }

    return 0;
}

//初始化一个空的哈希表
void InitHashTable(HashTable *hashTable){

    m = HASHSIZE;
    hashTable->elem = (int *)malloc(m * sizeof(int)); //申请内存
    hashTable->count = m;
    for(int i = 0;i < m;i++){
        hashTable->elem[i] = NULLKEY;
    }
}

//哈希函数(除留余数法)
Status Hash(int key){
    return key % m;
}

//插入
void Insert(HashTable *hashTable,int key){

    /**
     *  根据每一个关键字，计算哈希地址hashAddress；
     */
    int hashAddress = Hash(key); //求哈希地址
    /**
     *  发生冲突，表示该位置已经存有数据
     */
    while(hashTable->elem[hashAddress] != NULLKEY){
        //利用开放定址的线性探测法解决冲突
        hashAddress = (hashAddress + 1) % m;
    }
    //插入值
    hashTable->elem[hashAddress] = key;
}

//查找
Status Search(HashTable *hashTable,int key){
    //求哈希地址
    int hashAddress = Hash(key);
    //发生冲突
    while(hashTable->elem[hashAddress] != key){
        //利用开放定址的线性探测法解决冲突
        hashAddress = (hashAddress + 1) % m;
        if (hashTable->elem[hashAddress] == NULLKEY || hashAddress == Hash(key)){
            return -1;
        }
    }
    //查找成功
    return hashAddress;
}

//打印结果
void DisplayHashTable(HashTable *hashTable){
    for (int i = 0;i < hashTable->count;i++){
        printf("%d ",hashTable->elem[i]);
    }
    printf("\n");
}


