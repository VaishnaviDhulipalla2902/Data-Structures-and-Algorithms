#include<stdio.h>
int b[1000000];
int bs(int a[1000],int n,int k){
    int start=0;
    int end=n;
    int mid;
    while(start<=end){
    	if(k<=a[start]){
    		mid=start;
			return mid;
		}
		if(k>=a[end-1]){
    		return -1;
		}
		mid=start+(end-start)/2;
		if(k==a[mid]){
    		mid++;
            return mid;
    	}
    	if(k<a[mid]){
    		if(mid-1>=0 && a[mid-1]<=k){
    			return mid;
			}
			else 
				end=mid-1;
		}
		if(k>a[mid]){
    		if(mid+1<=end-1 && a[mid+1]>=k){
    			mid++;
    			return mid;
     		}
    		else 
    			start=mid+1;
    	}
    }
}
int main(){
    int a[100000];
    int k=0,n,i,t;//t = no. of test cases
    scanf("%d",&t);
    while(t--){
    	k=0;
    	scanf("%d",&n);
    	for(i=0;i<n;i++) // n = no. of elements in the array
    	    scanf("%d",&a[i]);
		b[k]=a[k];
		k++;
		for(i=1;i<n;i++){
    		if(a[i]>=b[k-1]){
    			b[k++]=a[i];
    		}
    		else{
    			b[bs(b,k,a[i])]=a[i];
    		}
    	}
    	printf("%d\n",k);
    }
    return 0;
}
     

