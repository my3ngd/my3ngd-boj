# [Ruby IV] Tapestries - 8237 

[문제 링크](https://www.acmicpc.net/problem/8237) 

### 성능 요약

메모리: 2040 KB, 시간: 24 ms

### 분류

기하학(geometry)

### 문제 설명

<p>An exhibition of tapestries is opening in Byteotian Museum of Fine Arts. The main exhibition room, viewed from top, is a polygon (not necessarily convex). A tapestry is hanged on each wall of the room, each tapestry taking all the area of its wall.</p>

<p>A lamp has been installed in the room in order to illuminate the exhibition. The lamp is glowing uniformly in all directions. However, while some of the tapestries have to be flooded with light, others cannot be exposed to strong light.</p>

<p>Byteasar, the curator, has been moving the lamp around the room, but so far he is not satisfied with the results. Now he is terrified by the prospect of moving the tapestries around instead - this would require much effort, and the exhibition is to open soon. Perhaps you will be able to tell him if his attempts are doomed or not?</p>

<p>Your task is to determine if there is such a spot that placing the lamp in it satisfies the following:</p>

<ul>
	<li>each wall is to be either completely illuminated or completely shaded, as required by the tapestry hanging on it; there can be no wall that is partly illuminated and partly shaded;</li>
	<li>if the lamp is located exactly on the wall or its extension, this wall is not illuminated;</li>
	<li>the lamp can neither be switched off nor taken away from the room; it has to be on while located (strictly) inside the room (i.e., it cannot be placed in a corner or on any wall).</li>
</ul>

### 입력 

 <p>There is a single integer t(1 ≤ t ≤ 20) in the first line of the standard input, denoting the number of data sets. The following lines describe these data sets.</p>

<p>The first line of a single description holds a single integer n(3 ≤ n ≤ 1,000), denoting the number of walls in the main exhibition room. Then the following n lines specify the room's shape. Each of those lines contains a pair of integers xi and yi(-30,000 ≤ xi,yi ≤ 30,000 for i=1,2,…,n), separated by a single space, denoting the coordinates of the room's corner or, in other words, the vertex of corresponding polygon. The vertices are given clockwise.</p>

<p>The next  lines specify the tapestries' requirements. Each of those lines contains a single letter, S or C, denoting that the wall has to be illuminated or shaded, respectively. The letter in the i-th of these lines (for 1 ≤ i ≤ n-1) regards the wall between the i-th and the (i+1)-th vertex. The letter in the last of these lines regards the wall between the last and the first vertex.</p>

<p>The polygon depicting the room's shape has no self-crossings, i.e., with the exception of successive sides, which share a common vertex, no two sides of the polygon share a common point. Furthermore, no three vertices of the polygon are collinear.</p>

### 출력 

 <p>For each data set your program should print to the standard output a single line containing a single word:</p>

<ul>
	<li>TAK (Polish for yes) if the lamp can be placed so as to satisfy all aforementioned requirements, or</li>
	<li>NIE (Polish for no) otherwise.</li>
</ul>

