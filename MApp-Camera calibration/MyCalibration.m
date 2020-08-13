function cal=MyCalibration(In ,Out, min, max, pic)
%   这是一个标正图片的函数
%   以下为参数解释
%   In ：内部参数矩阵
%   Out：外部畸变参数矩阵
%   min：循环的最小值
%   max：循环的最大值
%   pic：需要校正的图像，完整路径
%   In： cameraParams.IntrinsicMatrix
%   Out：[cameraParams. *RotationMatrices(Matrix)*  cameraParams.TranslationVectors]
%   eg：cal=MyCalibration(In ,Out, min, max, pic)
%       imshow(uint8(cal))
H = In * Out;
for X = min:max
     for Y = min:max
       u = H*[X, Y, 0, 1]';  %通过乘系数来改变图像分辨率，展示细节
       U(X-min+1,Y-min+1) = round(u(1)/u(3)); V(X-min+1,Y-min+1) = round(u(2)/u(3)); 
     end
end
U =uint16(U);
V = uint16(V);
for X =1:max-min+1 %修改X,Y起始值，改变最终显示的图像范围
     for Y = 1:max-min+1
       if(0<U(X,Y) &&U(X,Y)<=2736 && 0<V(X,Y) && V(X,Y)<=2192)
          cal(X,Y,:) = pic(V(X,Y),U(X,Y),:); %U,V坐标和X,Y的对应关系需要调换一下，V对应X,U对应Y
       end
     end
end
%%
%1.内参：IntrinsicMatrix对应内参，注意这个和OpenCV中*转置* 的关系，注意不要搞错。
%2.畸变参数：
%  RadialDistortion：径向畸变，摄像头由于光学透镜的特性使得成像存在着径向畸变，可由K1，K2，K3确定。
%  TangentialDistortion：切向畸变，由于装配方面的误差，传感器与光学镜头之间并非完全平行，因此成像存在切向畸变，可由两个参数P1，P2确定。
%  Tip1，matlab选择3 Coefficients，则是K1,K2,K3三个参数非线性拟合；畸变不严重的情况下可以选择2 Coefficients，这样径向畸变就由K1，K2确定，K3为0。
%  Tip2，对于畸变较小的图像中心区域，主要是k1起作用；对于畸变较大的边缘区域主要是k2起作用。普通相机这两个系数就够用了，对于鱼眼相机这种畸变特别大的才用的上第三个参数k3  
%3，Opencv使用时，需要注意外部畸变参数矩阵的排放顺序，即K1，K2，P1，P2，K3。千万不要以为k是连着的。