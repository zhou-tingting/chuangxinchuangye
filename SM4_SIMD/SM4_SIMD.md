实验简介：

本实验采用SIMD指令集对SM4加密算法进行加速。  
SM4单次加解密一个标准长度（128 比特）的数据：  
明文：0123456789ABCDEFFEDCBA9876543210  
密钥：0123456789ABCDEFFEDCBA9876543210  
密文：681EDF34D206965E86B3E94F536E4246  
sm4_simd.h中定义了一些加解密函数等  
sm4_simd.cpp中采用SIMD指令集优化加解密运算  
源.cpp为主函数  
注：SM4采用SIMD指令集加速是计算机系统原理课的一次实验，当时是小组合作，因此可能本小组成员也上传了该代码。  

实验运行结果：  
![I(M`)I AS$WA NL9 MN$RFX](https://user-images.githubusercontent.com/109579171/181450040-f9fc0cf5-bac0-454f-b55a-e5646331dcdb.png)

