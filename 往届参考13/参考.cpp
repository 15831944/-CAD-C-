#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <graphics.h>
#include <conio.h>

void rw();
void initialize();
void calculate();
void SOR();
void equal();

///////////////////////������///////////////////////
void main()
{
	rw();              //��д�ļ�
	initialize();      //�ռ�糡��ʼ��
	calculate();       //�ռ�糡�ֲ�����
	equal();           //���Ƶ�λ��
}

///////////////////////��������///////////////////////
FILE *fp;                 //���ļ�ָ��    
FILE *p;                  //д�ļ�ָ��
double d;                 //�缫���
int n;                    //�缫����
double *dz;               //���ڵ缫֮�����
int *N;                   //���ڵ缫֮��Ҫ���ֵĲ�����
double *V;                //�缫��λ
double r1;                //�缫�ڿ׾��뾶
int M1;                   //�缫�ڿ׾��뾶��Χ�ڵȲ������ֵ�������
double r2;                //�ӵ缫�ڿױ��ص���ձ߽紦�ľ������
int M2;                   //�ӵ缫�ڿױ��ص���ձ߽紦�ľ�����뷶Χ�ڵȲ������ֵ�������
double e;                 //�������ƾ���
int NST;                  //�����ӡ�ռ��λʱ���������
						  //int INS;                  //���ϵ�λ���Ⱦ��ֵʱ�Ĳ�����
double dV;                //Ҫ��ɨ�������ȵ�λ�ߵĵ�λ���ֵ
int row = 0, col = 0;          //������С���
int *np;                  //�缫λ�ø��
double **zl;              //z�����ڸ�㲽��
double **rl;              //r�����ڸ�㲽��
double *z;                //z�����������
double *r;                //r�����������
double **V1;              //����λ
double c1, c2, c3, c4, c0;    //ϵ��
double V2;                //������ĸ���λ
int T;                    //�����ִ�
int Time;                 //��������
int Timeall;              //�����ܴ���
double w;                 //��������
double **Vd;              //����λ�в�
double Vds;               //����λ�в��
double Vdm;               //����λ���в�
double Vda;               //����λƽ���в�
double Vda1;              //����λƽ���в�
double Vda2;              //����λƽ���в�
double x;                 //�в��ֵ
double ux;                //�м����
double wx;                //�м����
double wm;                //�������w
double wm1;               //�������w
int m = 1;                  //�ȵ�λ����
double *Ve;               //�ȵ�λֵ
double *zp, *rp;           //�ȵ�λ������
double *Vzp, *Vrp;         //ͼ�δ����еĵȵ�λ�����꣨ԭ��������10����

						   ///////////////////////��д�ļ�///////////////////////
