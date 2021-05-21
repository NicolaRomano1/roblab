q = zeros(6, 1); %home

dh_params = [0.15,   0.525,   -pi/2,    q(1);
             0.79,   0,       0,        q(2);
             0.15,   0,       -pi/2,    q(3);
             0,      0.835,   pi/2,     q(4);
             0,      0,       -pi/2,    q(5);
             0.1,    0,       0,        q(6)];

%trz rz trx rx
T01 = trvec2tform([0, 0, dh_params(1,1)]) * rotm2tform(rotz(rad2deg(dh_params(1,3)))) * trvec2tform([dh_params(1,2), 0, 0]) * rotm2tform(rotx(rad2deg(dh_params(1,4))));
T12 = trvec2tform([0, 0, dh_params(2,1)]) * rotm2tform(rotz(rad2deg(dh_params(2,3)))) * trvec2tform([dh_params(2,2), 0, 0]) * rotm2tform(rotx(rad2deg(dh_params(2,4))));
T23 = trvec2tform([0, 0, dh_params(3,1)]) * rotm2tform(rotz(rad2deg(dh_params(3,3)))) * trvec2tform([dh_params(3,2), 0, 0]) * rotm2tform(rotx(rad2deg(dh_params(3,4))));
T34 = trvec2tform([0, 0, dh_params(4,1)]) * rotm2tform(rotz(rad2deg(dh_params(4,3)))) * trvec2tform([dh_params(4,2), 0, 0]) * rotm2tform(rotx(rad2deg(dh_params(4,4))));
T45 = trvec2tform([0, 0, dh_params(5,1)]) * rotm2tform(rotz(rad2deg(dh_params(5,3)))) * trvec2tform([dh_params(5,2), 0, 0]) * rotm2tform(rotx(rad2deg(dh_params(5,4))));
T56 = trvec2tform([0, 0, dh_params(6,1)]) * rotm2tform(rotz(rad2deg(dh_params(6,3)))) * trvec2tform([dh_params(6,2), 0, 0]) * rotm2tform(rotx(rad2deg(dh_params(6,4))));

T46 = T45*T56;
T36 = T34*T46;
T26 = T23*T36;
T16 = T12*T26;
T06 = T01*T16;

%%estrazione dei dati dalle matrici di trasformazione

%T56
TRASL56 = tform2trvec(T56);
ROT56 = tform2rotm(T56);
RPY56 = rotm2eul(R56, 'XYZ');
AXANG56 = rotm2axang(R56);

%T46
TRASL46 = tform2trvec(T46);
ROT46 = tform2rotm(T46);
RPY46 = rotm2eul(R46, 'XYZ');
AXANG46 = rotm2axang(R46);

%T36
TRASL36 = tform2trvec(T36);
ROT36 = tform2rotm(T36);
RPY36 = rotm2eul(R36, 'XYZ');
AXANG36 = rotm2axang(R36);

%T26
TRASL26 = tform2trvec(T26);
ROT26 = tform2rotm(T26);
RPY26 = rotm2eul(R26, 'XYZ');
AXANG26 = rotm2axang(R26);

%T16
TRASL16 = tform2trvec(T16);
ROT16 = tform2rotm(T16);
RPY16 = rotm2eul(R16, 'XYZ');
AXANG16 = rotm2axang(R16);

%T06
TRASL06 = tform2trvec(T06);
ROT06 = tform2rotm(T06);
RPY06 = rotm2eul(R06, 'XYZ');
AXANG06 = rotm2axang(R06);

















