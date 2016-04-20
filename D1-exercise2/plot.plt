set terminal png
set output "GaussianRN.png"
f(x) = exp(-x*x/(2*0.5*0.5))/sqrt(2*pi*0.5*0.5)
p "NormGauss.dat" w lp, f(x)
