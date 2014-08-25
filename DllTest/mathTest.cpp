#include "mathTest.h"
#include"publicpro.h"
#include "cantools/tools.h"
_USE_CANNP

/*
	�ж��߶�ab�Ƿ���cd�ཻ�� �������p
	�����е㳤����
	��Ҫ�ǵ�ṹ�ĳ�Ա��double�� Ҫ�ж�double�͵����Ƿ�Ϊ���� 0 ���߸�����Ҫ�����һ������
	���ܿ���ʵ�����ཻ�㣬���ֻ���ж��ཻ�Ļ� ���������ȥһЩ���
	*/

/*
�жϸ�����
����ֵ
1��������
0���㣻
-1������
*/////

uint8 dblcmp(double d)//������ȵ��ж�С��0
{
	if (fabs(d) < E) return 0;

	return (d > 0) ? 1 : -1;
}
//������������ˣ�AB * AC
double cross(const Point &A, const Point &B, const Point &C)
{
	return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

int xycmp(double p, double mini, double maxi)
{
	return dblcmp(p - mini) * dblcmp(p - maxi);
}
/*
	ǰ��������a��bcֱ����
	���أ�
	1��ʾa�����߶�bc��
	0��ʾa��b�����c����
	-1��ʾa���߶�bc��
	*/
int betweencmp(const Point &a, const Point &b, const Point &c)
{
	if (fabs(b.x - c.x) > fabs(b.y - c.y)) return xycmp(a.x, min(b.x, c.x), max(b.x, c.x));

	else return xycmp(a.y, min(b.y, c.y), max(b.y, c.y));
}
//�ж��߶�ab�Ƿ���cd�ཻ�� �������p
//����ֵ��0��ʾ���ཻ�� 1��ʾ�淶�ཻ�� 2��ʾ�ǹ淶�ཻ
int segcross(const Point &a, const Point &b, const Point &c, const Point &d, Point &p)//p�������÷�����
{
	double s1, s2, s3, s4;
	uint8 d1, d2, d3, d4;

	d1 = dblcmp(s1 = cross(a, b, c));
	d2 = dblcmp(s2 = cross(a, b, d));
	d3 = dblcmp(s3 = cross(c, d, a));
	d4 = dblcmp(s4 = cross(c, d, b));
	
	//�жϹ淶�ཻ�����㲻���ڶ˵���
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2)
	{
		p.x = (c.x * s2 - d.x * s1) / (s2 - s1);
		p.y = (c.y * s2 - d.y * s1) / (s2 - s1);
		return 1;
	}
	

	// �жϷǹ淶�ཻ�������ڶ˵���
	if (d1*d2*d3*d4)
		return 0;

	if (d1 == 0 && betweencmp(c, a, b) <= 0) {
		p = c;
		return 2;
	}
	if (d2 == 0 && betweencmp(d, a, b) <= 0) {
		p = d;
		return 2;
	}
	if (d3 == 0 && betweencmp(a, c, d) <= 0) {
		p = a;
		return 2;
	}
	if (d4 == 0 && betweencmp(b, c, d) <= 0) {
		p = d;
		return 2;
	}

	return 0;
}
int segcrossEX(const Point &a, const Point &b, const Point &c, const Point &d, Point &p)//p�������÷�����
{
	double s1, s2, s3, s4;
	uint8 d1, d2, d3, d4;

	// �жϷǹ淶�ཻ�������ڶ˵���
	d1 = dblcmp(s1 = cross(a, b, c));
	if (d1 == 0 && IsInLinePart(a, b,c)) {
		p = c;
		return 2;
	}
	d2 = dblcmp(s2 = cross(a, b, d));
	if (d2 == 0 && IsInLinePart(a, b,d)) {
		p = d;
		return 2;
	}
	d3 = dblcmp(s3 = cross(c, d, a));
	if (d3 == 0 && IsInLinePart(c, d,a) ) {
		p = a;
		return 2;
	}
	d4 = dblcmp(s4 = cross(c, d, b));
	if (d4 == 0 && IsInLinePart(c, d,b)) {
		p = d;
		return 2;
	}

	//�жϹ淶�ཻ�����㲻���ڶ˵���
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2)
	{
		p.x = (c.x * s2 - d.x * s1) / (s2 - s1);
		p.y = (c.y * s2 - d.y * s1) / (s2 - s1);
		return 1;
	}
	else
		return 0;
}

