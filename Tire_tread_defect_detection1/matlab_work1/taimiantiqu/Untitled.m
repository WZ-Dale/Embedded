% ̥����ȡ
% clear all;
close all;
clc;
% ԭͼ
rgb =imread('D:\Tire_Test\image6\2.png');
subplot(4,5,1);imshow(rgb),title('rgb');
% �Ҷ�ͼ
gray =rgb2gray(rgb);
subplot(4,5,2);imshow(gray),title('gray');
% ֱ��ͼ
subplot(4,5,3);imhist(gray);title('ԭͼ��ֱ��ͼ');
% ���ڻҶ�ͼ��
J=imadjust(gray,[0.15 0.9],[0 1]);
subplot(4,5,4);imshow(J);title('��ֱ��ͼ�õ�����ͼ��');
subplot(4,5,5);imhist(J);title('����imadjust���ں����ֱ��ͼ');
% ֱ��ͼ���⻯
K=histeq(gray);
subplot(4,5,6);imshow(K);title('�ɾ��⻯���ֱ��ͼ�õ��ľ�����ͼ��');
subplot(4,5,7);imhist(K);title('���⻯���ֱ��ͼ');
% ��Ե���1
I=gray;
BW1=edge(I,'Roberts',0.16,'both');
BW2=edge(I,'Sobel',0.16,'both');
BW3=edge(I,'Prewitt',0.06,'both');
BW4=edge(I,'LOG',0.012,'both'); 
BW5=edge(I,'Canny','both');
% BW1=edge(I,'Roberts');
% BW2=edge(I,'Sobel');
% BW3=edge(I,'Prewitt');
% BW4=edge(I,'LOG'); 
% BW5=edge(I,'Canny');
subplot(4,5,8);imshow(I);title('ԭͼ');
subplot(4,5,11);imshow(BW1);title('Robert���ӱ�Ե���')
subplot(4,5,12);imshow(BW2);title('Sobel���ӱ�Ե���')
subplot(4,5,13);imshow(BW3);title('Prewitt���ӱ�Ե���');
subplot(4,5,14);imshow(BW4);title('LOG���ӱ�Ե���');
subplot(4,5,15);imshow(BW5);title('Canny��Ե���');
% ��Ե���2
I=J;
BW1=edge(I,'Roberts');
BW2=edge(I,'Sobel');
BW3=edge(I,'Prewitt');
BW4=edge(I,'LOG'); 
BW5=edge(I,'Canny');
subplot(4,5,9);imshow(I);title('ԭͼ');
subplot(4,5,16);imshow(BW1);title('Robert���ӱ�Ե���')
subplot(4,5,17);imshow(BW2);title('Sobel���ӱ�Ե���')
subplot(4,5,18);imshow(BW3);title('Prewitt���ӱ�Ե���');
subplot(4,5,19);imshow(BW4);title('LOG���ӱ�Ե���');
subplot(4,5,20);imshow(BW5);title('Canny��Ե���');