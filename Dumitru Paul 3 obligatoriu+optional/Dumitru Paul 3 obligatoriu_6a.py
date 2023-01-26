#Complexitate O(n*m)
#Construim o matrice cu len(text1)+1 linii si len(text2)+1 coloane care initial e plina de 0,ultima linie si ultima coloana fiind ajutatoare
#parcurgem matricea,pornind de la ultimul element al matricei si o luam in sus verificam daca text1[i]==text2[j] si daca da,adaugam 1 la distanta din dp[i+1][j+1],daca nu,luam maximul dintre elementul de sub si cel din dreapta
#la final returnam primul element din matrice (dp[0][0])
class Solution(object):
    def longestCommonSubsequence(self, text1, text2):
        dp=[[0 for j in range(len(text2)+1)] for i in range(len(text1)+1)]
        for i in range(len(text1)-1,-1,-1):
            for j in range(len(text2)-1,-1,-1):
                if text1[i]==text2[j]:
                    dp[i][j]=1+dp[i+1][j+1]
                else:
                    dp[i][j]=max(dp[i+1][j],dp[i][j+1])
        return dp[0][0]