void rw()
{
	int i, j;     //ѭ������

				  ///////////////���ļ�///////////////
	fp = fopen("C:\\Users\\axin\\Desktop\\1120131087_����ܰ\\1120131087_����ܰ.dat", "r");//���ļ�
	if (fp == NULL)
	{
		printf("Cannot open file.\n");         //����ļ�������ʾ��ʾ��Ϣ
		exit(0);                               //����exit������ֹ��������
	}
	fscanf(fp, "�缫��ȣ�ռ1�����������е缫�����ͬ��=%lfmm��\n", &d);
	fscanf(fp, "�缫�����������м�缫��ӫ����������������λΪ0V��������=%ld��\n", &n);
	fscanf(fp, "���ڵ缫֮��ľ���=");
	dz = (double*)calloc(n * sizeof(double), sizeof(double));
	for (i = 0; i<n; i++)
		fscanf(fp, "%lfmm��", &dz[i]);
	fscanf(fp, "\n���ڵ缫֮��Ҫ���ֵĲ�����=");
	N = (int*)calloc(n * sizeof(int), sizeof(int));
	for (i = 0; i<n; i++)
		fscanf(fp, "%ld��", &N[i]);
	fscanf(fp, "\n�缫��λ=");
	V = (double*)calloc(n * sizeof(double), sizeof(double));
	for (i = 0; i<n; i++)
		fscanf(fp, "%lfV��", &V[i]);
	fscanf(fp, "\n�缫�ڿ׾��뾶�����е缫�ڿ׾��뾶��ͬ��=%lfmm��\n", &r1);
	fscanf(fp, "�缫�ڿ׾��뾶��Χ�ڵȲ������ֵ�������=%ld��\n", &M1);
	fscanf(fp, "�ӵ缫�ڿױ��ص���ձ߽紦�ľ������=%lfmm��\n", &r2);
	fscanf(fp, "�ӵ缫�ڿױ��ص���ձ߽紦�ľ�����뷶Χ�ڵĵȲ������ֵ�������=%ld��\n", &M2);
	fscanf(fp, "�������ƾ���=%lfV��\n", &e);
	fscanf(fp, "�����ӡ�ռ��λʱ���������=%ld��\n", &NST);
	//fscanf(fp,"���ϵ�λ���Ⱦ��ֵʱ�Ĳ�����=%ld��\n",&INS);
	fscanf(fp, "Ҫ��ɨ�������ȵ�λ�ߵĵ�λ���ֵ���λֵ=");
	Ve = (double*)calloc(100 * sizeof(double), sizeof(double));
	while (fscanf(fp, "%lfV��", &Ve[m]) != EOF)
		m++;
	if (m == 2)
		dV = Ve[1];
	fclose(fp);

	///////////////д�ļ�///////////////
	p = fopen("C:\\Users\\axin\\Desktop\\1120131087_����ܰ\\1120131087_����ܰ.res", "w");//���ļ�
	if (p == NULL)
	{
		printf("Cannot open file.\n");         //����ļ�������ʾ��ʾ��Ϣ
		exit(0);                               //����exit������ֹ��������
	}
	fprintf(p, "\t\t\t\tԭʼ����\n");
	fprintf(p, "�缫��ȣ�ռ1�����������е缫�����ͬ��=%lfmm��\n", d);
	fprintf(p, "�缫�����������м�缫��ӫ����������������λΪ0V��������=%ld��\n", n);
	fprintf(p, "���ڵ缫֮��ľ���=");
	for (i = 0; i<n; i++)
		fprintf(p, "%lfmm��", dz[i]);
	fprintf(p, "\n���ڵ缫֮��Ҫ���ֵĲ�����=");
	for (i = 0; i<n; i++)
		fprintf(p, "%ld��", N[i]);
	fprintf(p, "\n�缫��λ=");
	for (i = 0; i<n; i++)
		fprintf(p, "%lfV��", V[i]);
	fprintf(p, "\n�缫�ڿ׾��뾶�����е缫�ڿ׾��뾶��ͬ��=%lfmm��\n", r1);
	fprintf(p, "�缫�ڿ׾��뾶��Χ�ڵȲ������ֵ�������=%ld��\n", M1);
	fprintf(p, "�ӵ缫�ڿױ��ص���ձ߽紦�ľ������=%lfmm��\n", r2);
	fprintf(p, "�ӵ缫�ڿױ��ص���ձ߽紦�ľ�����뷶Χ�ڵĵȲ������ֵ�������=%ld��\n", M2);
	fprintf(p, "�������ƾ���=%lfV��\n", e);
	fprintf(p, "�����ӡ�ռ��λʱ���������=%ld��\n", NST);
	//fprintf(p,"���ϵ�λ���Ⱦ��ֵʱ�Ĳ�����=%ld��\n",INS);
	fprintf(p, "Ҫ��ɨ�������ȵ�λ�ߵĵ�λ���ֵ���λֵ=");
	for (i = 1; i<m; i++)
		fprintf(p, "%lfV��", Ve[i]);
	fprintf(p, "\n\n\t\t\t\t���������(z��r���귽�����񲽳�����)\n");
}

