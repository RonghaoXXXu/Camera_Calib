% Intrinsic and Extrinsic Camera Parameters
%
% This script file can be directly executed under Matlab to recover the camera intrinsic and extrinsic parameters.
% IMPORTANT: This file contains neither the structure of the calibration objects nor the image coordinates of the calibration points.
%            All those complementary variables are saved in the complete matlab data file Calib_Results.mat.
% For more information regarding the calibration model visit http://www.vision.caltech.edu/bouguetj/calib_doc/


%-- Focal length:
fc = [ 1148.775245636960790 ; 1140.921418476898452 ];

%-- Principal point:
cc = [ 722.426524588206235 ; 542.958500299952675 ];

%-- Skew coefficient:
alpha_c = 0.000000000000000;

%-- Distortion coefficients:
kc = [ 0.205151106407555 ; -1.004807625268344 ; -0.002331808520362 ; -0.000857781090025 ; 0.000000000000000 ];

%-- Focal length uncertainty:
fc_error = [ 5.943369306184847 ; 4.828870780381203 ];

%-- Principal point uncertainty:
cc_error = [ 4.920205036324528 ; 7.247447990521213 ];

%-- Skew coefficient uncertainty:
alpha_c_error = 0.000000000000000;

%-- Distortion coefficients uncertainty:
kc_error = [ 0.016813641030493 ; 0.111993009827549 ; 0.001877876316454 ; 0.001707504112458 ; 0.000000000000000 ];

%-- Image size:
nx = 1440;
ny = 1080;


%-- Various other variables (may be ignored if you do not use the Matlab Calibration Toolbox):
%-- Those variables are used to control which intrinsic parameters should be optimized

n_ima = 9;						% Number of calibration images
est_fc = [ 1 ; 1 ];					% Estimation indicator of the two focal variables
est_aspect_ratio = 1;				% Estimation indicator of the aspect ratio fc(2)/fc(1)
center_optim = 1;					% Estimation indicator of the principal point
est_alpha = 0;						% Estimation indicator of the skew coefficient
est_dist = [ 1 ; 1 ; 1 ; 1 ; 0 ];	% Estimation indicator of the distortion coefficients


%-- Extrinsic parameters:
%-- The rotation (omc_kk) and the translation (Tc_kk) vectors for every calibration image and their uncertainties

%-- Image #1:
omc_1 = [ 2.671676e-01 ; 2.618182e+00 ; 4.498580e-01 ];
Tc_1  = [ 5.235553e+01 ; -1.643603e+02 ; 5.697105e+02 ];
omc_error_1 = [ 2.007103e-03 ; 5.863289e-03 ; 7.376244e-03 ];
Tc_error_1  = [ 2.483623e+00 ; 3.678745e+00 ; 2.409895e+00 ];

%-- Image #2:
omc_2 = [ 2.156589e-01 ; 2.465926e+00 ; 6.793238e-01 ];
Tc_2  = [ 8.189077e+01 ; -2.088584e+02 ; 7.856332e+02 ];
omc_error_2 = [ 2.701889e-03 ; 5.656916e-03 ; 6.706555e-03 ];
Tc_error_2  = [ 3.420920e+00 ; 5.123564e+00 ; 3.549636e+00 ];

%-- Image #3:
omc_3 = [ 3.562792e-01 ; 2.308677e+00 ; 6.586766e-01 ];
Tc_3  = [ 5.813664e+01 ; -1.790996e+02 ; 6.859751e+02 ];
omc_error_3 = [ 3.043891e-03 ; 5.350926e-03 ; 6.668151e-03 ];
Tc_error_3  = [ 2.981005e+00 ; 4.413464e+00 ; 2.901013e+00 ];

%-- Image #4:
omc_4 = [ 9.264381e-02 ; -2.713005e+00 ; -1.157287e+00 ];
Tc_4  = [ 7.523989e+01 ; -9.439259e+01 ; 3.790745e+02 ];
omc_error_4 = [ 2.520637e-03 ; 4.539206e-03 ; 6.816437e-03 ];
Tc_error_4  = [ 1.655107e+00 ; 2.566158e+00 ; 2.164971e+00 ];

%-- Image #5:
omc_5 = [ 9.110970e-02 ; 2.743502e+00 ; 8.814154e-01 ];
Tc_5  = [ 1.311179e+02 ; -1.103666e+02 ; 5.404383e+02 ];
omc_error_5 = [ 2.153110e-03 ; 5.353233e-03 ; 6.740265e-03 ];
Tc_error_5  = [ 2.332106e+00 ; 3.593236e+00 ; 2.823540e+00 ];

%-- Image #6:
omc_6 = [ 3.660520e-02 ; 2.591682e+00 ; 1.004864e+00 ];
Tc_6  = [ 1.214208e+02 ; -3.708470e+01 ; 5.344421e+02 ];
omc_error_6 = [ 2.786500e-03 ; 5.602072e-03 ; 6.478208e-03 ];
Tc_error_6  = [ 2.290198e+00 ; 3.450990e+00 ; 2.642894e+00 ];

%-- Image #7:
omc_7 = [ 7.607304e-02 ; 2.541902e+00 ; 3.672538e-01 ];
Tc_7  = [ 2.153643e+02 ; -8.417178e+01 ; 1.289418e+03 ];
omc_error_7 = [ 3.119404e-03 ; 6.135382e-03 ; 7.451246e-03 ];
Tc_error_7  = [ 5.601959e+00 ; 8.225059e+00 ; 5.903704e+00 ];

%-- Image #8:
omc_8 = [ 6.711786e-02 ; 2.970718e+00 ; 5.446925e-01 ];
Tc_8  = [ 1.053080e+02 ; -8.330118e+01 ; 3.463052e+02 ];
omc_error_8 = [ 1.239803e-03 ; 4.710080e-03 ; 6.444259e-03 ];
Tc_error_8  = [ 1.500077e+00 ; 2.335891e+00 ; 1.968668e+00 ];

%-- Image #9:
omc_9 = [ -2.554906e-02 ; 2.398155e+00 ; 3.354376e-01 ];
Tc_9  = [ 2.085621e+02 ; 3.228197e+01 ; 1.274047e+03 ];
omc_error_9 = [ 3.627761e-03 ; 5.964314e-03 ; 6.733598e-03 ];
Tc_error_9  = [ 5.563508e+00 ; 8.116400e+00 ; 5.453245e+00 ];

