function [lambda, mu] = emu_to_lame(E, p)

    lambda = (E*p)/((1.0+p)*(1.0-2.0*p));
    mu = E/(2.0*(1.0+p));
    
end