#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int* twoSum(int* nums,int sz,int target)
{
	assert(nums!=NULL);
	int *ret =(int*)malloc(sizeof(int)*2);
	int i = 0;
	for(i=1;i<sz;i++)
	{
		int j = 0;
		for(j=0;j<i;j++)
		{
			if(nums[i]+nums[j]==target)
			{
				*ret= j;
				*(ret+1)=i;
				return ret;
			}
		}
	}
	return ret;
}
int main()
{
	int nums[]={2,7,11,15};
	int sz = sizeof(nums)/sizeof(nums[0]);
	int* ret=twoSum(nums,sz,13);
	printf("%d %d\n",*ret,*(ret+1));
}

