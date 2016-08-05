师父，我做了几个版本的那个开发板程序。

PM25 			是使用16Mhz内部时钟 以nop delay处理的pm2.5的程序；
PM25_de_4Mhz 		是使用4Mhz内部时钟 以nop delay处理的pm2.5的程序；
PM25_tim_4Mhz		是使用4Mhz内部时钟 以Timer2定时delay的pm2.5程序；
PM25_tim_16Mhz 		是使用16Mhz内部时钟 以Timer2定时delay的pm2.5程序；

我做了一些粗略的测试：
	使用16Mhz内部时钟，我那种nop方式delay
	
	main
	{
		while（1）
		{
			delay_us(300);
			PD_ODR_ODR0 = !PD_ODR_ODR0;
		}
	}
	
	测试下来，这种方式300的delay会延时450多us，可以准确的抓住pm2.5的数据；
	然后我使用定时器做delay 使用不精确的450us延时也可以准确的抓住pm2.5的数据；

我大概算了一下，一组数据是9bit，每个bit会持续420us时间，我只需要保证每个417us中有采样的动作就可以了
417*9 = 3753 us
我开始检测低电平起始，需要忽略一开始的417us，需要delay掉417开始采样8次，
所以允许的delay时间  417<delay<(3753/8 = 469.125)  就可以保证这8次采样都落在9个电平中有效的8个。所以这个延时也不需要很精确了。

所以我一开始修改nop的delay侥幸把数据位对上了。





  