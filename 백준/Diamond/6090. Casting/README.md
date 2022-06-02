# [Diamond I] Casting - 6090 

[문제 링크](https://www.acmicpc.net/problem/6090) 

### 성능 요약

메모리: 4372 KB, 시간: 16 ms

### 분류

이분 탐색(binary_search), 볼록 껍질(convex_hull), 기하학(geometry), 회전하는 캘리퍼스(rotating_calipers)

### 문제 설명

<p>Casting is a manufacturing process in which liquid is poured into a cast that has a cavity with the shape of the object to be manufactured. The liquid then hardens, after which the cast is removed. To ensure that the given object can be mass produced by re-using the same case parts, the cast parts must be removed from the object without destroying either the cast parts or the object. </p>

<p style="text-align:center"><img alt="" src="https://www.acmicpc.net/upload/images2/casting.png" style="height:343px; width:652px"></p>

<p style="text-align:center">Figure 1.</p>

<p>Figure 1(a) shows an object (dark gray) with its cast (light gray). Our goal is to divide the cast into two parts along a straight line through two vertices of the object such that the cast parts can be removed from the object by translation without destroying either the cast parts or the object. In Figure 1(b), the cast is divided into two parts by the straight line through v<sub>4</sub> and v<sub>7</sub> such that the upper part is removed vertically upward and the lower part is removed vertically downward from the object without destroying either the cast parts or the object. Figure 1(c) and Figure 2(d) show such divisions by the straight line through v<sub>5</sub> and v<sub>7</sub>, and by the straight line through v<sub>2</sub> and v<sub>6</sub>, respectively. However, not every pair of vertices defines such a division. In Figure 1(e), the left part defined by the straight line through v<sub>3</sub> and v<sub>5</sub> cannot be removed from the object without destroying either the cast parts or the object. </p>

<p>Given a convex polygon P with n vertices in the plane, your program is to find all pairs (v<sub>i</sub>, v<sub>j</sub>) of vertices of P such that both cast parts of P divided by the straight line through (v<sub>i</sub>, v<sub>j</sub>) can be removed by translation without destroying either the cast parts or the object. </p>

### 입력 

 <p>Your program is to read from standard input. The input consists of T test cases. The number of test cases T is given in the first line of the input. Each test case starts with integer n, the number of vertices of a convex polygon P, where 3 ≤ n ≤ 100,000. The next line contains a sequence of 2n integers, x<sub>1</sub> y<sub>1</sub> x<sub>2</sub> y<sub>2</sub> ... x<sub>n</sub> y<sub>n</sub>, where x<sub>i</sub> and y<sub>i</sub> are the x-coordinate and y-coordinate of vertex v<sub>i</sub> of P, respectively. The coordinates are all integers with -1,000,000,000 ≤ x<sub>i</sub> ≤ 1,000,000,000 and -1,000,000,000 ≤ yi ≤ 1,000,000,000. Vertices v<sub>1</sub>, v<sub>2</sub>, …, v<sub>n</sub> of P are given in clockwise order along the boundary of P.</p>

### 출력 

 <p>Your program is to write to standard output. For each test case, print a line containing the number of pairs (v<sub>i</sub>, v<sub>j</sub>) of vertices with i < j such that both cast parts of P divided by the straight line through (v<sub>i</sub>, v<sub>j</sub>) can be removed by translation without destroying either the cast parts or the object. </p>

