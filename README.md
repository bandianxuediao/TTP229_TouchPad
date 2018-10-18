# TTP229_TouchPad
（用于商业用途前请务必与本人联系，否则一切法律后果由您自行承担。示例代码底层驱动直接调用正点原子例程，相关注释一概保存。）</br>
## [开发过程记录](https://github.com/bandianxuediao/TTP229_TouchPad/blob/master/project_process.md)<br/>
### 详细的开发过程请点击上面的链接，或者直接访问project_process.md<br/>
### 更丰富的内容请访问我的个人网站[文禾每](http://www.wenhemei.com)<br/>
### Use the TTP229 make a 4x4 matrix touch keyboard;使用TTP229做的一版本4x4触摸矩阵键盘，两片74hc595级联控制16个双色LED灯。<br/>
## 项目背景：</br>
　　一年多以前做过一款使用XW系列触摸芯片的矩阵键盘，只是XW系列触摸芯片最大支持12个触摸按键，所以16个按键需要使用2块芯片组合。前些日子逛淘宝时无意间发现了使用TTP229芯片做的4x4触摸矩阵键盘，一块TTP229芯片直接支持16个按键，而且还有多种模式可供选择。想着再使用TTP229打一次板，GitHub能够再增加一个repositories,个人网站也有东西可写。于是就有了接下来那糟糕而又丰满的旅程--[<开发记录>](https://github.com/bandianxuediao/TTP229_TouchPad/blob/master/project_process.md)。<br/>

## 概要描述：</br>
　　触摸芯片选择了标准IIC通讯接口，控制端使用IIC接口读取数据即可得到按键值。</br>
　　16个双色LED使用了2块74HC595级联来控制，双色Led的控制使用了一个超经典特简单的电路，如下图所示：
![一个引脚控制2个led](https://github.com/bandianxuediao/TTP229_TouchPad/blob/master/DOC/Photos/OnePinTwoLED.jpg)</br>
　　图中LED1_G和LED1_R是链接在同一个引脚上面的，此引脚通过输出高低电平点亮不同颜色的LED。</br>
　　其他更详细的问题描述以及问题解决过程，解决方案都已经在开发记录里面详述过，这里就不再赘述。</br>
