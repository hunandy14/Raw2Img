## 2017/06/14
- static inline 的函式不知道為何不能寫在外面
- 如果要把 fun() 定義寫在頭文件就要上 inline
- 類內定義會自己幫你上inline

在成員內 fun() 的定義：
inline 可以寫在h也可以寫在cpp

static        只能寫在cpp (寫在h會出現重複定義)
static inline 只能寫在 .h (寫在c會出現沒有定義)
