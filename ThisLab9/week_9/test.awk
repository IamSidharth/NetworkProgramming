BEGIN{
tcpstartTime=400.0; # random large value
tcpstopTime=0.0;
udpstartTime=400.0; # random large value
udpstopTime=0.0;
tcprecvdSize=0.0;
udprecvdSize=0.0;
}

{
action = $1;
time = $2;
from = $3;
to = $4;
type = $5;

  if(from==2 && to==3 && action == "+" && type=="tcp"){
    if(time < tcpstartTime) {
      tcpstartTime = time;
    }
  }
  
  if(from==2 && to==3 && action == "r" && type=="tcp"){
    if(time > tcpstopTime) {
      tcpstopTime = time;
    }
    tcprecvdSize++;
  }
  
  if(from==2 && to==3 && action == "+" && type=="cbr"){
    if(time < udpstartTime) {
      udpstartTime = time;
    }
  }
  
  if(from==2 && to==3 && action == "r" && type=="cbr"){
    if(time > udpstopTime) {
      udpstopTime = time;
    }
    udprecvdSize++;
  }

}
END{
  printf("TCP Average Throughput[kbps] = %.2f\n",
       (tcprecvdSize/(tcpstopTime - tcpstartTime))*(8/1000.0));
  
  printf("UDP Average Throughput[kbps] = %.2f\n",
       (udprecvdSize/(udpstopTime - startTime))*(8/1000.0));
}
