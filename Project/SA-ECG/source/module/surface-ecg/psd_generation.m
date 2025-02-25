Htime = @(f,fl,fh) (f.^2 .* fh^4)./((f.^2 + fl^2).*(f.^2 + fh^2).^2);
Y=zeros(200,8193+4097-1);
W=zeros(200,8193);
for k=1:1,
H1 = Htime(linspace(0,720, 8192/2 + 1),30,60);
H1amp = sqrt(H1./2);
%H1mir = [fliplr(H1amp(1:end-1)) H1amp];
%H1phi = 2*pi*rand(size(H1amp));
%H1phi = [-fliplr(H1phi(1:end-1)) H1phi];
%H1cpx = H1mir.*exp(i.*H1phi);
h1 = ifft(H1amp);
W = randn(1,2*4096 + 1);
Y(k,:) = conv(real(h1),W);
end
%HH1=ecg_fft(Y(:,1:1024)', 1440,1);
%HH2=ecg_fft(W(:,1:1024)', 1440,1);