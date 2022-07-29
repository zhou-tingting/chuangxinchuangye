from requests_html import HTMLSession
#创建Session对象
session = HTMLSession()
#某区块浏览器的链接
url = 'https://api.blockcypher.com/v1/btc/test3/addrs/miAMpCdoM3SuRMRoEVHp8smFdDAz29WA9g'
#GET请求访问指定的url
response = session.get(url)
with open("result.txt","w") as f:
    f.write(response.html.full_text)