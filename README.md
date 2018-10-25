# Converting-RPY-Euler-angles-to-Rotation-Vector-Angle-Axis-for-Universal-Robots

## Maintainer

- [zhulei2017](https://zhulei2017.github.io/)<<zhulei2017@outlook.com>>

## Read this first

- 本程序使用c语言，将欧拉角（RPY角）转换为旋转矢量（Rx，Ry，Rz）；
- 在UR脚本语言中,关于位姿的定义为：（x,y,z,Rx,Ry,Rz）；不方便实现机器人绕工具系旋转；
- Roll, Pitch and Yaw中，改变Yaw的值可以实现机器人绕工具系的z轴方向旋转；
- ToRotVector函数输入：欧拉角：r，p，y；
- ToRotVector函数输出：旋转矢量的数组[Rx,Ry,Rz];

## Reference

1. http://www.zacobria.com/universal-robots-knowledge-base-tech-support-forum-hints-tips/c-code-example-of-converting-rpyeuler-angles-to-rotation-vectorangle-axis-for-universal-robots/
2. http://www.zacobria.com/universal-robots-knowledge-base-tech-support-forum-hints-tips/python-code-example-of-converting-rpyeuler-angles-to-rotation-vectorangle-axis-for-universal-robots/