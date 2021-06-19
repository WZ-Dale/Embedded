% ��ֵ�ָ������

clear all;

f=imread('D:\Tire_Test\image4\18.jpg');
f=rgb2gray(f);%ת��Ϊ�Ҷ�ͼ��
f=im2double(f);%��������ת��
%ȫ����ֵ
T=0.5*(min(f(:))+max(f(:)));
done=false;
while ~done
	g=f>=T;
	Tn=0.5*(mean(f(g))+mean(f(~g)));
	done = abs(T-Tn)<0.1;
	T=Tn;
end
display('Threshold(T)-Iterative');%��ʾ����
T
r=im2bw(f,T);
subplot(221);imshow(f);
xlabel('(a)ԭʼͼ��');
subplot(222);imshow(r);
xlabel('(b)������ȫ����ֵ�ָ�');
Th=graythresh(f);%��ֵ
display('Global Thresholding- Otsu''s Method');
Th
s=im2bw(f,Th);
subplot(223);imshow(s);
xlabel('(c)ȫ����ֵOtsu����ֵ�ָ�');
se=strel('disk',10);
ft=imtophat(f,se);
Thr=graythresh(ft);
display('Threshold(T) -Local Thresholding');
Thr
lt = im2bw(ft,Thr);
subplot(224);imshow(lt);
xlabel('(d)�ֲ���ֵ�ָ�');
