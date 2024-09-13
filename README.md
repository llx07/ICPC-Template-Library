# ICPC 模板库

本项目是上海交通大学 2024 级 ACM 队 “电光火石的前奏” 的 ICPC 模板库，由 $\LaTeX$ 编写。

本项目参考了 23 级 ACM 队 “星尘幻想” 的模板库（我忘了他们的链接在哪了，找到了再挂上来），向他们表示感谢。

本项目的模板 `main.tex` 的编写大致已经完成。如果想要增加条目，请在 `\src` 中加入您的内容，并将其 input 到 `main.tex` 中。

若想要在本地编译此项目，您需要先下载 TeX Live 和 Python ，以及 Python 的 pygments 库，编译命令为 `xelatex -shell-escape -8bit main.tex` 。