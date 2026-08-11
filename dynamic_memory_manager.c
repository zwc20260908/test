#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*模块一：头文件的引入，自定义类型，全局变量定义
功能同意封装所有结构体，基础数据类型，全局链表头*/


//统一longlong别名：适配超大内存地址 
typedef long long ll;

// 已分配内存块链表结点
typedef struct AllocNode {
    char id[20];        // 内存块唯一标识
    unsigned long start;           // 起始地址
    unsigned long size;            // 占用大小
    struct AllocNode* next;
} AllocNode;

// 空闲内存块链表结点
typedef struct FreeNode {
    ll start;
    ll size;
    struct FreeNode* next;
} FreeNode;

// COMPACT压缩时记录块移动日志，全局定义解决VS函数内typedef报错
typedef struct MoveLog {
    char id[20];
    ll old_s;  // 移动前地址
    ll new_s;  // 移动后地址
} MoveLog;

// 全局链表头指针
AllocNode* alloc_head = NULL;   // 已分配块链表头
FreeNode* free_head = NULL;     // 空闲块链表头
ll total_mem;                   // 模拟内存总大小M

/*模块 2：空闲链表初始化工具函数 init_free
 功能：程序启动初始化整块内存为单一空闲块*/

void init_free(ll M) {
    total_mem = M;
    // 创建初始空闲块：地址 0，大小 M
    free_head = (FreeNode*)malloc(sizeof(FreeNode));
    free_head->start = 0;
    free_head->size = M;
    free_head->next = NULL;
}