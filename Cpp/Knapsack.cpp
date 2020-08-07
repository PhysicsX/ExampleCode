#include <iostream>


// the idea is that first begin from first light element to put in bag in a way that calculate every each size for bag.
// for instance have a 3 kg object, 8 kg bag, there will be 8 iterations for 3 kg object. 
// for w = 1 -> bag is 1 kg, object is greater than the bag so we can not put anything K[0][0] = 0;
// for w = 2 -> bag is 2 kg, object is greater than the bag so we can not put anything K[0][1] = 0; // bag is empty
// for w = 3 -> bag is 3 kg, object is same with bag capacity for right now so K[0][2] = val_of_3kg_object;
// for other cases there is no object so between w = 3 and w = 8 there will be 3 kg object in the bag,
// after for second object calculate that if current bag size is greater or equal then the object weight, then
// check the remaning size in the bag, what was the value before ? so add with current object value and compare 
// it with before object with exact index, if it is greater than save it to map K[i][w]
// finally K[n][W] will be the result.


int knapsack(int W, int wt[], int val[], int n)
{
    int K[n+1][W+1];
    
    for(int i=0; i<=n; i++)
    {
        for(int w=0; w<=W; w++)
        {
                
                int prev = K[i-1][w];
                
                if( i == 0 || w == 0)
                    K[i][w] = 0;
                else if(wt[i-1] <= w)
                {
                    int remainWeight = val[i-1] + K[i-1][w-wt[i-1]];
                    K[i][w] = (prev <= remainWeight) ? remainWeight : prev;
                }
                else
                {
                    K[i][w] = prev;
                }
        }
    }
    
    return K[n][W];
}




int main()
{
    
    
    int val[] = {1,2,5,6};
    int wt[] = {2,3,4,5};
    
    int W = 8;
    int n = sizeof(val)/sizeof(val[0]);
    std::cout<<knapsack(W, wt, val, n);
    
    
    return 0;
}