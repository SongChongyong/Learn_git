# 14 文件&位运算

本周是关于C语言如何做文件和底层操作的。

文件操作，从根本上说，和C语言无关。这部分的内容，是教你如何使用C语言的标准库所提供的一系列函数来操作文件，最基本的最原始的文件操作。你需要理解，我们在这部分所学习的，是函数库的使用，而非C语言。顺便我们还学习了很多和计算机相关的知识，比如重定向、文本文件和二进制文件的江湖恩怨。但是既然不是C语言，也就意味着你将来的工业环境下，未必还会使用这么原始的文件操作函数了。这些函数，只是一个标本，让你知道可以这样来操纵文件。但是，不见得所有的库都是以这样的方式来操纵文件的。

围绕文件操作，还有一个C语言受时代局限，处理得不够好的东西，就是错误处理。因为文件操作的每一个步骤都很可能在实行过程中遇到问题：文件打不开啦，读了一半出错啦，等等等等，所以设计文件操作函数如何反馈和处理这类运行时刻的问题是需要很好的手段的。C的这个函数库，主要是通过特殊的返回值来实现的。后来的语言，如C++和Java，则引入了异常机制来处理这些事情。

关于底层操作，我们主要是介绍了按位操作，包括按位的运算、移位和位段。这些操作在日常程序中难得遇到，主要是用于接触硬件的底层程序的。这些内容在本课程是选读的。

## 14.1 格式化输入输出

- `printf`
    - `%[flags][width][.prec][hIL]type`

- `scanf`
    - `%[flag]type`

### printf

- `%[flags][width][.prec][hIL]type`



|  Flag   |     含义     |
| :-----: | :----------: |
|    -    |    左对齐    |
|    +    | 在前面放+或- |
| (space) |   正数留空   |
|    0    |    0填充     |

```c
int main(int argc, char const *argv[])
{
    printf("%9d\n", 123);
    printf("%-9d\n", 123);    // -表示左对齐
    printf("%+9d\n", 123);
    printf("%-+9d\n", 123);
    printf("%09d\n", 123);     // 0填充
}
/*
      123
123      
     +123
+123     
000000123 
*/
```



| width 或 prec |            含义            |
| :-----------: | :------------------------: |
|    number     |         最小字符数         |
|       *       |     下一个参数是字符数     |
|    .number    |       小数点后的位数       |
|      .*       | 下一个参数是小数点后的位数 |

```c
int main(int argc, char const *argv[])
{
    printf("%9.2f\n", 123.0);   // 9.2f表示浮点数总共占据9位，其中小数2位
    printf("%*d\n",6, 123);     // *d中，*对应后面的6，表示总共占据6位，d对应的是123

}

/*
   123.00
   123
*/
```



| hIL修饰符 (修饰类型) |    含义     |
| :------------------: | :---------: |
|          hh          |  单个字节   |
|          h           |    short    |
|          l           |    long     |
|          ll          |  long long  |
|          L           | long double |





|  type  |        用于        |  type  |      用于       |
| :----: | :----------------: | :----: | :-------------: |
| i 或 d |        int         |   g    |      float      |
|   u    |    unsigned int    |   G    |      float      |
|   o    |       八进制       | a 或 A |  十六进制浮点   |
|   x    |      十六进制      |   c    |      char       |
|   X    | 字母大写的十六进制 |   s    |     字符串      |
| f 或 F |      float，6      |   p    |      指针       |
| e 或 E |        指数        |   n    | 读入/写出的个数 |

```c
int main(int argc, char const *argv[])
{
    int num;
    // %d对应,12345，%n表示当printf进行到此语句已经输出的字符个数，这里存入变量num
    printf("%d%n\n", 12345, &num);   
    printf("%d\n",num);

    printf("%dyyyyy%n\n", 12345, &num);   
    printf("%d\n",num);    
}

/*
12345
5
12345yyyyy
10
*/

```



### scanf

- `%[flag]type`

| flag |    含义    | flag |     含义     |
| :--: | :--------: | :--: | :----------: |
|  *   |    跳过    |  l   | long, double |
| 数字 | 最大字符数 |  ll  |  long long   |
|  hh  |    char    |  L   | long double  |
|  h   |   short    |      |              |