///////////////////////�ռ�糡��ʼ��///////////////////////
void initialize()
{
	int i, j, k;    //ѭ������

					///////////////���м���///////////////
	row = M1 + M2 + 1;
	for (i = 0; i<n; i++)
		col = col + N[i] + 1;

	///////////////������������///////////////
	np = (int*)calloc((n + 1) * sizeof(int), sizeof(int));  //�缫λ�ø������ڴ�
	np[0] = 0;
	for (i = 1; i<n + 1; i++)
	{
		if (i == n)
			np[i] = np[i - 1] + N[i - 1];    //ӫ�������λ��
		else
			np[i] = np[i - 1] + N[i - 1] + 1;  //�缫�ұ߽���λ��
	}
	zl = (double**)calloc((row - 1) * sizeof(double*), sizeof(double));  //z�����ڸ�㲽�������ڴ�
	for (i = 0; i<row - 1; i++)
		zl[i] = (double*)calloc((col - 1) * sizeof(double), sizeof(double));

	///////////////z�����ڸ�㲽������///////////////
	j = 1;      //�缫����
	for (i = 0; i<col - 1; i++)
	{
		if (((i + 1) != np[j]) || (j == n))
		{
			for (k = 0; k<row - 1; k++)
				zl[k][i] = dz[j - 1] / N[j - 1];
		}
		else
		{
			for (k = 0; k<row - 1; k++)
				zl[k][i] = d;
			j++;
		}
	}

	///////////////���z������λ�ü�������///////////////
	fprintf(p, "z���귽��\n");
	for (i = 0; i<col; i++)
		fprintf(p, "%ld\t\t", i);
	z = (double*)calloc(col * sizeof(double), sizeof(double));
	for (i = 0; i<col; i++)
	{
		if (i == 0)
		{
			z[i] = 0;
			fprintf(p, "\n%.2lf\t", z[i]);
		}
		else
		{
			z[i] = z[i - 1] + zl[0][i - 1];
			fprintf(p, "%.2lf\t", z[i]);
		}
	}
	rl = (double**)calloc((row - 1) * sizeof(double*), sizeof(double));  //r�����ڸ�㲽�������ڴ�
	for (i = 0; i<row - 1; i++)
		rl[i] = (double*)calloc((col - 1) * sizeof(double), sizeof(double));

	///////////////r�����ڸ�㲽������///////////////
	for (i = 0; i<col - 1; i++)
	{
		for (j = 0; j<row - 1; j++)
		{
			if (j<M1)
				rl[j][i] = r1 / M1;
			else
				rl[j][i] = r2 / M2;
		}
	}

	///////////////���r������λ�ü�������///////////////
	fprintf(p, "\nr���귽��\n");
	for (i = 0; i<row; i++)
		fprintf(p, "%ld\t\t", i);
	r = (double*)calloc(row * sizeof(double), sizeof(double));
	for (i = 0; i<row; i++)
	{
		if (i == 0)
		{
			r[i] = 0;
			fprintf(p, "\n%.2lf\t", r[i]);
		}
		else
		{
			r[i] = r[i - 1] + rl[i - 1][0];
			fprintf(p, "%.2lf\t", r[i]);
		}
	}
	fprintf(p, "\n\n");

	///////////////����λ��ʼ��///////////////
	V1 = (double**)calloc(row * sizeof(double*), sizeof(double));  //����λ�����ڴ�
	for (i = 0; i<row; i++)
		V1[i] = (double*)calloc(col * sizeof(double), sizeof(double));
	for (i = 0; i<row; i++)  //����λ�õ�λ��ʼ����ֵ
		V1[i][0] = 0;
	for (i = 1; i<n + 1; i++)  //�缫λ�õ�λ��ʼ����ֵ
	{
		if (i == n)
		{
			for (j = 0; j<row; j++)
				V1[j][np[i]] = V[i - 1];
		}
		else
		{
			for (j = M1; j<row; j++)
			{
				V1[j][np[i] - 1] = V[i - 1];
				V1[j][np[i]] = V[i - 1];
			}
		}
	}
	j = 1;      //�缫����
	for (k = 1; k<col - 1; k++)  //�ϱ߽�缫���λ��ʼ����ֵ
	{
		if (((k<np[n])&(k>np[n - 1])) || ((k<np[j] - 1)&(k>np[j - 1])))
		{
			if (j == 1)
				V1[row - 1][k] = V1[row - 1][k - 1] + V[j - 1] / N[j - 1];
			else
				V1[row - 1][k] = V1[row - 1][k - 1] + (V[j - 1] - V[j - 2]) / N[j - 1];
		}
		else
		{
			if ((k != np[j])&(k != np[j - 1]))
				j++;
		}
	}
}

