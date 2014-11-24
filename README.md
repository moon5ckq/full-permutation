## 高精度排列计算 ##

### 通用算法模型 ###

1. 问题定义
	* 输入：一个排列P，一个数字n
	* 输出：在排列P之后的第n个排列(或者该排列不存在)
2. 基本算法描述
	* 计算P的中介数m
	* 计算新的排列中介数m'=n+m
	* 计算m'对应的排列P'

### 字典序排列 ###

1. 细节算法描述
	* 若P的长度为P.n，则
		* f(i) = count(P[i] > P[0 .. i-1]) * i!
		* m = ∑ f(i)
	* m' = m + n
	* 令 i = P'.n-1 .. 0, x = m'， s={1,2, ..., P'.n}
		* c = x / i!
		* P'[i] = s中第c+1大的数
		* s = s - P'[i]
		* x = x % i!
2. 高精度算法描述
	* 令 i = 0 .. P.n-1, fact = 1
		* if i>0 : fact = fact * i
		* m = m + count(P[i] > P[0 .. i-1]) * fact
	* m' = m + n
	* 令 i = P'.n-1 .. 0, x = m'， s={1,2, ..., P'.n}, fact = P'.n!
		* if i>0 : fact = fact / i
		* 二分[0, i]得到c，使得c * fact <= x
		* x = x - c * fact
		* P'[i] = s中第c+1大的数
		* s = s - P'[i]
3. 算法细节
	* count(P[i] > P[0 .. i-1])： 可以用树状数组完成 O(log(P.n)) 的计算
	* s中第c+1大的数： 可以用线段树(树状数组)完成 O(log(P'.n)) 的计算
	* 需要完成高精度计算
		1. 高精度+高精度
		2. 高精度*低精度
		3. 高精度/低精度
		4. 高精度-高精度
		5. 高精度之间的大小比较
4. 整体算法复杂度
	* 第一步： O(P.n * ( log(2^31, P.n!) + log(P.n)) )
	* 第二步： O(log(2^31, P.n!))
	* 第三步： O(P.n * ( log(P.n) * log(2^31, P.n!) + log(P.n) ))
	* 故总体复杂度： O(P.n * log(P.n) * log(2^31, P.n!))
		* 由于 ln(P.n!) ≈ P.n ln(P.n) - P.n + ln(2πP.n)/2
		* 故 log(2^31, P.n!) ≈ (P.n ln(P.n) - P.n + ln(2πP.n)/2) / ln(2^31)
			≈ P.n ln(P.n) / 21.4875
		* 总体复杂度约为 O(P.n^2 * log(P.n) * ln(P.n) / 21.4875)

### 递增进位制法 ###
1. 细节算法描述
	* 若P的长度为P.n，Q为P的置换表示，则
		* f(i) = count(Q[i] > Q[0 .. i-1]) * i!
		* m = ∑ f(i)
	* m' = m + n
	* 令 i = P'.n - 1 .. 0, x = m', s={1,2, ..., P'.n}
		* c = x / i!
		* P'[s中第c+1大的数] = i + 1
		* x = x % i!
		* s -= s中第c+1大的数
2. 高精度算法描述
	* 令 i = P.n - 1 .. 0, Q为P的置换表示
		* m = m * (i + 1) + (Q[i] - count(Q[i] > Q[0 .. i-1]))
	* m' = m + n
	* 令 i = P'.n - 1 .. 0, fact = P'.n !, s={1,2, ..., P'.n}
		* fact = fact / (i + 1)
		* 二分[0, P'.n - 1]得到c，使得c * fact <= x
		* x = x - c * fact
		* P'[s中第c+1大的数] = i + 1
		* s -= s中第c+1大的数
3. 算法细节
	* count(Q[i] > Q[0 .. i-1])： 可以使用树状数组完成 O(log(Q.n)) 的计算
	* 需要完成高精度计算
		1. 高精度+高精度
		2. 高精度*低精度
		3. 高精度/低精度
		4. 高精度-高精度
		5. 高精度之间的大小比较
4. 算法复杂度
	* O(P.n^2 * log(P.n) * ln(P.n) / 21.4875)

### 递减进位制法 ###
1. 细节算法描述
	* 若P的长度为P.n，Q为P的置换表示，则
		* f(P.n - i - 1) = count(Q[i] > Q[0 .. i-1])
		* m = f(0) *  1) + f(1) * 2 ) * ...
	* m' = m + n
	* 令 i = P'.n - 1 .. 0, x = m', s={1,2, ..., P'.n}
		* c = x % (i + 1)
		* P'[s中第c+1大的数] = i + 1
		* x = x / (i + 1)
		* s -= s中第c+1大的数
2. 高精度算法描述
	* 若P的长度为P.n，Q为P的置换表示，则
		* f(P.n - i - 1) = count(Q[i] > Q[0 .. i-1])
		* 令 i = 1 .. P.n - 1, Q为P的置换表示
			* m = m * (i + 1) + f(i)
	* m' = m + n
	* 令 i = P'.n - 1 .. 0, s={1,2, ..., P'.n}
		* c = x % (i + 1)
		* x = x / (i + 1)
		* P'[s中第c+1大的数] = i + 1
		* s -= s中第c+1大的数
3. 算法细节
	* count(Q[i] > Q[0 .. i-1])： 可以使用树状数组完成 O(log(Q.n)) 的计算
	* 需要完成高精度计算
		1. 高精度+高精度
		2. 高精度*低精度
		3. 高精度/(%)低精度
		4. 高精度-高精度
4. 算法复杂度
	* O(P.n^2 * ln(P.n) / 21.4875)

### 临位对换法 ###
1. 细节算法描述
	* 若P的长度为P.n，Q为P的置换表示，则 for i in 1...n-1，其中 tmp(0) = 0
    * tmp(i) = tmp(i-1) + (i & 1) * tmp(i-2)
    * f(i) = (tmp(i) & 1) * count(Q[i] > Q[0 .. i - 1] + ((tmp(i) + 1) & 1) * count(Q[i] < Q[0 .. i-1])
		* m = f(1) *  2) + f(2) * 3 ) * ...
	* m' = m + n
	* 令 i = P'.n - 1 .. 2, x = m'
		* D[i] = x % (i + 1)
		* x = x / (i + 1)
  * 令 i = P'.n - 1 .. 1, 其中cur(1)=0
    * cur(i) = D[i-1] + (i & 1) * D[i-2]
    * 若i为奇数 r(i) = P'从高向低第(D[i] + 1)个空位的位置
    * 若i为偶数 r(i) = P'从低向高第(D[i] + 1)个空位的位置
    * P'[r(i)] = i + 1
  * P'[P'中最后一个空位] = 1
2. 算法细节
	* count(Q[i] > Q[0 .. i-1]), count(Q[i] < Q[0 .. i-1])： 可以使用树状数组完成 O(log(Q.n)) 的计算
	* 寻找P'中任意方向第i个空位： 可以使用两个树状数组完成 O(log(P'.n)) 的计算
	* 需要完成高精度计算
		1. 高精度+高精度
		2. 高精度*低精度
		3. 高精度/(%)低精度
3. 算法复杂度
  * ???
