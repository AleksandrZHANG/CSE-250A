/// LeetCode, Medinums1n of Two Sorted Arrays
#include <iostream>

using namespace std;
int main()
{
	int A[6] = {1,1,1,2,2,3};
	int B[7] = {0,1,2,4,5,6,7};
    vector<int>& nums1, vector<int>& nums2;
    int temp1, temp2, flag1, flag2, i;
	float median;
	temp1 = temp2 = flag1 = flag2 = 0;
	int *p=nums1;
	if (nums1.size()%2) 
	{
		median = nums1[nums1.size()/2];
		p += nums1.size()/2;
	}
	else
	{
		median = nums1[nums1.size()/2-1];
		p += nums1.size()/2-1;
		temp1 = nums1[nums1.size()-1];
		flag1++;
		nums1.size()--;
	}
	if (nums2.size()%2) 
	{
		temp2 = nums2[nums2.size()/2];
		flag2++;
	}
	for(i=0;i<nums2.size()/2;i++)
	{
		if (nums2[i]>median && nums2[nums2.size()-1-i]>median)
		{
			if (p==nums1+nums1.size()-1)
				p = nums2-1;
			if (nums2[i]>*(p+1))
				median = *++p;
			else
				median =nums2[i];
		}
		else if (nums2[i]<median && nums2[nums2.size()-1-i]<median)
		{
			if (p==nums1)
				p = nums2+nums2.size();
			if (nums2[nums2.size()-1-i]<*(p-1))
				median = *--p;
			else
				median = nums2[nums2.size()-1-i];
		}
		else
			continue;
	}
	if (flag1*flag2)
	{
		if (temp1>median && temp2>median)
		{
			if (p==nums1+nums1.size()-1)
				p = nums2-1;
			if (temp1>*(p+1) && temp2>*(p+1))
				median = *++p;
			else if (temp1>temp2)
				median = temp2;
			else
				median = temp1;
		}
		else if (temp1<median && temp2<median)
		{
			if (p==nums1)
				p = nums2+nums2.size();
			if (temp1<*(p-1) && temp2<*(p-1))
				median = *--p;
			else if (temp1<temp2)
				median = temp2;
			else
				median = temp1;
		}
	}
	else if (flag1)
	{
		if (temp1>median)
		{
			if (p==nums1+nums1.size()-1)
				p = nums2-1;
			if (temp1>*(p+1))
				median = (*++p+median)/2;
			else
				median = (temp1+median)/2;
		}
		else
		{
			if (p==nums1)
				p = nums2+nums2.size();
			if (temp1<*(p-1))
				median = (*--p+median)/2;
			else
				median = (temp1+median)/2;
		}
	}
	else if (flag2)
	{
		if (temp2>median)
		{
			if (p=nums1+nums1.size()-1)
				p = nums2-1;
			if (temp2>*(p+1))
				median = (*++p+median)/2;
			else
				median = (temp2+median)/2;
		}
		else
		{
			if (p==nums1)
				p = nums2+nums2.size();
			if (temp2<*(p-1))
				median = (*--p+median)/2;
			else
				median = (temp2+median)/2;
		}
	}
	return median;
}
