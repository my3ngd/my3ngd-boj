# [Ruby V] 촛불과 그림자 - 18190 

[문제 링크](https://www.acmicpc.net/problem/18190) 

### 성능 요약

메모리: 6408 KB, 시간: 264 ms

### 분류

이분 탐색(binary_search), 볼록 껍질(convex_hull), 기하학(geometry), 구현(implementation), 누적 합(prefix_sum)

### 문제 설명

<p>꼭짓점이 (<em>A</em><sub>1</sub>, <em>B</em><sub>1</sub>), (<em>A</em><sub>2</sub>, <em>B</em><sub>2</sub>), ···, (<em>A<sub>N</sub></em>, <em>B<sub>N</sub></em>)인 빨간색 볼록 <em>N</em>각형과, 꼭짓점이 (<em>C</em><sub>1</sub>, <em>D</em><sub>1</sub>), (<em>C</em><sub>2</sub>, <em>D</em><sub>2</sub>), ···, (<em>C<sub>M</sub></em>, <em>D<sub>M</sub></em>)인 파란색 볼록 <em>M</em>각형이 있다.</p>

<p>여기서 재미있는 점은 아래 그림과 같이, 빨간색 볼록 다각형 내부에 파란색 볼록 다각형이 완전하게 포함된다.</p>

<p style="text-align: center;"><img alt="" src="" style="width: 570px; height: 400px;"></p>

<p style="text-align: center;"><strong><그림 1></strong> 파란색 다각형을 포함하는 빨간색 다각형</p>

<p>빨간색 볼록 다각형 내부이나, 파란색 볼록 다각형의 내부와 경계에 포함되지 않는 영역을 <em>S</em>라 하자. 아래 그림과 같이, 영역 <em>S</em>의 한 점에 촛불을 설치하면 노랑색 영역이 밝아지고, 회색 영역에는 그림자가 생긴다.</p>

<p style="text-align: center;"><img alt="" src="" style="width: 575px; height: 400px;"></p>

<p style="text-align: center;"><strong><그림 2></strong> 밝혀진 영역과 그림자 영역</p>

<p>다각형의 정보와 촛불의 위치가 주어질 때, 그림자 영역의 넓이를 계산하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫 번째 줄에 빨간색 다각형과 파란색 다각형의 꼭짓점 개수를 의미하는 두 자연수 <em>N</em>과 <em>M</em>, 쿼리의 개수를 의미하는 자연수 <em>Q</em>가 사이에 공백을 두고 주어진다.</p>

<p>두번째 줄부터 <em>N</em>개의 줄에 걸쳐, 빨간색 다각형의 꼭짓점 정보가 반시계 방향으로 주어진다. (<em>i</em>+1)번째 줄에는 두 정수 <em>A<sub>i</sub></em>와 <em>B<sub>i</sub></em>가 사이에 공백을 두고 주어진다(1 ≤ <em>i</em> ≤ <em>N</em>).</p>

<p>(<em>N</em>+2)번째 줄부터 <em>M</em>개의 줄에 걸쳐, 파란색 다각형의 꼭짓점 정보가 반시계 방향으로 주어진다. (<em>N</em>+<em>i</em>+1)번째 줄에는 두 정수 <em>C<sub>i</sub></em>와 <em>D<sub>i</sub></em>가 사이에 공백을 두고 주어진다(1 ≤ <em>i</em> ≤ <em>M</em>).</p>

<p>(<em>N</em>+<em>M</em>+2)번째 줄부터 <em>Q</em>개의 줄에 걸쳐, <em>Q</em>개의 쿼리에 관한 정보가 주어진다. (<em>N</em>+<em>M</em>+<em>i</em>+1)번째 줄에는 두 정수 <em>X<sub>i</sub></em>와 <em>Y<sub>i</sub></em>가 사이에 공백을 두고 주어진다(1 ≤ <em>i</em> ≤ <em>Q</em>). 이는 <em>i</em>번째 쿼리에서는 촛불을 (<em>X<sub>i</sub></em>, <em>Y<sub>i</sub></em>)에 설치함을 의미한다.</p>

<p>모든 <em>Q</em>개의 쿼리는 서로 독립적임에 유의하라.</p>

### 출력 

 <p>첫 번째 줄부터 <em>Q</em>개의 줄에 걸쳐, 쿼리에 대한 답을 차례대로 출력한다.</p>

<p>만약 촛불의 위치가 빨간색 볼록 다각형의 외부나 경계에 존재한다면, "<code>OUT</code>"을 출력한다.</p>

<p>만약 촛불의 위치가 파란색 볼록 다각형의 내부가 경계에 존재한다면, "<code>IN</code>"을 출력한다.</p>

<p>위 두 가지 경우가 모두 아니라면, 그림자의 영역의 넓이를 출력한다.</p>

<p>실수에 대한 절대·상대 오차는 10<sup>-6</sup>까지 허용된다.</p>

