# Sign

sign主要解决c/c++在调用某些接口的时候需要进行AKSK验证，这个是用来计算sign验证数据的
验证的数据主要算法如下：
1.key-value 的参数进行字典排序
2.对排序完的数据进行转换成字符串key1=value1，多个参数需要使用“&”进行连接，例如：key1=value1&key2=value2
3.在生成的字符串后面添加加密key值例如：key1=value1&key2=value2&key=keyvalue
4.将生成的字符串进行使用hmac-sha256进行加密
5.将加密后的数据转成大写
