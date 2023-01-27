# 替换空格

> 难度：简单

## 题目

请实现一个函数，把字符串 `s` 中的每个空格替换成"%20"。

**示例 1：**

```
输入：s = "We are happy."
输出："We%20are%20happy."
```

## 思路

一、使用js的split和join函数

二、原地修改

​	需要将空格替换为"%20"，字符串的总字符串数增加，因此需要拓展原字符串s的长度，计算公式为：`新字符串长度 = 原字符串长度 + 2 * 空格个数`，如下图

​	<img src="https://pic.leetcode-cn.com/1599931882-pPgkor-Picture6.png"/>

## 代码

一、使用js函数

```typescript
	function replaceSpace(s: string): string {
    	return s.split(' ').join('%20')
	};
```

二、原地修改C++

C++的string是可变的

1. 统计空格数量`count`，遍历`s`，遇到空格则`count++`
2. 修改`s`长度，新长度应该为`s.length() + 2 * count`
3. 倒序遍历修改，`i`指向原字符串尾部元素，`j`指向新字符串尾部元素，当`i == j`时跳出(代表左方已没有空格了，前面的内容没必要改了，无需继续遍历)
   1. 当`s[i]`不为空格时，`s[j] = s[i]`
   2. 当`s[i]`为空格时，将字符串区间[j-2,j]的元素修改为"%20",由于修改了3个元素，所以需要`j-=2`

4. 返回值，已经修改完毕的`s`

```c++
class Solution {
public:
    string replaceSpace(string s) {
        int count = 0, len = s.size();
        // 统计空格数量
        for (char c : s) {
            if (c == ' ') count++;
        }
        // 修改 s 长度
        s.resize(len + 2 * count);
        // 倒序遍历修改
        for(int i = len - 1, j = s.size() - 1; i < j; i--, j--) {
            if (s[i] != ' ')
                s[j] = s[i];
            else {
                s[j - 2] = '%';
                s[j - 1] = '2';
                s[j] = '0';
                j -= 2;
            }
        }
        return s;
    }
};
```

## 复杂度

原地修改法，时间复杂度O(n)，空间复杂度O(1)

# 左旋转字符串

> 难度:简单

字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串`"abcdefg"`和数字2，该函数将返回左旋转两位得到的结果`"cdefgab"`。

**示例 1：**

```
输入: s = "abcdefg", k = 2
输出: "cdefgab"
```

**示例 2：**

```
输入: s = "lrloseumgh", k = 6
输出: "umghlrlose"
```

## 思路

使用取余法，从`n~len+n`，对`len`取模，当 `i <= len`时，整个遍历过程拿到的时`n~len`的字符，但当`i>len`时，`i%len`的结果等于`0~n`的下标

## 代码

```typescript
    function reverseLeftWords(s: string, n: number): string {
        let res:string = ""
        let length = s.length
        for(let i = n;i < n + length; i++) {
            res += s[i % length]
        }
        return res
    };
```

## 复杂度

时间复杂度O(n)

空间复杂度O(n)