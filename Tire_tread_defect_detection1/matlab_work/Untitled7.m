% �ĸ��Ƕȵ� Radon�任

clear all;
close all;
clc;

rgb = imread('D:\Tire_Test\image8\image4.jpg');
gray = rgb2gray(rgb);

r2 = radon(gray,0);
%r2 = radon(gray,90);
subplot(1,1,1);
plot(r2),title('Radon 0');
%plot(r2),title('Radon 90');