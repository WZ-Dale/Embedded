
image=imread('ԭͼ.png');

%%%%%%%%og=[]

I_gray=rgb2gray(image);
b=double(image);
n=size(gm(:,1));


%%%%%�����ı��ηָ���������
[height_divise_lable,width_divise_lable]=fengezuobiao(hengxiang_number,zongxiang_number,I_gray) ;  %%%%�ı��ηָ�����

distortion_factor_matix=gmodify(pic,gm,og)


[hh,ww]=size(b(:,:,1));
sps=zeros(hh,ww,3)+255;

for i=1:zongxiang_number
    for j=1:hengxiang_number
        
a0=distortion_factor_matix(:,1,(i-1)*zongxiang_number+j);   %%%%%%%��¼�����ı��εĻ������
b0=distortion_factor_matix(:,2,(i-1)*zongxiang_number+j);
[h,w]=size(b(height_divise_lable(i)+1:height_divise_lable(i+1),width_divise_lable(j)+1:width_divise_lable(j+1),1));
sps(height_divise_lable(i)+1:height_divise_lable(i+1),width_divise_lable(j)+1:width_divise_lable(j+1),:)=zeros(h,w,3)+255;
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
                sps(ii,jj,k)=(1-arf)*ft1+arf*ft2;
            end
        end
    end
end

    end
   
end

imshow(uint8(sps));      %��ʾУ��ͼ��



