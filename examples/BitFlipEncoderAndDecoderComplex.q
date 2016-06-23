h q[1,2,3]; // place an h gate in bits 1, 2 and 3
h q[2];
cx q[1], q[2];
cx q[3], q[2];
h q[1,2,3];

repeat 3 { // repeat 3 times the instruction id
id q[1,2,3];
}

h q[1,2,3];
cx q[3], q[2];
cx q[1], q[2];
h q[1,3];

repeat 2 {
cx q[3], q[2];
tdg q[2];
cx q[1], q[2];
t q[2];
}

h q[2];
bloch q[2];
