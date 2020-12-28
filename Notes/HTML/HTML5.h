//
//  HTML5.h
//  Notes
//
//  Created by Civet on 2020/12/28.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef HTML5_h
#define HTML5_h


#endif /* HTML5_h */

<!--视频播放器-->
<video width="320" height="240" controls>
  <source src="movie.mp4" type="video/mp4">
  <source src="movie.ogg" type="video/ogg">
</video>

画布(canvas):
<canvas id="myCanvas"></canvas>
 
<script type="text/javascript">
var canvas=document.getElementById('myCanvas');
var ctx=canvas.getContext('2d');
ctx.fillStyle='#FF0000';
ctx.fillRect(0,0,80,60);
</script>

音频(audio):定义音频内容
<audio controls>
  <source src="horse.ogg" type="audio/ogg">
  <source src="horse.mp3" type="audio/mpeg">
  您的浏览器不支持 audio 元素。
</audio>

视频(video):定义视频（video 或者 movie）
<video width="320" height="240" controls>
    <source src="movie.mp4" type="video/mp4">
    <source src="movie.ogg" type="video/ogg">
    您的浏览器不支持 video 标签。
</video>

<source>:定义多媒体资源 <video> 和 <audio>
<embed>:定义嵌入的内容，比如插件。
<track>:为诸如 <video> 和 <audio> 元素之类的媒介规定外部文本轨道。

<datalist>:定义选项列表。请与 input 元素配合使用该元素，来定义 input 可能的值。
<input list="browsers">
<datalist id="browsers">
  <option value="Internet Explorer">
  <option value="Firefox">
  <option value="Chrome">
  <option value="Opera">
  <option value="Safari">
</datalist>

moveTo(x,y) 定义线条开始坐标
lineTo(x,y) 定义线条结束坐标

arc(x,y,r,start,stop)
画布的左上角坐标为(0,0)
 x：圆心在x轴上的坐标
 y：圆心在y轴上的坐标
 r：半径长度
 start：起始角度，以弧度表示，圆心平行的右端为0度
 stop：结束角度，以弧度表示
注意：Math.PI表示180°，画圆的方向是顺时针

font - 定义字体
fillText(text,x,y) - 在 canvas 上绘制实心的文本
strokeText(text,x,y) - 在 canvas 上绘制空心的文本

<canvas id="myCanvas" width="200" height="100"
style="border:1px solid #000000;">
</canvas>
<script>
  var c=document.getElementById("myCanvas");
  var ctx=c.getContext("2d");
  ctx.moveTo(0,0);
  ctx.lineTo(200,100);
  ctx.stroke();
  
  var c=document.getElementById("myCanvas");
  var ctx=c.getContext("2d");
  ctx.beginPath();
  ctx.arc(95,50,40,0,2*Math.PI);
  ctx.stroke();
  
  var c=document.getElementById("myCanvas");
  var ctx=c.getContext("2d");
  ctx.font="30px Arial";
  ctx.fillText("Hello World",10,50);
  
  var c=document.getElementById("myCanvas");
  var ctx=c.getContext("2d");
  ctx.font="30px Arial";
  ctx.strokeText("Hello World",10,70);
</script>

把一幅图像放置到画布上, 使用以下方法:
drawImage(image,x,y)

var c=document.getElementById("myCanvas");
var ctx=c.getContext("2d");
var img=document.getElementById("scream");
ctx.drawImage(img,10,10);
-----------------------------------------------------------------------------------------------------------------------------------
onopen:当通往服务器的连接被打开
onmessage:当接收到消息
onerror:当发生错误
