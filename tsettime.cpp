#include <graphics.h>
#include <math.h>   //����cos
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
    
	strftime(acYear,sizeof(acYear),"%Y",timenow);   //ת��Ϊ�ַ���
    strftime(acMonth,sizeof(acMonth),"%m",timenow);
    strftime(acDay,sizeof(acDay),"%d",timenow);
    strftime(acHour,sizeof(acHour),"%H",timenow);
    strftime(acMin,sizeof(acMin),"%M",timenow);
    strftime(acSec,sizeof(acSec),"%S",timenow);
	
	strncat(nowTime, acYear, 4);   //׷���ַ�
	strncat(nowTime,"��", 2);
	strncat(nowTime, acMonth, 2);
	strncat(nowTime,"��", 2);
	strncat(nowTime, acDay, 2);
	strncat(nowTime,"��", 2);
	strncat(nowTime, acHour, 2);
	strncat(nowTime,"ʱ", 2);
	strncat(nowTime, acMin, 2);
	strncat(nowTime,"��", 2);
	strncat(nowTime, acSec, 2);
	strncat(nowTime,"��", 2);
	return 0;
}

int main()
{
	int high=500;
	int width=500;
	int i;
	initgraph(width,high);      //����500*500����	
	IMAGE img;  //ͼ�����
	loadimage(&img,"E:\\��ѧ�γ�\\c++\\test2\\1.jpg");   //����ͼƬ��ͼƬ���޸ĸ߶�500����
	//putimage(0,0,&img);   //��ʾͼƬ
	SYSTEMTIME time;  //ʱ�����
	float angle_s = 0;   //ָ��ƫת�Ƕ�
	float angle_m = 0;
	float angle_h = 0;

	BeginBatchDraw(); //��ʼ������ͼ
	
	while(1) //����ѭ��
	{
		cleardevice();   //�õ�ǰ����ɫ��ջ�ͼ�豸��Ϊ�������һָ֡���ӡ��
		putimage(0,0,&img);   //����ʾ����ͼƬ
		
		char nowTime[32] = {0};
		getNowTime(nowTime);
		settextcolor(WHITE);   //���������ʽ
		settextstyle(30,0,"΢���ź�");
		outtextxy(width/2-150,30,nowTime);

		GetLocalTime(&time);   //���ϵͳʱ�䱣�浽time
		angle_s = time.wSecond*2*PI/60;   //����time.w (GetLocalTime)��ȡʱ�롢���롢����ƫת�Ƕ�
		angle_m = time.wMinute*2*PI/60;
		angle_h = time.wHour*2*PI/12;
		
		setlinestyle(PS_SOLID,7);   //���Ʊ��� �߿�Ϊ7
		setlinecolor(0x08BAFF);
		circle(width/2,high/2,150);
		//arc(130,130,370,370,0,999); //��Բ����

		setlinestyle(PS_SOLID,5);
		line(width/2,high/2+140,width/2,high/2+150);   //6��̶�
		line(width/2-140,high/2,width/2-150,high/2);   //9��̶�
		line(width/2+140,high/2,width/2+150,high/2);   //3��̶�
		line(width/2+121,high/2+70,width/2+129,high/2+75);   //4��̶� ���ݶԳ�
		line(width/2+70,high/2+121,width/2+75,high/2+129);   //5��̶�
		line(width/2-70,high/2+121,width/2-75,high/2+129);   //7��̶�
		line(width/2-121,high/2+70,width/2-129,high/2+75);   //8��̶�
		line(width/2-121,high/2-70,width/2-129,high/2-75);   //10��̶�
		line(width/2-70,high/2-121,width/2-75,high/2-129);   //11��̶�
		
		setcolor(GREEN);   //��������
		setlinestyle(PS_SOLID,3);
		line(width/2,high/2,width/2+120*sin(angle_s),high/2-120*cos(angle_s));   //ʼ,�� ����
		setcolor(RED);   //���Ʒ���
		setlinestyle(PS_SOLID,4);
		line(width/2,high/2,width/2+80*sin(angle_m),high/2-80*cos(angle_m));
		setcolor(BLUE);   //����ʱ��
		setlinestyle(PS_SOLID,5);
		line(width/2,high/2,width/2+50*sin(angle_h),high/2-50*cos(angle_h));
		
		FlushBatchDraw();   //�����ͼ

		//���ǰһָ֡�� ����:�԰�ɫ�������ǣ�����ÿ����ջ���
		//setcolor(WHITE);
		//line(width/2,high/2,width/2+120*sin(angle_s),high/2-120*cos(angle_s));
		//line(width/2,high/2,width/2+80*sin(angle_m),high/2-80*cos(angle_m));
		//line(width/2,high/2,width/2+50*sin(angle_h),high/2-50*cos(angle_h));

		Sleep(100);   //������cpu���ģ�����100ms����100ms�����
	}
	EndBatchDraw();   //������ͼ
	closegraph();
	return 0;
	system("pause");
}