//////////////////////////�ռ�糡�ֲ�����/////////////////////////
void calculate()
{
	int i, j, k, rule;
	T = 1;
	Time = 1;
	Timeall = 0;
	w = 1;
	SOR();   //��һ�ֵ���
	Timeall++;
	fprintf(p, "�����ִΣ�%-3ld\t\t����������%-3ld\t\tÿ�ֵ�������ֵ:%lf\t\t", T, Timeall, w);
	fprintf(p, "ÿ�ֵ�������ʱƽ���в%lf\t\t���в%lf\n", Vda, Vdm);
	w = 1.375;
	T++;
	for (Time = 1; Time<13; Time++)
	{
		SOR();   //�ڶ��ֵ���
		Timeall++;
		if (Time == 11)
			Vda1 = Vda;
		else if (Time == 12)
			Vda2 = Vda;
	}
	fprintf(p, "�����ִΣ�%-3ld\t\t����������%-3ld\t\tÿ�ֵ�������ֵ:%lf\t\t", T, Timeall, w);
	fprintf(p, "ÿ�ֵ�������ʱƽ���в%lf\t\t���в%lf\n", Vda, Vdm);
	x = Vda2 / Vda1;
	ux = (x + w - 1) / (sqrt(x)*w);
	wx = 2 / (1 + sqrt(1 - ux * ux));
	wm = 1.25*wx - 0.5;
	do
	{
		w = wm;
		T++;
		for (Time = 1; Time<13; Time++)
		{
			SOR();   //�����ֵ���
			Timeall++;
			if (Time == 11)
				Vda1 = Vda;
			else if (Time == 12)
				Vda2 = Vda;
		}
		fprintf(p, "�����ִΣ�%-3ld\t\t����������%-3ld\t\tÿ�ֵ�������ֵ:%lf\t\t", T, Timeall, w);
		fprintf(p, "ÿ�ֵ�������ʱƽ���в%lf\t\t���в%lf\n", Vda, Vdm);
		wm1 = wm;
		x = Vda2 / Vda1;
		ux = (x + w - 1) / (sqrt(x)*w);
		wx = 2 / (1 + sqrt(1 - ux * ux));
		wm = 1.25*wx - 0.5;
	} while (fabs((wm - wm1) / (2 - wm1)) >= 0.05);
	w = wm;
	do
	{
		T++;
		SOR();   //��ѵ�������ȷ�����������
		Timeall++;
		fprintf(p, "�����ִΣ�%-3ld\t\t����������%-3ld\t\tÿ�ֵ�������ֵ:%lf\t\t", T, Timeall, w);
		fprintf(p, "ÿ�ֵ�������ʱƽ���в%lf\t\t���в%lf\n", Vda, Vdm);
		rule = 0;
		for (i = 0; i<row; i++)
			for (j = 0; j<col; j++)
			{
				if (Vd[i][j] >= e)
					rule++;
			}
	} while (rule>0);

	//////////////////����ռ�糡��������//////////////////
	fprintf(p, "\n\t\t\t\t������ϵĵ�λֵ\n\t\t");
	for (i = 0; i<col; i++)
	{
		fprintf(p, "%ld\t\t\t", i);
		i = i + NST - 1;
	}
	fprintf(p, "\n");
	for (i = row - NST; i >= 0; i--)
	{
		fprintf(p, "%ld\t\t", i);
		for (j = 0; j<col; j++)
		{
			fprintf(p, "%lf\t", V1[i][j]);
			j = j + NST - 1;
		}
		fprintf(p, "\n");
		i = i - NST + 1;
	}
}

