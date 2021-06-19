function undistorted_img = undistortImage(img, K, D)
% Corrects an image for lens distortion.
% KΪ�ڲξ���������һ������ģ�������
% DΪ������������������
 
[height, width] = size(img);
 
fx = K(1,1);
fy = K(2,2);
cx = K(1,3);
cy = K(2,3);
 
 
%Finish image undistorted function
undistorted_img = uint8(zeros(height, width));
 
% �����ҵ�ȥ������ͼ�����꣨y,x����Ӧ�Ļ�������
for y = 1:height
    for x = 1:width
 
        % ��һ����ͨ���ڲξ����һ������ͼ�������       
        x1 = (x-cx)/fx;  
        y1 = (y-cy)/fy;
        
        % �ڶ�����ͨ���������ģ�͵õ���һ���Ļ�������
        r2 = x1^2+y1^2;
        x2  = x1*(1+D(1)*r2+D(2)*r2^2); 
        y2 = y1*(1+D(1)*r2+D(2)*r2^2);
        
        % ������������ӳ���ȥ��ȥ��һ�����õ��������ꡣ
        u_distorted = fx*x2+cx;  % ��
        v_distorted = fy*y2+cy;  % ��
        
        % ͨ������Ĳ��裬�����ҵ�������ͼ�����꣨y,x����Ӧ�Ļ���ͼ�����꣨u_distorted, v_distorted������һ�����Ǹ�ֵ�ˣ������õ�������ڲ�ֵ��
 
        % ���Ĳ�������ڲ�ֵ
        if (u_distorted >= 0 && v_distorted >= 0 && u_distorted < width && v_distorted < height) % ��ֹ����Խ��
            undistorted_img(y, x) = img(round(v_distorted), round(u_distorted)); % ͨ��round����ȡ���������
        else
            undistorted_img(y, x) = 0;
        end
    end
end
 
end
 