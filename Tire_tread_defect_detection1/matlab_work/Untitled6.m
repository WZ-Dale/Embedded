src_img_name = 'D:\Tire_Test\image4\4.jpg';  
% img = imread(src_img_name);  
%   
% % get binary image  
% gray_img = rgb2gray(img);  
% T = graythresh(gray_img);  
% bw_img = im2bw(gray_img, T);  

bw_img = imread(src_img_name);

% find the largest connected region  ����ȡͼ���е���ͨ���򣬿���ʹ�����´��룩
img_reg = regionprops(bw_img,  'area', 'boundingbox');  
areas = [img_reg.Area];  
rects = cat(1,  img_reg.BoundingBox);  

% show all the largest connected region  ����ʾ������ͨ����
figure(1),  
imshow(bw_img);  
for i = 1:size(rects, 1)  
    rectangle('position', rects(i, :), 'EdgeColor', 'r');  
end 

[~, max_id] = max(areas);  
max_rect = rects(max_id, :);  
  
% show the largest connected region  ����ʾ�����ͨ����
figure(2),   
imshow(bw_img);  
rectangle('position', max_rect, 'EdgeColor', 'r'); 