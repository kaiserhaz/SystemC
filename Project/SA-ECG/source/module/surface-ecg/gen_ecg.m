%% Signal generation stage
% ECG Generation
Fs = 2000;                                                                      % Sampling frequency
[s, ipeaks] = ecgsyn(Fs, 51, 0, 60, 0, 0.5, 2*Fs);                              % Generate synthetic ECG
N = length(s);                                                                  % Get length of signal

% EMG envelope generation (using RC-filter like coefficients + echelon
% response)
[bamp,aamp]=rc_filter(2e5,1e-6,Fs,'low');
stepsig = [repmat([zeros(1,512) ones(1,3072) zeros(1,4608)],1,floor(N/8192)) zeros(1,N - floor(N/8192)*8192)]';
ampsig = filter(bamp,aamp,stepsig);                                             % EMG envelope (basically, complement exponential rise)

% EMG noise generation (using inverse FFT of root PSD to get filter kernel)
emgnoisepow = 200;
Htime = @(f,fl,fh) (f.^2 .* fh^4)./((f.^2 + fl^2).*(f.^2 + fh^2).^2);
H1 = Htime(linspace(0,720, 8192/2 + 1),30,60);
H1amp = sqrt(H1./2);
h1 = ifft(H1amp);
W = sqrt(emgnoisepow).*randn(N-4096,1);
Y = conv(real(h1),W);
emgsig = Y.*ampsig;

ecgSig = s + emgSig;

save('ecgSig.dat','ecgSig','-ascii');
