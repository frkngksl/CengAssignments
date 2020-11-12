N=38416; % size Of Monte Carlo Study for error = 0.005 with alpha = 0.05 0.9251
lambda = 35; % 7*5 for 7 hours parameter
lambdaForPart2 = 50; %10*5 for 10 hours parameter
totalNumber = zeros(N,1);
totalNumberForPart2 = zeros(N,1);
totalNumFor3 = zeros(N,1);
mu = 0; sigma = 1;
muexp = 2;
for k=1:N
	U = rand; i = 0; % first generate sample Y, the number of creatures in 7 hours using sampling from Poisson
	F = exp(-lambda);
	while (U>=F)
		i=i+1;
		F = F+exp(-lambda)*lambda^i/gamma(i+1);
    end
    totalNumbers=0;
	Y = i;   % Y is the number of creature caught
	s = 0; m=exp(-2); b=10; % the boundary of the rejection sampling rectangle a is already 0 b is convergence limit
    for f=1:Y
       SX=0; SY=2.5; CX =0;
       while(SY > SX*CX*exp(-SX-CX))
           K = rand; L = rand; M =rand;
           SX = b*K; SY = m*L; CX = b*M;
       end
        if(CX >= 2*SX)
        totalNumbers = totalNumbers+1;
        end
    end
    totalNumber(k)=totalNumbers;
end
for p=1:N
    U2 = rand; i2 = 0; % first generate sample Y, the number of creatures in 7 hours using sampling from Poisson
	F2 = exp(-lambdaForPart2);
	while (U2>=F2)
		i2=i2+1;
		F2 = F2+exp(-lambdaForPart2)*lambdaForPart2^i2/gamma(i2+1);
    end
    Y2 = i2;
    totalNumbers2=0;
    s2 = 0; m2=exp(-1); b2=10;  % the boundary of the rejection sampling rectangle a is already 0 when b is bigger than 10 it will converge
    for z=1:Y2
        CX2 = 0; CY2 = m2; % initial coordinates for rejection sampling
        while(CY2 > CX2*exp(-CX2))
           U2 = rand; V2 = rand;
           CX2 = b*U2; CY2 = m2*V2;
        end
        totalNumbers2 = totalNumbers2+CX2;
    end
    totalNumberForPart2(p)=totalNumbers2;
end
for C=1:N
    A = exprnd(0.5);
    B = normrnd(0,1);
    totalNumFor3(C) = (2*A+3*B)/(3+2*abs(B));
end
p_est= mean(totalNumber > 8);
expectedWeight = mean(totalNumberForPart2);
estimateE = mean(totalNumFor3);
fprintf('Part 1)Estimated probability = %f\n',p_est);
fprintf('Part 2)Estimated weight = %f\n',expectedWeight);
fprintf('Part 3)Estimated value = %f\n',estimateE);
