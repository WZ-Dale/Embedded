% D:\Tire_Test\image3\1.jpg

close;clear;clc;
I=im2double(imread('D:\Tire_Test\image3\1.jpg'));
k=graythresh(I);              %�õ�������ֵ
J=im2bw(I,k);                  %ת���ɶ�ֵͼ��kΪ�ָ���ֵ
subplot(121);imshow(I); 
subplot(122);imshow(J);   