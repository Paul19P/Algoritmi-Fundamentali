from collections import defaultdict
class Solution:
    def accountsMerge(self, accounts):
        def find(x):
            if tata[x] != x:
                tata[x] = find(tata[x])
            return tata[x]

        def union(x, y):
            r1 = find(x)
            r2 = find(y)
            if r1 != r2:
                tata[r2] = r1

        tata = {}
        emailtoname = {}
        for acct in accounts:
            name = acct[0]
            for email in acct[1:]:
                emailtoname[email] = name
                tata[email] = email

        for acct in accounts:
            email1 = acct[1]
            for email2 in acct[2:]:
                union(email1, email2)

        groups = defaultdict(list)
        for email in tata:
            r = find(email)
            groups[r].append(email)

        ans = []
        for key in groups:
            ans.append([emailtoname[key]] + sorted(groups[key]))

        return ans
