
% function I= chessBoard(rows,cols,length,margin,name)
%   This function writes a chessboard on image.
%   �÷��̴���һ�����̸�ͼ��
%   �������ͣ�
%   rows��pattern�����̸������
%   cols��pattern�����̸������
%   length��pattern�����̸�Ĵ�С
%   ////////margin: �������״�С
%   name��д���ͼƬ����
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
%   �÷��̴���һ�����̸�ͼ��
%   �������ͣ�
%   width��pattern�Ŀ�
%   height��pattern�ĳ�
%   rows��pattern�����̸������
%   cols��pattern�����̸������
%   length��pattern�����̸�Ĵ�С
%   background���������ȣ� 0<=background<=1�� 0��ʾ���ڣ�1��ʾ
%   name��д���ͼƬ����

org_X=(height-rows*length)/2;            %pattern�������᷽���λ�ã�Ĭ�Ϸ����м�
org_Y=(width-cols*length)/2;             %pattern���ں��᷽���λ�ã�Ĭ�Ϸ����м�
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
        %���ӵĻ�������ע�͵�
        color2=~color2;
    end
    color1=~color1;
end
I(org_X:org_X+rows*length-1,org_Y:org_Y+cols*length-1)=img;
I=~I;
figure;imshow(I);   
imwrite(I,name);
 
