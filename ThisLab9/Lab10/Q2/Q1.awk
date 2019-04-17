
BEGIN {
fsDrops = 0;
numFs = 0;
totalData = 0;
startTime=0;
stopTime=0;
}
{
action = $1;
time = $2;
from = $3;
to = $4;
type = $5;
pktsize = $6;
flow_id = $8;
src = $9;
dst = $10;
seq_no = $11;
packet_id = $12;
if(action == "+"){

if(startTime>time) {
startTime = time;
}
numFs++;}
if(action == "r"){
stopTime = time;
recvdSize+=$6;
}
if(action == "d"){
lossData+=$6
}
}
END {
printf("received size: %d", recvdSize);
printf("loss size: %d", lossData);
printf("Average Throughput[kbps] = %.2f",(recvdSize/(stopTime-startTime))*(8/1000));

}