//////////////////////////////////////////////////////////////////////////////////////



//�ж�pk �Ƿ����߶�pipj��
bool IsInLinePart(Point pi, Point pj, Point pk)
{
	return (min(pi.x, pj.x) <= pk.x&&pk.x <= max(pi.x, pj.x) && min(pi.y, pj.y) <= pk.y&&pk.y <= max(pi.y, pj.y));
}

//�ж���ƽ���߶�pkpl��pipj�Ƿ����ص�����   
bool onsegment(Point pi, Point pj, Point pk,Point pl) 
{
	bool intersect = IsEqualFloat((pi.y - pk.y)*(pj.x - pk.x),(pj.y - pk.y)*(pi.x - pk.x));
	if (intersect)
		return (IsInLinePart(pi, pj, pk) || IsInLinePart(pi, pj, pl) || IsInLinePart(pk, pl, pi) || IsInLinePart(pk, pl, pj));
	else
		return false;
}
double determinant(double v1, double v2, double v3, double v4)  // ����ʽ  
{
	return (v1*v4 - v2*v3);
}

bool intersect3(Point aa, Point bb, Point cc, Point dd)
{
	double delta = determinant(bb.x - aa.x, cc.x - dd.x, bb.y - aa.y, cc.y - dd.y);
	if (delta <= (1e-6) && delta >= -(1e-6))  // delta=0����ʾ���߶��غϻ�ƽ��  
	{
		return onsegment(aa, bb, cc,dd);
		//return false;
	}
	double namenda = determinant(cc.x - aa.x, cc.x - dd.x, cc.y - aa.y, cc.y - dd.y) / delta;
	if (namenda > 1 || namenda < 0)
	{
		return false;
	}
	double miu = determinant(bb.x - aa.x, cc.x - aa.x, bb.y - aa.y, cc.y - aa.y) / delta;
	if (miu>1 || miu < 0)
	{
		return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////

/**
* @brief ���߶���Բ�Ľ���
* @return ����н��㷵��true,���򷵻�false
* @note ��Բ���ܴ����������㣬�����������������ptInter1��ptInter2��Ϊ��Чֵ�������һ�����㣬��ptInter2��ֵΪ
*       ��Чֵ���˴�Ϊ65536.0
*/
bool LineInterCircle(
	const Point ptStart, // �߶����  
	const Point ptEnd, // �߶��յ�  
	const Point ptCenter, // Բ������  
	const float Radius,
	Point& ptInter1,
	Point& ptInter2)
{
	ptInter1.x = ptInter2.x = 65536.0f;
	ptInter2.y = ptInter2.y = 65536.0f;

	float fDis = sqrt((ptEnd.x - ptStart.x) * (ptEnd.x - ptStart.x) + (ptEnd.y - ptStart.y) * (ptEnd.y - ptStart.y));

	Point d;
	d.x = (ptEnd.x - ptStart.x) / fDis;
	d.y = (ptEnd.y - ptStart.y) / fDis;

	Point E;
	E.x = ptCenter.x - ptStart.x;
	E.y = ptCenter.y - ptStart.y;

	float a = E.x * d.x + E.y * d.y;
	float a2 = a * a;

	float e2 = E.x * E.x + E.y * E.y;

	float r2 = Radius * Radius;

	if ((r2 - e2 + a2) < 0)
	{
		return false;
	}
	else
	{
		float f = sqrt(r2 - e2 + a2);

		float t = a - f;

		if (((t - 0.0) > -EPS) && (t - fDis) < EPS)
		{
			ptInter1.x = ptStart.x + t * d.x;
			ptInter1.y = ptStart.y + t * d.y;
		}

		t = a + f;

		if (((t - 0.0) > -EPS) && (t - fDis) < EPS)
		{
			ptInter2.x = ptStart.x + t * d.x;
			ptInter2.y = ptStart.y + t * d.y;
		}

		return true;
	}
}