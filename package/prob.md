## Problem Description

There are $N$ classmates of Little Shimeming playing **Dragon's Song: Awakening** (DSA), a mobile game notorious for its inflationary powers.

The classmates are labeled from $1$ to $N$ based on their ranks in the game. Each of them possesses a power denoted as $p_1, p_2, \cdots, p_N$, where $p_1 \geq p_2 \geq \cdots \geq p_N$.

Then $T$ incidents happens sequentially. The $i$-th incidents is one of the following:

1. The classmate labeled $a_i$ tops up their power to equal to that of the person ahead of they in ranking by one place. Then launch an attack and swap their ranks. 
* If the classmate labeled $a_i$ is already the first place, no action is taken.
* If the power of the classmate labeled $a_i$ is the same as that of the person ahead of they in ranking by one place, they still top up their power by 0.

2. As rewards for ranking, the game reinforce the $1^{\text{st}}$ place's power by $(N-1)$ points, the $2^{\text{nd}}$ place's power by $(N-2)$, and so on.

3. Little Shimeming wants to investigate in power inflation. Please tell them the last place with at least $q_i$ points of power and that person's label.

4. Little Shimeming wants to know how much the classmate labeled $b_i$ has spent for topping up rencently. Please tell they the sum of the power gained by topping up in the last $m_i \leq M$ ($m_i = M$ for the basic 100 pts) attacks launched by the classmate labeled $b_i$.

### Input

The first line contains three space-separated integer $N$, $T$ and $M$.
The second line contains $N$ integers $p_1$, $p_2$, $\cdots$, $p_N$.
The $i$-th line of the following $T$ lines is one of the following:
* $1$ $a_i$, indicating incident 1 happens.
* $2$, indicating incident 2 happens.
* $3$ $q_i$, indicating incident 3 happens.
* $4$ $b_i$ $m_i$, indicating incident 4 happens.

where $a_i$, $q_i$, $b_i$, $m_i$ are integers.


### Output
The output consists of two parts separated by an empty line.

The first part consists of the answers to Little Shimeming's question.
* For incident 3, output 2 integers, representing the last place with at least $q_i$ power and the label of the classmate at that place. If no such classmate, output "$0$ $0$" (without quotation marks).
* For incident 4, output 1 integer, representing the total power gained by topping up in the last $m_i$ attacks launched by the classmate labeled $b_i$. If the number of attacks launched by the classmate is less than $m_i$, output the sum of the power gained by topping up in all their attacks.

Then output an empty line.

The first integer $k_j$ in the $j$-th line of the second part (consists of $N$ lines) represents the number of attack the classmate labeled $j$ launched. The subsequent integers denote the power gained by topping up in each attack, in order.

Please separate integers in a line by spaces.

### Constraints
* $1\leq N \leq 10^6$
* $1\leq T \leq 5\cdot 10^5$
* $1\leq M \leq 5\cdot 10^5$
* $0\leq p_N\leq p_{N-1}\leq \cdots \leq p_1 \leq 10^9$
* $1\leq a_i, b_i\leq N$
* $0\leq q_i \leq 10^{18}$
* $1\leq m_i \leq M$

## Subtasks
### Subtask 1 (10 pts)
（純暴力：事件一慢慢找、事件二暴力更新、不用二分搜、不用雙指針、不會爆 int）
* $1\leq N\leq 10^3$
* $1\leq T\leq 10^3$
* $m_i = M$

### Subtask 2 (10 pts)
（只要會二分搜就好）
* Only incidents 1 and 3 occur.

### Subtask 3 (30 pts)
（不用雙指針）
* $m_i = M = 1$

### Subtask 4 (50 pts)
* $m_i = M$

### Subtask 5 (20 bonus pts)
No other constraints.

## Sample Testcases
### Sample Input 1 (basic)
```
5 6 10
20 15 10 10 0
1 1
1 4
1 4
2
3 16
4 4 10
```
### Sample Output 1
```
3 2
5

0
0
0
2 0 5
0
```
### Explanation for Sample Testcase 1
The initial ranking is: 1(20) 2(15) 3(10) 4(10) 5(0).
After each incident, the rankings become:
1. No changes occur because the classmate labeled 1 is already the first place.
2. 1(20) 2(15) 4(10) 3(10) 5(0)
3. 1(20) 4(15) 2(15) 3(10) 5(0)
4. 1(24) 4(18) 2(17) 3(11) 5(0)
5. No changes occur.
6. No changes occur.

### Sample Input 2 (basic)
```
8 11 2
52 43 41 41 26 20 20 18
3 41
2
3 100
1 5
1 6
2
1 6
2
4 6 2
1 6
4 6 2
```
### Sample Output 2
```
4 4
0 0
24
4

0
0
0
0
1 16
3 23 1 3
0
0
```

### Sample Input 3 (bonus)
```
3 7 20
487 6 3
4 3 19
1 3
4 3 1
1 3
4 3 1
1 3
4 3 8
```
### Sample Output 3
```
0
3
481
484

0
0
2 3 481
```
