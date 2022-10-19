#include "bits/stdc++.h"
using namespace std;

/* Distinct Subsequences 
    1. don't remember the approach 
    2. if(i < 0 or j < 0) => if(j < 0) <- 1, if(i < 0) <= 0
    3. pre(i-1,j-1,s,t) => pre(i-1,j-1,s,t) + pre(i-1,j,s,t) 
    4. pre(i,j-1,s,t) + pre(i-1,j,s,t) => pre(i-1,j,s,t) 
    5. for(int j=0;j<=m;j++) => for(int j=1;j<=m;j++) */
    // brute 0 based indexing
        int M = 1e9+7;
        class Solution {
        public:
            int pre(int i,int j,string &s,string &t){
                if(j < 0) return 1; // ⭐
                if(i < 0) return 0; // ⭐
                
                if(s[i] == t[j])
                    return (pre(i-1,j-1,s,t) + pre(i-1,j,s,t))%M;// ⭐
                else return pre(i-1,j,s,t); // ⭐
            }
            int numDistinct(string s, string t) {
                int n = s.size(),m = t.size();
                return pre(n-1,m-1,s,t);
            }
        };

    // brute 1 based indexing
        int M = 1e9+7;
        class Solution {
        public:
            int pre(int i,int j,string &s,string &t){
                if(j == 0) return 1;
                if(i == 0) return 0;
                
                if(s[i-1] == t[j-1])
                    return (pre(i-1,j-1,s,t) + pre(i-1,j,s,t))%M;
                else return pre(i-1,j,s,t);
            }
            int numDistinct(string s, string t) {
                int n = s.size(),m = t.size();
                return pre(n,m,s,t);
            }
        };

    // memo
        int M = 1e9+7;
        class Solution {
        public:
            int pre(int i,int j,string &s,string &t,vector<vector<int>> &dp){
                if(j == 0) return 1;
                if(i == 0) return 0;
                
                if(dp[i][j] != -1) return dp[i][j];
                
                if(s[i-1] == t[j-1])
                    return dp[i][j] = (pre(i-1,j-1,s,t,dp) + pre(i-1,j,s,t,dp))%M;
                else return dp[i][j] = pre(i-1,j,s,t,dp);
            }
            int numDistinct(string s, string t) {
                int n = s.size(),m = t.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,-1));
                return pre(n,m,s,t,dp);
            }
        };

    // tab
        int M = 1e9+7;
        class Solution {
        public:
            int numDistinct(string s, string t) {
                int n = s.size(),m = t.size();
                vector<vector<int>> dp(n+2,vector<int> (m+2,0));
                
                for(int i=0;i<=n;i++) dp[i][0] =1;
                
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=m;j++){ // ⭐
                        if(s[i-1] == t[j-1])
                            dp[i][j] = (dp[i-1][j-1] + dp[i-1][j])%M;
                        else dp[i][j] = dp[i-1][j];   
                    }
                }
                
                return dp[n][m];
            }
        };
    // optimize
        int M = 1e9+7;
        class Solution {
        public:
            int numDistinct(string s, string t) {
                int n = s.size(),m = t.size();
                vector<int> dp(m+2,0),curr(m+2,0);
                
                dp[0] =1;
                curr[0] = 1;
                
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=m;j++){ 
                        if(s[i-1] == t[j-1])
                            curr[j] = (dp[j-1] + dp[j])%M;
                        else curr[j] = dp[j];   
                    }
                    dp = curr;
                }
                
                return dp[m];
            }
        };

