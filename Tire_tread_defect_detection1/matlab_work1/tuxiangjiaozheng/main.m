

%function  gmodify(pic,gm,og) %pic��ʾҪ�����ͼ���·���ļ���
clc
clear all

%uv��һ����ά����,uv(:,1)��������pic�����غ�����u,uv(:,2)��ʾ����pic������������V
%gm��һ����ά����,gm(j,:)������У��ͼ�ռ�����uv(j,:)һһӦ�ĵ�
%og ����Գ����ģ�����һ����ά����
gm=[5,3;16,3;28,3;39,3;50,3;61,3;72,4;84,4;95,4;106,4;117,4;129,4;
    140,4;5,15;16,15;27,15;39,15;50,15;61,15;72,15;84,15;95,15;106,16;
    117,16;129,16;140,16;5,26;16,26;27,26;39,26;50,27;61,27;72,27;84,27;
    95,27;106,27;117,27;129,27;140,27;5,38;16,38;27,38;39,38;50,38;61,38;
    72,38;84,38;95,38;106,38;117,39;129,39;140,39;5,49;16,49;27,49;39,50;
    50,50;61,50;72,50;83,50;95,50;106,50;117,50;128,50;140,50;5,61;16,61;
    27,61;38,61;50,61;61,61;72,61;83,61;95,61;106,62;117,62;128,62;140,62;
    5,72;16,72;27,72;39,72;50,72;61,73;72,73;83,73;94,73;106,73;117,73;128,73;
    140,73;5,84;16,84;27,84;39,84;50,84;61,84;72,84;83,84;95,85;106,85;117,85;
    128,85;140,85;5,96;16,96;27,96;38,96;49,95;61,96;72,96;83,96;95,96;106,96;
    117,96;129,97;140,97;5,107;16,107;27,107;38,107;50,107;61,107;72,107;83,108;
    95,108;106,108;117,108;128,108;140,108;5,119;16,119;27,119;38,119;49,119;
    61,119;72,119;83,119;94,119;106,119;117,120;128,120;140,120;5,130;16,130;
    27,130;38,130;49,130;61,130;72,130;83,131;95,131;106,131;117,131;128,131;
    140,131;5,141;16,142;27,142;38,142;49,142;61,142;72,142;83,142;94,142;106,142;
    117,142;128,142;140,143;5,153;16,153;27,153;38,153;49,154;60,154;72,154;83,154;94,154;
    106,154;117,154;128,154;139,154;5,165;16,165;27,165;38,165;49,165;61,165;72,165;83,166;
    94,165;106,166;117,166;128,166;139,166;4,176;16,176;27,176;38,177;49,176;60,177;72,177;
    83,177;94,177;106,177;117,177;128,177;139,177;5,188;15,188;27,188;38,188;49,188;60,188;
    72,188;83,188;94,188;106,189;117,189;128,189;139,189;];


og=[72,93]; %%%%%%%%%%�Գ���������




a=imread('D:\Tire_Test\image3\1.jpg');   %%%%%%%%�����Լ���·���޸�



I_gray=rgb2gray(a);
b=double(a);
n=size(gm(:,1));

hengxiang_number=7;   %%%%%ͼ�������θ���
zongxiang_number=5;    %%%%%ͼ��������θ���

%%%%%�����ı��ηָ���������
[height_divise_lable,width_divise_lable]=fengezuobiao(hengxiang_number,zongxiang_number,I_gray) ;  %%%%�ı��ηָ�����
%%%%%%%%%��������
[plot_x,plot_y ]=calculate_zhixin(a) ;  

section=zeros(length(plot_x),2);
%%%%%%�����󻮷ֵ������ı�����%%%%%%%%%%%%%%%%%%%%
for i=1:length(plot_x)
    for j=1:(length(height_divise_lable)-1)
       if  plot_x(i)>=height_divise_lable(j)&&plot_x(i)<=height_divise_lable(j+1)
        
          for h=1:(length(width_divise_lable)-1)
              if plot_y(i)>width_divise_lable(h)&&plot_y(i)<width_divise_lable(h+1)
            
             section(i,:)=[j h];
              end
          end
       end
    end
end
             
             
      

%%%%%%%%��ÿһ���ı��Σ�����ȡ���ĸ��㣬��ȡ�����ı������Ӧ�Ļ���ϵ��%%%%%%%%%%%%%
distortion_factor_matix=zeros(4,2,zongxiang_number*hengxiang_number);
[hh,ww]=size(b(:,:,1));
sp=zeros(hh,ww,3)+255;

for i=1:zongxiang_number
    for j=1:hengxiang_number
        
            number=find(section(:,1)==i);
            number1=find(section(number,2)==j);
            number=number(number1(1:4,:));   %%%%%%%%ȡ�ĸ���
            


%%ת�����ԶԳƵ�Ϊԭ��Ŀռ��ϵ���������A
A=[ones(4,1),gm( number,1)-og(1),gm( number,2)-og(2), (gm( number,1)-og(1)).*(gm( number,2)-og(2))];
a0=pinv(A)*( plot_y(number)-og(2));  %���������ᵽ�ĵ�ַӳ���ϵ������a
b0=pinv(A)* (plot_x(number)-og(1));  %�����������ᵽ�ĵ�ַӳ���ϵ������b
distortion_factor_matix(:,:,(i-1)*zongxiang_number+j)=[a0,b0];    %%%%%%%��¼�����ı��εĻ������

[h,w]=size(b(height_divise_lable(i)+1:height_divise_lable(i+1),width_divise_lable(j)+1:width_divise_lable(j+1),1));
sp(height_divise_lable(i)+1:height_divise_lable(i+1),width_divise_lable(j)+1:width_divise_lable(j+1),:)=zeros(h,w,3)+255;
for ii=height_divise_lable(i)+1:height_divise_lable(i)+h     %������ͼ������������
    for jj=width_divise_lable(j)+1:width_divise_lable(j)+w
        x=[1,ii-og(1),jj-og(2),(ii-og(2))*(jj-og(1))];
        u=x*a0+og(2);  % ����ӳ�䣨j��i��������ͼ�����v��u��
        v=x*b0+og(1);
        if (u>width_divise_lable(j))&&(u<width_divise_lable(j)+w)&&(v>height_divise_lable(i))&&(v<height_divise_lable(i)+h) %������ͼ���С��Χ�ڵ����ص�
            if u<=1
                uu=floor(u)+1;   %��uȡ��
            else
                uu=floor(u);
            end
             if v<=1
                vv=floor(v)+1;   %��uȡ��
            else
                vv=floor(v);
            end  %��vȡ��
            arf=u-uu;     %���������ᵽ��
            bta=v-vv;     %���������ᵽ��
            for k=1:3         %���лҶ�˫���Բ�ֵ
                ft1=(1-bta)*b(vv,uu,k)+bta*b(vv+1,uu,k);
                ft2=(1-bta)*b(vv,uu+1,k)+bta*b(vv+1,uu+1,k);
                sp(ii,jj,k)=(1-arf)*ft1+arf*ft2;
            end
        end
    end
end

    end
   
end
figure(5)
imshow(uint8(sp));      %��ʾУ��ͼ��




