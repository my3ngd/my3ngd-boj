# [Diamond I] 가까운 점 찾기 - 7890 

[문제 링크](https://www.acmicpc.net/problem/7890) 

### 성능 요약

메모리: 19580 KB, 시간: 1328 ms

### 분류

델로네 삼각분할(delaunay), 기하학(geometry), 보로노이 다이어그램(voronoi)

### 문제 설명

<p>2차원 평면 상에 N개의 점이 주어진다. </p>

<p>1 ≤ i, j ≤ N에 대해서 dist(i, j) = (x<sub>j</sub> - x<sub>i</sub>)<sup>2</sup> + (y<sub>j</sub> - y<sub>i</sub>)<sup>2</sup> 라 정의할 때, 각각의 점 i에 대해서, Min(dist(i, j)) (1 ≤ j ≤ N, j ≠ i) 를 출력하라.</p>

### 입력 

 <p>입력은 여러 개의 테스트 케이스로 주어진다.</p>

<p>첫 번째 줄에 테스트 케이스의 수 T (1 ≤ T ≤ 15)가 주어진다.</p>

<p>이후 각각의 테스트 케이스마다, 첫 번째 줄에 N (2 ≤ N ≤ 10<sup>5</sup>) 이 주어진다. 이후 N개의 줄에 x, y가 주어진다 (0 ≤ x, y ≤ 10<sup>9</sup>)</p>

### 출력 

 <p>각각의 테스트 케이스마다 N줄을 출력하라.</p>

<p>i번째 줄은 Min(dist(i, j)) (1 ≤ j ≤ N, j ≠ i)의 값이어야 한다.</p>

