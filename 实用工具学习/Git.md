# Git

master:通常代表代码的主开发分支，视为指向最新提交的pointer。

HEAD：特殊引用，指向正在查看的提交。

git知道head 和哪个分支是联动的：![image-20250304115725062](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250304115725062.png)

如果此时git commit，master会随着head指向最新的快照。

但是如果这个时候checkout到cat分支,head联动cat，ggit commit 之后，cat指向最新的快照

git checkout ：移动HEAD指针，会修改当前工作目录的内容

git checkout file:直接放弃所有pwd下做的changes 去到head所在的快照的状态

需要回到之前某个分支并做出一些改变，先创建一个新的分支最后Merge，一些冲突可能就需要手动解决

git checkout -d branchname:直接新建一个branch并切换至此

git diff 文件:查询文件与head的差异

git diff hash file:某次提交与

git hash1 hash2

git log --oneline

git push <remote> <local branch>：<remote branch>创建或者更新远程仓库

git fetch <remote>该命令并不会更改任何本地历史记录，但他会知道远程仓库里面分支的更新

git full=git fetch +git merge