# 合并一个分支的commit到另一个分支

将B分支的commit合并到A分支

1. 在B分支git pull，预防冲突
2. 在B分支git log，查看要合并的commit id
3. git checkout A分支
4. git cherry-pick 具体使用如下

```shell
#1.A是commit id
git cherry-pick A 

#2.合并A B
git cherry-pick A B 

#3.合并从A到B的所有提交，不包括A
git cherry-pick A..B 

#4.合并从A到B的所有提交，包括A
git cherry-pick A^..B
```

