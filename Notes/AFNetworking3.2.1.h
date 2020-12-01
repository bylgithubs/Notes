//
//  AFNetworking3.2.1.h
//  Notes
//
//  Created by Civet on 2020/11/13.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef AFNetworking3_2_1_h
#define AFNetworking3_2_1_h


#endif /* AFNetworking3_2_1_h */

*************请求头**************
请求头：包含了对客户端的环境描述、客户端请求信息等
GET /minion.png HTTP/1.1   //包含了请求方法、请求资源路径、HTTP协议版本

Host: 120.25.226.186:32812   //客户端想访问的服务器主机地址

User-Agent: Mozilla/5.0  //客户端的类型，客户端的软件环境

Accept: text/html,*/*   //客户端所能接收的数据类型

Accept-Language: zh-cn   //客户端的语言环境,如：zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3

Accept-Encoding: gzip   //客户端支持的数据压缩格式,如： gzip, deflate


Cookie   //请求头，服务器或客户端在上次设置的COOKIE，包括作用域名(.360buy.com)，过期时间，键与值。大部分WEB服务器都会在第一次访问时在响应头上加Set-Cookie，
如：BAIDUID=49415814CDBBB4CE65EC50EE4BB65E9A:FG=1; expires=Wed, 07-Nov-42 07:03:34 GMT; path=/; domain=.baidu.com

Referer  //从一个连接打开一个新页面，新页面的请求一般会加此信息，标名是从哪里跳过来的，所有的页面的打开历史链就可被挖掘出来，有利于分析用户行为与CPS分成

请求体：客户端发给服务器的具体数据，比如文件数据(POST请求才会有)

************响应头************

客户端向服务器发送请求，服务器应当做出响应，即返回数据给客户端
HTTP协议规定：1个完整的HTTP响应中包含以下内容
响应头：包含了对服务器的描述、对返回数据的描述
HTTP/1.1 200 OK            //包含了HTTP协议版本、状态码、状态英文名称

Server:Apache-Coyote/1.1   //服务器的类型

Content-Type: image/jpeg  //响应的数据类型：text/html;charset=gbk

Content-Length: 56811   //返回数据的长度

Date  //响应的时间


Content-Encoding  // 如果为文本、HTML信息，则使用的编码方式

Set-Cookie  // 第一次访问或服务设置COOKIE时，响应头里会有此信息，
如,BAIDUID=49415814CDBBB4CE65EC50EE4BB65E9A:FG=1; expires=Wed, 07-Nov-42 07:03:34 GMT; path=/; domain=.baidu.com


响应体：服务器返回给客户端的具体数据，比如文件数据

*************常见的响应状态码**************

1xx消息
这一类型的状态码，代表请求已被接受，需要继续处理。这类响应是临时响应，只包含状态行和某些可选的响应头信息，并以空行结束。由于HTTP/1.0协议中没有定义任何1xx状态码，所以除非在某些试验条件下，服务器禁止向此类客户端发送1xx响应。 这些状态码代表的响应都是信息性的，标示客户应该采取的其他行动。

2xx成功
这一类型的状态码，代表请求已成功被服务器接收、理解、并接受。

200 OK
请求已成功，请求所希望的响应头或数据体将随此响应返回。

3xx重定向
这类状态码代表需要客户端采取进一步的操作才能完成请求。通常，这些状态码用来重定向，后续的请求地址（重定向目标）在本次响应的Location域中指明。
当且仅当后续的请求所使用的方法是GET或者HEAD时，用户浏览器才可以在没有用户介入的情况下自动提交所需要的后续请求。
客户端应当自动监测无限循环重定向（例如：A→B→C→……→A或A→A），因为这会导致服务器和客户端大量不必要的资源消耗。按照HTTP/1.0版规范的建议，浏览器不应自动访问超过5次的重定向。

4xx客户端错误
这类的状态码代表了客户端看起来可能发生了错误，妨碍了服务器的处理。除非响应的是一个HEAD请求，否则服务器就应该返回一个解释当前错误状况的实体，
以及这是临时的还是永久性的状况。这些状态码适用于任何请求方法。浏览器应当向用户显示任何包含在此类错误响应中的实体内容。
如果错误发生时客户端正在传送数据，那么使用TCP的服务器实现应当仔细确保在关闭客户端与服务器之间的连接之前，客户端已经收到了包含错误信息的数据包。
如果客户端在收到错误信息后继续向服务器发送数据，服务器的TCP栈将向客户端发送一个重置数据包，以清除该客户端所有还未识别的输入缓冲，
以免这些数据被服务器上的应用程序读取并干扰后者。

5xx服务器错误
这类状态码代表了服务器在处理请求的过程中有错误或者异常状态发生，也有可能是服务器意识到以当前的软硬件资源无法完成对请求的处理。
除非这是一个HEAD请求，否则服务器应当包含一个解释当前错误状态以及这个状况是临时的还是永久的解释信息实体。
浏览器应当向用户展示任何在当前响应中被包含的实体。
这些状态码适用于任何响应方法。

--------------------------------------------------------------------------------------------------------------------
Http请求中的Content-Type:
类型格式：type/subtype(;parameter)? type
主类型，任意的字符串，如text，如果是*号代表所有；
subtype 子类型，任意的字符串，如html，如果是*号代表所有；
parameter 可选，一些参数，如Accept请求头的q参数， Content-Type的 charset参数。
例如： Content-Type: text/html;charset:utf-8;
        
常见的媒体格式类型如下：

text/html ： HTML格式
text/plain ：纯文本格式
text/xml ：  XML格式
image/gif ：gif图片格式
image/jpeg ：jpg图片格式
image/png：png图片格式
以application开头的媒体格式类型：

application/xhtml+xml ：XHTML格式
application/xml     ： XML数据格式
application/atom+xml  ：Atom XML聚合格式
application/json    ： JSON数据格式
application/pdf       ：pdf格式
application/msword  ： Word文档格式
application/octet-stream ： 二进制流数据（如常见的文件下载）
application/x-www-form-urlencoded ： <form encType=””>中默认的encType，form表单数据被编码为key/value格式发送到服务器（表单默认的提交数据的格式）
另外一种常见的媒体格式是上传文件之时使用的：

multipart/form-data ： 需要在表单中进行文件上传时，就需要使用该格式
以上就是我们在日常的开发中，经常会用到的若干content-type的内容格式。
                    

1. AFHTTPRequestSerializer：是普通的 HTTP 的编码格式的，也就是 mid=10&method=userInfo&dateInt=20160818 这种格式的。

2. AFJSONRequestSerializer：是 JSON 编码格式的，也就是 {"mid":"11","method":"userInfo","dateInt":"20160818"} 这种格式的。

3. AFPropertyListRequestSerializer：这个没用过，但是看介绍说是编码成 plist 格式的参数。

MIME (Multipurpose Internet Mail Extensions) 是描述消息内容类型的因特网标准。

MIME 消息能包含文本、图像、音频、视频以及其他应用程序专用的数据。

