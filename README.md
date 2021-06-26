# DTL
Data Template Library

## 容器
* vector：动态数组
* list：双向循环链表
* avl_tree：平衡二叉树

## 容器适配器
* deque：双端队列 -> list
* queue：队列 -> deque
* stack：栈 -> deque
* heap：堆 -> vector
* priority_queue：优先队列 -> heap
* set：单重有序集合 -> avl_tree
* multiset：多重有序集合 -> avl_tree
* map：单重有序映射 -> avl_tree
* multimap：多重有序映射 -> avl_tree