////////////////////////SOR�㷨/////////////////////////
void SOR()
{
	int i, j, k;   //ѭ������
	Vd = (double**)calloc(row * sizeof(double*), sizeof(double));  //����λ�в�����ڴ�
	for (i = 0; i<row; i++)
		Vd[i] = (double*)calloc(col * sizeof(double), sizeof(double));
	for (i = 0; i<row; i++)
	{
		for (j = 0; j<col; j++)
		{
			int judge = 1;   //�߽���ж�ָ��
			if ((i != row - 1)&(j != 0)&(j != col - 1))   //�߽���ж�
			{
				if (i>M1 - 1)
				{
					for (k = 1; k<n; k++)
					{
						judge = 0;
						if ((j == np[k] - 1) || (j == np[k]))
						{
							judge = 1;
							k = n;
						}
					}
				}
				else
					judge = 0;
			}
			if (judge == 0)   //�Ǳ߽�����
			{
				c1 = 2 / (zl[i][j - 1] * (zl[i][j - 1] + zl[i][j]));   //ϵ������
				c2 = 2 / (zl[i][j] * (zl[i][j - 1] + zl[i][j]));
				if (i == 0)
				{
					c3 = 0;
					c4 = 4 / (rl[i][j] * rl[i][j]);
				}
				else
				{
					c3 = (2 * r[i] - rl[i][j]) / (r[i] * rl[i - 1][j] * (rl[i - 1][j] + rl[i][j]));
					c4 = (2 * r[i] + rl[i - 1][j]) / (r[i] * rl[i][j] * (rl[i - 1][j] + rl[i][j]));
				}
				c0 = c1 + c2 + c3 + c4;
				if (i != 0)
					V2 = (1 - w)*V1[i][j] + w * (c1*V1[i][j - 1] + c2 * V1[i][j + 1] + c3 * V1[i - 1][j] + c4 * V1[i + 1][j]) / c0;
				else
					V2 = (1 - w)*V1[i][j] + w * (c1*V1[i][j - 1] + c2 * V1[i][j + 1] + c4 * V1[i + 1][j]) / c0;
				Vd[i][j] = fabs(V2 - V1[i][j]);
				V1[i][j] = V2;
			}
		}
	}
	Vds = 0;
	Vdm = 0;
	for (i = 0; i<row; i++)
	{
		for (j = 0; j<col; j++)
		{
			Vds = Vds + Vd[i][j];
			if (Vd[i][j]>Vdm)
				Vdm = Vd[i][j];
		}
	}
	Vda = Vds / (row*col);
}

