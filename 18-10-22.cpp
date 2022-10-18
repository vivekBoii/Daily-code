#include "bits/stdc++.h"
using namespace std;

// git problem resolved
// click on window button > credential manager > Windows credentials > Generic credentials
// Next, remove or edit the Github keys.

/* longest common subsequence 
    0. writing base condition wrong
    1. (ind1 < 0 or ind2 < 0) => (ind1 == 0 or ind2 == 0) , base condition
    2. (s1[ind1] == s2[ind2]) => (s1[ind1-1] == s2[ind2-1]) , comparision
    3. n => n + 1 , during dp decleration
    4. for i -> n : (not n-1)
        for j -> m : (not m-1)
    */
    // brute   
        class Solution {
        public:
            int pre(int ind1,int ind2,string & s1,string & s2){
                if(ind1 < 0 or ind2 < 0) return 0; // ⭐
                if(s1[ind1] == s2[ind2])
                    return 1 + pre(ind1-1,ind2-1,s1,s2);
                else return max(pre(ind1-1,ind2,s1,s2),pre(ind1,ind2-1,s1,s2));
            }
            int longestCommonSubsequence(string s1, string s2) {
                int n = s1.size();
                int m = s2.size();
                vector<vector<int>> dp(n,vector<int> (m+1,-1));
                return pre(n-1,m-1,s1,s2);
            }
        };

    // memo
        class Solution {
        public:
            int pre(int ind1,int ind2,string & s1,string & s2,vector<vector<int>> &dp){
                if(ind1 < 0 or ind2 < 0) return 0;
                if(dp[ind1][ind2] != -1) return dp[ind1][ind2];
                if(s1[ind1] == s2[ind2])
                    return 1 + pre(ind1-1,ind2-1,s1,s2,dp);
                else return dp[ind1][ind2] = max(pre(ind1-1,ind2,s1,s2,dp),pre(ind1,ind2-1,s1,s2,dp));
            }
            int longestCommonSubsequence(string s1, string s2) {
                int n = s1.size();
                int m = s2.size();
                vector<vector<int>> dp(n,vector<int> (m+1,-1));
                return pre(n-1,m-1,s1,s2,dp);
            }
        };

    // memo code with index change
        class Solution {
        public:
            int pre(int ind1,int ind2,string & s1,string & s2,vector<vector<int>> &dp){
                if(ind1 == 0 or ind2 == 0) return 0; // ⭐
                if(dp[ind1][ind2] != -1) return dp[ind1][ind2];
                if(s1[ind1-1] == s2[ind2-1]) // ⭐
                    return 1 + pre(ind1-1,ind2-1,s1,s2,dp);
                else return dp[ind1][ind2] = max(pre(ind1-1,ind2,s1,s2,dp),pre(ind1,ind2-1,s1,s2,dp));
            }
            int longestCommonSubsequence(string s1, string s2) {
                int n = s1.size(), m = s2.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,-1)); // ⭐
                return pre(n,m,s1,s2,dp);
            }
        };

    // tab
        class Solution {
        public:
            int longestCommonSubsequence(string s1, string s2) {
                int n = s1.size(), m = s2.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,0));
                                    
                for(int ind1=1;ind1<=n;ind1++){
                    for(int ind2=1;ind2<=m;ind2++){
                        if(s1[ind1-1] == s2[ind2-1])
                            dp[ind1][ind2] = dp[ind1-1][ind2-1] + 1;
                        else dp[ind1][ind2] = max(dp[ind1-1][ind2],dp[ind1][ind2-1]);
                    }
                }
                            
                return dp[n][m];
            }
        };

    // optimize
        class Solution {
        public:
            int longestCommonSubsequence(string s1, string s2) {
                int n = s1.size(), m = s2.size();
                vector<int> dp(m+1,0),curr(m+1,0);
                                    
                for(int ind1=1;ind1<=n;ind1++){ // ⭐
                    for(int ind2=1;ind2<=m;ind2++){ // ⭐ 
                        if(s1[ind1-1] == s2[ind2-1])
                            curr[ind2] = dp[ind2-1] + 1;
                        else curr[ind2] = max(dp[ind2],curr[ind2-1]);
                    }
                    dp = curr;
                }
                            
                return dp[m];
            }
        };

