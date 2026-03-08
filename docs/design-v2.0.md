# Expression Calculator-v1.0 设计说明
## 1 程序结构
程序核心是 ExpressionCalculator 类，主要包含以下模块：
ExpressionCalculator
├ tokenize()
├ infixToPostfix()
├ evaluatePostfix()
├ applyOperator()
└ applyFunction()
整体流程：
输入表达式
↓
tokenize()
↓
中缀表达式
↓
infixToPostfix()
↓
后缀表达式
↓
evaluatePostfix()
↓
输出结果
## 2 Token 结构
程序将表达式拆分为多个 Token。
Token 类型：
Number 数字
Operator 运算符
Identifier 变量或函数名
LeftParen (
RightParen )
例如表达式：
3+4*2
会被解析为：
3 + 4 * 2
## 3 词法分析 tokenize()
`tokenize()` 函数负责读取输入字符串并生成 Token。
可以识别：
- 数字
- 运算符
- 变量名
- 函数名
- 括号
例如：
sqrt(16)+2
会被解析为：
sqrt ( 16 ) + 2
## 4 中缀转后缀
程序使用 **Shunting Yard 算法** 将中缀表达式转换为后缀表达式。
示例：
3+4*2
转换为：
3 4 2 * +
优先级顺序：
!
**
/
比较运算
逻辑运算
## 5 后缀表达式求值
使用栈进行计算：
步骤：
1. 遇到数字 → 入栈  
2. 遇到运算符 → 弹出两个数计算  
3. 结果重新入栈  
例如：
3 4 2 * +
计算过程：
4*2=8
3+8=11
## 6 变量存储
变量使用：
unordered_map<string,double>
存储变量名与对应数值，例如：
x=10
会在变量表中保存：
x → 10//键值对容器
## 7 数学函数
函数由 applyFunction() 处理。
支持：
sin cos tan
sqrt abs
log ln exp
函数调用方式：
sin(pi/2)
## 8 运算符处理
applyOperator() 负责执行具体运算：
算术运算：
/ **
比较运算：
< > >= <= == !=
逻辑运算：
&& ||
## 9 错误处理
程序使用 `try-catch` 捕获异常，例如：
- 除零错误
- 未知函数
- 非法表达式
示例：
Error: Divide by zero
## 10 主程序
主函数不断读取用户输入：
while(true)
流程：
1. 读取表达式  
2. 调用 evaluate()  
3. 输出结果  
输入 exit 时程序结束。
exit  程序退出。
