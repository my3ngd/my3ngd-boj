# [Ruby V] timeismoney - 5257 

[문제 링크](https://www.acmicpc.net/problem/5257) 

### 성능 요약

메모리: 2336 KB, 시간: 408 ms

### 분류

볼록 껍질(convex_hull), 기하학(geometry), 그래프 이론(graphs), 최소 스패닝 트리(mst)

### 문제 설명

<p>The NetLine company wants to offer broadband internet to N towns. For this, it suffices to construct a network of N-1 broadband links between the towns, with the property that a message can travel from any town to any other town on this network. NetLine has already identified all pairs of towns between which a direct link can be constructed. For each such possible link, they know the cost and the time it would take to construct the link.</p>

<p>The company is interested in minimizing both the total amount of time (links are built one at a time) and the total amount of money spent to build the entire network. Since they couldn’t decide among the two criteria, they decided to use the following formula to evaluate the value of a network:</p>

<ul>
	<li>SumTime = sum of times spent to construct the chosen links</li>
	<li>SumMoney = sum of the money spent to construct the chosen links</li>
	<li>V = SumTime * SumMoney</li>
</ul>

<p>Find a list of N-1 links to build, which minimizes the value V.</p>

### 입력 

 <p>The first line of input contains integers N – the number of towns and M – the number of pairs of towns which can be connected. The towns are numbered starting from 0 to N-1. Each of the next M lines contain four integers x, y, t and c – meaning town x can be connected to town y in time t and with cost c.</p>

### 출력 

 <p>In the first line of output print two numbers: the total time (SumTime) and total money (SumMoney) used in the optimal solution (the one with minimal value V), separated by one space. The next N-1 lines describe the links to be constructed. Each line contains a pair of numbers (x,y) describing a link to be build (which must be among the possible links described in the input file). The pairs can be printed out in any order. When multiple solutions exist, you may print any of them.</p>

