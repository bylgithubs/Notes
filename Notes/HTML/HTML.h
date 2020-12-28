//
//  HTML.h
//  Notes
//
//  Created by Civet on 2020/12/24.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef HTML_h
#define HTML_h


#endif /* HTML_h */

<h1> //大标题
  click button
</h1>
<p> //段落
  click button ,trigger action
</p>
<button type="button" onclick="alert('hello')">
  点击
</button><br/>
<label type = "label" id="demo">
text content111
</label>
<script>
   x = document.getElementById("demo");
   x.innerHTML="Hello JavaScript";
</script><br/>
<a href="https://baidu.com">跳转到百度</a><br/>
<img loading="lazy" src="" width="50" height="50" title="image"/>   //图片
<hr>    //水平线
<p>
  创建水平线
</p>
<hr>
<!-- 这是一个注释 -->
<font size="6">this is six size font</font> //设置文字大小
<p>
  段落<br/>换行<br/>嵌套使用
</p>

<b>这是加粗文本</b><br/>
<strong>这是加粗文本，起强调作用</strong><br/>
<big>放大文本字体</big><br/>
<em>这是斜体文本</em><br/>
<i>这是斜体文本</i><br/>
<small>缩小文本字体</small><br/>
文本<sub>下标</sub><br/>
文本<sup>上标</sup>
-----------------------------------------------------------------------------------------------------------------------------------
内联样式：
使用内联样式的方法是在相关的标签中使用样式属性。样式属性可以包含任何 CSS 属性。以下实例显示出如何改变段落的颜色和左外边距。
<p style="color:blue;margin-left:20px;">这是一个段落。</p> //CSS内联样式
<body style="background-color:yellow;">
<h2 style="background-color:red;">这是一个标题</h2>
<p style="background-color:green;">这是一个段落。</p>
</body>

可以使用font-family（字体），color（颜色），和font-size（字体大小）属性来定义字体的样式:
<h1 style="font-family:verdana;">一个标题</h1>
<p style="font-family:arial;color:red;font-size:20px;">一个段落。</p>
<h1 style="text-align:center;">居中对齐的标题</h1>

内部样式表：
当单个文件需要特别样式时，就可以使用内部样式表。你可以在<head> 部分通过 <style>标签定义内部样式表:
<head>
<style type="text/css">
body {background-color:yellow;}
p {color:blue;}
</style>
</head>

外部样式表
当样式需要被应用到很多页面的时候，外部样式表将是理想的选择。使用外部样式表，你就可以通过更改一个文件来改变整个站点的外观。
<head>
<link rel="stylesheet" type="text/css" href="mystyle.css">
</head>

-----------------------------------------------------------------------------------------------------------------------------------
表格：
<table border="1" align="left">
  <thead align="center">    //表格的页眉
      <tr>
      <th>Title</th>
      <th>Price</th>
      <th>Available</th>
    </tr>
  </thead>
  <tbody align="center">    //表格的主体
      <tr>
      <td>title1</td>
      <td>111</td>
      <td>1</td>
    </tr>
    <tr>
      <td>title2</td>
      <td>222</td>
      <td>2</td>
    </tr>
    <tr>
      <td>title3</td>
      <td>333</td>
      <td>3</td>
    </tr>
  </tbody>
  <tfoot align="center">    //表格的页脚
    <tr>
      <td>total</td>
      <td></td>
      <td></td>
    </tr>
  </tfoot>
</table>

1.<table>：表格根元素。
2.<thead>：表格头。
3.<tbody>：表格体。
4.<tfoot>：表格尾，一般可忽略该结构。
5.<tr>：表格行。
表格内容标签：
1.<th>：表头单元格。
2.<td>：表体单元格。

跨列：colspan
跨行：rowspan
单元格内边距：cellpadding
单元格外边距：cellspacing
col 和 colgroup 用于便捷定义表格指定列的样式。

列表：
<ul>
  <li>Coffee</li>
  <li>Milk</li>
</ul>
<ol>
  <li>Coffee</li>
  <li>Milk</li>
</ol>
<dl>
  <dt>Coffee</dt>
  <dd>-hot drink</dd>
  <dt>Milk</dt>
  <dd>-cold drink</dd>
</dl>
<ul>:定义无序列表
<ol>:定义有序列表
<li>:定义列表项
<dl>:定义自定义列表
<dt>:定义自定义列表项
<dd>:定义自定义列表项描述
-----------------------------------------------------------------------------------------------------------------------------------
HTML <div> 元素是块级元素，它可用于组合其他 HTML 元素的容器。
<div> 元素没有特定的含义。除此之外，由于它属于块级元素，浏览器会在其前后显示折行。
如果与 CSS 一同使用，<div> 元素可用于对大的内容块设置样式属性。

