def back(s):
    s = s.lower()
    ret = ""
    for i in range(len(s) - 1, len(s) - 9, -1):
        ret += s[i]
    ret = ret[::-1]
    return ret

lns = []
s = input()
x = ""
while not (len(s) >= 8 and back(s) == '</table>'):
    x += s
    s = input()
x += s

x = x.lower()
x = x.replace(" ", "")
x = x.replace("\n", "")
x = x.replace("\"", "")
x = x[x.find("<table>"):]

def Solve(x):
    for i in range(len(x) - 3):
        if x[i : i + 4] == "<tr>":
            lns.append([])
        elif x[i : i + 3] == "<td":
            j = x[i:].find(">") + i
            par = [x[i : j + 1]]
            h = 1
            w = 1
            for t in range(len(par)):
                if par[t].find("rowspan=") != -1:
                    we = ""
                    X = par[t].find("rowspan=") + 8
                    while '0'<=par[t][X] <= '9':
                        we += par[t][X]
                        X += 1
                    h = int(we)
                if par[t].find("colspan=") != -1:
                    we = ""
                    X = par[t].find("colspan=") + 8
                    while '0' <= par[t][X] <= '9':
                        we += par[t][X]
                        X += 1
                    w = int(we)
            lns[-1].append([h, w])
             
    ans = []
    for i in range(300):
        ans.append([])
        for j in range(2100):
            ans[-1].append(" ")

    y = 0
    for st in lns:
        x = 0
        for cl in st:
            fd = 0
            while fd == 0:
                fd = 1
                for i in range(x, x + cl[1] * 2 + 1):
                    if ans[y][i] == 'g':
                        fd = 0
                        break
                if fd == 0:
                    x += 1

            ly = y + cl[0] * 2
            lx = x + cl[1] * 2

            ans[y][x] = '+'
            ans[y][lx] = '+'
            ans[ly][x] = '+'
            ans[ly][lx] = '+'

            for i in range(x + 1, lx):
                if(ans[y][i] != '+'):
                    ans[y][i] = '-'
                if(ans[ly][i] != '+'):
                    ans[ly][i] = '-'
            for i in range(y + 1, ly):
                if(ans[i][x] != '+'):
                    ans[i][x] = '|'
                if(ans[i][lx] != '+'):
                    ans[i][lx] = '|'
            for i in range(y + 1, ly):
                for j in range(x + 1, lx):
                    ans[i][j] = 'g'
            x = lx
        y += 2

    for i in range(len(ans)):
        while len(ans[i]) > 0 and ans[i][-1] == " ":
            ans[i].pop()
            
    while len(ans) > 0 and len(ans[-1]) == 0:
        ans.pop()
    for i in range(len(ans)):
        for j in range(len(ans[i])):
            if ans[i][j] == 'g':
                ans[i][j] = " "
            print(ans[i][j], end = '')
        print()

Solve(x)
