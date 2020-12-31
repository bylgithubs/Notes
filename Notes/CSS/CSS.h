//
//  CSS.h
//  Notes
//
//  Created by Civet on 2020/12/29.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef CSS_h
#define CSS_h


#endif /* CSS_h */

px:像素，pixel； pt：磅，point
1pt = 2px
pixel是相对大小，而point是绝对大小

外部样式表(External style sheet)
内部样式表(Internal style sheet)
内联样式(Inline style)

外部样式表:当样式需要应用于很多页面时，外部样式表将是理想的选择。在使用外部样式表的情况下，你可以通过改变一个文件来改变整个站点的外观。
每个页面使用 <link> 标签链接到样式表。 <link> 标签在（文档的）头部：
<head>
<link rel="stylesheet" type="text/css" href="mystyle.css">
</head>

内部样式表:当单个文档需要特殊的样式时，就应该使用内部样式表。你可以使用 <style> 标签在文档头部定义内部样式表
<head>
<style>
hr {color:sienna;}
p {margin-left:20px;}
body {background-image:url("images/back40.gif");}
</style>
</head>

内联样式:由于要将表现和内容混杂在一起，内联样式会损失掉样式表的许多优势。请慎用这种方法，例如当样式仅需要在一个元素上应用一次时。
要使用内联样式，你需要在相关的标签内使用样式（style）属性。Style 属性可以包含任何 CSS 属性。
<p style="color:sienna;margin-left:20px">这是一个段落。</p>

多重样式:如果某些属性在不同的样式表中被同样的选择器定义，那么属性值将从更具体的样式表中被继承过来。
例如，外部样式表拥有针对 h3 选择器的三个属性：
h3
{
    color:red;
    text-align:left;
    font-size:8pt;
}
而内部样式表拥有针对 h3 选择器的两个属性：
h3
{
    text-align:right;
    font-size:20pt;
}
假如拥有内部样式表的这个页面同时与外部样式表链接，那么 h3 得到的样式是：
color:red;
text-align:right;
font-size:20pt;
即颜色属性将被继承于外部样式表，而文字排列（text-alignment）和字体尺寸（font-size）会被内部样式表中的规则取代。

多重样式优先级
内联样式）Inline style > （内部样式）Internal style sheet >（外部样式）External style sheet > 浏览器默认样式
内联样式 > id 选择器 > 类选择器 = 伪类选择器 = 属性选择器 > 标签选择器 = 伪元素选择器
-----------------------------------------------------------------------------------------------------------------------------------
CSS 链接：
a:link - 正常，未访问过的链接
a:visited - 用户已访问过的链接
a:hover - 当用户鼠标放在链接上时
a:active - 链接被点击的那一刻
example：
a:link {color:#000000;}      /* 未访问链接*/
a:visited {color:#00FF00;}  /* 已访问链接 */
a:hover {color:#FF00FF;}  /* 鼠标移动到链接上 */
a:active {color:#0000FF;}  /* 鼠标点击时 */

-----------------------------------------------------------------------------------------------------------------------------------
CSS 盒子模型
Margin(外边距) - 清除边框外的区域，外边距是透明的。
Border(边框) - 围绕在内边距和内容外的边框。
Padding(内边距) - 清除内容周围的区域，内边距是透明的。
Content(内容) - 盒子的内容，显示文本和图像。

最终元素的总宽度计算公式是这样的：
总元素的宽度=宽度+左填充+右填充+左边框+右边框+左边距+右边距

元素的总高度最终计算公式是这样的：
总元素的高度=高度+顶部填充+底部填充+上边框+下边框+上边距+下边距
