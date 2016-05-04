(文件编码utf-8 可能存在中文乱码)

##蚁群算法在银行客户信用上的一个应用

###对文献《利用蚁群算法求解电信客户初始信用评分问题》(张玉洁 北京邮电大学学报 2010年2月)的C++实现。

###参数
客户数量	1000
蚂蚁数量	10
运行次数	30
alpha		1.5
beta		1.0
rou			0.7
tau			3.0
eta			1.0

客户属性及各属性分级比例为：
年龄，		1 35% 2 45% 3 15% 4 %5
性别，		1 69% 2 31%
婚姻，		1 42% 2 58%
文化程度，	1 15% 2 80% 3 5%
住宅属性，	1 40% 2 15% 3 45%
职业收入，	1 24% 2 25% 3 30% 4 21%

用户属性对欠钱的影响
年龄：1:20% 2:20% 3:20% 4:20%
性别：1:80% 2:20%
婚姻：1:30% 2:70%
文化程度：1:30% 2:40% 3:30%
住房：1:40% 2:50% 3:10%
收入：1:20% 2:35% 3:15%


###编译运行
使用matlab和C/C++混合编程
建议GCC+matlab+GNUMEX

llcx-plot.m为绘图程序


可以生成1000个用户属性
	ImportSamples();
也可以导入生成的数据
	CreateSamples();
	
每次蚂蚁初始位置随机，故结果每次有偏差，但是趋向于收敛

运行结果：
结果1:
![alt tag](https://github.com/yanshuicc/ant-colony-algorithm/blob/master/res/res1.png?raw=true)

结果2:
![alt tag](https://github.com/yanshuicc/ant-colony-algorithm/blob/master/res/res2.png?raw=true)

结果3:
![alt tag](https://github.com/yanshuicc/ant-colony-algorithm/blob/master/res/res3.png?raw=true)

结果4:
![alt tag](https://github.com/yanshuicc/ant-colony-algorithm/blob/master/res/res4.png?raw=true)