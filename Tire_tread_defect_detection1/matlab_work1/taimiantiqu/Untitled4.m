clear all;
close all;
warning off all;
I = imread('D:\Tire_Test\image6\5.png'); %%�������������ͼ��,����ת��Ϊ�Ҷ�ͼ
I = rgb2gray(I);
%%û������ʱbai�ļ����
BW_sobel = edge(I,'sobel');
BW_prewitt = edge(I,'prewitt');
BW_roberts = edge(I,'roberts');
BW_laplace = edge(I,'log');
BW_canny = edge(I,'canny');
figure(1);
subplot(2,3,1),imshow(I),xlabel('ԭʼͼ��');
subplot(2,3,2),imshow(BW_sobel),xlabel('sobel���');
subplot(2,3,3),imshow(BW_prewitt),xlabel('prewitt���');
subplot(2,3,4),imshow(BW_roberts),xlabel('roberts���');
subplot(2,3,5),imshow(BW_laplace),xlabel('laplace���');
subplot(2,3,6),imshow(BW_canny),xlabel('canny���');
% %%�����˹��������=0����^2=0.01�������
% I_g1 = imnoise(I,'gaussian',0,0.01);
% BW_sobel = edge(I_g1,'sobel');
% BW_prewitt = edge(I_g1,'prewitt');
% BW_roberts = edge(I_g1,'roberts');
% BW_laplace = edge(I_g1,'log');
% BW_canny = edge(I_g1,'canny');
% figure(2);
% subplot(2,3,1),imshow(I_g1),xlabel('�����˹����(��=0����^2=0.01)ͼ��');
% subplot(2,3,2),imshow(BW_sobel),xlabel('sobel���');
% subplot(2,3,3),imshow(BW_prewitt),xlabel('prewitt���');
% subplot(2,3,4),imshow(BW_roberts),xlabel('roberts���');
% subplot(2,3,5),imshow(BW_laplace),xlabel('laplace���');
% subplot(2,3,6),imshow(BW_canny),xlabel('canny���');
% %%�����˹��������=0����^2=0.02�������
% I_g2 = imnoise(I,'gaussian',0,0.02);
% BW_sobel = edge(I_g2,'sobel');
% BW_prewitt = edge(I_g2,'prewitt');
% BW_roberts = edge(I_g2,'roberts');
% BW_laplace = edge(I_g2,'log');
% BW_canny = edge(I_g2,'canny');
% figure(3);
% subplot(2,3,1),imshow(I_g2),xlabel('�����˹����(��=0����^2=0.02)ͼ��');
% subplot(2,3,2),imshow(BW_sobel),xlabel('sobel���');
% subplot(2,3,3),imshow(BW_prewitt),xlabel('prewitt���');
% subplot(2,3,4),imshow(BW_roberts),xlabel('roberts���');
% subplot(2,3,5),imshow(BW_laplace),xlabel('laplace���');
% subplot(2,3,6),imshow(BW_canny),xlabel('canny���');