%
% @file gen_ecg.m
%
% @brief MATLAB/Octave ECG simulator script.
% 
% -- Versioning Info --
%
% v1.0 : 26/02/2025 : Initial working config write-up.
%
% @copyright
% Copyright 2025 British Malaysian Institute, Universiti Kuala Lumpur.
% 
% Written by Muhammad Haziq Kamarul Azman a.k.a. Kaiser Haz.
%

if exist('OCTAVE_VERSION','builtin') ~= 0
	pkg load signal;
end

%% Signal generation stage
% ECG Generation
fS = 1000;                                                                      % Sampling frequency
tS = 1/fS;                                                                      % Sampling interval
[s, iPeaks] = ecgsyn(fS, 10, 0.05, 60, 1, 0.5, 2*fS);                           % Generate synthetic ECG
N = length(s);                                                                  % Get length of signal

% EMG envelope generation (using RC-filter like coefficients + echelon
% response)
rEnv = 2e5;
cEnv = 1e-6;
tau = rEnv*cEnv;
[bAmp,aAmp]=rc_filter(rEnv,cEnv,fS,'low');                                      % Time constant = 200 ms
pass = false;
while ~pass
    iNoise = randi([50 N-5*round(tau/tS)], [1 10]);
    dNoise = randi([1 4].*round(tau/tS), size(iNoise));
    pass = any( diag(max(iNoise(1), diag(iNoise(2:end)))) - diag(max(iNoise(1)+dNoise(1), diag(iNoise(2:end)+dNoise(2:end)))) <= 0 );
end
aNoise = rand([1 numel(iNoise)]);
stepSig = zeros(N,1);
for i=1:numel(iNoise)
    stepSig( iNoise(i)+(0:dNoise(i)) ) = aNoise(i);
end
ampSig = filter(bAmp,aAmp,stepSig);                                             % EMG envelope (basically, complement exponential rise)

% EMG noise generation (using inverse FFT of root PSD to get filter kernel)
emgNoisePow = 20;
hTime = @(f,fl,fh) (f.^2 .* fh^4)./((f.^2 + fl^2).*(f.^2 + fh^2).^2);
h1 = hTime(linspace(0,720, 8192/2 + 1),30,60);
h1Amp = sqrt(h1./2);
h1 = ifft(h1Amp);
w = sqrt(emgNoisePow) .* ampSig .* randn(N,1);
y = conv(real(h1),w);
emgSig = y(1:N);

ecgSig = s + emgSig;

save('ecgSig.dat','ecgSig','-ascii');
