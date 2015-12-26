% Channel ID to read data from
readChannelID = 71223;
readkey = 'L5WC4RZ6WCM9GK4T';
% Temperature Field ID
TimeID = 1;

[data, time] = thingSpeakRead(readChannelID, 'Fields', TimeID,'ReadKey',readkey,'NumPoints',100);
% disp(data)
NUM = length(data);
% [data2, time] =thingSpeakRead(readChannelID, 'Fields', TimeID,'ReadKey',readkey,'NumPoints',NUM);
histogram(data);
xlabel('Time');
ylabel('Number of Times Fed');
title({['Your Feeding Habits: ','You have fed your fish ',num2str(NUM),' times'];...
['You last fed your fish at around ',num2str(data(end)),':00']});
axis tight
grid on
