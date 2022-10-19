#include "bits/stdc++.h"
using namespace std;

/* Best Time to Buy and Sell Stock III 
    1. wrong memo answer b/c take only two transition not 4 only on else part*/
    // brute
        class Solution {
        public:
            int pre(int ind,int buy,int t,int n,vector<int>& prices){
                if(ind == n or t == 0) return 0;
                
                int profit = 0;
                if(buy) profit = max(-prices[ind] + pre(ind+1,0,t-1,n,prices), pre(ind+1,1,t,n,prices));
                else profit = max(prices[ind] + pre(ind+1,1,t-1,n,prices), pre(ind+1,0,t,n,prices));
                
                return profit;
            }
            int maxProfit(vector<int>& prices) {
                int n = prices.size();
                
                return pre(0,1,4,n,prices);
            }
        };

    // memo
        class Solution {
        public:
            int pre(int ind,int buy,int t,int n,vector<int>& prices,vector<vector<vector<int>>> &dp){
                if(ind == n or t == 0) return 0;
                if(dp[ind][buy][t] != -1) return dp[ind][buy][t];

                int profit = 0;
                if(buy) profit = max(-prices[ind] + pre(ind+1,0,t,n,prices,dp), pre(ind+1,1,t,n,prices,dp));
                else profit = max(prices[ind] + pre(ind+1,1,t-1,n,prices,dp), pre(ind+1,0,t,n,prices,dp)); // ⭐

                return dp[ind][buy][t] = profit;
            }
            int maxProfit(vector<int>& prices) {
                int n = prices.size();
                vector<vector<vector<int>>> dp(n+1,vector<vector<int>> (2,vector<int> (4,-1)));

                return pre(0,1,2,n,prices,dp); // ⭐
            } 
        };

    // tab ❌
        class Solution {
        public:
            int pre(int ind,int buy,int t,int n,vector<int>& prices,vector<vector<vector<int>>> &dp){
                if(ind == n or t == 0) return 0;
                if(dp[ind][buy][t] != -1) return dp[ind][buy][t];

                int profit = 0;
                if(buy) profit = max(-prices[ind] + pre(ind+1,0,t,n,prices,dp), pre(ind+1,1,t,n,prices,dp));
                else profit = max(prices[ind] + pre(ind+1,1,t-1,n,prices,dp), pre(ind+1,0,t,n,prices,dp));

                return dp[ind][buy][t] = profit;
            }
            int maxProfit(vector<int>& prices) {
                int n = prices.size();
                vector<vector<vector<int>>> dp(n+1,vector<vector<int>> (2,vector<int> (4,0)));
                
                for(int ind=n-1;ind>=0;ind--){
                    for(int buy=1;buy>=0;buy--){
                        for(int t=2;t>=0;t--){
                            int profit = 0;
                            if(buy) profit = max(-prices[ind] + dp[ind+1][0], dp[ind+1][1]);
                            else profit = max(prices[ind] + dp[ind+1][1], dp[ind+1][0]);
                            dp[ind][buy][t] = profit;
                        }
                    }
                }

                return dp[0][1][2];
            }
        };
    // optimize 