HTML <span> 元素是内联元素，可用作文本的容器
<span> 元素也没有特定的含义。
当与 CSS 一同使用时，<span> 元素可用于为部分文本设置样式属性。

<div>:定义文档区块，块级(block-level)
<span>:定义 span，用来组合文档中的行内元素。
<div>实例：
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>菜鸟教程(runoob.com)</title>
</head>
<body>

<div id="container" style="width:500px">

<div id="header" style="background-color:#FFA500;">
<h1 style="margin-bottom:0;">主要的网页标题</h1></div>

<div id="menu" style="background-color:#FFD700;height:200px;width:100px;float:left;">
<b>菜单</b><br>
HTML<br>
CSS<br>
JavaScript</div>

<div id="content" style="background-color:#EEEEEE;height:200px;width:400px;float:left;">
内容在这里</div>

<div id="footer" style="background-color:#FFA500;clear:both;text-align:center;">
版权 © runoob.com</div>

</div>

</body>
</html>
-----------------------------------------------------------------------------------------------------------------------------------
表单：
<form>
  <!--文本域 Text Fields-->
  first text:<input type="text" name="firstInput"><br/>
  second text:<input type="text" name="secondInput"><br/>
  <!--密码字段 -->
  Password:<input type="password" name="pwd"><br/>
  <!--单选按钮 Radio Ruttons-->
  <input type="radio" name="sex" value="male">Male<br/>
  <input type="radio" name="sex" value="female">Female<br/>
  <!--复选按钮 Checkboxes-->
  <input type="checkbox" name="vehicle" value="Bike">bike<br/>
  <input type="checkbox" name="vehicle" value="Car">car<br/>
</form>
当用户单击确认按钮时，表单的内容会被传送到另一个文件。表单的动作属性定义了目的文件的文件名。由动作属性定义的这个文件通常会对接收到的输入数据进行相关的处理。
<!--提交按钮 Submit Button-->
<form name="input" action="target_file_name_action.php" method="get">
  UserName:<input type="text" name="userName">
  <input type="submit" value="Submit">
</form>

iframe框架
<!--定义一个内联的iframe-->
<iframe src="htmlName.html" name="iframe" width="200" height="100" frameborder="1"></iframe>
<p>
  <a href="http://www.baidu.com" target="iframe">使用iframe加载目标链接页面</a>
</p>

-----------------------------------------------------------------------------------------------------------------------------------
字符实体：
小于号(<):&lt;,&#60;,&#060;
大于号(>):&gt;,&#62;
不间断空格：&nbsp;
和号(&):&amp;,&#38;
引号("):&quot;,&#34;
撇号('):&apos;(IE不支持),&#39;
人民币/日元(¥):&yen;,&#165;
乘号(×):&times;,&#215;
除号(÷):&divide;,&#247;
-----------------------------------------------------------------------------------------------------------------------------------
统一资源定位器（Uniform Resource Locators)
scheme://host.domain:post/path/filename
说明：
scheme - 定义因特网服务的类型。最常见的类型是 http
host - 定义域主机（http 的默认主机是 www）
domain - 定义因特网域名，比如 runoob.com
:port - 定义主机上的端口号（http 的默认端口号是 80）
path - 定义服务器上的路径（如果省略，则文档必须位于网站的根目录中）。
filename - 定义文档/资源的名称

-----------------------------------------------------------------------------------------------------------------------------------
   <!--链接Links-->
   <a href="http://www.example.com/">普通链接</a><br/>
   <a href="http://www.example.com"><img src="URL" alt="图像链接"></a><br/>
   <a href="mailto:mailaccount@example.com">发送e-mail</a><br/>
   <!--书签-->
   <a id="tips">提示部分</a><br/>
   <a href="#tips">跳到提示部分</a><br/>
   <!--图片Images-->
   <img loading="lazy" src"URL" alt="替换文本" height="50" width="60"><br/>
   <!--样式Style/区块Sections-->
   <style type="text/css">
   h1{color:red;}
   p{color:blue;}
   </style>
   <div>
   文档中的块级元素
   </div>
   <span>文档中的内联元素</span><br/>
   <!--框架Iframe-->
   <iframe src="demo_iframe.htm"></iframe><br/>
   <!--表单Forms-->
   <hr>
   
   
   <form action="demo_example.php" method="post/get">
   <input type="text" name="文本" size="40" maxlength="50"><br/>
   <input type="password"><br/>
   <input type="checkbox" checked="checked"><br/>
   <input type="radio" checked="checked"><br/>
   <input type="submit" value="Send"><br/>
   <input type="reset"><br/>
   <input type="hidden"><br/>
   <select>
   <option>苹果</option>
   <option selected="selected">香蕉</option>
   <option>樱桃</option>
   </select><br/>
   <textarea name="comment" rows="5" cols="20"></textarea>
    


