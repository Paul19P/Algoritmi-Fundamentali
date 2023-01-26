#Complexitate O(n*m)
#calculam cea mai lunga subsecventa (lcs) folosind algoritmul de la punctul a putin modificat
#apoi luam fiecare element (c) al lui lcs si mai intai adaugam elementele din str1 si str2 care nu-s egale cu c apoi c
#si repetam pana cand am parcurs toate elementele lui lcs apoi adaugam ce-a mai ramas din str1 si str2
class Solution:
    def shortestCommonSupersequence(self, str1, str2):
        def longestCommonSubsequence(text1, text2):
            dp = [["" for j in range(len(text2) + 1)] for i in range(len(text1) + 1)]
            for i in range(len(text1) - 1, -1, -1):
                for j in range(len(text2) - 1, -1, -1):
                    if text1[i] == text2[j]:
                        dp[i][j] = text1[i] + dp[i + 1][j + 1]
                    else:
                        if len(dp[i + 1][j]) > len(dp[i][j + 1]):
                            dp[i][j] = dp[i + 1][j]
                        else:
                            dp[i][j] = dp[i][j + 1]
            return dp[0][0]

        ans = ""
        lcs = longestCommonSubsequence(str1, str2)
        p1 = 0
        p2 = 0
        for c in lcs:
            while str1[p1] != c:
                ans += str1[p1]
                p1 += 1
            while str2[p2] != c:
                ans += str2[p2]
                p2 += 1
            ans += c
            p1 += 1
            p2 += 1

        ans += str1[p1:] + str2[p2:]
        return ans