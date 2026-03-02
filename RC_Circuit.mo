model RC_Circuit
  parameter Real R = 1000;   // Resistência em ohms
  parameter Real C = 0.001;  // Capacitância em farads
  Real v(start = 1);         // Tensão no capacitor (começa com 1 V)
equation
  // Equação diferencial: dv/dt = -v / (R*C)
  der(v) = -v / (R * C);
end RC_Circuit;