/* Printing longest common subsequence */
    // optimal
        class Solution {
        public:
            int longestCommonSubsequence(string s1, string s2) {
                int n = s1.size(), m = s2.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,0));
                                    
                for(int ind1=1;ind1<=n;ind1++){
                    for(int ind2=1;ind2<=m;ind2++){
                        if(s1[ind1-1] == s2[ind2-1])
                            dp[ind1][ind2] = dp[ind1-1][ind2-1] + 1;
                        else dp[ind1][ind2] = max(dp[ind1-1][ind2],dp[ind1][ind2-1]);
                    }
                }
                int i=n,j=m;
                string s="";
                while(i > 0 and j > 0){
                    if(s1[i] == s2[j]){
                        s.push_back(s1[i]);
                        i--,j--;
                    }else if(dp[i-1][j] > dp[i][j-1]){
                        i--;
                    }else{
                        j--;
                    }
                }
                reverse(s.begin(),s.end());
                cout<<s<<endl;
                return dp[n][m];
            }
        };

/* Printing longest common subsequence all */
/* Longest Common Substring 
    1. approach unique
    2. res maintain and store in the incremented value ( res = incremented)
    3. else case have the maximum
    4. tab code , (s1[i] == s2[j]) => (s1[i-1] == s2[j-1])
    */
    // brute ❌
        #include <bits/stdc++.h> 
        int pre(int i,int j,string &s1,string &s2,int res){
            if(i < 0 or j < 0) return res;
            if(s1[i] == s2[j]){
                res = pre(i-1,j-1,s1,s2,res+1); // ⭐
            }    
            return max({res,pre(i-1,j,s1,s2,0),pre(i,j-1,s1,s2,0)});  // ⭐
        }
        int lcs(string &s1, string &s2){
            int n = s1.size(),m = s2.size();
            return pre(n-1,m-1,s1,s2,0);
        }

    // memo : ❌ not working testcase ( str1 = "bc" , str2 = "bcbccc" => 1)
    // tab
        #include <bits/stdc++.h> 
        int lcs(string &s1, string &s2){
            int n = s1.size(),m = s2.size();
            vector<vector<int>> dp(n+1,vector<int> (m+1,0));
            int maxi = 0;
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    if(s1[i-1] == s2[j-1]){ // ⭐ 
                        dp[i][j] = 1 + dp[i-1][j-1];
                    }else dp[i][j] = 0;
                    maxi = max(maxi,dp[i][j]);
                }
            }
            return maxi;    
        }

    // optmize
        #include <bits/stdc++.h> 
        int lcs(string &s1, string &s2){
            int n = s1.size(),m = s2.size();
            vector<int> dp(m+1,0),curr(m+1,0);
            
            int maxi = 0;
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    if(s1[i-1] == s2[j-1]){ // ⭐ 
                        curr[j] = 1 + dp[j-1];
                    }else curr[j] = 0;
                    maxi = max(maxi,curr[j]);
                }
                dp = curr;
            }
            return maxi;    
        }

// Longest Palindromic Subsequence
    // memo
        class Solution {
        public:
            int pre(int i,int j,string &s1,string &s2,vector<vector<int>> &dp){
                if(i == 0 or j == 0) return 0;
                if(dp[i][j] != -1) return dp[i][j];
            
                if(s1[i-1] == s2[j-1])
                    return dp[i][j] = 1 + pre(i-1,j-1,s1,s2,dp);
                else return dp[i][j] = max(pre(i-1,j,s1,s2,dp),pre(i,j-1,s1,s2,dp)); 
            }
            int common(string &s1,string &s2){
                int n = s1.size(), m= s2.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,-1));
                return pre(n,m,s1,s2,dp);
            }
            int longestPalindromeSubseq(string s) {
                string str1 = s,str2 = s;
                reverse(str1.begin(),str1.end());
                return common(str1,str2);
            }
        };

    // tab
        class Solution {
        public:
            int common(string &s1,string &s2){
                int n = s1.size(), m= s2.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,0));
                
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=m;j++){
                        if(s1[i-1] == s2[j-1])
                            dp[i][j] = 1 + dp[i-1][j-1];
                        else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                    }
                }
                
                return dp[n][m];
            }
            int longestPalindromeSubseq(string s) {
                string str1 = s,str2 = s;
                reverse(str1.begin(),str1.end());
                return common(str1,str2);
            }
        };

    // optimize
        class Solution {
        public:
            int common(string &s1,string &s2){
                int n = s1.size(), m= s2.size();
                vector<int> dp(m+1,0),curr(m+1,0);
                
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=m;j++){
                        if(s1[i-1] == s2[j-1])
                            curr[j] = 1 + dp[j-1];
                        else curr[j] = max(dp[j],curr[j-1]);
                    }
                    dp = curr;
                }
                
                return dp[m];
            }
            int longestPalindromeSubseq(string s) {
                string str1 = s,str2 = s;
                reverse(str1.begin(),str1.end());
                return common(str1,str2);
            }
        };

