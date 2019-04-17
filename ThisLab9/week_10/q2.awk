BEGIN{
startTime=400.0; # random large value
stopTime=0.0;
recvdSize=0.0;
sent=0;
recv=0;
}

{
action = $1;
time = $2;
from = $3;
to = $4;

  if(from==1 && to==2 && action == "+") {
    if(time < startTime) {
      startTime = time;
    }
  }
  
  if(from==1 && to==2 && action == "r") {
    if(time > stopTime) {
      stopTime = time;
    }
    recvdSize++;
  }

  if(from == 0 && action == "+") {
    sent++;
  }

  if(to == 2 && action == "r") {
    recv++;
  }
}
END{
throughput = (recvdSize / (stopTime - startTime)) * (8/1000);
loss = (sent - recv) / sent;
print rate, throughput >> "throughput.dat"
print rate, loss >> "loss.dat"
} 
