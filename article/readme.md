% 文档模板建设
% Liyiqiang
% 2013-01-18

# 前言

我需要一个专心写字的工具，而不是匆忙中时间匆忙而逝的事情。


# 模板
## pandoc.latex.article.template.cn.tex
pandoc 转换latex格式的中文模板
使用如下的命令进行运行

    pandoc --template pandoc.latex.article.template.cn.tex \
		--latex-engine=xelatex readme.md -o readme.pdf

## pandoc.latex.article.template.cn.tex
pandoc 转换latex格式的英文模板
使用如下的命令进行运行

    pandoc --template pandoc.latex.article.template.en.tex \
		--latex-engine=xelatex readme.md -o readme.pdf

