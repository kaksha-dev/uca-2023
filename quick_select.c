#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void* swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {

        if (arr[j] < pivot) { 
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void findMedians(int* nums, int* medians, int numSize) {
    int groups = numSize / 5;
    if(numSize%5 != 0) groups++;
    int groupSize = 5;

    for(int i = 0; i < groups; i++) {
        if(i == groups-1) groupSize = numSize-(groups-1)*5;
        qsort(nums+5*i, groupSize, sizeof(int), compare);
        medians[i] = nums[5*i+groupSize/2];
    }
}

int findKthLargest(int* nums, int numsSize, int k) {
    if(numsSize == 1) return nums[0];

    int groups = numsSize / 5;
    if(numsSize%5 != 0) groups++;
    int* medians = (int *) malloc(sizeof(int)*groups);
    qsort(medians, groups, sizeof(int), compare);

    findMedians(nums, medians, numsSize);
    int median = findKthLargest(medians, groups, groups/2); // Find Median of Medians.
    for(int i=0; i < numsSize;  i++)
        if(nums[i] == median)
            swap(&nums[i], &nums[numsSize-1]);
        
    int pivotIndex = partition(nums, 0, numsSize-1);
    if(k < pivotIndex) {
        if(pivotIndex == 0 || pivotIndex <= k)
        return findKthLargest(nums, pivotIndex-1, k);
    }
    else if(k > pivotIndex) return findKthLargest(nums+pivotIndex+1, numsSize-pivotIndex-1, k-pivotIndex-1);
    return nums[pivotIndex];

}


int main()
{
    int nums[10] = {4, 5, 2, 1, 3, 17, 1, 21, 8, 13};
    int expected_nums[10] = {1, 2, 3, 4, 5, 1, 8, 13, 17, 21};
    int expected_medians[2] = {3, 13};
    int* medians = (int *) malloc(sizeof(int)*2);
    findMedians(nums, medians, 10);
    for(int i = 0; i<10; i++) assert(nums[i] == expected_nums[i]);
    for(int i = 0; i<2; i++) assert(medians[i] == expected_medians[i]);
    

    int nums_1[9] = {5, 2, 1, 3, 17, 1, 21, 8, 13};
    int expected_nums_1[9] = {1, 2, 3, 5, 17, 1, 8, 13, 21};
    int expected_medians_1[2] = {3, 13};
    medians = (int *) malloc(sizeof(int)*2);
    findMedians(nums_1, medians, 9);
    for(int i = 0; i<9; i++) assert(nums_1[i] == expected_nums_1[i]);
    for(int i = 0; i<2; i++) assert(medians[i] == expected_medians_1[i]);
    

    int nums_2[11] = {5, 2, 1, 3, 35, 2, 17, 1, 21, 8, 13};
    int expected_nums_2[11] = {1, 2, 3, 5, 35, 1, 2, 8, 17, 21, 13};
    int expected_medians_2[3] = {3, 8, 13};
    medians = (int *) malloc(sizeof(int)*3);
    findMedians(nums_2, medians, 11);
    for(int i = 0; i<11; i++) assert(nums_2[i] == expected_nums_2[i]);
    for(int i = 0; i<3; i++) assert(medians[i] == expected_medians_2[i]);
    

    int nums_3[1] = {5};
    int expected_nums_3[1] = {5};
    medians = (int *) malloc(sizeof(int)*1);
    findMedians(nums_3, medians, 1);
    for(int i = 0; i<1; i++) assert(nums_3[i] == expected_nums_3[i]);

    int nums_4[9] = {3, 2, 1, 4, 5, 6, -2, -7, 9};
    printf("%d \n", findKthLargest(nums_4, 9, 4));
    assert(findKthLargest(nums_4, 9, 4) == 2);
    
    
    return 0;
}