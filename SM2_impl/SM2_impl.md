实验内容
====
  基于gmssl库实现SM2加解密算法

运行指导
====
SM2_impl.py为实现代码，可在Thonny或者IDLE上直接运行

代码说明
====
固定SM2的公私钥，调用库函数实现加解密。    
class sm2Encrypt:  
    # 加密  
    def encrypt(self, info):  
        encode_info = sm2_crypt.encrypt(info.encode(encoding="utf-8"))  
        encode_info = b64encode(encode_info).decode()    
        return encode_info  
    # 解密  
    def decrypt(self, info):  
        decode_info = b64decode(info.encode())  
        decode_info = sm2_crypt.decrypt(decode_info).decode(encoding="utf-8")  
        return decode_info  

参考文献
===
https://blog.csdn.net/u014651560/article/details/113744296  

运行结果
===
![U0@4K{367}V6B52YV`(F3HY](https://user-images.githubusercontent.com/109579171/181788771-3ba9543a-2125-4b4e-8ab5-2272f4e468c6.png)

