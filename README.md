# Camera_Calib
# 项目概述：
本项目实现：
1,双目摄像头标定，获得左右特定内参CameraMatrix，畸变系数Distcoeffs和左右相机关系Rec,T,E,F;

2,利用旋转向量rvecsMat,平移向量tvecsMat对黑白格标定板进行纠正，进行效果验证;

3,利用标定参数,可以获得的左右相机的映射表Rl,Rr,Pl,Pr,mapLx,mapLy,mapRx,mapRy;

4,利用映射表对摄像头捕捉到的每一帧进行实时纠正;

5,利用BM(SGBM)算法进行立体匹配，获得深度图;

6,利用深度图进行双目测距。
# 疑问点：
1,世界坐标系下图像点的制作;

2,立体匹配算法的参数调节;

3,测距时深度(Z坐标)负数的处理办法。
