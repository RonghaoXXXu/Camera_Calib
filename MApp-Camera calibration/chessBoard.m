
% function I= chessBoard(rows,cols,length,margin,name)
%   This function writes a chessboard on image.
%   该方程创建一个棋盘格图像。
%   参数解释：
%   rows：pattern中棋盘格的行数
%   cols：pattern中棋盘格的列数
%   length：pattern中棋盘格的大小
%   ////////margin: 背景留白大小
%   name：写入的图片名字
% I = ones(rows*length+2*margin,cols*length+2*margin)*255;
% the first grid is black
% for i = 1:rows
%     if mod(i,2)==1
%         for j = 1:cols
%             if mod(j,2)==1
%                 I(1+(i-1)*length+margin:i*length+margin,...
%                 1+(j-1)*length+margin:j*length+margin) = 0;
%             end
%         end
%     else
%         for j = 1:cols
%             if mod(j,2)==0
%                I(1+(i-1)*length+margin:i*length+margin,...
%                 1+(j-1)*length+margin:j*length+margin) = 0;
%             end
%         end
%     end
% end
% imshow(I);
% imwrite(I,name)

function I= chessBoard( width, height,rows,cols,length,background,name)
%   This function writes a chessboard on image.
%   该方程创建一个棋盘格图像。
%   参数解释：
%   width：pattern的宽
%   height：pattern的长
%   rows：pattern中棋盘格的行数
%   cols：pattern中棋盘格的列数
%   length：pattern中棋盘格的大小
%   background：背景亮度， 0<=background<=1， 0表示纯黑，1表示
%   name：写入的图片名字

org_X=(height-rows*length)/2;            %pattern关于纵轴方向的位置，默认放在中间
org_Y=(width-cols*length)/2;             %pattern关于横轴方向的位置，默认放在中间
I=zeros(height,width);
I(:)=background;
color1=1;
img=zeros(rows*length,cols*length);
for i=0:(rows-1)
    color2=color1;
    for j=0:(cols-1)
        if color2==1
        img(i*length+1:(i+1)*length-1,j*length+1:(j+1)*length-1)=color2;
        end
        %不加的话，可以注释掉
        color2=~color2;
    end
    color1=~color1;
end
I(org_X:org_X+rows*length-1,org_Y:org_Y+cols*length-1)=img;
I=~I;
figure;imshow(I);   
imwrite(I,name);
 