// Minimum Insertion Steps to Make a String Palindrome
    // memo
        class Solution {
        public:
            int pre(int i,int j,string & s1,string & s2,vector<vector<int>> & dp){
                if(i == 0 or j == 0) return 0;
                if(dp[i][j] != -1) return dp[i][j];
                
                if(s1[i-1] == s2[j-1])
                    return dp[i][j] = 1 + pre(i-1,j-1,s1,s2,dp);
                else return dp[i][j] = max(pre(i-1,j,s1,s2,dp),pre(i,j-1,s1,s2,dp));
            }
            int common(string &s1,string &s2){
                int n= s1.size(),m = s1.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,-1));
                return pre(n,m,s1,s2,dp);        
            }
            int minInsertions(string s) {
                string s1=s,s2 =s;
                reverse(s1.begin(),s1.end());
                return s.size() - common(s1,s2);
            }
        };

    // tab
        class Solution {
        public:
            int common(string &s1,string &s2){
                int n= s1.size(),m = s1.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,0));
                
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=m;j++){
                        if(s1[i-1] == s2[j-1])
                            dp[i][j]= 1 + dp[i-1][j-1];
                        else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                    }
                }
                
                return dp[n][m];
            }
            int minInsertions(string s) {
                string s1=s,s2 =s;
                reverse(s1.begin(),s1.end());
                return s.size() - common(s1,s2);
            }
        };
    
    // optimize
        class Solution {
        public:
            int common(string &s1,string &s2){
                int n= s1.size(),m = s1.size();
                // vector<vector<int>> dp(n+1,vector<int> (m+1,0));
                vector<int> dp(m+1,0),curr(m+1,0);
                
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=m;j++){
                        if(s1[i-1] == s2[j-1])
                            curr[j]= 1 + dp[j-1];
                        else curr[j] = max(dp[j],curr[j-1]);
                    }
                    dp = curr;
                }
                
                return dp[m];
            }
            int minInsertions(string s) {
                string s1=s,s2 =s;
                reverse(s1.begin(),s1.end());
                return s.size() - common(s1,s2);
            }
        };

// Delete Operation for Two Strings
    // brute
        class Solution {
        public:
            int pre(int i,int j,string & s1,string & s2){
                if(i == 0 or j == 0) return 0;
                
                if(s1[i-1] == s2[j-1])
                    return 1 + pre(i-1,j-1,s1,s2);
                else return max(pre(i-1,j,s1,s2),pre(i,j-1,s1,s2));
            }
            int common(string &s1,string &s2){
                int n = s1.size(),m = s2.size();
                return pre(n,m,s1,s2);        
            }
            int minDistance(string word1, string word2) {
                return word1.size() + word2.size() - 2*common(word1,word2);   
            }
        };

    // memo
        class Solution {
        public:
            int pre(int i,int j,string & s1,string & s2,vector<vector<int>> &dp){
                if(i == 0 or j == 0) return 0;
                if(dp[i][j] != -1) return dp[i][j];
                
                if(s1[i-1] == s2[j-1])
                    return dp[i][j] = 1 + pre(i-1,j-1,s1,s2,dp);
                else return dp[i][j] = max(pre(i-1,j,s1,s2,dp),pre(i,j-1,s1,s2,dp));
            }
            int common(string &s1,string &s2){
                int n = s1.size(),m = s2.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,-1));
                return pre(n,m,s1,s2,dp);        
            }
            int minDistance(string word1, string word2) {
                return word1.size() + word2.size() - 2*common(word1,word2);   
            }
        };

    // tab
        class Solution {
        public:
            int common(string &s1,string &s2){
                int n = s1.size(),m = s2.size();
                vector<vector<int>> dp(n+1,vector<int> (m+1,0));
                
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=m;j++){
                        if(s1[i-1] == s2[j-1])
                            dp[i][j]= 1 + dp[i-1][j-1];
                        else
                            dp[i][j]= max(dp[i-1][j],dp[i][j-1]);
                    }
                }
                
                return dp[n][m];
            }
            int minDistance(string word1, string word2) {
                return word1.size() + word2.size() - 2*common(word1,word2);   
            }
        };
        
    // optimize
        class Solution {
        public:
            int common(string &s1,string &s2){
                int n = s1.size(),m = s2.size();
                vector<int> dp(m+1,0),curr(m+1,0);
                
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=m;j++){
                        if(s1[i-1] == s2[j-1])
                            curr[j]= 1 + dp[j-1];
                        else
                            curr[j]= max(dp[j],curr[j-1]);
                    }
                    dp = curr;
                }
                
                return dp[m];
            }
            int minDistance(string word1, string word2) {
                return word1.size() + word2.size() - 2*common(word1,word2);   
            }
        };

/* Shortest Common Supersequence 
    1. don't know have any aproach*/
    // brute
    // memo
    // tab
    // optimize