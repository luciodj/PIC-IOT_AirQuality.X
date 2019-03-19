% MQ135 correlation helper v0.1
% 
% copyright (c) Davide Gironi, 2013
% 
% Released under GPLv3.
% Please refer to LICENSE file for licensing information.

% correlate raw data from mq135 sensor to get the fitting curve for the 
% gas we are investigating

rawdataname = 'out_raw.xls'; %raw data from mq135 sensor
condataname = 'out_co2.xls'; %co2ppm data from mhz14 sensor

sensor_pullupresistor = 22000; %ohm, resistor attached to the sensor

a_ds = 116.6020682; %datasheed scaling factor
b_ds = -2.769034857; %datasheet exponent
Ro_ds = 41763; %estimated ro by datasheet curve 

%load raw data
rawdata = xlsread(rawdataname);
%load con data
condata = xlsread(condataname);

%estimate the read resistance
rawdata_res = (1024*sensor_pullupresistor)./rawdata-sensor_pullupresistor;

if ~isequal(size(rawdata), size(condata))
    display('rawdata and condata has to be the same size.');
    break;
end

ws = warning('off','all');%turn off warning

%linear regression correlation
p = polyfit(rawdata_res, condata, 1);
corr_condatalin = p(1)*rawdata_res + p(2);
p

%imposed Ro
Ro = 41000
rawdata_resro = rawdata_res./Ro;

%power regression correlation
c = polyfit(log(rawdata_resro),log(condata),1);
a = exp(c(2));
b = c(1);
corr_condatapow = a * (rawdata_res./Ro).^ b;
a
b

%datasheet calcultion
ds_condatapow = a_ds * (rawdata_res./Ro_ds).^ b_ds;


%329ppm resistance
res392ppm = (1024*sensor_pullupresistor)./473-sensor_pullupresistor;
corr_condatapow_ppmvalue  = a * (res392ppm./Ro).^ b;
corr_condatapow_ppmvalue


warning(ws) %turn it back on.
 
%plot
x = 1:size(rawdata);
plot(x,rawdata,'-',x,condata,'-',x,corr_condatalin,'-',x,corr_condatapow,'-',x,ds_condatapow);
legend('raw data','reference data','polyfit 3 correlated data','power reg correlated data', 'datasheet curve data',5);