```c
int main(int argc, char const *argv[])
{
    int num;
    scanf("%*d%d", &num);   // %*d%d表示输入两个%d，跳过第一个%d，读入第二个%d
    printf("%d\n",num); 
    return 0;
}
/*
123 456
456
*/
```



|    type    |             用于             | type  |     用于     |
| :--------: | :--------------------------: | :---: | :----------: |
|     d      |             int              |   s   | 字符串(单词) |
|     i      | 整数，可能为十六进制或八进制 | [...] | 所允许的字符 |
|     u      |         unsigned int         |   p   |     指针     |
|     o      |            八进制            |       |              |
|     x      |           十六进制           |       |              |
| a, e, f, g |            float             |       |              |
|     c      |             char             |       |              |



### printf()函数和scanf()函数的返回值

printf()函数和scanf()函数都有返回值：

- scanf()函数返回读入的项目数
- printf()函数返回输出的字符数

```c
#include<stdio.h>

int main(int argc, char const *argv[])
{
    int num;
    int i1 = scanf("%i", &num);     // scanf()函数返回读入的项目数
    int i2 = printf("%d\n",num);    // printf()函数返回输出的字符数
    printf("i1=%d, i2=%d\n", i1, i2);

    return 0;
}

/*
12345
12345
i1=1, i2=6
*/

```

(详细代码见: [return.c](./return.c))

- 在要求严格的程序中，应该判断每次调用scanf()或printf()的返回值，从而了解程序运行中是否存在问题





## 14.2 文件输入输出

- 用>和<做重定向

    - `>`：指定把前面文件的输出指定到后面文件

        ```
        $./return > new.out     // 把return 的输出指定到new.out文件
        12345
        $ more new.out          // 查看new.out文件内容
        12345
        i1=1, i2=6
        ```

        

    - `<`：指定一个文件为输入

        ```
        // 先建立一个new.in文件，文件中存储的是123456
        // 然后用<将new.in的内容指定为return的输入
        $ ./return < new.in
        123456
        i1=1, i2=7
        ```

        



- FILE   文件结构

    - FILE* fopen(const char * restrict path, const char *restrict mode);

    - int fclose(FILE *stream);

    - fscanf(FILE*, ...)

    - fprintf(FILE*, ...)

        

    ```c
    #include<stdio.h>
    int main(int argc, char const *argv[])
    {
        FILE *fp = fopen("new.in", "r");   // 打开new.in这个文件
        if (fp){
            int num;
            fscanf(fp, "%d", &num);        // fscanf()函数去度fp指向的文件
            printf("%d\n", num);
            fclose(fp);
        } else {
            printf("无法打开文件\n");
        }
    
        return 0;
    }
    /*
    123456
    */
    ```

    (详细代码见: [FILE.c](./FILE.c))

| 参数 |                        用于                        |
| :--: | :------------------------------------------------: |
|  r   |                      打开只读                      |
|  r+  |               打开读写，从文件头开始               |
|  w   |     打开只读。如果不存在则新建，如果存在则清空     |
|  w+  |     打开读写。如果不存在则新建，如果存在则清空     |
|  a   | 打开追加。如果不存在则新建，如果存在则从文件尾开始 |
| ...x |          只新建，如果文件已存在则不能打开          |



## 14.3 二进制文件

- 其实所有的文件最终都是二进制的
- 文本文件是可以用最简单的方式可以读写的文件(more, tail, cat, vi)
- 二进制文件是需要专门的程序来读写的文件
- 文本文件的输入输出是格式化，可能经过转码



|          |               文本               |             二进制             |
| :------: | :------------------------------: | :----------------------------: |
|   优点   |     方便人类读写，而且跨平台     |           程序读写快           |
|   缺点   | 程序输入输出要经过格式化，开销大 | 人类读写困难，并且**不跨平台** |
| 使用系统 |               Unix               |            Windows             |



- 现实中，程序通过第三方库来读写文件，很少直接读写二进制文件，更好的方案是用文本







----

## 参考资料

1. 翁凯讲义：[文件.pdf](./文件.pdf)
2. 翁凯讲义：[位运算.pdf](./位运算.pdf)