////////////////////////���Ƶ�λ��////////////////////////
void equal()
{
	int i, i1, j, j1, k, l, c, b, pan, f, f1, f2, f3, f4, f5, f6, *hi;
	double a = 0, zlm, rlm, zrlm;
	if (m == 2)
	{
		for (m = 1; a<(V[n - 1] - dV); m++)   //�����λ����
			a = a + dV;
		Ve = (double*)calloc((m - 1) * sizeof(double), sizeof(double));
		for (i = 0; Ve[i]<(V[n - 1] - dV); i++)
			Ve[i + 1] = Ve[i] + dV;         //���������λֵ
	}

	//////////////////�����λ������//////////////////
	initgraph(100 + int(10 * z[col - 1]), 100 + int(10 * r[row - 1]));   //����ര�ڱ�Ե���ܾ�50������ֵ������10��
	setbkcolor(BLACK);   //���ú�ɫ����
	cleardevice();
	rectangle(50, 50, 50 + int(10 * z[col - 1]), 50 + int(10 * r[row - 1]));   //�ര�ڱ�Ե���ܾ�50������
	for (i = 1; i<n; i++)
		bar(50 + int(10 * z[np[i] - 1]), 50, 50 + int(10 * (z[np[i]])), 50 + int(10 * r2));   //���缫
	zp = (double*)calloc(row*col * sizeof(double), sizeof(double));   //�ȵ�λ��z����ֵ�����ڴ�
	rp = (double*)calloc(row*col * sizeof(double), sizeof(double));   //�ȵ�λ��r����ֵ�����ڴ�
	Vzp = (double*)calloc(row*col * sizeof(double), sizeof(double));  //����10���ĵȵ�λ��z����ֵ�����ڴ�
	Vrp = (double*)calloc(row*col * sizeof(double), sizeof(double));  //����10���ĵȵ�λ��r����ֵ�����ڴ�
	zlm = zl[0][0];
	for (i = 0; i<col - 1; i++)
	{
		if (zlm<zl[0][i])
			zlm = zl[0][i];        //����z�����������
	}
	rlm = rl[0][0];
	if (rlm<rl[row - 2][0])
		rlm = rl[row - 2][0];        //����r�����������
	zrlm = sqrt(zlm*zlm + rlm * rlm);	 //����Խ��߷��������
	for (k = 1; k<m; k++)
	{
		f1 = 0;    //��¼���еȵ�λ��������ʼ��
		l = 0;     //�ȵ�λ��������ʼ��
		for (i1 = row - 1; i1 >= 0; i1--)
		{
			for (j1 = 0; j1<col - 1; j1++)   //z�᷽�����Բ�ֵ����ȵ�λ������
			{
				if (((V1[i1][j1]<Ve[k])&(Ve[k]<V1[i1][j1 + 1])) || ((V1[i1][j1]>Ve[k])&(Ve[k]>V1[i1][j1 + 1])) || (V1[i1][j1] == Ve[k]))
				{
					rp[l] = r[i1];
					if (rp[l] == r[row - 1])
						f1++;          //���б��ֵ��¼���еȵ�λ���������ڿ��Ƶ�λ�߻���
					if (V1[i1][j1] == Ve[k])
						zp[l] = z[j1];
					else
						zp[l] = z[j1] + (Ve[k] - V1[i1][j1])*zl[0][j1] / (V1[i1][j1 + 1] - V1[i1][j1]);
					Vrp[l] = 50 + 10 * (r[row - 1] - rp[l]);  //����10�����ͼ������ 
					Vzp[l] = 50 + 10 * zp[l];             //����10�����ͼ������ 
					l++;
				}
			}
			for (j = 0; j<col; j++)        //r�᷽�����Բ�ֵ����ȵ�λ������
			{
				if (i1>0)
				{
					i = i1;
					if (((V1[i][j]<Ve[k])&(Ve[k]<V1[i - 1][j])) || ((V1[i][j]>Ve[k])&(Ve[k]>V1[i - 1][j])))
					{
						zp[l] = z[j];
						rp[l] = r[i] - (Ve[k] - V1[i][j])*rl[i - 1][0] / (V1[i - 1][j] - V1[i][j]);
						Vrp[l] = 50 + 10 * (r[row - 1] - rp[l]);   //����10�����ͼ������
						Vzp[l] = 50 + 10 * zp[l];              //����10�����ͼ������
						l++;
					}
				}
			}
		}

		//////////////////���Ƶ�λ��//////////////////
		f = 0;   //�����߶����λ�ñ�����ʼ��
		c = 0;   //�������ӹ��ĵȵ�λ��λ��ѭ��������ʼ��
		f6 = 0;  //���ڼ�¼��λ���ڵ缫��λʱ�ĵ缫λ�ó�ʼ��
		hi = (int*)calloc(l * sizeof(int), sizeof(int));   //�������ӹ��ĵȵ�λ��λ��
		do
		{
			fprintf(p, "\n��λֵΪ%lf�ĵ�λ�ߵĸ�������ֵ��\n", Ve[k]);
			setcolor(20 * k*RED + 10 * k*GREEN + BLUE);    //ȷ����λ����ɫ
			for (i = 0; i<l; i++)
			{
				pan = 1;
				for (b = 0; b<c; b++)    //�ж��Ƿ�Ϊ�����ӹ��ĵ�
				{
					if (i == hi[b])
					{
						pan = 0;
						break;
					}
				}
				if ((pan == 1)&(rp[i] == r[row - 1]))    //�����а���ʱ�ҳ���һ����λ�ߵ����λ��
				{
					f = i;
					break;
				}
			}
			for (i = f; i<l; i++)
			{
				for (j = 0; j<l; j++)
				{
					pan = 1;
					for (b = 0; b<c; b++)    //�ж��Ƿ�Ϊ�����ӹ��ĵ�
					{
						if (j == hi[b])
						{
							pan = 0;
							break;
						}
					}
					if ((j != i)&(pan == 1)&(sqrt((Vzp[j] - Vzp[i])*(Vzp[j] - Vzp[i]) + (Vrp[j] - Vrp[i])*(Vrp[j] - Vrp[i]))<12 * zrlm)&(fabs(Vzp[j] - Vzp[i])<12 * zlm)&(fabs(Vrp[j] - Vrp[i])<12 * rlm))
					{    //����ڶ��㲻�ǵ�һ�� �� ���������ӹ��ĵ� �� ����֮���������Ҫ��
						f3 = 0;
						for (f2 = 0; f2<n; f2++)    //������ڵ缫��λ���¼�缫λ�ò������
						{
							if (Ve[k] == V[f2])
							{
								f3 = 1;    //�����
								f6 = f2;   //��¼�缫λ��
								break;
							}
						}
						if ((f3 == 1)&((z[np[f6 + 1]] == zp[j]) || (z[np[f6 + 1] - 1] == zp[j]))&(r[row - 1] == rp[j]))
						{    //����ǵ缫��λ�ҵڶ���Ϊ�缫��������λ����������¡�Z���������ӵ缫��λ��
							for (f2 = 0; f2<M2; f2++)
							{
								fprintf(p, "(%lf\t,\t%lf\t)\n", rp[i], zp[i]);   //�����һ������
								if (rp[i] == r[row - 1])
									f1--;     //�����һ���ڶ�������ֵ��1
								line(int(Vzp[i]), int(Vrp[i]), int(Vzp[j]), int(Vrp[j]));
								hi[c] = i;      //��¼��һ��λ��
								c++;
								fprintf(p, "(%lf\t,\t%lf\t)\n", rp[j], zp[j]);   //����ڶ�������
								if (rp[j] == r[row - 1])
									f1--;	  //����ڶ����ڶ�������ֵ��1			
								for (f4 = 0; f4<l; f4++)
								{
									if ((zp[f4] == zp[i])&(rp[f4] == rp[i] - r2 / M2))
									{
										i = f4;      //Ѱ����һ����һ��
										break;
									}
								}
								line(int(Vzp[j]), int(Vrp[j]), int(Vzp[i]), int(Vrp[i]));
								hi[c] = j;
								c++;
								for (f5 = 0; f5<l; f5++)
								{
									if ((zp[f5] == zp[j])&(rp[f5] == rp[j] - r2 / M2))
									{
										j = f5;      //Ѱ����һ���ڶ���
										break;
									}
								}
							}
							fprintf(p, "(%lf\t,\t%lf\t)\n", rp[i], zp[i]);  //����缫�׶�����λ������
							if (rp[i] == r[row - 1])
								f1--;			//����˵��ڶ�������ֵ��1		
							line(int(Vzp[i]), int(Vrp[i]), int(Vzp[j]), int(Vrp[j]));   //���ӵ缫�׶�ˮƽ��
							hi[c] = i;            //��¼�缫�׶�����λ��λ��
							c++;
							break;
						}
						else if ((f3 == 1)&((z[np[f6 + 1]] == zp[j]) || (z[np[f6 + 1] - 1] == zp[j]))&(r[row - 1] != rp[j]))
						{   //����ǵ缫��λ�ҵڶ��㲻�ǵ缫��������λ����������ϵ���Z���������ӵ缫��λ��
							fprintf(p, "(%lf\t,\t%lf\t)\n", rp[i], zp[i]);
							if (rp[i] == r[row - 1])
								f1--;
							line(int(Vzp[i]), int(Vrp[i]), int(Vzp[j]), int(Vrp[j]));
							hi[c] = i;
							c++;
							fprintf(p, "(%lf\t,\t%lf\t)\n", rp[j], zp[j]);
							if (rp[j] == r[row - 1])
								f1--;
							for (f4 = 0; f4<l; f4++)
							{
								if ((zp[f4] == zp[np[f6 + 1]])&(rp[f4] == rp[M1]))
								{
									i = f4;
									j = f4 - 1;
									break;
								}
							}
							for (f2 = 0; f2<M2; f2++)
							{
								fprintf(p, "(%lf\t,\t%lf\t)\n", rp[i], zp[i]);
								if (rp[i] == r[row - 1])
									f1--;
								line(int(Vzp[i]), int(Vrp[i]), int(Vzp[j]), int(Vrp[j]));
								hi[c] = i;
								c++;
								fprintf(p, "(%lf\t,\t%lf\t)\n", rp[j], zp[j]);
								if (rp[j] == r[row - 1])
									f1--;
								for (f4 = 0; f4<l; f4++)
								{
									if ((zp[f4] == zp[i])&(rp[f4] == rp[i] + r2 / M2))
									{
										i = f4;
										break;
									}
								}
								line(int(Vzp[j]), int(Vrp[j]), int(Vzp[i]), int(Vrp[i]));
								hi[c] = j;
								c++;
								for (f5 = 0; f5<l; f5++)
								{
									if ((zp[f5] == zp[j])&(rp[f5] == rp[j] + r2 / M2))
									{
										j = f5;
										break;
									}
								}
							}
							fprintf(p, "(%lf\t,\t%lf\t)\n", rp[i], zp[i]);
							if (rp[i] == r[row - 1])
								f1--;
							line(int(Vzp[i]), int(Vrp[i]), int(Vzp[j]), int(Vrp[j]));
							hi[c] = i;
							c++;
							break;
						}
						else
						{   //����ڶ��㲻�ǵ缫����λ���������һ�����겢���ӵ�һ����
							fprintf(p, "(%lf\t,\t%lf\t)\n", rp[i], zp[i]);
							if (rp[i] == r[row - 1])
								f1--;
							line(int(Vzp[i]), int(Vrp[i]), int(Vzp[j]), int(Vrp[j]));
							hi[c] = i;
							c++;
							break;
						}
					}
				}
				if ((rp[j] == r[0]) || (rp[j] == r[row - 1]))
				{   //����ڶ���λ�ڶ��л����������ڶ������겢����ѭ���ж��Ƿ�����һ����λ��
					fprintf(p, "(%lf\t,\t%lf\t)\n", rp[j], zp[j]);
					if (rp[j] == r[row - 1])
						f1--;
					hi[c] = j;
					c++;
					break;
				}
				else   //����ڶ��㲻λ�ڶ��л�����򽫵ڶ�����Ϊ��һ��ѭ���ĵ�һ��
					i = j - 1;
			}
		} while (f1>0);      //������б��ֵ��Ϊ0���������������һ����λ��
	}
	fclose(p);
	system("pause");
	closegraph();
}
