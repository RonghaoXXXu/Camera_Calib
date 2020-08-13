function cal=MyCalibration(In ,Out, min, max, pic)
%   ����һ������ͼƬ�ĺ���
%   ����Ϊ��������
%   In ���ڲ���������
%   Out���ⲿ�����������
%   min��ѭ������Сֵ
%   max��ѭ�������ֵ
%   pic����ҪУ����ͼ������·��
%   In�� cameraParams.IntrinsicMatrix
%   Out��[cameraParams. *RotationMatrices(Matrix)*  cameraParams.TranslationVectors]
%   eg��cal=MyCalibration(In ,Out, min, max, pic)
%       imshow(uint8(cal))
H = In * Out;
for X = min:max
     for Y = min:max
       u = H*[X, Y, 0, 1]';  %ͨ����ϵ�����ı�ͼ��ֱ��ʣ�չʾϸ��
       U(X-min+1,Y-min+1) = round(u(1)/u(3)); V(X-min+1,Y-min+1) = round(u(2)/u(3)); 
     end
end
U =uint16(U);
V = uint16(V);
for X =1:max-min+1 %�޸�X,Y��ʼֵ���ı�������ʾ��ͼ��Χ
     for Y = 1:max-min+1
       if(0<U(X,Y) &&U(X,Y)<=2736 && 0<V(X,Y) && V(X,Y)<=2192)
          cal(X,Y,:) = pic(V(X,Y),U(X,Y),:); %U,V�����X,Y�Ķ�Ӧ��ϵ��Ҫ����һ�£�V��ӦX,U��ӦY
       end
     end
end
%%
%1.�ڲΣ�IntrinsicMatrix��Ӧ�ڲΣ�ע�������OpenCV��*ת��* �Ĺ�ϵ��ע�ⲻҪ���
%2.���������
%  RadialDistortion��������䣬����ͷ���ڹ�ѧ͸��������ʹ�ó�������ž�����䣬����K1��K2��K3ȷ����
%  TangentialDistortion��������䣬����װ�䷽��������������ѧ��ͷ֮�䲢����ȫƽ�У���˳������������䣬������������P1��P2ȷ����
%  Tip1��matlabѡ��3 Coefficients������K1,K2,K3����������������ϣ����䲻���ص�����¿���ѡ��2 Coefficients����������������K1��K2ȷ����K3Ϊ0��
%  Tip2�����ڻ����С��ͼ������������Ҫ��k1�����ã����ڻ���ϴ�ı�Ե������Ҫ��k2�����á���ͨ���������ϵ���͹����ˣ���������������ֻ����ر��Ĳ��õ��ϵ���������k3  
%3��Opencvʹ��ʱ����Ҫע���ⲿ�������������ŷ�˳�򣬼�K1��K2��P1��P2��K3��ǧ��Ҫ��Ϊk�����ŵġ