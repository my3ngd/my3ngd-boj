# [Ruby II] Scissors and Tape - 17645 

[문제 링크](https://www.acmicpc.net/problem/17645) 

### 성능 요약

메모리: 2068 KB, 시간: 4 ms

### 분류

기하학(geometry), 수학(math)

### 문제 설명

<p>You are given a piece of paper in the shape of a simple polygon S. Your task is to turn it into a simple polygon T that has the same area as S.</p>

<p>You can use two tools: scissors and tape. Scissors can be used to cut any polygon into smaller polygonal pieces. Tape can be used to combine smaller pieces into larger polygons. You can use each tool multiple times, in any order.</p>

<p>The polygons given in the input have integer coordinates, but you are allowed to produce shapes with <strong>non-integer coordinates</strong> in your output.</p>

<p>A formal definition of the task follows.</p>

<p>A <strong>shape</strong> Q = (Q<sub>0</sub>, . . . , Q<sub>n−1</sub>) is a sequence of three or more points in the plane such that:</p>

<ul>
	<li>The closed polyline Q<sub>0</sub>Q<sub>1</sub>Q<sub>2</sub> . . . Q<sub>n−1</sub>Q<sub>0</sub> never touches or intersects itself, and therefore it forms the boundary of a simple polygon.</li>
	<li>The polyline goes around the boundary of the polygon in the counter-clockwise direction.</li>
</ul>

<p>The polygon whose boundary is the shape Q will be denoted P(Q).</p>

<p>Two shapes are called <strong>equivalent</strong> if one can be translated and/or rotated to become identical with the other.</p>

<p>Note that mirroring a shape is not allowed. Also note that the order of points matters: the shape (Q<sub>1</sub>, . . . , Q<sub>n−1</sub>, Q<sub>0</sub>) is not necessarily equivalent to the shape (Q<sub>0</sub>, . . . , Q<sub>n−1</sub>).</p>

<p><img alt="" src="https://upload.acmicpc.net/8dd3085f-5d9d-4029-a9a4-ce7318812a84/-/preview/" style="width: 377px; height: 117px; float: left;">In the figure on the left: Shapes U and V are equivalent. Shape W is not equivalent with them because the points of W are given in a different order. Regardless of the order of points, the fourth shape is not equivalent with the previous ones either as flipping a shape is not allowed.</p>

<p>In both input and output, a shape with n points is represented as a single line that contains 2n+ 1 space-separated numbers: the number n followed by the coordinates of the points: Q<sub>0,x</sub>, Q<sub>0,y</sub>, Q<sub>1,x</sub>, . . .</p>

<p>Shapes have <strong>identification numbers</strong> (IDs). The given shape S has ID 0, the shapes you produce in your solutions are given IDs 1, 2, 3, . . . , in the order in which they are produced.</p>

<p>Shapes B<sub>1</sub>, . . . , B<sub>k</sub> form a <strong>subdivision</strong> of shape A if:</p>

<ul>
	<li>The union of all P(Bi) is exactly P(A).</li>
	<li>For each i ≠ j, the area of the intersection of P(B<sub>i</sub>) and P(B<sub>j</sub>) is zero.</li>
</ul>

<p>The <strong>scissors</strong> operation destroys one existing shape A and produces one or more shapes B<sub>1</sub>, . . . , B<sub>k</sub> that form a subdivision of A.</p>

<p><img alt="" src="https://upload.acmicpc.net/d223bbec-4244-424c-9265-b398b9e5e5c8/-/preview/" style="width: 138px; height: 124px; float: left;">In the figure on the left: Shape A (square) subdivided into shapes B<sub>1</sub>, B<sub>2</sub>, B<sub>3</sub> (the three triangles). One valid way to describe one of the B<sub>i</sub> is “3 3 1 6 1 5.1 4”.</p>

<p>The <strong>tape</strong> operation destroys one or more existing shapes A<sub>1</sub>, . . . , A<sub>k</sub> and produces one new shape B. In order to perform this operation, you must first specify shapes C<sub>1</sub>, . . . , C<sub>k</sub> and only then the final shape B. These shapes must satisfy the following:</p>

<ul>
	<li>For each i, the shape C<sub>i</sub> is equivalent to the shape A<sub>i</sub>.</li>
	<li>The shapes C<sub>1</sub>, . . . , C<sub>k</sub> form a subdivision of the shape B.</li>
</ul>

<p>Informally, you choose the shape B and show how to move each of the existing Ai to its correct location C<sub>i</sub> within B. Note that only the shape B gets a new ID, the shapes C<sub>i</sub> do not.</p>

### 입력 

 <p>The first line contains the source shape S.</p>

<p>The second line contains the target shape T.</p>

<p>Each shape has between 3 and 10 points, inclusive. Both shapes are given in the format specified above.</p>

<p>All coordinates in the input are integers between −10<sup>6</sup> and 10<sup>6</sup>, inclusive.</p>

<p>In each shape, no three points form an angle smaller than 3 degrees. (This includes non-consecutive points and implies that no three points are collinear.)</p>

<p>The polygons P(S) and P(T) have the same area.</p>

### 출력 

 <p>Whenever you use the scissors operation, output a block of lines of the form:</p>

<pre>scissors
id(A) k
B_1
B_2
...
B_k</pre>

<p>where id(A) is the ID of the shape you want to destroy, k is the number of new shapes you want to produce, and B<sub>1</sub>, . . . , B<sub>k</sub> are those shapes.</p>

<p>Whenever you use the tape operation, output a block of lines of the form:</p>

<pre>tape
k id(A_1) ... id(A_k)
C_1
C_2
...
C_k
B</pre>

<p>where k is the number of shapes you want to tape together, id(A<sub>1</sub>), . . . , id(A<sub>k</sub>) are their IDs, C<sub>1</sub>, . . . , C<sub>k</sub> are equivalent shapes showing their position within B, and B is the final shape obtained by taping them together.</p>

<p>It is recommended to output coordinates of points to at least 10 decimal places.</p>

<p>The output must satisfy the following:</p>

<ul>
	<li>All coordinates of points in the output must be between −10<sup>7</sup> and 10<sup>7</sup>, inclusive.</li>
	<li>Each shape in the output must have at most 100 points.</li>
	<li>In each operation the number k of shapes must be between 1 and 100, inclusive.</li>
	<li>The number of operations must not exceed 2000.</li>
	<li>The total number of points in all shapes in the output must not exceed 20000.</li>
	<li>In the end, there must be exactly one shape (that hasn’t been destroyed), and that shape must be equivalent to T.</li>
	<li>All operations must be valid according to the checker. Solutions with small rounding errors will be accepted. (Internally, all comparisons check for absolute or relative error up to 10<sup>−3</sup> when verifying each condition.)</li>
</ul>