/* Edit Distance
    1. no idea of basic case 
        recursion code of 0 based indexing
    2. if(i < 0 or j < 0) <- 0 => if(i < 0) <- j+1 , if(j < 0) <- i+1
    3. <- 1 + common(i-1,j-1,s1,s2), min(common(i-1,j,s1,s2),common(i,j-1,s1,s2)) => min({ 1 + common(i-1,j,s1,s2) , 1 + common(i,j-1,s1,s2) , 1 + common(i-1,j-1,s1,s2) })
        recursion code of 1 based indexing
    4. base conditon
        if(i == 0) <- j+1 , if(j == 0) <- i+1 => if(i == 0) <- j , if(j == 0) <- i
    5. writing base condtion of optimize 
        curr[0] = 1 => curr[0] = i;

        */
    // brute 0 index : TLE
        class Solution {
        public:
            int common(int i,int j,string &s1,string &s2){
                if(i < 0) return j+1;  // ⭐
                if(j < 0) return i+1;  // ⭐
                
                if(s1[i] == s2[j])
                    return 0 + common(i-1,j-1,s1,s2);  // ⭐
                else return min({ 1 + common(i-1,j,s1,s2) , 1 + common(i,j-1,s1,s2) , 1 + common(i-1,j-1,s1,s2) }); // ⭐
                        //              delete              insert                        replace
            }
            int minDistance(string s1, string s2) {
                int n = s1.size(),m = s2.size();
                return common(n-1,m-1,s1,s2);
            }
        };
    
    // brute 1 indexing : TLE
        class Solution {
        public:
            int common(int i,int j,string &s1,string &s2){
                if(i == 0) return j;  // ⭐
                if(j == 0) return i;  // ⭐
                
                if(s1[i-1] == s2[j-1])
                    return 0 + common(i-1,j-1,s1,s2);
                else return min({ 1 + common(i-1,j,s1,s2) , 1 + common(i,j-1,s1,s2) , 1 + common(i-1,j-1,s1,s2) });
                        //              delete              insert                        replace
            }
            int minDistance(string s1, string s2) {
                int n = s1.size(),m = s2.size();
                return common(n,m,s1,s2);
            }
        };

    // memo
        class Solution {
        public:
            int common(int i,int j,string &s1,string &s2,vector<vector<int>> &dp){
                if(i == 0) return j;
                if(j == 0) return i;
                
                if(dp[i][j] != -1) return dp[i][j];
                if(s1[i-1] == s2[j-1])
                    return dp[i][j] = 0 + common(i-1,j-1,s1,s2,dp);
                else return dp[i][j] = min({ 1 + common(i-1,j,s1,s2,dp) , 1 + common(i,j-1,s1,s2,dp) , 1 + common(i-1,j-1,s1,s2,dp) });
                    
            }
            int minDistance(string s1, string s2) {
                int n = s1.size(),m = s2.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,-1));
                return common(n,m,s1,s2,dp);
            }
        };

    // tab
        class Solution {
        public:
            int minDistance(string s1, string s2) {
                int n = s1.size(),m = s2.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,0));
                
                for(int i=0;i<=n;i++) dp[i][0] = i;
                for(int j=0;j<=m;j++) dp[0][j] = j;
                
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=m;j++){
                        if(s1[i-1] == s2[j-1])
                            dp[i][j] = dp[i-1][j-1];
                        else
                            dp[i][j] = min({1 + dp[i-1][j],1 + dp[i][j-1], 1 + dp[i-1][j-1]});
                    }
                }
                
                
                return dp[n][m];
            }
        };

    // optimize
        class Solution {
        public:
            int minDistance(string s1, string s2) {
                int n = s1.size(),m = s2.size();
                vector<int> dp(m+1,0),curr(m+1,0);
                
                // curr[0] = 1; ⭐
                for(int j=0;j<=m;j++) dp[j] = j;
                
                for(int i=1;i<=n;i++){
                    curr[0] = i; // ⭐
                    for(int j=1;j<=m;j++){
                        if(s1[i-1] == s2[j-1])
                            curr[j] = dp[j-1];
                        else
                            curr[j] = min({1 + dp[j],1 + curr[j-1], 1 + dp[j-1]});
                    }
                    dp = curr;
                }
                
                
                return dp[m];
            }
        };

/* Wildcard Matching */
    // brute
    // memo
    // tab
    // optimize