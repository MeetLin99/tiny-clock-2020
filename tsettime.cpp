#include <graphics.h>
#include <math.h>   //计算cos
#include <time.h>
#define PI 3.1415926

int getNowTime(char *nowTime)
{
	char acYear[5] = {0};
	char acMonth[5] = {0};
	char acDay[5] = {0};
	char acHour[5] = {0};
	char acMin[5] = {0};
	char acSec[5] = {0};
	
	time_t now;
    struct tm* timenow;
    time(&now);
    timenow = localtime(&now);
    
	strftime(acYear,sizeof(acYear),"%Y",timenow);   //转化为字符串
    strftime(acMonth,sizeof(acMonth),"%m",timenow);
    strftime(acDay,sizeof(acDay),"%d",timenow);
    strftime(acHour,sizeof(acHour),"%H",timenow);
    strftime(acMin,sizeof(acMin),"%M",timenow);
    strftime(acSec,sizeof(acSec),"%S",timenow);
	
	strncat(nowTime, acYear, 4);   //追加字符
	strncat(nowTime,"年", 2);
	strncat(nowTime, acMonth, 2);
	strncat(nowTime,"月", 2);
	strncat(nowTime, acDay, 2);
	strncat(nowTime,"日", 2);
	strncat(nowTime, acHour, 2);
	strncat(nowTime,"时", 2);
	strncat(nowTime, acMin, 2);
	strncat(nowTime,"分", 2);
	strncat(nowTime, acSec, 2);
	strncat(nowTime,"秒", 2);
	return 0;
}

int main()
{
	int high=500;
	int width=500;
	int i;
	initgraph(width,high);      //创建500*500画布	
	IMAGE img;  //图像对象
	loadimage(&img,"E:\\大学课程\\c++\\test2\\1.jpg");   //加载图片，图片已修改高度500像素
	//putimage(0,0,&img);   //显示图片
	SYSTEMTIME time;  //时间对象
	float angle_s = 0;   //指针偏转角度
	float angle_m = 0;
	float angle_h = 0;

	BeginBatchDraw(); //开始批量绘图
	
	while(1) //无限循环
	{
		cleardevice();   //用当前背景色清空绘图设备，为了清除上一帧指针的印记
		putimage(0,0,&img);   //再显示背景图片
		
		char nowTime[32] = {0};
		getNowTime(nowTime);
		settextcolor(WHITE);   //输出文字样式
		settextstyle(30,0,"微软雅黑");
		outtextxy(width/2-150,30,nowTime);

		GetLocalTime(&time);   //获得系统时间保存到time
		angle_s = time.wSecond*2*PI/60;   //根据time.w (GetLocalTime)获取时针、分针、秒针偏转角度
		angle_m = time.wMinute*2*PI/60;
		angle_h = time.wHour*2*PI/12;
		
		setlinestyle(PS_SOLID,7);   //绘制表盘 线宽为7
		setlinecolor(0x08BAFF);
		circle(width/2,high/2,150);
		//arc(130,130,370,370,0,999); //椭圆表盘

		setlinestyle(PS_SOLID,5);
		line(width/2,high/2+140,width/2,high/2+150);   //6点刻度
		line(width/2-140,high/2,width/2-150,high/2);   //9点刻度
		line(width/2+140,high/2,width/2+150,high/2);   //3点刻度
		line(width/2+121,high/2+70,width/2+129,high/2+75);   //4点刻度 数据对称
		line(width/2+70,high/2+121,width/2+75,high/2+129);   //5点刻度
		line(width/2-70,high/2+121,width/2-75,high/2+129);   //7点刻度
		line(width/2-121,high/2+70,width/2-129,high/2+75);   //8点刻度
		line(width/2-121,high/2-70,width/2-129,high/2-75);   //10点刻度
		line(width/2-70,high/2-121,width/2-75,high/2-129);   //11点刻度
		
		setcolor(GREEN);   //绘制秒针
		setlinestyle(PS_SOLID,3);
		line(width/2,high/2,width/2+120*sin(angle_s),high/2-120*cos(angle_s));   //始,终 坐标
		setcolor(RED);   //绘制分针
		setlinestyle(PS_SOLID,4);
		line(width/2,high/2,width/2+80*sin(angle_m),high/2-80*cos(angle_m));
		setcolor(BLUE);   //绘制时针
		setlinestyle(PS_SOLID,5);
		line(width/2,high/2,width/2+50*sin(angle_h),high/2-50*cos(angle_h));
		
		FlushBatchDraw();   //输出绘图

		//清除前一帧指针 方案:以白色线条覆盖，不用每次清空画布
		//setcolor(WHITE);
		//line(width/2,high/2,width/2+120*sin(angle_s),high/2-120*cos(angle_s));
		//line(width/2,high/2,width/2+80*sin(angle_m),high/2-80*cos(angle_m));
		//line(width/2,high/2,width/2+50*sin(angle_h),high/2-50*cos(angle_h));

		Sleep(100);   //大大减轻cpu消耗，挂起100ms，有100ms内误差
	}
	EndBatchDraw();   //结束绘图
	closegraph();
	return 0;
	system("pause");
}