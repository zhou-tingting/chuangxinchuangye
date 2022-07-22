from itertools import product
from __table import*
#十六进制字符串转换为二进制比特流(每个字符4位)
def hexTobin(hexstr):
    binstr = ""
    decstr = [str(int(i, 16)) for i in hexstr]
    for i in decstr:
        ch_bin = bin(int(i, 10))[2:]
        binstr += (4-len(ch_bin)) * '0' + ch_bin
    return binstr

#二进制比特流转为十六进制字符串
def binTohex(bitstr):
    bitlst = [bitstr[i:i+4] for i in range(0, len(bitstr), 4)]
    hexlst = [hex(int(i, 2))[2:] for i in bitlst]
    return ''.join(hexlst)

#十进制转二进制
def dexTobin(num):
    result=""
    while(num!=0):
        ret = num%2
        num=num//2
        result = str(ret)+result
    return result

#逆P置换/E扩展
def permutate(bitstr,table):
    res = ""
    for i in table:
        res += bitstr[i-1]
    return res

#两个比特串异或
def XOR(str1,str2):
    res = ""
    for i in range(len(str1)):
        xor = int(str1[i]) ^ int(str2[i])
        res += str(xor)
    return res


#计算S盒输入差分
def calculate_in_xor(ciphertext):
    in_xor_list=[]
    for i in range(2):
        c1 = ciphertext[2*i]
        c2 = ciphertext[2*i+1]
        c1 = hexTobin(c1)
        c2 = hexTobin(c2)
        L3 = c1[:32]
        L3_ = c2[:32]
        L3 = permutate(L3,E)
        L3_ = permutate(L3_,E)
        temp = XOR(L3,L3_)
        in_xor_list.append(temp)
    return in_xor_list
#计算S盒输出差分
def calculate_out_xor(plaintext,ciphertext):
    out_xor_list=[]
    for i in range(2):
        c1 = ciphertext[2*i]
        c2 = ciphertext[2*i+1]
        c1 = hexTobin(c1)
        c2 = hexTobin(c2)
        R3 = c1[32:]
        R3_ = c2[32:]
        t1 = XOR(R3,R3_)#密文右半部分差分
        p1 = plaintext[2*i]
        p2 = plaintext[2*i+1]
        p1 = hexTobin(p1)
        p2 = hexTobin(p2)
        L0 = p1[0:32]
        L0_ = p2[0:32]
        t2 = XOR(L0,L0_)
        temp = XOR(t1,t2)
        out_xor_list.append(temp)
    return out_xor_list

        
    
#单个S盒运算
def Sbox(bitstr,num):
    row = int(bitstr[0]+bitstr[-1],2)
    column = int(bitstr[1:-1],2)
    index = row * 16+column
    result = bin(SBOX[num][index])[2:]
    result = '0' * (4-len(result))+result
    return result
    
#构造s盒差分分布表,输入差分64种，输出差分16种
def difference_table():
    table = [[[[]for k in range(16)] for i in range(64)] for j in range(8)]
    for n in range(8):
        for a in range(64):
            for x in range(64):
                B1 = dexTobin(a ^ x)
                t1 = "0" * (6-len(B1))+B1
                B2 = dexTobin(x)
                t2 = "0" * (6-len(B2))+B2
                S_B1 = Sbox(t1,n)
                S_B2 = Sbox(t2,n)
                S_xor = XOR(S_B1,S_B2)
                S_xor = int(S_xor,2)
                table[n][a][S_xor].append(x)
    return table
                
   
#对L3进行E扩展
def E_L3(ciphertext):
    E_L3_result=[]
    for i in range(2):
        bits_ciphertext = hexTobin(ciphertext[2*i])
        c = bits_ciphertext[0:32]
        f= permutate(c,E)
        E_L3_result.append(f)
    return E_L3_result

#寻找k3可能出现的情况
def possible_key3(plaintext,ciphertext):
    E_L3_result = E_L3(ciphertext)
    k3 = [[[] for i in range(8)]for i in range(2)]
    table = difference_table()
    in_xor_list = calculate_in_xor(ciphertext)#S盒输入差分
    out_xor_list = calculate_out_xor(plaintext,ciphertext)#S盒输出差分
    for h in range(2):
        out_xor_list[h] = permutate(out_xor_list[h],P_INV)
    for m in range(2):
        bit6_list =[in_xor_list[m][i:i+6] for i in range(0,48,6)]
        bit4_list = [out_xor_list[m][i:i+4] for i in range(0,32,4)]
        bit6_list_L3 = [E_L3_result[m][i:i+6] for i in range(0,48,6)]
        for i in range(8):
            row = int(bit6_list[i],2)
            column = int(bit4_list[i],2)
            for B in table[i][row][column]:
                B = dexTobin(B)
                B = "0"*(6-len(B))+B
                E_sub3 = bit6_list_L3[i]
                key0 = XOR(B,E_sub3)
                k3[m][i].append(key0)
    return k3


plaintext = ["848BE77BB9194DB1","852D6F03B9194DB1","DB4BB16DFF8C67CF","6A98C6FBFF8C67CF"]
ciphertext = ["4A47BCECFC1A80C3","6674C511D8B64259","55A870BC589330CC","94B120CA76A892C2"]
key3 = possible_key3(plaintext,ciphertext)
round_key3=[]
for i in range(8):
    temp = list(set(key3[0][i]).intersection(set(key3[1][i])))
    round_key3.append(temp)
print(round_key3)
result = product(round_key3[0],round_key3[1],round_key3[2],round_key3[3],round_key3[4],round_key3[5],round_key3[6],round_key3[7])
print("可恢复的第三轮轮密钥的集合：")
for x in result:
    key=""
    for k in range(8):
        key = key+x[k]
    possible_key = binTohex(key)
    print(possible_key)

            
